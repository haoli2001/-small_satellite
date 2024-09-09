
#ifndef CASE_DECODER_H
#define CASE_DECODER_H

#include <QObject>
#include <QMutex>
#include <windows.h>
#include <QThread>
#include <QListWidget>

#include "unpack.h"
#include "dealsourcepackage.h"
#include <QMetaType>
#include "port_num.h"
class CASE_Decoder : public QThread
{
    Q_OBJECT
public:
    explicit CASE_Decoder(bool *isRUNNING_DECODER, QObject *parent = nullptr);

    bool LoadToStruct(QString filename);

    bool GetisDealing() { return isDealing; }
    void judgeFrameHand(unsigned char* inputdata, int inputlen, char *_outputfileLog);
    void judgeFrameCount(unsigned char* inputdata, int inputlen, char *_outputfileLog);
    int rate;
    QMutex m_mutex, mutex;

    UnPack     *unpack = NULL;
    DealSourcePackage *dealSourcePackage = NULL;


signals:
    void dialogTitleSig(QString name);

    void stateInfoSig(QString part);
    void stateSig(QString title, QString text);

    void raw_rt_Sig(QString filename, int width, int height,  int pixelBitDepth, int Endian, int datatype);
    void raw_back_Sig(QString filename, int width, int height,  int pixelBitDepth, int Endian, int datatype);
    void timeSig(double time);
    void endSig(QString title, QString text);
    void imageready(unsigned char* _str,int _len,int* remainlen,unsigned char * remaincode,int* packnum,int flag);
    void kcready(unsigned char* _str,int _len,int flag);

    void newimageready(unsigned char * _str,int len,int flag);

public slots:
    //void OnRunPara(QList<QString> slist, QList<int> ilist,QVector<int>vcid);
    void OnRunPara(QList<QString> slist);
    void cyclestart();

protected:
    void run();

private:

    QString mch1, mch2, mcompressed, savepath;

    int frame_len = 1024;

    bool *isRUNNING_DECODER;
    long long ZXGClength, RWSJlength, DKCBlength, DKZCBlength, DDDPDlength, DDDBlength, XJCSlength, JGCSlength, JGYYlength;
    bool isDealing = false;
    bool autoexit = false;
    bool dddpdunzip = false;
    bool sended=true;

    int firstflag = 1;
    int contFlag = 0;
};

#endif // CASE_DECODER_H

