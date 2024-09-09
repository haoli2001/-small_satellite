#ifndef NETWORKSIN_H
#define NETWORKSIN_H

#define WIN32_LEAN_AND_MEAN
#include <QThread>
#include <windows.h>
#include <winsock2.h>
#include <QReadWriteLock>
#include "gdata.h"
#include "ccyclebuffer.h"

#include <QTcpSocket>
#include <QDateTime>

class QTimer;

class Networksin : public QThread
{
    Q_OBJECT
public:
    explicit Networksin(CCycleBuffer *buffer1, QReadWriteLock *writelock, bool *isConnected, QString IP, quint16 PORT, QString SavePath, Gdata * pData, QObject *parent = nullptr);

    bool Connect();

    bool GetIsOver() { return over; }

    Gdata * pData;

    bool decoderERROR = false;
    bool autoexit = false;
signals:

    void connectSucSig();//连接成功
    void closeSig();

public slots:
    void OnCloseSocket();

protected:
    void run();

private:
    WSADATA mWasData;
    SOCKET mSocket;

    QString mAddrStr;
    QString ip;
    quint16 port;
    QString savepath;
    bool *isConnected;

    unsigned char* buffer;
    CCycleBuffer *buffer1;

    QReadWriteLock *writelock;
    QMutex m_mutex;

    bool over = false;

};

#endif // NETWORKSIN_H
