#ifndef REALTIMEDECODERSIN_H
#define REALTIMEDECODERSIN_H

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
#include "port_num.h"

class RealtimeDecodersin : public QThread
{
    Q_OBJECT
public:
    RealtimeDecodersin(CCycleBuffer *buffer1, QReadWriteLock *readlock1,  QObject *parent = nullptr);

    void OnRunPara(QString path);

    bool LoadToStruct(QString filename);

    bool GetIsOver() { return (Recved1ended && Recved2ended && buffer1->isEmpty()); }

    int         rate;


    UnPack     *unpack;
    DealSourcePackage *dealSourcePackage;

    bool Recved1ended = false, Recved2ended = false;

    bool isfailed = false;   //错误退出  //未解完退出
signals:
    void InitReadySig();

//    void dialogTitleSig(QString name);

//    void stateInfoSig(QString part);
    void stateSig(QString title, QString text);


//    void raw_rt_Sig(QString filename, int width, int height,  int pixelBitDepth, int Endian, int datatype);
//    void raw_back_Sig(QString filename, int width, int height,  int pixelBitDepth, int Endian, int datatype);
//    void timeSig(double time);
    void endSig(QString title, QString text);
    void errorSig();
    void imageready(unsigned char* _str,int _len,int flag);
    void kcready(unsigned char* _str,int _len,int flag);
    void newimageready(unsigned char *_str,int _len,int flag);
protected:
    void run();

public slots:
    void Onend1Slot();
    //void Onend2Slot();
    void cyclestart();

private:
    CCycleBuffer *buffer1;

    QReadWriteLock *readlock1;

    QString     savepath;
//    int         skip_len, record_len, frame_len, bit_depth, bigsmall, block_size,vcNum;
    //bool        isOver = false;

    QList<int> vcid;
    bool vcstate[20];
    int frame_len = 1024;

    QMutex m_mutex;
    //bool        isOver = false;     //全部解压缩完成
    bool dddpdunzip;

    int firstflag = 1;
    int contFlag = 0;
    bool sended=1;


};

#endif // REALTIMEDECODERSIN_H
