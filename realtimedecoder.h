#ifndef REALTIMEDECODER_H
#define REALTIMEDECODER_H
#include <QThread>
#include <windows.h>
#include <QThread>
#include <QListWidget>
#include <QReadWriteLock>
#include <QMetaType>
#include <QDebug>

#include "dealsourcepackage.h"
#include "unpack.h"
#include "ccyclebuffer.h"


class RealtimeDecoder : public QThread
{
    Q_OBJECT
public:
    RealtimeDecoder(CCycleBuffer *buffer1, CCycleBuffer *buffer2, QReadWriteLock *readlock1, QReadWriteLock *readlock2, QObject *parent = nullptr);

    void OnRunPara(QString path);

    bool LoadToStruct(QString filename);

    bool GetIsOver() { return (Recved1ended && Recved2ended && buffer1->isEmpty() && buffer2->isEmpty()); }

    int         rate;


    UnPack     *unpack;
    DealSourcePackage *dealSourcePackage;

    bool Recved1ended = false, Recved2ended = false;

    bool isfailed = false;   //错误退出  //未解完退出
    int frame_len = 1024;

public slots:
    void Onend1Slot();
    void Onend2Slot();
    void cyclestart();

signals:
    void InitReadySig();

    void dialogTitleSig(QString name);

    void stateInfoSig(QString part);
    void stateSig(QString title, QString text);


    void raw_rt_Sig(QString filename, int width, int height,  int pixelBitDepth, int Endian, int datatype);
    void raw_back_Sig(QString filename, int width, int height,  int pixelBitDepth, int Endian, int datatype);
    void timeSig(double time);
    void endSig(QString title, QString text);
    void errorSig();
    void newimageready(unsigned char *_syr,int _len,int flag);

protected:
    void run();

private:
    CCycleBuffer *buffer1, *buffer2;

    QReadWriteLock *readlock1, *readlock2;

private:

    QString     savepath;
    QMutex m_mutex;
    //bool        isOver = false;     //全部解压缩完成

    int firstflag = 1;
    int contFlag = 0;
    bool sended=1;
//    bool *isRUNNING_DECODER;
//    bool autoexit = false;

};


#endif // REALTIMEDECODER_H
