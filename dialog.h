#ifndef DIALOG_H
#define DIALOG_H

#include <QMainWindow>
#include <windows.h>
#include <winsock2.h>
#include <QLabel>
#include "transmission.h"
#include "sockinfo.h"
#include "port_num.h"
//包含端口号宏定义的头文件

namespace Ui {
class Dialog;
}
class Dialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
private:
    Ui::Dialog *ui;
private:
    WSADATA mWasdata;
    SOCKET mSocket;
    QString ip;//输入的ip地址字符串
    QString mport_temp;
    QByteArray m_ip;//ip地址（纯数字）  ip地址分主机端和网络端，常常需要相互转换，也可使用转换函数；没用上
    //与快视链接的套接字
    SOCKET socketGYA = NULL;
    SOCKET socketGYB = NULL;
    SOCKET socketGYC = NULL;
    //to do
    //需要GYAsocket，GYBsocket，GYCsocket，JGXJsocket，XSCLsocket作为客户端套接字与服务端进行通信
    SOCKET GYAsocket = NULL;
    SOCKET GYBsocket = NULL;
    SOCKET GYCsocket = NULL;
    SOCKET JGXJsocket = NULL;
    SOCKET XSCLsocket = NULL;
   //done
    SOCKET servicesocket = NULL;//服务器套接字
    QString port;//服务器端口号
    int mflag;
signals:
    void clientsocket(SOCKET mSocket);

    void clientsocketGYA(SOCKET mSocket);
    void clientsocketGYB(SOCKET mSocket);
    void clientsocketGYC(SOCKET mSocket);
    void clientsocketXWGC(SOCKET mSocket);
    void clientsocketXSCL(SOCKET mSocket);
    void clientsocketXJLL(SOCKET mSocket);
    void clientsocketJGXJ(SOCKET mSocket);

    void clientsocketZT(SOCKET mSocket);
//这些好像变得没啥用了
private slots:
    void on_pushButton_connect_clicked();
    void on_pushButton_clean_clicked();
    void on_pushButton_close_clicked();

public slots:
    void sended(int sendbyte);
    void closed(QString msg);
public:
    void setLED(QLabel* label, int color, int size);//用来设置状态灯显示数据的发送状态
    DataThread* mdatathread;

    QString get_ip(){
        return this->ip;
    }

};

#endif // DIALOG_H
