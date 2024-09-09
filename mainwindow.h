#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "network1.h"
#include "network2.h"
#include "networksin.h"
#include "ccyclebuffer.h"
#include <winsock2.h>
#include <windows.h>
#include "case_decoder.h"
#include "myInclude.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QThread>
#include "case_sindecoder.h"
#include "dialog.h"
#include "port_num.h"
#include "connectdialog.h"
#include "connectdialogsin.h"
#include "SocketConstant.h"
#include "realtimedecoder.h"
#include "realtimedecodersin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<QString> slist;
    //双通道是实时解压缩的ip和端口
    QString IPaddress1, IPaddress2;
    quint16 port1, port2;
    static MainWindow *fakeUi;

    void setLinetext(QString text);

protected:
    void closeEvent(QCloseEvent *event);


//信号
signals:
    void runParaSig(QList<QString> slist);
    void pauseSucSig(bool isSuc);

    void dialogshowSig();
    void dowork();
    void pauseSig(bool ispaused);


    void ConnectSig();
    void SendAndRevSig();
    void endSig();
    void isSend(QString msg);
    void sended();

    void closed(QString msg);//用来处理服务端断开的情况
    void senddataready(unsigned char * data,int datalen);
    
private slots:
    void on_Run();
    void on_Runsin();
    
    void on_pushButton_OpenCH1_clicked();

    void on_pushButton_OpenCH2_clicked();

    void on_pushButton_pause_clicked();

    void showBox(QString title, QString text);
    void infoBox(QString title, QString text);

    void on_pushButton_SavePath_clicked();

    void on_pushButton_OpenSingleCH_clicked();

    /*******************实时解压缩功能槽函数，在mainwindow的构造函数里与按钮连接******************************/
    void on_openChannel();//处理双通道实时解压缩
    void on_openSinChannel();//处理单通道实时解压缩
   /**************************************************************************************************/
    void on_pushButton_output_clicked();
    void recsocketGYA(SOCKET mSocket);
    void recsocketGYB(SOCKET mSocket);
    void recsocketGYC(SOCKET mSocket);
    void recsocketZT(SOCKET mSocket);
    void recsocketJGXJ(SOCKET mSocket);
    void recsocketXSCL(SOCKET mSocket);
    void dealimagedata(unsigned char *data,int datalen,int* remainlen,unsigned char * remaincode,int* packnum,int flag);

    void senddata(unsigned char * data,int datalen , int flag);
private:
    Ui::MainWindow *ui;

    CASE_Decoder *decoder;      //解压缩核
    CASE_SinDecoder *sindecoder;
    
    //输入路径与输出路径  
    QString m_savepath;         //本地保存路径
    QString m_ch1;              //通道1数据路径
    QString m_ch2;              //通道2数据路径
    QString m_chsin;              //单通道数据路径

    //运行状态
    bool isRUNNING_DECODER = false;  //双回放


    
    //连接状态
    bool isConnected1, isConnected2,isConnected;
    //实时解压缩
    RealtimeDecoder *RT_decoder = NULL;
    RealtimeDecodersin * RT_decodersin = NULL;
    Network1 *network1;
    Network2 *network2;
    Networksin *networksin;
    CCycleBuffer *buffer1, *buffer2,*bufferDDDPD;
    Gdata * pGdata;
    QReadWriteLock *lock1, *lock2;
    QMutex m_mutex;
    bool isPaused = false;
    WSADATA mWasData;
    //数据传输socket
    SOCKET GYAsocket=NULL;
    SOCKET GYBsocket=NULL;
    SOCKET GYCsocket=NULL;
    SOCKET ZTsocket=NULL;
    SOCKET JGXJsocket=NULL;
    SOCKET XWGCsocket=NULL;
    SOCKET XJLLsocket=NULL;
    SOCKET XSCLsocket=NULL;
    //备用socket
    SOCKET ssdddbsocket=NULL;
    SOCKET hfdddbsocket=NULL;
    SOCKET ssdkzcbsocket=NULL;
    SOCKET hfdkzcbsocket=NULL;
    int test = 0;

    Dialog * dialog;
};
#endif // MAINWINDOW_H
