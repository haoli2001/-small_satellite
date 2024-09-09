#include "network2.h"
#include "mainwindow.h"
#include "SocketConstant.h"
#include <QDateTime>
#include <QTextCodec>
#include <errno.h>
#include <thread>
#include <sys/time.h>
#include <QTextCodec>

Network2::Network2(CCycleBuffer *buffer2, QReadWriteLock *writelock, bool *isConnected, QString IP, quint16 PORT, QString SavePath, Gdata * pData, QObject *parent) :
    QThread(parent), isConnected(isConnected), buffer2(buffer2), writelock(writelock)
{
    this->ip = IP;
    this->port = PORT;
    this->savepath = SavePath;
    this->pData = pData;
    buffer = NULL;
}

bool Network2::Connect()
{
    //qDebug()<<"connect2"<<QThread::currentThread();
    //winsock 初始化
    if(WSAStartup(MAKEWORD(2,2),&mWasData) != 0)
    {
        MainWindow::fakeUi->setLinetext("通道 2 : Failed to load Winsock\n");
        m_mutex.lock();
        *isConnected = false;
        m_mutex.unlock();
        return false;
    }
    //默认阻塞
    mSocket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(mSocket == INVALID_SOCKET)
    {
        MainWindow::fakeUi->setLinetext(QString("通道 2 : socket create failed\n"));
        m_mutex.lock();
        *isConnected = false;
        m_mutex.unlock();
        return false;
    }

    QByteArray ip_m =ip.toLatin1();
    SOCKADDR_IN addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons((u_short)port);
    addr.sin_addr.S_un.S_addr = inet_addr(ip_m);//点分十进制转ip地址
    int val = ::connect(mSocket,(SOCKADDR*)&addr,sizeof(addr));
    int error;
    if( val == SOCKET_ERROR)
    {
        MainWindow::fakeUi->setLinetext(QString("通道 2 连接失败！！！\n"));
        error = WSAGetLastError();
        MainWindow::fakeUi->setLinetext(QString("error: %1 \n").arg(error));
        OnCloseSocket();
        return false;
    }
    MainWindow::fakeUi->setLinetext(QString("通道 2 连接成功\n"));
    m_mutex.lock();
    *isConnected = true;
    m_mutex.unlock();
    emit connectSucSig();
    return true;
}

void Network2::run()
{
   /* ********** 发送 ********** */
    //int send[TCP_Length/sizeof(int)] = {0};
    int NetTimeout_send = 300000;//20秒->300

    ::setsockopt(mSocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&NetTimeout_send,sizeof(int));

//    send[0] = TCP_START;
//    send[1] = TCP_Length;
//    send[2] = TCP_StreamID;
//    send[3] = TCP_Channel_I;
//    send[4] = TCP_Request;
//    send[8] = 0;        //block
//    send[31] = TCP_END;

//    for(int i = 0; i < 32; i++)
//    {
//        send[i] = htonl(send[i]);
//    }
//    while(true)
//    {
//                char sendBuf[1024] = "from Client:   hello service.";
////        //发送
////        if(::send(mSocket, (const char*)send, sizeof (send),0) < 0)
////        {
////            MainWindow::fakeUi->setLinetext("通道 2 发送失败\n");
////            OnCloseSocket();
////            return;
////        }
////        else
////        {
////            MainWindow::fakeUi->setLinetext("通道 2 请求发送完毕\n");
////            break;
////        }
//        if(::send(mSocket, sendBuf, strlen(sendBuf), 0) < 0)
//        {
//            MainWindow::fakeUi->setLinetext("通道 2 发送失败\n");
//            OnCloseSocket();
//            return;
//        }
//        else
//        {
//            MainWindow::fakeUi->setLinetext("通道 2 请求发送完毕\n");
//            break;
//        }
//    }

    /* ********** 接收 ********** */
    long long sendSize = BUFFERSIZE;
    long long recSize;
    long long num = 0;
    long long RecAllLen = 0;
    long long GB = 1024 * 1024 *1024;

    //写入
    FILE     *fpOut;


    QString  out_path;
    int      wirtecout = 0; //写2GB数据的大小
    QTextCodec *textCodec = QTextCodec::codecForName("gb18030");
    if (textCodec == NULL)
    {
        MainWindow::fakeUi->setLinetext("通道 1 接收文件打开失败！");
        return;
    }
    out_path = textCodec->fromUnicode(savepath).data();

    int NetTimeout_recv = 30000;//30秒
    ::setsockopt(mSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&NetTimeout_recv,sizeof(int));

    int nRecvBuf=256 * 1024 *1024;//接收缓冲区设置为256M
    ::setsockopt(mSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));

    buffer = (unsigned char*)malloc(sizeof(unsigned char) * BUFFERSIZE);
    assert(buffer != 0);

    //接收
    int errorCode = WSAGetLastError();
    //连接超时
    if( errorCode == WSAECONNABORTED)
    {
        MainWindow::fakeUi->setLinetext("通道 2 连接超时, 尝试断开重连...\n");
        OnCloseSocket();
        Connect();
        return;
    }

#if clocktest
    struct timeval ta, tb;
    double mseca, msecb;
    gettimeofday(&ta, NULL);
    mseca = ta.tv_sec*1000000.0 + ta.tv_usec;
#endif

    out_path = out_path.left(out_path.length() - 4);
    fpOut = fopen((out_path+ QString("_") + QString().setNum(wirtecout) + QString(".dat")).toStdString().c_str(), "ab");
    while(true)
    {
//        pData->sem1->acquire(); // -1 //l 信号量好像没什么用，没有往同一个缓冲区里写数据

        unsigned char *buf = buffer;
        sendSize = BUFFERSIZE;
        long long writelen = 0;
        long long recSizes = 0;
        bool temp = false;

        while(true)
        {
            //等待服务端回应
            recSize = ::recv(mSocket, (char*)buf, sendSize, 0);

            //qDebug()<<"1111";

            recSizes += recSize;

            if( recSizes >0 )
            {
                if(recSizes == recSize && recSizes < sendSize) //recSizes < BUFFERSIZE
                {
                    num++;
                    sendSize = recSizes;
                    break;
                }
                else if(recSizes == BUFFERSIZE)
                {
                    num++;
                    sendSize = BUFFERSIZE;
                    break;
                }
                else
                {
                    buf = buf + recSize;
                    sendSize = sendSize - recSize;
                }
            }
            else
            {
                if((recSize<0) &&(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)) //这几种错误码， 认为连接是正常的，继续接收
                {
                    continue;//继续接收数据
                }
                MainWindow::fakeUi->setLinetext(QString("解调器关闭, 通道 2 接收数据帧完毕, 共计 %1 Bytes\n").arg(RecAllLen + recSizes));
                over = true;
                break;//跳出接收循环
            }
        }

        //qDebug()<<"22222";

        struct Data data;
        memcpy(&data, buffer, sizeof(data));

        data.list[4] = ntohl(data.list[4]);

        if(data.list[4] == TCP_END)
        {
            int error = data.list[3];
            QString recERROR;
            switch (error)
            {
            case 0:  recERROR = "正确";
                break;
            case 1:  recERROR = "错误语法";
                break;
            case 2:  recERROR = "DPU未装好";
                break;
            case 3-5:  recERROR = "xx";
                break;
            case 6:  recERROR = "实时数据传输授权码不可用";
                break;
            case 7:  recERROR = "配置模式激活";
                break;
            default: recERROR = "未知错误";
                break;
            }
            MainWindow::fakeUi->setLinetext(QString("通道1：解调器发出错误 【%1】 \n").arg(recERROR));
            MainWindow::fakeUi->setLinetext(QString("请重新连接\n"));
            break;
        }

        //qDebug()<<"33333";

        writelen = 0;
        while(writelen < recSizes)
        {
            m_mutex.lock();
            bool errortemp =  decoderERROR;
            temp = autoexit;
            m_mutex.unlock();
            if(temp || errortemp)
                break;
            writelock->lockForWrite();
            int len = buffer2->write(buffer + writelen, recSizes - writelen);
            writelock->unlock();
            if(len < recSizes - writelen)
                Sleep(30);
            writelen += len;
        }

        RecAllLen += recSizes;

        fwrite(buffer, recSizes, 1, fpOut);

        //qDebug()<<"44444";
        if(recSizes >= BUFFERSIZE)
        {
            if((RecAllLen / (GB * 2)) > 0 && (RecAllLen % (GB * 2)) == 0)
                wirtecout++;
            fclose(fpOut);
            fpOut = NULL;
            fpOut = fopen((out_path+ QString("_") + QString().setNum(wirtecout) + QString(".dat")).toStdString().c_str(), "ab");
        }

        //msleep(30);
        pData->sem2->release(); // +1
        //qDebug()<<"55555";
        if(over || temp)
        {
#if clocktest
            gettimeofday(&tb, NULL);
            msecb = tb.tv_sec*1000000.0 + tb.tv_usec;
            msecb -= mseca;
            qDebug("recv2: Total time is %.10f us.\n", msecb);
            qDebug("recv2: %lld bytes\n", RecAllLen); //乘1000，000因为msecb为us
            qDebug("recv2: %f MB/s\n", (RecAllLen * 1000000) / (msecb * 1024 * 1024)); //乘1000，000因为msecb为us
#endif
            break;
        }
    }
    fclose(fpOut);
    //qDebug()<<"6666";
    fpOut = NULL;
    free(buffer);
    buffer = NULL;
    OnCloseSocket();
    return;
}

void Network2::OnCloseSocket()
{
    //如果要已经处于连接状态的soket在调用closesocket后强制关闭，不经历TIME_WAIT的过程：
    BOOL bDontLinger = FALSE;
    ::setsockopt(mSocket,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(BOOL));
    ::closesocket(mSocket);
    ::WSACleanup();
    m_mutex.lock();
    *isConnected = false;
    m_mutex.unlock();
    MainWindow::fakeUi->setLinetext(QString("通道 2 已关闭\n"));
    return;
}





