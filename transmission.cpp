#include "transmission.h"
#include <QThread>
#include <QObject>
#include <windows.h>
#include "dialog.h"
DataThread::DataThread(struct sockinfo* info,int flag,unsigned char *_strdata, int _datalen,QDialog *parent) : QThread(parent)
{
//    this->mSocket=mSocket;
    int BUFFSIZE=1024;
    _strdata= (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    this->mSocket=info->clientsocket;
    this->flag=flag;
    this->_strdata=_strdata;
    this->datalen=_datalen;
}

void DataThread::run()
{

        if((flag == 1)||(flag == 2)||(flag == 3))//flag=1,传送GY数据
        {
            char sendbuff[1000];
            int deallen=0;
            int size=1000;
            int count=datalen/1000;
            int sendbyte=0;
//            qDebug() << datalen;
            //在首行首字节处添加标识符

            //将数据每1000字节发送，最后一包不足1000字节补齐
            while(deallen <= datalen)
            {
                if((deallen+size)< datalen)
                {
                        for(int i=0;i<=count;i++)
                        {
                            for(int j=0;j<1000;j++)
                            {
                                sendbuff[j]=_strdata[j+i*size];
                            }
                            int ret=send(mSocket,sendbuff,strlen(sendbuff),0);
                             deallen=deallen+1000;
                            if(ret==SOCKET_ERROR)
                            {
                                emit isClose();
                                qDebug()<<"send error";
                            }
                            else
                            {
                                sendbyte=sendbyte+ret;
                                qDebug()<<"send success";
                            }
                        }
                }
                else
                {
                    for(int i=0;i<1000;i++)
                    {
                        if(i+deallen<datalen)
                        {
                            sendbuff[i]=_strdata[i+deallen];
                        }
                        else
                        {
                            sendbuff[i]=0xFF;
                        }

                    }
                    int ret=send(mSocket,sendbuff,strlen(sendbuff),0);
                    if(ret==SOCKET_ERROR)
                    {
                        emit isClose();
                    }
                    else
                    {
                        sendbyte=sendbyte+ret;
                    }
                }
            }
            emit sended(sendbyte);
            closesocket(mSocket);
        }
        if(flag=4)//flag=4,传送其他数据
        {

        }

}
