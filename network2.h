#ifndef NETWORK2_H
#define NETWORK2_H

#include <QThread>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include "gdata.h"
#include "ccyclebuffer.h"
#include <QReadWriteLock>

class Network2 : public QThread
{
    Q_OBJECT
public:
    explicit Network2(CCycleBuffer *buffer2, QReadWriteLock *writelock, bool *isConnected, QString IP, quint16 PORT, QString SavePath, Gdata * pData, QObject *parent = nullptr);

    bool Connect();

    bool GetIsOver() { return over; }

    Gdata * pData;

    bool decoderERROR = false;
    bool autoexit = false;

signals:
    void connectSucSig();
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

    CCycleBuffer *buffer2;

    QReadWriteLock *writelock;
    QMutex m_mutex;

    bool over = false;
};

#endif // NETWORK2_H
