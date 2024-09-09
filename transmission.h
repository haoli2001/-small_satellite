#ifndef TRANSMISSION_H
#define TRANSMISSION_H
#include <QDialog>
#include <QThread>
#include <winsock2.h>
#include <QTime>
#include <QDebug>

class DataThread : public QThread
{
    Q_OBJECT
public:
    explicit DataThread(struct sockinfo* info,int flag,unsigned char *_strdata, int datalen,QDialog *parent = nullptr);
    void senddata();
    void dealotherdata();
    void run();
signals:
    void sended(int sendbyte);
    void isClose();
private:
    SOCKET mSocket;
    int flag;
    unsigned char *_strdata;
    int datalen;

public slots:
//    void dealsend(SOCKET mSocket);


};
#endif // TRANSMISSION_H
