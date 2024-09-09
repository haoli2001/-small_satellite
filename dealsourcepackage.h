#ifndef DEALSOURCEPACKAGE_H
#define DEALSOURCEPACKAGE_H

#include <QObject>
#include "unpack.h"

//2711源包类型

//vc3 vc5 载荷数据
#define DKCB_S 0X11    //DKCB图像
#define DKZCB_S 0X12    //DKZCB图像
//XJCS源包
#define DK_S 0X14   //DKTCXJCS数据
#define DD_S 0X24  //DDTCXJCS数据
#define DDDB_S 0X21  //DDDB图像
//DDDPD源包
#define DDDPD_S 0X22  //DDDPD图像
#define DDDPDKC_S 0X28    //DDDPD开窗图像
//回放实时JGYY数据源包00A2  2711包类型
#define JGCJGZHB 0x38   //
#define JGCJGZ 0x3B    //
#define JGCJJG 0x4F

//vc5 回放激光测试数据00B1  2711包类型
#define JGHW_S 0X31   //JGCJCBZF
#define JGCJFSJZ_S 0X34  //JGCJJSJZ
#define JGCJJSJZ_S 0X32  //JGCJFSJZ

//vc1 实时任务数据源包 2711包类型
//vc4 回放任务数据源包 2711包类型
#define XJSJ_S 0X40     //空间网络管理数据包
#define DDZT_S 0X41   //DDZT100Hz工程数据
#define DKZT_S 0X42   //DKZT100Hz工程数据
#define XMSJ_S 0X43   //星敏数据包
#define GMTLC_S 0X44   //光纤陀螺C数据
#define XXCLA_S 0X45   //本星XXCLA过程数据（20Hz遥测数据）
#define NBYK_S 0X46    //内部遥控指令
#define XXCL_S 0X47    //XXCL数据
#define DXXT_S 0X48    //多星协同数据
#define XXCLB_S 0X49    //本星XXCLB过程数据
#define RWGH_S 0X4A    //本星任务规划结果数据
#define Res_1 0x4B     //预留1
#define SXQD_S 0X4C    //本星XXCL的视线确定数据
#define XJSC 0x4D     //星间数传数据
#define SJGB 0x4E     //时间广播
#define TXCSYC 0x50   //通过他星传输遥测数据
#define TXCSSC 0x51    //通过他星传输数传数据


///////////////////////////2711子包///////////////////////////////
//2711内部分包类型,F:分
//空间网络管理包0x40
#define KJBXY_F 0XA1  //空间包协议数据
#define FZBXY_F 0XA2  //封装包协议数据
#define AOSXY_F 0XA3  //AOS帧协议
#define MPDUXY_F 0XA4  //MPDU协议
//DDZT100Hz工程数据0x41
#define DDZT100 0X28
//DKZT100Hz工程数据 0x42
#define DKZT100 0X27
//星敏数据包 0x43
#define XMA_F 0X38
#define XMB_F 0X39
#define XMC_F 0X3A
#define XMD_F 0X3B
//光敏陀螺C数据 0x44
#define GMTLC 0X14  //这里有疑问？图与表格不符
//#define TLB_F 0X3C
//#define TLC_F 0X3D
//XXCL数据 0X47
#define XXCLKJB 0X01
#define XXCLFZB 0X02
#define XXCLAOS 0X03
#define XXCLMPDU 0X04
////XXCLA数据0x45
//#define XXCLADB 0X09
//#define XXCLADPD 0X0A
//#define XXCLACB 0X0B
//#define XXCLAZCB 0X0C
//#define XXCLABQT 0X33
//#define XXCLADBDSP 0X05
//#define XXCLADPDDSP 0X06
//#define XXCLACBDSP 0X07
//#define XXCLAZCBDSP 0X08
//#define XXCLARH 0X0D
//#define XXCLADWYHJ 0X0E


////DXXT数据0X48
//#define DXXTKJB 0X01
//#define DXXTFZB 0X02
//#define DXXTAOS 0X03
//#define DXXTMPDU 0X04


//#define DXXT01 0x65
//#define DXXT02 0x66
//#define DXXT03 0x67

///////////////////////子子包////////////////////////
//星间网络管理包空间包
#define XXWL001 0x01
#define XXWL002 0x02
#define XXWL003 0x03
#define XXWL004 0x04
#define XXWL005 0x05
#define XXWL006 0x06
#define XXWL007 0x07
#define XXWL008 0x08
#define XXWL009 0x09
#define XXWL010 0x0A
#define XXWL011 0x0B
#define XXWL012 0X0C
#define XXWL013 0X0D
#define XXWL014 0X0E
#define XXWL015 0X0F
#define XXWL016 0X10
#define XXWL017 0X11
#define XXWL018 0x12
#define XXWL019 0x13
#define XXWL020 0X14
#define XXWL021 0X15
#define XXWL022 0X16
#define XXWL023 0X17
#define XXWL024 0X18
//XXCL数据空间包
////DXXT空间包
//#define DXXT201 0XC9//201
//#define DXXT202 0XCA//202
//#define DXXT203 0XCB//203
//#define DXXT204 0XCC//204
//#define DXXT205 0XCD//205
//#define DXXT206 0XCE//206
//#define DXXT207 0XCF//207
//#define DXXT208 0XD0//208
//#define DXXT025 0X19//025
//#define DXXT026 0X1A//026
struct Flags{
  unsigned int zflag,zflag2,bflag,bflag2,hflag,hflag2;
  bool headflag ;
  Flags():zflag(0),zflag2(0),bflag(0),bflag2(0),hflag(0),hflag2(0),headflag(true){};
};
#define DLL_API extern "C" __declspec(dllimport)

DLL_API int DeCompressMap(unsigned char *pCompress,unsigned int lCompressLength,unsigned int *lDeCompressLength,unsigned char *pDeCompress,char *pDecErrorDes);

class DealSourcePackage : public QObject
{
    Q_OBJECT
public:
    explicit DealSourcePackage(UnPack *unpack, QObject *parent = nullptr);

    //源包的内存开辟与释放
    void initDealSourcePackage(struct SourceStream *_obtainedSourceStream, long long BUFFSIZE);
    void freeSourcePackage(struct SourceStream *_obtainedSourceStream);
    //结构体内存开辟与释放
    void initDealCompressedStream(struct compressedStream *_comZXGC, struct compressedStream *_comRWSJ, struct compressedStream *_comDKCB,
                                  struct compressedStream *_comDKZCB, struct compressedStream *_comDDDPD, struct compressedStream *_comDDDB,
                                  struct compressedStream *_comXJCS, struct compressedStream *_comJGCS, struct compressedStream *_comJGYY,
                                  struct compressedStream *_comSSZXGC, struct compressedStream *_comSSRWSJ, struct compressedStream *_comSSDKCB,
                                  struct compressedStream *_comSSDKZCB, struct compressedStream *_comSSDDDPD, struct compressedStream *_comSSDDDB,
                                  struct compressedStream *_comSSXJCS, struct compressedStream *_comSSJGYY,long long BUFFSIZE);
    void freeCompressedStream(struct compressedStream *_comZXGC, struct compressedStream *_comRWSJ, struct compressedStream *_comDKCB,
                              struct compressedStream *_comDKZCB, struct compressedStream *_comDDDPD, struct compressedStream *_comDDDB,
                              struct compressedStream *_comXJCS, struct compressedStream *_comJGCS, struct compressedStream *_comJGYY,
                              struct compressedStream *_comSSZXGC, struct compressedStream *_comSSRWSJ, struct compressedStream *_comSSDKCB,
                              struct compressedStream *_comSSDKZCB, struct compressedStream *_comSSDDDPD, struct compressedStream *_comSSDDDB,
                              struct compressedStream *_comSSXJCS, struct compressedStream *_comSSJGYY);

    void initDealStream(struct compressedStream *_comSSXWGC, struct compressedStream *_comXWGC, struct compressedStream *_comGY,
                        struct compressedStream *_comJG, struct compressedStream *_comJG100, struct compressedStream *_comXSCL,long long BUFFSIZE);
    void freeStream(struct compressedStream *_comSSXWGC, struct compressedStream *_comXWGC, struct compressedStream *_comGY,
                    struct compressedStream *_comJG, struct compressedStream *_comJG100, struct compressedStream *_comXSCL);
    //源包数据，源包长度 EPDU数据
    int dealRWSJPackage(unsigned char* _strRWSJ,int _RWSJlen,struct compressedStream *_comRWSJ,struct SourceStream *_obtainedSourceStream,unsigned char* _RWSJout,int *rmlen,bool state,unsigned int *packnumid,unsigned int *ddztid,unsigned int *dkztid);
    int dealDKCBPackage(unsigned char* _strDKCB,int _DKCBlen,struct compressedStream *_comDKCB,struct SourceStream *_obtainedSourceStream,unsigned char* _DKCBout,unsigned char* _DKCB2711out,int *rmlen,bool state,unsigned int *packnumid,unsigned int *cbid);
    int dealDDDPDPackage(unsigned char* _strDDDPD,int _DDDPDlen,struct compressedStream *_comDDDPD,struct SourceStream *_obtainedSourceStream,unsigned char* _DDDPDout,unsigned char* _DDDPDKCout,int *rmlen,bool state,unsigned int *packnumid,unsigned int *dddpdkclen,unsigned int *pdid,unsigned int *kcid);
    int dealDDDBPackage(unsigned char* _strDDDB,int _DDDBlen,struct compressedStream *_comDDDB,struct SourceStream *_obtainedSourceStream,unsigned char* _DDDBout,unsigned char* _DDDB2711out,int *rmlen,bool state,unsigned int *packnumid,unsigned int *dddbid);
    int dealDKZCBPackage(unsigned char* _strDKZCB,int _DKZCBlen,struct compressedStream *_comDKZCB,struct SourceStream *_obtainedSourceStream,unsigned char* _DKZCBout,unsigned char* _DKZCB2711out,int *rmlen,bool state,unsigned int *packnumid,unsigned int *zcbid);

    void dealZXGCPackage(unsigned char* _strZXGC,int _ZXGClen,struct compressedStream *_comZXGC,struct SourceStream *_obtainedSourceStream,unsigned char* _ZXGCout,int *rmlen,bool state);
    void dealXJCSPackage(unsigned char* _strXJCS,int _XJCSlen,struct compressedStream *_comXJCS,struct SourceStream *_obtainedSourceStream,unsigned char* _XJCSout,int *rmlen,bool state,unsigned int *packnumid);
    void dealJGCSPackage(unsigned char* _strJGCS,int _JGCSlen,struct compressedStream *_comJGCS,struct SourceStream *_obtainedSourceStream,unsigned char* _JGCSout,int *rmlen,unsigned int *packnumid);
    void dealJGYYPackage(unsigned char* _strJGYY,int _JGYYlen,struct compressedStream *_comJGYY,struct SourceStream *_obtainedSourceStream,unsigned char* _JGYYout,int *rmlen,bool state,unsigned int *packnumid);

    //l 7.5修改
    //增加三个行显示参数
    int dealGYPackage(unsigned char* _strGY,int _GYlen,struct compressedStream *_comGY,unsigned char* _GYout,unsigned char* GYout,unsigned char * GY21out,unsigned char * GY41out,int *rmlen,int Pack_flag,unsigned int *packnumid,struct RZid *rzid);
    int dealJGPackage(unsigned char* _strJG,int _JGlen,struct compressedStream *_comJG,unsigned char* _JGout,unsigned char * JGout,int *rmlen,unsigned int *packnumid,struct RZid *rzid);

    /*****************************************************************************************
     * 此处需要修改第三层解包函数，一个是连续性判断时候，行计数有问题，一个是需要拿到数据长度，返回值需要有int
     * 1.int dealXSCLPackage  难点是XSCL数据类型太多了，不知道时分开发送还是一起发送，暂时先留着，询问清楚之后再写
     *********************************************************************************************/
    void dealXSCLPackage(unsigned char* _strXSCL,int _XSCLlen,struct compressedStream *_comXSCL,unsigned char* _XSCLout,int *rmlen,int Pack_flag,unsigned int *packnumid,struct RZid *rzid);
    void dealJG100Package(unsigned char* _strJG100,int _JG100len,struct compressedStream *_comJG100,unsigned char* _JG100out,int *rmlen,unsigned int *packnumid,struct RZid *rzid);


    //缺省 询问数据格式后如果与星上处理数据相同可并入xscl
    void dealXWGCPackage(unsigned char* _strXWGC,int _XWGClen,struct compressedStream *_comXWGC,unsigned char* _XWGCout,int *rmlen,int Pack_flag,unsigned int *packnumid,struct RZid *rzid);

    void undddpd(unsigned char* _strDDDPD,int _DDDPDlen,struct compressedStream *_comDDDPD,unsigned char* _DDDPDout,int *rmlen);

    int judge(unsigned char *Inputcode,int Inputlength,unsigned int *sumpack,int *packflag,int *frameflag);
    int continuejudge(unsigned char *Inputcode,int Inputlength,int imagetypeflag,unsigned int *lineid);
    int continuejudgejgcj(unsigned char *Inputcode,int Inputlength,int imagetypeflag);

    int continuejudgegy(unsigned char *Inputcode,int Inputlength,int imagetypeflag,unsigned int *lineid);
    int continuejudgejg(unsigned char *Inputcode,int Inputlength,int imagetypeflag,unsigned int *lineid);
    int continuejudgejg100(unsigned char *Inputcode,int Inputlength,int imagetypeflag,unsigned int *lineid);
    int continuejudgexscl(unsigned char *Inputcode,int Inputlength,int imagetypeflag,unsigned int *lineid);

    UnPack     *unpack;
 //public:  int	ZXGCframeNo ,RWSJframeNo ,DKCBframeNo , DKZCBframeNo , DDDPDframeNo , DDDBframeNo , XJCSframeNo , JGCSframeNo , JGYYframeNo ;//代表其为本文件第几个对应的压缩码流数据，序号
    //int dataType=-1;

//    int typeflag;
    struct Flags flags_gy,flags_jg,flags_zt,flags_xscl;

signals:



//private:

     //__int64 iShiftLenZXGC = 0, iShiftLenRWSJ = 0, iShiftLenDKCB = 0, iShiftLenDKZCB = 0, iShiftLenDDDPD = 0, iShiftLenDDDB = 0, iShiftLenXJCS = 0, iShiftLenJGCS = 0, iShiftLenJGYY = 0;//iSumLenRHW本小轮已处理长度



};



#endif // DEALSOURCEPACKAGE_H
