#include "dialog.h"
#include "ui_dialog.h"
#include<QMessageBox>
#include <QFont>
#include <QDebug>
#include <QLabel>
#include <QThread>
#include "transmission.h"
#include "case_decoder.h"
#include "case_sindecoder.h"
#include <cstring>
#include "sockinfo.h"
#include <QFile>


Dialog::Dialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("快视链接");
    //winsock 初始化
    WSAStartup(MAKEWORD(2,2),&mWasdata);
    //设置初始状态灯
//    setLED(ui->label_GYA,0,19);
//    setLED(ui->label_GYB,0,19);
//    setLED(ui->label_GYC,0,19);
//    setLED(ui->label_XWGC,0,19);
//    setLED(ui->label_XJLL,0,19);
//    setLED(ui->label_XSCL,0,19);
//    setLED(ui->label_ZT,0,19);
//    setLED(ui->label_JGXJ,0,19);
//    ui->lineEdit_ip->setText(QString("10.112.17.78"));
    ui->lineEdit_GYA->setText(QString::number(GYAport));
    ui->lineEdit_GYB->setText(QString::number(GYBport));
    ui->lineEdit_GYC->setText(QString::number(GYCport));
    ui->lineEdit_JGXJ->setText(QString::number(JGXJport));
    ui->lineEdit_XSCL->setText(QString::number(XSCLport));
    //感觉没啥用
    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_close->setEnabled(false);

}

Dialog::~Dialog()
{
    delete ui;
    closesocket(mSocket);
    //winsock 释放
    WSACleanup();
}

void Dialog::on_pushButton_connect_clicked()
{

        if((ui->lineEdit_ip->text()!=NULL))
        {
            ip=ui->lineEdit_ip->text();//获得ip地址
    //        m_ip=ip.toLatin1();
        }
        else
        {
            QMessageBox::warning(this,"警告","ip地址输入为空");
        }
        if((ui->lineEdit_ip->text()!=NULL))
        {
            ip=ui->lineEdit_ip->text();//获得ip地址
    //        m_ip=ip.toLatin1();
        }
        else
        {
            QMessageBox::warning(this,"警告","ip地址输入为空");
        }
        //to do
        //修改GYA，GYB，GYC，JGXJ，XSCL为客户端代码
        //客户端通信流程
        /************************************************************************************************
         * 1.创建套接字 GYAsocket = socket(AF_INET,SOCK_STREAM,0);判断是否创建成功
         *  if(GYsocket == SOCKET_ERROR)
            {
                ui->listWidget_connect->addItem(QString("套接字创建失败"));
            }
            else
            {
                ui->listWidget_connect->addItem(QString("套接字创建成功"));
            }
         * 2.将套接字与本地端口绑定
         *  QString port = ui->lineEdit_GYA->text();
            struct sockaddr_in addr;
            addr.sin_family=AF_INET;
            addr.sin_port=htons(port.toInt());//大端端口
            addr.sin_addr.S_un.S_addr=inet_addr(ip.toLatin1());
         * 3.与服务端进行连接
         *  int ret1=::connect(GYsocket,(struct sockaddr*)&addr,sizeof(addr));
            if(SOCKET_ERROR==ret1)
            {
                ui->listWidget_connect->addItem(QString("socket连接失败!"));
            }
            else
            {
                qDebug()<<"连接成功";
                emit send_GY_socket(GYsocket);//连接成功后发送套接字去MainWindow
                ui->listWidget_connect->addItem(QString("socket连接成功!可发送GY数据"));
//                ui->pushButton_connect->setEnabled(false);
                ui->pushButton_closed->setEnabled(true);
            }
         *************************************************************************************************/
        if(ui->checkBox_GYA->isChecked())
        {
            //1.创建套接字
            GYAsocket = socket(AF_INET,SOCK_STREAM,0);
            if(GYAsocket == SOCKET_ERROR)
            {
                ui->listWidget_connect->addItem(QString("套接字创建失败"));
            }
            else
            {
                ui->listWidget_connect->addItem(QString("套接字创建成功"));
            }
            //2.将socket返回值与本地端口绑定
            struct sockaddr_in addr;
            addr.sin_family=AF_INET;
            addr.sin_port=htons(GYAport);//大端端口
            addr.sin_addr.S_un.S_addr=inet_addr(ip.toLatin1());
            int ret1=::connect(GYAsocket,(struct sockaddr*)&addr,sizeof(addr));
           if(SOCKET_ERROR==ret1)
           {
               ui->listWidget_connect->addItem(QString("socket连接失败!"));
           }
           else
           {
               emit clientsocketGYA(GYAsocket);//连接成功后发送套接字去MainWindow
               ui->listWidget_connect->addItem(QString("socket连接成功!可发送GYA数据"));
           }


        }

        if(ui->checkBox_GYB->isChecked())
        {
            GYBsocket = socket(AF_INET,SOCK_STREAM,0);
            if(GYBsocket == SOCKET_ERROR)
            {
                ui->listWidget_connect->addItem(QString("套接字创建失败"));
            }
            else
            {
                ui->listWidget_connect->addItem(QString("套接字创建成功"));
            }
            //2.将socket返回值与本地端口绑定
            struct sockaddr_in addr;
            addr.sin_family=AF_INET;
            addr.sin_port=htons(GYBport);//大端端口
            addr.sin_addr.S_un.S_addr=inet_addr(ip.toLatin1());
            int ret1=::connect(GYBsocket,(struct sockaddr*)&addr,sizeof(addr));
           if(SOCKET_ERROR==ret1)
           {
               ui->listWidget_connect->addItem(QString("socket连接失败!"));
           }
           else
           {
               emit clientsocketGYB(GYBsocket);//连接成功后发送套接字去MainWindow
               ui->listWidget_connect->addItem(QString("socket连接成功!可发送GYB数据"));
           }

        }
        if(ui->checkBox_GYC->isChecked())
        {
            GYCsocket = socket(AF_INET,SOCK_STREAM,0);
            if(GYCsocket == SOCKET_ERROR)
            {
                ui->listWidget_connect->addItem(QString("套接字创建失败"));
            }
            else
            {
                ui->listWidget_connect->addItem(QString("套接字创建成功"));
            }
            //2.将socket返回值与本地端口绑定
            struct sockaddr_in addr;
            addr.sin_family=AF_INET;
            addr.sin_port=htons(GYCport);//大端端口
            addr.sin_addr.S_un.S_addr=inet_addr(ip.toLatin1());
            int ret1=::connect(GYCsocket,(struct sockaddr*)&addr,sizeof(addr));
           if(SOCKET_ERROR==ret1)
           {
               ui->listWidget_connect->addItem(QString("socket连接失败!"));
           }
           else
           {
               emit clientsocketGYC(GYCsocket);//连接成功后发送套接字去MainWindow
               ui->listWidget_connect->addItem(QString("socket连接成功!可发送GYC数据"));
           }

        }
        if(ui->checkBox_JGXJ->isChecked())
        {
            JGXJsocket = socket(AF_INET,SOCK_STREAM,0);
            if(JGXJsocket == SOCKET_ERROR)
            {
                ui->listWidget_connect->addItem(QString("套接字创建失败"));
            }
            else
            {
                ui->listWidget_connect->addItem(QString("套接字创建成功"));
            }
            //2.将socket返回值与本地端口绑定
            struct sockaddr_in addr;
            addr.sin_family=AF_INET;
            addr.sin_port=htons(JGXJport);//大端端口
            addr.sin_addr.S_un.S_addr=inet_addr(ip.toLatin1());
            int ret1=::connect(JGXJsocket,(struct sockaddr*)&addr,sizeof(addr));
           if(SOCKET_ERROR==ret1)
           {
               ui->listWidget_connect->addItem(QString("socket连接失败!"));
           }
           else
           {
               emit clientsocketJGXJ(JGXJsocket);//连接成功后发送套接字去MainWindow
               ui->listWidget_connect->addItem(QString("socket连接成功!可发送JGXJ数据"));
           }

        }
        if(ui->checkBox_ZT->isChecked())
        {


        }
        if(ui->checkBox_XSCL->isChecked())
        {
            XSCLsocket = socket(AF_INET,SOCK_STREAM,0);
            if(XSCLsocket == SOCKET_ERROR)
            {
                ui->listWidget_connect->addItem(QString("套接字创建失败"));
            }
            else
            {
                ui->listWidget_connect->addItem(QString("套接字创建成功"));
            }
            //2.将socket返回值与本地端口绑定
            struct sockaddr_in addr;
            addr.sin_family=AF_INET;
            addr.sin_port=htons(XSCLport);//大端端口
            addr.sin_addr.S_un.S_addr=inet_addr(ip.toLatin1());
            int ret1=::connect(XSCLsocket,(struct sockaddr*)&addr,sizeof(addr));
           if(SOCKET_ERROR==ret1)
           {
               ui->listWidget_connect->addItem(QString("socket连接失败!"));
           }
           else
           {
               emit clientsocketXSCL(XSCLsocket);//连接成功后发送套接字去MainWindow
               ui->listWidget_connect->addItem(QString("socket连接成功!可发送XSCL数据"));
           }
        }
        ui->pushButton_connect->setEnabled(false);
        ui->pushButton_close->setEnabled(true);
}

void Dialog::on_pushButton_close_clicked()
{
    if(GYAsocket != NULL)
    {
        shutdown(GYAsocket,SD_SEND);
        GYAsocket = NULL;
        ui->listWidget_connect->addItem(QString("GYA断开连接"));
    }
    if(GYBsocket != NULL)
    {
        shutdown(GYBsocket,SD_SEND);
        GYBsocket = NULL;
        ui->listWidget_connect->addItem(QString("GYB断开连接"));
    }
    if(GYCsocket != NULL)
    {
        shutdown(GYCsocket,SD_SEND);
        GYCsocket = NULL;
        ui->listWidget_connect->addItem(QString("GYC断开连接"));
    }
    if(XSCLsocket != NULL)
    {
        shutdown(XSCLsocket,SD_SEND);
        XSCLsocket = NULL;
        ui->listWidget_connect->addItem(QString("XSCL断开连接"));
    }
    if(JGXJsocket != NULL)
    {
        shutdown(JGXJsocket,SD_SEND);
        JGXJsocket = NULL;
        ui->listWidget_connect->addItem(QString("JGXJ断开连接"));
    }
    ui->pushButton_close->setEnabled(false);
    ui->pushButton_connect->setEnabled(true);
}

void Dialog::on_pushButton_clean_clicked()
{
    ui->listWidget_connect->clear();
    ui->listWidget_send->clear();

}
void Dialog::setLED(QLabel* label, int color, int size)
{
    // 将label中的文字清空
    label->setText("");
    // 先设置矩形大小
    // 如果ui界面设置的label大小比最小宽度和高度小，矩形将被设置为最小宽度和最小高度；
    // 如果ui界面设置的label大小比最小宽度和高度大，矩形将被设置为最大宽度和最大高度；
    QString min_width = QString("min-width: %1px;").arg(size);              // 最小宽度：size
    QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
    QString max_width = QString("max-width: %1px;").arg(size);              // 最小宽度：size
    QString max_height = QString("max-height: %1px;").arg(size);            // 最小高度：size
    // 再设置边界形状及边框
    QString border_radius = QString("border-radius: %1px;").arg(size/2);    // 边框是圆角，半径为size/2
    QString border = QString("border:1px solid black;");                    // 边框为1px黑色
    // 最后设置背景颜色
    QString background = "background-color:";
    switch (color) {
    case 0:
        // 灰色
        background += "rgb(190,190,190)";
        break;
    case 1:
        // 红色
        background += "rgb(255,0,0)";
        break;
    case 2:
        // 绿色
        background += "rgb(0,255,0)";
        break;
    case 3:
        // 黄色
        background += "rgb(255,255,0)";
        break;
    default:
        break;
    }

    const  QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}
void Dialog::sended(int sendbyte)
{
    ui->listWidget_send->addItem(QString("发送完毕！共发送字节数1%!").arg(sendbyte));

}
void Dialog::closed(QString msg)
{
    ui->listWidget_connect->addItem(QString("发送%1数据失败，该端口号断开连接!").arg(msg));
}
//利用多线程进行通信的话，需要将套接字，ip地址以及端口放在一个结构体里

