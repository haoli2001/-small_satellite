#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"

#include<cerrno>
MainWindow *MainWindow::fakeUi = nullptr;
char outputpathLog[fileNameLen];  //输出日志路径

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), isConnected1(false), isConnected2(false),isConnected(false)
{
    ui->setupUi(this);
    fakeUi = this;
    
    //初始化
    WSAStartup(MAKEWORD(2,2),&mWasData);
    setWindowTitle("CASE_Decoder");//界面命名，设置窗口标题

    //+ 单核 实时核
    decoder = NULL;
    network1 = NULL;
    network2 = NULL;
    buffer1 = NULL;
    buffer2 = NULL;
    pGdata = NULL;
    lock1 = NULL;
    lock2 = NULL;

    pGdata = new Gdata;
    lock1 = new QReadWriteLock;
    lock2 = new QReadWriteLock;

    ui->pushButton_pause->setEnabled(false); //暂停按钮初始不可用

    //界面连接函数
    connect(ui->pushButton_run, SIGNAL(clicked()), this, SLOT(on_Run()));   //解压缩按钮  双
    connect(ui->pushButton_runsingle,SIGNAL(clicked()), this, SLOT(on_Runsin()));   //解压缩 单

    //实时接收双通道
    connect(ui->pushButton_channel, SIGNAL(clicked()), this, SLOT(on_openChannel()));
    connect(ui->pushButton_singlechannel, SIGNAL(clicked()), this, SLOT(on_openSinChannel()));



    
}

MainWindow::~MainWindow()
{
    //+ socket

    //winsock
    WSACleanup();
    delete ui;
}

void MainWindow::setLinetext(QString text)
{
    m_mutex.lock();
    ui->listWidget->addItem(text);
    m_mutex.unlock();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //解压缩
    if(decoder!= NULL)
    {
        if(isRUNNING_DECODER)
        {
            isRUNNING_DECODER = false;
             if(isPaused)
                 on_pushButton_pause_clicked();
            decoder->wait();//connect delete
        }
        else
        {
            decoder->terminate();
            decoder->deleteLater();
        }
    }
//    //实时解压缩
    if(RT_decoder != NULL)//连接是否关闭
    {
        if(RT_decoder->isRunning())
        {
            if(!RT_decoder->GetIsOver())
            {
                RT_decoder->isfailed = true;
                RT_decoder->wait();//connect delete
            }
            else
            {
                RT_decoder->terminate();
                RT_decoder->deleteLater();
                RT_decoder = NULL;
            }

            if(!network1->GetIsOver() || !network2->GetIsOver())
            {
                network1->autoexit = true;
                network2->autoexit = true;
                network1->wait();//connect delete
                network2->wait();//connect delete
            }
            else
            {
                network1->terminate();
                network1->deleteLater();
                network1 = NULL;
                network2->terminate();
                network2->deleteLater();
                network2 = NULL;
            }
        }
    }
    if(RT_decodersin != NULL)//单通道连接是否关闭
    {
        if(RT_decodersin->isRunning())
        {
            if(!RT_decodersin->GetIsOver())
            {
                RT_decodersin->isfailed = true;
                RT_decodersin->wait();//connect delete
            }
            else
            {
                RT_decodersin->terminate();
                RT_decodersin->deleteLater();
                RT_decodersin = NULL;
            }

            if(!networksin->GetIsOver())
            {
                networksin->autoexit = true;
                networksin->wait();//connect delete
            }
            else
            {
                networksin->terminate();
                networksin->deleteLater();
                networksin = NULL;
            }
        }
    }
    if(buffer1 != NULL)
        delete buffer1;
    if(buffer2 != NULL)
        delete buffer2;

    if(pGdata != NULL)
        delete pGdata;

    if(lock1 != NULL)
        delete lock1;
    if(lock2 != NULL)
        delete lock2;
}

void MainWindow::on_Run()
{
    if(isRUNNING_DECODER)
    {
        QMessageBox::warning(this, "CASE_DECODER 2.0", "上一次AOS帧解压缩任务还在进行，请等待结束");
        return;
    }

    if(!ui->lineEdit_SavePath->text().isEmpty() && m_savepath.isEmpty())
    {
        m_savepath = ui->lineEdit_singlechannel->text();
        m_savepath = m_savepath.replace("/", "\\");
    }

    ui->pushButton_pause->setEnabled(true);


    if(m_ch1.isEmpty()||m_ch2.isEmpty()||m_savepath.isEmpty())
    {
        QMessageBox::warning(this, "CASE_Decoder", "还未填写输入输出地址");
        return;
    }

    //        ui->listWidget->clear();
    slist.clear();
    //        ilist.clear();

    //列表添加元素
    slist << m_ch1 << m_ch2 << m_savepath;

    decoder = new CASE_Decoder(&isRUNNING_DECODER, this);

    connect(this, &MainWindow::runParaSig, decoder, &CASE_Decoder::OnRunPara);//主界面发送runParaSig信号，主函数读取参数
    connect(decoder, &CASE_Decoder::stateSig, this, &MainWindow::showBox);//主函数发送stateSig信号给主界面，将状态显示在状态信息窗口
    connect(this, &MainWindow::sended, decoder, &CASE_Decoder::cyclestart);//主线程发送结束之后，将sended置为true传递给case_decoder

    connect(decoder, &CASE_Decoder::endSig, this, &MainWindow::infoBox);//主函数发送endSig，主界面

    //连接转发快视相关的信号槽
    /***************************************************************************************/
    connect(decoder,&CASE_Decoder::newimageready,this,&MainWindow::senddata);  //发送连接槽
    connect(decoder,&CASE_Decoder::imageready,this,&MainWindow::dealimagedata);//处理数据连接槽
   /*********************************************************************************************/
    //..........//
    connect(decoder, &CASE_Decoder::finished, [=]() mutable
    {
        ui->listWidget->addItem("本次解压缩任务完成！\n");
        //*
        if(decoder->isRunning())
            decoder->terminate();
        decoder->deleteLater();
        decoder = NULL;
    });

    connect(this, &MainWindow::pauseSig, [=](bool ispause) mutable //暂停信号
    {
        if(ispause == true)
        {
            if(!decoder->GetisDealing())
                decoder->m_mutex.lock();

        }
        else
        {
            if(!decoder->GetisDealing())
                decoder->m_mutex.unlock();

        }
    });


    //emit runParaSig(slist, ilist,vcid,select_vcid_list);
    emit runParaSig(slist);
    decoder->start();
}
//单通道解包
void MainWindow::on_Runsin()
{
    if(isRUNNING_DECODER)
    {
        QMessageBox::warning(this, "CASE_SID", "上一次AOS帧解压缩任务还在进行，请等待结束");
        return;
    }

    if(!ui->lineEdit_SavePath->text().isEmpty() && m_savepath.isEmpty())
    {
        m_savepath = ui->lineEdit_singlechannel->text();
        m_savepath = m_savepath.replace("/", "\\");
    }

    ui->pushButton_pause->setEnabled(true);


    if(m_chsin.isEmpty()||m_savepath.isEmpty())
    {
        QMessageBox::warning(this, "CASE_Decoder", "还未填写输入输出地址");
        return;
    }

    //        ui->listWidget->clear();
    slist.clear();
    //        ilist.clear();

    //列表添加元素
    slist << m_chsin << m_savepath;

    sindecoder = new CASE_SinDecoder(&isRUNNING_DECODER, this);

    connect(this, &MainWindow::runParaSig, sindecoder, &CASE_SinDecoder::OnRunPara);//主界面发送runParaSig信号，主函数读取参数
    connect(sindecoder, &CASE_SinDecoder::stateSig, this, &MainWindow::showBox);//主函数发送stateSig信号给主界面，将状态显示在状态信息窗口
    connect(this, &MainWindow::sended, sindecoder, &CASE_SinDecoder::cyclestart);


    connect(sindecoder, &CASE_SinDecoder::endSig, this, &MainWindow::infoBox);//主函数发送endSig，主界面
    /***********************************************************************************************/
    /****************************连接decoder解出来的数据与Mainwindow的发送数据槽****************************/

    connect(sindecoder,&CASE_SinDecoder::newimageready,this,&MainWindow::senddata);  //发送连接槽
    /***********************************************************************************************/

    connect(sindecoder, &CASE_SinDecoder::finished, [=]() mutable
    {
        ui->listWidget->addItem("本次解压缩任务完成！\n");
        //*
        if(sindecoder->isRunning())
            sindecoder->terminate();
        sindecoder->deleteLater();
        sindecoder = NULL;
    });

    connect(this, &MainWindow::pauseSig, [=](bool ispause) mutable //暂停信号
    {
        if(ispause == true)
        {
            if(!sindecoder->GetisDealing())
                sindecoder->m_mutex.lock();

        }
        else
        {
            if(!sindecoder->GetisDealing())
                sindecoder->m_mutex.unlock();

        }
    });


    //emit runParaSig(slist, ilist,vcid,select_vcid_list);
    emit runParaSig(slist);
    sindecoder->start();
}

//打开通道一文件
void MainWindow::on_pushButton_OpenCH1_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "打开通道1文件", "./", "*.dat");
    ui->lineEdit_CH1->setText(filename);
    m_ch1 = filename.replace("/", "\\");


}
//打开通道二文件
void MainWindow::on_pushButton_OpenCH2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "打开通道2文件", "./", "*.dat");
    ui->lineEdit_CH2->setText(filename);
    m_ch2 = filename.replace("/", "\\");
}

void MainWindow::on_pushButton_pause_clicked()
{
    static bool ispaused;
    if(ui->pushButton_pause->text() == QString("暂停"))
    {
        ispaused = true;
        emit pauseSig(ispaused);
    }
    else
    {
        ispaused = false;
        emit pauseSig(ispaused);
    }
}

void MainWindow::showBox(QString title, QString text)
{
    QMessageBox::information(this, title, text);
    ui->listWidget->addItem(text);
}

void MainWindow::infoBox(QString title, QString text)
{
    QMessageBox::information(this, title, text, QMessageBox::Ok);
}

void MainWindow::on_pushButton_SavePath_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "保存路径", "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_SavePath->setText(path);
    m_savepath = path.replace("/", "\\");
}
//打开单通道文件
void MainWindow::on_pushButton_OpenSingleCH_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "打开单通道文件", "./", "*.dat");
    ui->lineEdit_singlechannel->setText(filename);
    m_chsin = filename.replace("/", "\\");
}
//2024.6.19 双通道实时解压缩功能
void MainWindow::on_openChannel()
{
    ui->pushButton_pause->setEnabled(false);

    if(ui->lineEdit_SavePath->text().isEmpty())
    {
        QMessageBox::warning(this, "CASE_DECODER 2.0", "请先填写实时解压缩保存地址", QMessageBox::Ok);
        return;
    }
    if (isConnected1 == true)
    {
        QMessageBox::warning(this, "警告", "通道 1 已连接，请勿重复连接！", QMessageBox::Ok);
    }
    if (isConnected2 == true)
    {
        QMessageBox::warning(this, "警告", "通道 2 已连接，请勿重复连接！", QMessageBox::Ok);
        return;
    }

    QString recpath, outfile1, outfile2;
    bool sended = false;
    ConnectDialog *connectdialog = new ConnectDialog(&IPaddress1, &port1, &IPaddress2, &port2, &recpath, &sended);

    //判断连接对话框执行与否，对话框退出执行break，跳出循环执行下面语句
    while (true)
    {
        if (QDialog::Accepted == connectdialog->exec())
            break;
    }

    delete connectdialog;

    //判断是否点击了连接发送请求的按钮
    if(!sended)
        return;

    ui->listWidget->clear();

    /*************************统一时间————文件名*************************/
    QString data_time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
    recpath.replace("/", "\\");
    //通道1,2的文件名
    if(recpath.endsWith("\\"))
    {
        outfile1 = recpath + QString("Channel1-") + data_time + ".dat";
        outfile2 = recpath + QString("Channel2-") + data_time + ".dat";
    }
    else
    {
        outfile1 = recpath + "\\" + QString("Channel1-") + data_time + ".dat";
        outfile2 = recpath + "\\" + QString("Channel2-") + data_time + ".dat";
    }

    /*************************解压缩核*************************/
    m_savepath = ui->lineEdit_SavePath->text();
    m_savepath = m_savepath.replace("/", "\\");
    //创建缓冲区
    buffer1 = new CCycleBuffer(BUFFERSIZE * 8);
    buffer2 = new CCycleBuffer(BUFFERSIZE * 8);

    //如果连接的话实时解压缩开启
    RT_decoder = new RealtimeDecoder(buffer1, buffer2, lock1, lock2);
    RT_decoder->OnRunPara(m_savepath);  //读参数

    /************ 双线程接收通道数据 ************/
    network1 = new Network1(buffer1, lock1, &isConnected1, IPaddress1, port1, outfile1, pGdata);
    network2 = new Network2(buffer2, lock2, &isConnected2, IPaddress2, port2, outfile2, pGdata);

    if(!network1->Connect()||!network2->Connect())
    {
        QMessageBox::information(this, "Error", "请检查网络连接！");
        return;
    }
    else
    {
        ui->label_channelopen->setStyleSheet("color:orange;");
        network1->start();  //这里start有什么用
        network2->start();
        RT_decoder->start();
    }

    //y
    connect(network1, &Network1::finished, [=]() mutable
    {
        if(!network1->decoderERROR && RT_decoder != NULL)
            RT_decoder->Onend1Slot();
        if(network1->isRunning())
            network1->terminate();
        network1->deleteLater();
        network1 = NULL;

        if(!isConnected1 && !isConnected2)
            ui->label_channelopen->setStyleSheet("color:black;");
    });

    connect(network2, &Network2::finished, [=]() mutable
    {
        if(!network2->decoderERROR && RT_decoder != NULL)
            RT_decoder->Onend2Slot();
        if(network2->isRunning())
            network2->terminate();
        network2->deleteLater();
        network2 = NULL;

        if(!isConnected1 && !isConnected2)
            ui->label_channelopen->setStyleSheet("color:black;");
    });

    connect(RT_decoder, &RealtimeDecoder::InitReadySig, [=]()
    {
        network1->start(QThread::NormalPriority);
        network2->start(QThread::LowPriority);
    });

    //此处error指fopen失败的error，解压缩error会continue不影响
    connect(RT_decoder, &RealtimeDecoder::errorSig, [=]() mutable
    {
        network1->decoderERROR = true;
        network2->decoderERROR = true;
    });
    connect(this, &MainWindow::sended, RT_decoder, &RealtimeDecoder::cyclestart);

//    connect(RT_decoder, &RealtimeDecoder::imageready,this,&MainWindow::dddpddatarec);
//    connect(RT_decoder, &RealtimeDecoder::kcready,this,&MainWindow::kcdatarec);

    connect(RT_decoder,&RealtimeDecoder::newimageready,this,&MainWindow::senddata);
    connect(RT_decoder, &RealtimeDecoder::endSig, this, &MainWindow::infoBox);
    connect(RT_decoder, &RealtimeDecoder::finished,  [=]() mutable
    {
        MainWindow::fakeUi->setLinetext(QString("本次实时处理结束\n"));
        if(RT_decoder->isRunning())
            RT_decoder->terminate();
        RT_decoder->deleteLater();
        RT_decoder = NULL;
        delete buffer1;
        buffer1 = NULL;
        delete buffer2;
        buffer2 = NULL;
    });

}
//单通道实时解压缩功能
void MainWindow::on_openSinChannel()
{
    ui->pushButton_pause->setEnabled(false);

    if(ui->lineEdit_SavePath->text().isEmpty())
    {
        QMessageBox::warning(this, "CASE_DECODER 2.0", "请先填写实时解压缩保存地址", QMessageBox::Ok);
        return;
    }
    if (isConnected == true)
    {
        QMessageBox::warning(this, "警告", "通道 1 已连接，请勿重复连接！", QMessageBox::Ok);
    }
    QString recpath, outfile1;
    bool sended = false;
    ConnectDialogsin *connectdialogsin = new ConnectDialogsin(&IPaddress1, &port1, &recpath, &sended);

    //判断连接对话框执行与否，对话框退出执行break，跳出循环执行下面语句。需要两个break吗？
    while (true)
    {
        if (QDialog::Accepted == connectdialogsin->exec())
            break;
        break;
    }

    delete connectdialogsin;
    //点击了连接发送请求
    if(!sended)
        return;

    ui->listWidget->clear();
    /*************************统一时间————文件名*************************/
    QString data_time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
    recpath.replace("/", "\\");
    //通道1,2的文件名
    if(recpath.endsWith("\\"))
    {
        outfile1 = recpath + QString("Channelsin-") + data_time + ".dat";
    }
    else
    {
        outfile1 = recpath + "\\" + QString("Channelsin-") + data_time + ".dat";
    }
    /*************************解压缩核*************************/
    m_savepath = ui->lineEdit_SavePath->text();
    m_savepath = m_savepath.replace("/", "\\");
    //创建缓冲区
    //缓冲区  (256 * i)M
    buffer1 = new CCycleBuffer(BUFFERSIZE * 8 );
//    buffer2 = new CCycleBuffer(1024*1024*256);

    //lock是读写锁 改
    RT_decodersin = new RealtimeDecodersin(buffer1, lock1);
    RT_decodersin->OnRunPara(m_savepath);

    /* ********** 单线程接收 ********** */
    networksin = new Networksin(buffer1, lock1, &isConnected, IPaddress1, port1, outfile1, pGdata);
//    qDebug()<<"IPaddress:"<<IPaddress1;
//    qDebug()<<"port:"<<port1;


    //如果连接的话实时解压缩开启
    if(!networksin->Connect() )
    {
        QMessageBox::information(this, "Error", "请检查网络连接！");
        return;
    }
    else
    {
        ui->label_channelopen->setStyleSheet("color:orange;");
        networksin->start();         //这里要注释掉吗
//        qDebug()<<"networksin已完成";
        RT_decodersin->start();   //改  测试：不开启实时解压缩线程
//        qDebug()<<"RT_decodersin启动已完成";
    }

    //y
    connect(networksin, &Networksin::finished, [=]() mutable
    {
        //改
        if(!networksin->decoderERROR && RT_decodersin != NULL)
            RT_decodersin->Onend1Slot();
        if(networksin->isRunning())
            networksin->terminate();
        networksin->deleteLater();
        networksin = NULL;

        if(!isConnected)
            ui->label_channelopen->setStyleSheet("color:black;");
         MainWindow::fakeUi->setLinetext(QString("本次实时接收结束\n"));

    });


    connect(RT_decodersin, &RealtimeDecodersin::InitReadySig, [=]()
    {
        networksin->start(QThread::NormalPriority);
        //network2->start(QThread::LowPriority);
    });

    //此处error指fopen失败的error，解压缩error会continue不影响
    connect(RT_decodersin, &RealtimeDecodersin::errorSig, [=]() mutable
    {
        networksin->decoderERROR = true;
        //network2->decoderERROR = true;
    });

    connect(this, &MainWindow::sended, RT_decodersin, &RealtimeDecodersin::cyclestart);


//    connect(RT_decodersin, &RealtimeDecodersin::imageready,this,&MainWindow::dddpddatarec);
//    connect(RT_decodersin, &RealtimeDecodersin::kcready,this,&MainWindow::kcdatarec);

    connect(RT_decodersin,&RealtimeDecodersin::newimageready,this,&MainWindow::senddata);
    connect(RT_decodersin, &RealtimeDecodersin::endSig, this, &MainWindow::infoBox);
    connect(RT_decodersin, &RealtimeDecodersin::finished, [=]() mutable
    {
        MainWindow::fakeUi->setLinetext(QString("本次实时处理结束\n"));
        if(RT_decodersin->isRunning())
            RT_decodersin->terminate();
        RT_decodersin->deleteLater();
        RT_decodersin = NULL;
        delete buffer1;
        buffer1 = NULL;

    });
}
void MainWindow::on_pushButton_output_clicked()
{
  Dialog * dialog=new Dialog(this);

  connect(dialog,&Dialog::clientsocketGYA,this,&MainWindow::recsocketGYA);
  connect(dialog,&Dialog::clientsocketGYB,this,&MainWindow::recsocketGYB);
  connect(dialog,&Dialog::clientsocketGYC,this,&MainWindow::recsocketGYC);
  connect(dialog,&Dialog::clientsocketJGXJ,this,&MainWindow::recsocketJGXJ);
  connect(dialog,&Dialog::clientsocketZT,this,&MainWindow::recsocketZT);
  connect(dialog,&Dialog::clientsocketXSCL,this,&MainWindow::recsocketXSCL);
  connect(this,&MainWindow::closed,dialog,&Dialog::closed);//连接MainWindow的连接断开信号与dialog显示连接断开信息的槽，将其显示再界面上

  dialog->show();

  ui->pushButton_output->setEnabled(false);//设置选中后不可选
}
void MainWindow::recsocketGYA(SOCKET mSocket)
{
    GYAsocket = mSocket;
}
void MainWindow::recsocketGYB(SOCKET mSocket)
{
    GYBsocket = mSocket;
}
void MainWindow::recsocketGYC(SOCKET mSocket)
{
    GYCsocket = mSocket;
}
void MainWindow::recsocketJGXJ(SOCKET mSocket)
{
    JGXJsocket = mSocket;
}
void MainWindow::recsocketZT(SOCKET mSocket)
{
    ZTsocket = mSocket;
}
void MainWindow::recsocketXSCL(SOCKET mSocket)
{
    XSCLsocket = mSocket;
}
void MainWindow::dealimagedata(unsigned char *_data,int _datalen,int *rmlen,unsigned char * data,int* packnum,int flag)
{

}
void MainWindow::senddata(unsigned char * data, int datalen, int flag)
{

    FILE *fpOut;
    char fileName[400];

    if(GYAsocket != NULL && flag == GYAport)
    {
       int ret = ::send(GYAsocket,(char*)data,datalen,0);

//        /****** original ******/
       if(ret == -1)
       {
           qDebug()<<"GYA发送失败"<<strerror(errno);
           emit closed(QString("GYA"));
           GYAsocket = NULL;
       }
       else
       {
           if(ret != datalen)
           {
               qDebug()<<"发送字节不匹配";
           }
           qDebug()<<"GYA发送成功";
           sprintf(fileName, "E:/SOCGYA0814-8.dat");
           fpOut = fopen(fileName, "ab");
           if(NULL == fpOut)
           {
               MainWindow::fakeUi->setLinetext(QString("error: can not open %!\n").arg(QString(fileName)));
           }
           else
           {
               fwrite(data, ret, 1, fpOut);
               fclose(fpOut);
               fpOut = NULL;
           }
       }

    }
    if(GYBsocket != NULL && flag == GYBport )
    {
        int ret = ::send(GYBsocket,(char*)data,datalen,0);

        if(ret == -1)
        {
            qDebug()<<"GYB断开连接"<<strerror(errno);
            emit closed(QString("GYB"));
        }
        else
        {
//            sprintf(fileName, "SOCGYB.dat");
//            fpOut = fopen(fileName, "ab");
//            if(fpOut == NULL)
//            {
//                MainWindow::fakeUi->setLinetext(QString("error: can not open %!\n").arg(QString(fileName)));
//            }
//            else
//            {
//                fwrite(data, ret, 1, fpOut);
//                fclose(fpOut);
//                fpOut = NULL;
//            }
        }
    }
    if(GYCsocket!=NULL && flag == GYCport  )
    {
        int ret = ::send(GYCsocket,(char*)data,datalen,0);
        if(ret == -1)
        {
            emit closed(QString("GYC"));
        }
        else
        {

        }
    }
    if(JGXJsocket!=NULL && flag == JGXJport )
    {
        int ret = ::send(JGXJsocket,(char*)data,datalen,0);
        if(ret == -1)
        {
            emit closed(QString("JGXJ"));
        }
        else
        {
            qDebug()<<"JG发送成功";

        }
    }
    if(ZTsocket!=NULL && flag == ZTport )
    {
         ::send(ZTsocket,(char*)data,datalen,0);
    }

   emit sended();


}
