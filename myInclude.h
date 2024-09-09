#ifndef __myInclude__
#define  __myInclude__

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//#define myDeBugMode 1       //1调试（慢）  0

//输出更多信息decode哪一帧
//#define yygMode    1

//是否打印图片不连续性信息
#define checkPicContinuous 1

#define fileNameLen 400

//速率测试
//#define clocktest 1

#define DataLen 4016 //老数据格式
//#define DataLen 4014   //新数据格式

//combine.h

#define VC_1 0x5886  //实时卫星工程参数数据
#define VC_2 0x58A2  //回放载荷数据
#define VC_63 0x58BF //填充帧

//0122需求修改
#define VC_1_02 0x6146  //02星卫星工程参数数据 24902
#define VC_1_03 0x6186  //03星卫星工程参数数据 24996
#define VC_2_02 0x6162  //02星回放载荷数据 24930
#define VC_2_03 0x61A2  //03星回放载荷数据 24992
#define VC_63_02 0x617F  //02星填充帧 24959
#define VC_63_03 0x61BF  //03星填充帧 25023

#define VC0 0x5880  //实时星间数据
#define VC1 0x5883  //实时RW数据
#define VC2 0x5886  //实时卫星工程参数数据
#define VC3 0x588C  //实时载荷数据
#define VC4 0x5891  //回放工程参数数据
#define VC5 0x58A2  //回放载荷数据
#define VC63 0x58BF //填充帧


#ifdef __cplusplus
extern "C"
{
#endif
//根据文档存储源包分为如下几类
struct SourceStream
{
    unsigned char	*ZXGCdata; //从AOS帧提取出的RHW存储源包数据
    unsigned char	*RWSJdata;
    unsigned char	*DKCBdata;
    unsigned char	*DKZCBdata;
    unsigned char	*DDDPDdata;
    unsigned char	*DDDBdata;
    unsigned char	*XJCSdata;
    unsigned char	*JGCSdata;
    unsigned char	*JGYYdata;
    unsigned char	*SSZXGCdata; //从AOS帧提取出的RHW存储源包数据
    unsigned char	*SSRWSJdata;
    unsigned char	*SSDKCBdata;
    unsigned char	*SSDKZCBdata;
    unsigned char	*SSDDDPDdata;
    unsigned char	*SSDDDBdata;
    unsigned char	*SSXJCSdata;
    //unsigned char	*SSJGCSdata;
    unsigned char	*SSJGYYdata;
};


//建立的目的封装处理压缩码流到函数
//提取开启线程数量的压缩码流并存储，开启线程一起处理。处理结果即解压缩码流存储到数组里！
//还是分为RHW,DGPA,DGPB,WGA,WGB几类
struct compressedStream
{
    //提取一帧压缩码流
    int ilen;			   //提取的压缩码流数据长度
    int frameNum;           //代表其为本文件第几个对应的压缩码流数据，序号
    unsigned char *img;     //代表一帧压缩码流数据,缓存几个开启线程一起处理

};
//书写日志id
struct RZid{
    //XSCL日志
    unsigned int GYIPDid ;
    unsigned int JGIPDid ;
    unsigned int GYTWDW01id ;
    unsigned int GYTWDW02id ;
    unsigned int JGTWDW01id ;
    unsigned int JGTWDW02id ;
    unsigned int GYGTWid ;
    unsigned int GYYDXXid ;
    unsigned int GYYDXXXX01id ;
    unsigned int GYYDXXXX02id ;
    unsigned int GYTXCLRZid ;
    unsigned int TWDWRZid;
    unsigned int YDGZRZid ;
    unsigned int JGTXCLRZid;
    //JG 日志
    unsigned int JGid ;
    //JG100日志
    unsigned int ZTid ;
    //GY 日志
    unsigned int GYAid  ;
    unsigned int GYA21id ;
    unsigned int GYA41id ;
    unsigned int GYBid ;
    unsigned int GYB21id ;
    unsigned int GYB41id ;
    unsigned int GYCid ;
    unsigned int GYC21id ;
    unsigned int GYC41id ;
    unsigned int GYproid ;
    unsigned int GYpro21id ;
    unsigned int GYpro41id;
    //错误包数统计参数，用来在report里写文件
    //第二层
    unsigned int errorssxwgc;
    unsigned int errorhfxwgc;
    unsigned int errorxscl01;//01A2
    unsigned int errorxscl02;//02B1
    unsigned int errorztdata;//JG100  02C1
    unsigned int errorjgxjdata;//0218
    unsigned int errorgyadata;
    unsigned int errorgybdata;
    unsigned int errorgycdata;
    unsigned int errorgyprodata;
    //第三层
    unsigned int errorGYIPDid ;
    unsigned int errorJGIPDid ;
    unsigned int errorGYTWDW01id ;
    unsigned int errorGYTWDW02id ;
    unsigned int errorJGTWDW01id ;
    unsigned int errorJGTWDW02id ;
    unsigned int errorGYGTWid ;
    unsigned int errorGYYDXXid ;
    unsigned int errorGYYDXXXX01id ;
    unsigned int errorGYYDXXXX02id ;
    unsigned int errorGYTXCLRZid ;
    unsigned int errorTWDWRZid;
    unsigned int errorYDGZRZid ;
    unsigned int errorJGTXCLRZid;
    //JG 日志
    unsigned int errorJGid ;
    //JG100日志
    unsigned int errorZTid ;
    //GY 日志
    unsigned int errorGYAid  ;
    unsigned int errorGYA21id ;
    unsigned int errorGYA41id ;
    unsigned int errorGYBid ;
    unsigned int errorGYB21id ;
    unsigned int errorGYB41id ;
    unsigned int errorGYCid ;
    unsigned int errorGYC21id ;
    unsigned int errorGYC41id ;
    unsigned int errorGYproid ;
    unsigned int errorGYpro21id ;
    unsigned int errorGYpro41id;

};
#ifdef __cplusplus
}
#endif

struct testCompressedStream
{
    int frameNum;//该数据类型总的压缩码流数

    int correctNum; //帧和校验正确帧数
    int errorNum;
};


__int64 filesize64(FILE* stream);



enum { ZXGCtype, RWSJtype, DKCBtype, DKZCBtype, DDDPDtype, DDDBtype, XJCStype, JGCStype, JGYYtype};      //解压缩分辨

struct Frame
{
    unsigned char* data;
    long long sizelen;
};

void outputLog(struct testCompressedStream* p, const char* word);

//void combine(unsigned char* Inputcode1, int Inputlen1, unsigned char* Inputcode2, int Inputlen2,
//             unsigned char* SSRWdata, unsigned char* SSGCdata,
//             unsigned char* SSZHdata, unsigned char* HFGCdata, unsigned char* HFZHdata,
//             long long* SSRWlen, long long* SSGClen, long long* SSZHlen, long long* HFGClen, long long* HFZHlen,
//             unsigned char* remaincode1, unsigned char* remaincode2, long long* remainlen1, long long* remainlen2,
//             int ibypass, int irecord, int iactual, char outputpath[200],bool* vcstate);
void combine(unsigned char* Inputcode1, int Inputlen1, unsigned char* Inputcode2, int Inputlen2,
             unsigned char* SSRWdata, unsigned char* SSGCdata,
             unsigned char* SSZHdata, unsigned char* HFGCdata, unsigned char* HFZHdata,unsigned char* TCZdata,unsigned char* XJSJdata,
             long long* SSRWlen, long long* SSGClen, long long* SSZHlen, long long* HFGClen, long long* HFZHlen,long long* TCZlen,long long* XJSJlen,
             unsigned char* remaincode1, unsigned char* remaincode2, long long* remainlen1, long long* remainlen2,
             int ibypass, int irecord, int iactual, char outputpath[200],int vcNum,bool * vcflag,unsigned int *synvc,int *synflag);

void newcombine(unsigned char* Inputcode1, int Inputlen1, unsigned char* Inputcode2, int Inputlen2,
             unsigned char* SSdata, unsigned char* HFdata,unsigned char* TCZdata,
             long long* SSlen, long long* HFlen, long long* TCZlen,
             unsigned char* remaincode1, unsigned char* remaincode2, long long* remainlen1, long long* remainlen2,
             int irecord, int iactual, char outputpath[200],unsigned int *synvc,int *synflag);

void combine_one(unsigned char* Inputcode1, int Inputlen1,
             unsigned char* SSRWdata, unsigned char* SSGCdata, unsigned char* SSZHdata, unsigned char* HFGCdata, unsigned char* HFZHdata,unsigned char* TCZdata,unsigned char* XJSJdata,
             long long* SSRWlen, long long* SSGClen, long long* SSZHlen, long long* HFGClen, long long* HFZHlen,long long* TCZlen,long long* XJSJlen,
             unsigned char* remaincode1, long long* remainlen1, int ibypass, int irecord, int iactual, int vcNum,bool * vcflag);
//void newcombine_one(unsigned char* Inputcode1, int Inputlen1,
//             unsigned char* SSdata, unsigned char* HFdata, unsigned char* TCZdata,
//             long long* SSlen, long long* HFlen, long long* TCZlen,
//             unsigned char* remaincode1, long long* remainlen1, int irecord, int iactual, int vcNum,bool * vcflag,unsigned int *synvc,int *synflag);
void newcombine_one(unsigned char* Inputcode1, int Inputlen1,
             unsigned char* SSdata, unsigned char* HFdata, unsigned char* TCZdata,
             long long* SSlen, long long* HFlen, long long* TCZlen,
             unsigned char* remaincode1, long long* remainlen1, int irecord, int iactual);


#endif

