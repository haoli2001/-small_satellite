#ifndef __UNPACK__
#define __UNPACK__

#include <QObject>

#define ZXGC 0x040B //整星工程参数数据源包
#define RWSJ 0x0418 //RW数据源包
#define DKCB 0x0087 //DKCB图像数据源包
#define DKZCB 0x0094 //DKZCB图像数据源包
#define DDDPD 0x013F //DDDPD图像数据源包
#define DDDB 0X015C //DDDB图像数据源包
#define XJCS 0X0109 //相机测试数据源包
#define JGCS 0X00B1 //JG测试数据源包
#define JGYY 0X00A2 //JGYY数据源包


#define HF0187 0x0087 //分区1星务工程参数数据
#define HF01A2 0X00A2//分区01
#define HF02B1 0X00B1//(原HFO2B1 0xOOB1
#define HF02C1 0x00C1 //分区2JG转台10HZ数执
#define HF0218 0X0418
#define HF032E 0X042E
#define HF033D 0X043D
#define HF034D 0X044D //分区@3 GYC数据源包
#define HF045E 0X045E   //受保护的GY相机图像

class UnPack: public QObject
{
    Q_OBJECT
public:
    explicit UnPack(QObject *parent = nullptr);

    static int headDetect(unsigned char* buffer, int bufferlen, int buffertmp, int* iStartPos);
    static int barkDetect(unsigned char* buffer, int bufferlen, int buffertmp, int* iStartPos);
    static int xwgcDetect(unsigned char* buffer, int bufferlen, int buffertmp, int* iStartPos);
    static int gyDetect(unsigned char* buffer, int bufferlen, int buffertmp, int* iStartPos);
    static int jgDetect(unsigned char* buffer, int bufferlen, int buffertmp, int* iStartPos);
    static int jginDetect(unsigned char* buffer, int bufferlen, int buffertmp, int* iStartPos);
    static int jg100Detect(unsigned char* buffer, int bufferlen, int buffertmp, int* iStartPos);

    static int endDetect(unsigned char* buffer, int bufferlen, int buffertmp, int* iStartPos);
    int barkDetectMode2(unsigned char* buffer, int bufferlen, int buffertmp, int* iStartPos, int *_dataType);

    static int checkFinal(unsigned char* buffer, int bufferlen);
    int checkFrame(unsigned char *data, int dataLen, char* mode, char* pathLog, char* pathMiddle, struct testCompressedStream* p);
    static int unpack1(unsigned char* pInputCode, int InputLen, unsigned char* pout, int* Outputlen, char *pathLog,bool state,unsigned int *numid);
    static int unpack(unsigned char* pInputCode, int InputLen, unsigned char* pout, int* Outputlen, char *pathLog,bool state);
    static int unpackxwgc(unsigned char* pInputCode, int InputLen, unsigned char* pout, int* Outputlen, char *pathLog);
   //l 0705
    static int newunpack(unsigned char* pInputCode, int InputLen, unsigned char* pout, int* Outputlen, char *pathLog,unsigned int *numid);
    static int newunpackxwgc(unsigned char* pInputCode, int InputLen, unsigned char* pout, int* Outputlen, char *pathLog,unsigned int *numid);
    static int geterrornum(){return errornum;};
    int errorUnpackNum = 0; //错误压缩码流帧数
    int unpackNum = 0;		//压缩码流总帧数
public:
    static int errornum  ;

//private:
    int unpackFrameNum = 0;    //对应序号


};
#endif


