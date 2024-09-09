
#include "dealsourcepackage.h"
#include "mainwindow.h"
#include "myInclude.h"

#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include <direct.h>
#include <QString>



extern char outputpathLog[fileNameLen];   //输出日志路径

extern char outputpath2711package[fileNameLen]; //输出2711源包数据路径
extern char outputpath2711sub[fileNameLen]; //输出2711子包数据路径
extern char outputpath2711subsub[fileNameLen]; //子子包路径

DealSourcePackage::DealSourcePackage(UnPack *unpack, QObject *parent) : QObject(parent), unpack(unpack)
{
    //unpack = new UnPack;
}


//初始化压缩码流参数，切记调用此函数后一定要后面调用freeCompressedStream!!
void DealSourcePackage::initDealCompressedStream(struct compressedStream *_comZXGC, struct compressedStream *_comRWSJ, struct compressedStream *_comDKCB,
                                                 struct compressedStream *_comDKZCB, struct compressedStream *_comDDDPD, struct compressedStream *_comDDDB,
                                                 struct compressedStream *_comXJCS, struct compressedStream *_comJGCS, struct compressedStream *_comJGYY,
                                                 struct compressedStream *_comSSZXGC, struct compressedStream *_comSSRWSJ, struct compressedStream *_comSSDKCB,
                                                 struct compressedStream *_comSSDKZCB, struct compressedStream *_comSSDDDPD, struct compressedStream *_comSSDDDB,
                                                 struct compressedStream *_comSSXJCS, struct compressedStream *_comSSJGYY,long long BUFFSIZE)
{
        _comZXGC->ilen = _comRWSJ->ilen= _comDKCB->ilen = _comDKZCB->ilen = _comDDDPD->ilen = _comDDDB->ilen = _comXJCS->ilen = _comJGCS->ilen = _comJGYY->ilen = 0;
        _comZXGC->frameNum = _comRWSJ->frameNum = _comDKCB->frameNum = _comDKZCB->frameNum = _comDDDPD->frameNum = _comDDDPD->frameNum = _comDDDB->frameNum = _comXJCS->frameNum = _comJGCS->frameNum = _comJGYY->frameNum = 0;

        _comZXGC->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comRWSJ->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comDKCB->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comDKZCB->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comDDDPD->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comDDDB->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comXJCS->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comJGCS->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comJGYY->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));

        _comSSZXGC->ilen = _comSSRWSJ->ilen= _comSSDKCB->ilen = _comSSDKZCB->ilen = _comSSDDDPD->ilen = _comSSDDDB->ilen = _comSSXJCS->ilen  = _comJGYY->ilen = 0;
        _comSSZXGC->frameNum = _comSSRWSJ->frameNum = _comSSDKCB->frameNum = _comSSDKZCB->frameNum = _comSSDDDPD->frameNum = _comSSDDDPD->frameNum = _comSSDDDB->frameNum = _comSSXJCS->frameNum  = _comSSJGYY->frameNum = 0;

        _comSSZXGC->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comSSRWSJ->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comSSDKCB->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comSSDKZCB->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comSSDDDPD->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comSSDDDB->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comSSXJCS->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        //_comJGCS->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
        _comSSJGYY->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));

        if (NULL == _comZXGC->img && NULL == _comRWSJ->img && NULL == _comDKCB->img && NULL == _comDKZCB->img && NULL == _comDDDPD->img && NULL == _comDDDB->img && NULL == _comXJCS->img && NULL == _comJGCS->img && NULL == _comJGYY->img &&NULL == _comSSZXGC->img && NULL == _comSSRWSJ->img && NULL == _comSSDKCB->img && NULL == _comSSDKZCB->img && NULL == _comSSDDDPD->img && NULL == _comSSDDDB->img && NULL == _comSSXJCS->img  && NULL == _comSSJGYY->img)
        {
            MainWindow::fakeUi->setLinetext(QString("check: failed to apply for img space!!\n"));

            return;
        }

    return;
}

void DealSourcePackage::freeCompressedStream(struct compressedStream *_comZXGC, struct compressedStream *_comRWSJ, struct compressedStream *_comDKCB,
                                             struct compressedStream *_comDKZCB, struct compressedStream *_comDDDPD, struct compressedStream *_comDDDB,
                                             struct compressedStream *_comXJCS, struct compressedStream *_comJGCS, struct compressedStream *_comJGYY,
                                             struct compressedStream *_comSSZXGC, struct compressedStream *_comSSRWSJ, struct compressedStream *_comSSDKCB,
                                             struct compressedStream *_comSSDKZCB, struct compressedStream *_comSSDDDPD, struct compressedStream *_comSSDDDB,
                                             struct compressedStream *_comSSXJCS, struct compressedStream *_comSSJGYY)
{
    free(_comZXGC->img);_comZXGC->img =NULL;
    free(_comRWSJ->img);_comRWSJ->img = NULL;
    free(_comDKCB->img);_comDKCB->img =NULL;
    free(_comDKZCB->img);_comDKZCB->img =NULL;
    free(_comDDDPD->img);_comDDDPD->img =NULL;
    free(_comDDDB->img);_comDDDB->img =NULL;
    free(_comXJCS->img);_comDDDB->img =NULL;
    free(_comJGCS->img);_comJGCS->img =NULL;
    free(_comJGYY->img);_comJGYY->img= NULL;
    free(_comSSZXGC->img);_comSSZXGC->img=NULL;
    free(_comSSRWSJ->img);_comSSRWSJ->img=NULL;
    free(_comSSDKCB->img);_comSSDKCB->img =NULL;
    free(_comSSDKZCB->img);_comSSDKZCB->img=NULL;
    free(_comSSDDDPD->img);_comSSDDDPD->img =NULL;
    free(_comSSDDDB->img);_comSSDDDB->img =NULL;
    free(_comSSXJCS->img);_comSSXJCS->img = NULL;
    //free(_comJGCS->img);
    free(_comSSJGYY->img);_comSSJGYY->img = NULL;

    return;
}

void DealSourcePackage::initDealStream(compressedStream *_comSSXWGC, compressedStream *_comXWGC, compressedStream *_comGY, compressedStream *_comJG, compressedStream *_comJG100, compressedStream *_comXSCL, long long BUFFSIZE)
{
    _comSSXWGC->ilen = _comXWGC->ilen= _comJG->ilen = _comGY->ilen = _comJG100->ilen = _comXSCL->ilen = 0;
    _comSSXWGC->frameNum = _comXWGC->frameNum = _comJG->frameNum = _comGY->frameNum = _comJG100->frameNum = _comXSCL->frameNum = 0;

    _comSSXWGC->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    _comXWGC->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    _comGY->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    _comJG->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    _comJG100->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    _comXSCL->img = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));

    if (NULL == _comSSXWGC->img && NULL == _comXWGC->img && NULL == _comGY->img && NULL == _comJG->img && NULL == _comJG100->img && NULL == _comXSCL->img)
    {
        MainWindow::fakeUi->setLinetext(QString("check: failed to apply for img space!!\n"));

        return;
    }

    return;
}

void DealSourcePackage::freeStream(compressedStream *_comSSXWGC, compressedStream *_comXWGC, compressedStream *_comGY, compressedStream *_comJG, compressedStream *_comJG100, compressedStream *_comXSCL)
{
    free(_comSSXWGC->img);_comSSXWGC->img =NULL;
    free(_comXWGC->img);_comXWGC->img = NULL;
    free(_comGY->img);_comGY->img =NULL;
    free(_comJG->img);_comJG->img =NULL;
    free(_comJG100->img);_comJG100->img =NULL;
    free(_comXSCL->img);_comXSCL->img =NULL;

    return;

}

//使用完initDealSourcePackage函数后一定要freeSourcePackage
void DealSourcePackage::initDealSourcePackage(struct SourceStream *_obtainedSourceStream, long long BUFFSIZE)
{
    _obtainedSourceStream->ZXGCdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->RWSJdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->DKCBdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->DKZCBdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->DDDPDdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->DDDBdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->XJCSdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->JGCSdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->JGYYdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));

    _obtainedSourceStream->SSZXGCdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->SSRWSJdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->SSDKCBdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->SSDKZCBdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->SSDDDPDdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->SSDDDBdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->SSXJCSdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
//    _obtainedSourceStream->SSJGCSdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));
    _obtainedSourceStream->SSJGYYdata = (unsigned char*)malloc(2 * BUFFSIZE * sizeof(unsigned char));

    if (NULL == _obtainedSourceStream->ZXGCdata && NULL == _obtainedSourceStream->RWSJdata && NULL == _obtainedSourceStream->DKCBdata &&
        NULL == _obtainedSourceStream->DKZCBdata && NULL == _obtainedSourceStream->DDDPDdata && NULL == _obtainedSourceStream->DDDBdata &&
        NULL == _obtainedSourceStream->XJCSdata && NULL == _obtainedSourceStream->JGCSdata && NULL == _obtainedSourceStream->JGYYdata&&NULL == _obtainedSourceStream->SSZXGCdata && NULL == _obtainedSourceStream->SSRWSJdata && NULL == _obtainedSourceStream->SSDKCBdata &&
            NULL == _obtainedSourceStream->SSDKZCBdata && NULL == _obtainedSourceStream->SSDDDPDdata && NULL == _obtainedSourceStream->SSDDDBdata &&
            NULL == _obtainedSourceStream->SSXJCSdata && NULL == _obtainedSourceStream->SSJGYYdata)
    {
        MainWindow::fakeUi->setLinetext(QString("check: failed to apply for sourcePackage space!!\n"));
        return;
    }

    return;
}

void DealSourcePackage::freeSourcePackage(struct SourceStream *_obtainedSourceStream)
{
    free(_obtainedSourceStream->ZXGCdata);_obtainedSourceStream->ZXGCdata =NULL;
    free(_obtainedSourceStream->RWSJdata);_obtainedSourceStream->RWSJdata = NULL;
    free(_obtainedSourceStream->DKCBdata);_obtainedSourceStream->DKCBdata = NULL;
    free(_obtainedSourceStream->DKZCBdata);_obtainedSourceStream->DKZCBdata = NULL;
    free(_obtainedSourceStream->DDDPDdata);_obtainedSourceStream->DDDPDdata = NULL;
    free(_obtainedSourceStream->DDDBdata);_obtainedSourceStream->DDDBdata =NULL;
    free(_obtainedSourceStream->XJCSdata);_obtainedSourceStream->XJCSdata=NULL;
    free(_obtainedSourceStream->JGCSdata);_obtainedSourceStream->JGCSdata=NULL;
    free(_obtainedSourceStream->JGYYdata);_obtainedSourceStream->JGYYdata=NULL;
    free(_obtainedSourceStream->SSZXGCdata);_obtainedSourceStream->SSZXGCdata=NULL;
    free(_obtainedSourceStream->SSRWSJdata);_obtainedSourceStream->SSRWSJdata = NULL;
    free(_obtainedSourceStream->SSDKCBdata);_obtainedSourceStream->SSDKCBdata=NULL;
    free(_obtainedSourceStream->SSDKZCBdata);_obtainedSourceStream->SSDKZCBdata =NULL;
    free(_obtainedSourceStream->SSDDDPDdata);_obtainedSourceStream->SSDDDPDdata =NULL;
    free(_obtainedSourceStream->SSDDDBdata);_obtainedSourceStream->SSDDDBdata =NULL;
    free(_obtainedSourceStream->SSXJCSdata);_obtainedSourceStream->SSXJCSdata = NULL;
    //free(_obtainedSourceStream->JGCSdata);
    free(_obtainedSourceStream->SSJGYYdata);_obtainedSourceStream->SSJGYYdata = NULL;
    return;
}


//int DealSourcePackage::dealRWSJPackage(unsigned char *_strRWSJ, int _RWSJlen, compressedStream *_comRWSJ, SourceStream *_obtainedSourceStream, unsigned char *_RWSJout,int *rmlen,bool state,unsigned int *idnum)
int DealSourcePackage::dealRWSJPackage(unsigned char *_strRWSJ, int _RWSJlen, compressedStream *_comRWSJ, SourceStream *_obtainedSourceStream, unsigned char *_RWSJout,int *rmlen,bool state,unsigned int *packnumid,unsigned int *ddztid,unsigned int *dkztid)
{
    __int64         temp_XJSJ = 0,temp_DDZT=0,temp_DKZT = 0,temp_XMSJ= 0,temp_GXTLC=0,temp_XXCLA=0,temp_NBYK=0,temp_XXCL=0,temp_DXXT = 0,temp_XXCLB =0,temp_RWGH =0;
    __int64         temp_Res_1 =0,temp_SXQD=0,temp_XJSC = 0,temp_SJGB=0,temp_TXCSYC=0,temp_TXCSSC=0;

    __int64         temp_DDZTsub=0,temp_DKZTsub = 0;
    __int64         temp_XXCLADB=0,temp_XXCLADPD=0,temp_XXCLACB=0,temp_XXCLAZCB=0,temp_XXCLARH=0,temp_XXCLADWYHJ=0;
    __int64         temp_XXCLADBDSP=0,temp_XXCLADPDDSP=0,temp_XXCLACBDSP=0,temp_XXCLAZCBDSP=0;
    __int64         temp_XXCLADBBQT=0,temp_XXCLADPDBQT=0,temp_XXCLACBBQT=0,temp_XXCLAZCBBQT=0;

    __int64         temp_XJWLKJB=0,temp_XJWLFZB=0,temp_XJWLAOS=0,temp_XJWLMPDU=0;
    __int64         temp_DXXTKJB=0,temp_DXXTFZB=0,temp_DXXTAOS=0,temp_DXXTMPDU=0;
    //目标备选点根据目标波段类型划分，一共5种
    //备选点辅助行  1种
    //101 102 103 3种
    __int64         temp_XXCLBXD=0,temp_XXCLDKCB=0,temp_XXCLDKZCB=0,temp_XXCLDDDB=0,temp_XXCLDDDPD=0,temp_XXCLDDDPDKC=0;
    __int64         temp_XXCL101=0,temp_XXCL102=0,temp_XXCL103=0;


    __int64         temp_DKSXQD=0,temp_DDSXQD=0,temp_DKSXQDFZ=0,temp_DDSXQDFZ=0;
    __int64         temp_DXXT201=0,temp_DXXT202=0,temp_DXXT203=0,temp_DXXT204=0,temp_DXXT205=0,temp_DXXT206=0,temp_DXXT207=0,temp_DXXT208=0,temp_DXXT025=0,temp_DXXT026=0;


//    __int64         temp_XMA=0,temp_XMB=0,temp_XMC=0,temp_XMD=0;

    int cysumlen=0;
    //为2711包分配空间
    __int64 BUFFSIZE = (128* 1024 * 1024);
    //unsigned char	*XJSJout= NULL, *DDZTout= NULL,*DKZTout= NULL,*XMSJout= NULL,*GXTLCout= NULL,*XXCLAout= NULL,*NBYKout= NULL,*XXCLout= NULL,*DXXTout= NULL,*XXCLBout= NULL,*RWGHout= NULL;
    unsigned char	*XJSJout= NULL, *DDZTout= NULL,*DKZTout= NULL,*XMSJout= NULL,*GXTLCout= NULL,*NBYKout= NULL,*XXCLout= NULL,*DXXTout= NULL,*XXCLBout= NULL,*RWGHout= NULL;

    unsigned char	*Res_1out= NULL, *SXQDout= NULL,*XJSCout= NULL,*SJGBout= NULL,*TXCSYCout= NULL,*TXCSSCout= NULL;

    unsigned char *DDZTsubout= NULL,*DKZTsubout= NULL;
    unsigned char *XXCLADB=NULL,*XXCLADPD=NULL,*XXCLACB=NULL,*XXCLAZCB=NULL,*XXCLARH=NULL,*XXCLADWYHT=NULL;
    unsigned char *XXCLADBDSP=NULL,*XXCLADPDDSP=NULL,*XXCLACBDSP=NULL,*XXCLAZCBDSP=NULL;
    unsigned char *XXCLADBBQT=NULL,*XXCLADPDBQT=NULL,*XXCLACBBQT=NULL,*XXCLAZCBBQT=NULL;

    unsigned char *XJWLKJB=NULL,*XJWLFZB=NULL,*XJWLAOS=NULL,*XJWLMPDU=NULL;
    unsigned char *XXCLBXD=NULL,*XXCLDKCB=NULL,*XXCLDKZCB=NULL,*XXCLDDDB=NULL,*XXCLDDDPD=NULL,*XXCLDDDPDKC=NULL;
    unsigned char *XXCL101=NULL,*XXCL102=NULL,*XXCL103=NULL;

    unsigned char *DKSXQD=NULL,*DDSXQD=NULL,*DKSXQDFZ=NULL,*DDSXQDFZ=NULL;

    unsigned char *DXXTKJB=NULL,*DXXTFZB=NULL,*DXXTAOS=NULL,*DXXTMPDU=NULL;
    unsigned char *DXXT201=NULL,*DXXT202=NULL,*DXXT203=NULL,*DXXT204=NULL,*DXXT205=NULL,*DXXT206=NULL,*DXXT207=NULL,*DXXT025=NULL,*DXXT208=NULL,*DXXT026=NULL;


    //unsigned char *XMA=NULL,*XMB=NULL,*XMC=NULL,*XMD=NULL;

//    unsigned int rwsjnum = *idnum;  //该参数用于判断连续性

    XJSJout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    DDZTout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    DKZTout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    XMSJout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    GXTLCout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    //XXCLAout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    NBYKout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    XXCLout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    DXXTout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    XXCLBout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    RWGHout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    Res_1out = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    SXQDout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    XJSCout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    SJGBout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    TXCSYCout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    TXCSSCout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));   //16

    DDZTsubout = (unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DKZTsubout = (unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));

    XXCLADB=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLADPD=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLACB=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLAZCB=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));

    XXCLADBBQT=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLADPDBQT=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLACBBQT=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLAZCBBQT=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));

    XXCLARH=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLADWYHT=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));;
    XXCLADBDSP=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLADPDDSP=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLACBDSP=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLAZCBDSP=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));

    XJWLKJB=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XJWLFZB=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XJWLAOS=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XJWLMPDU=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));

    DXXTKJB=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DXXTFZB=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DXXTAOS=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DXXTMPDU=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));


    XXCLBXD=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLDKZCB=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLDKCB=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLDDDB=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLDDDPD=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCLDDDPDKC=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));  //46
    XXCL101=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCL102=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    XXCL103=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));


    DXXT201=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DXXT202=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DXXT203=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DXXT204=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DXXT205=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DXXT206=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DXXT207=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DXXT208=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DXXT025=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DXXT026=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));

    DKSXQD=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DDSXQD=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DKSXQDFZ=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    DDSXQDFZ=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));   //60
//    XMA=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
//    XMD=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
//    XMC=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
//    XMD=(unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));

    //补充完整
    if(NULL==TXCSSCout)
    {
        qDebug()<<"内存分配失败111";
    }



    int EPDUflag;
    int iStartPos1 = 0;

    unsigned int flag;
    int    type = 0x00;
    int xxclatype=0x00;
    int    datalen = 0;
    int deallen = 0;
    int subtype=0x00;
    int subsubtype=0x00;

    char fileName[fileNameLen];

    unsigned int rwsjpacknum = *packnumid;
    unpack->unpack1(_strRWSJ, _RWSJlen, _comRWSJ->img, &(_comRWSJ->ilen), outputpathLog,state,&rwsjpacknum);   //img为该buf中的EPDU数据
    *packnumid = rwsjpacknum;
//    unpack->unpack(_strRWSJ, _RWSJlen, _comRWSJ->img, &(_comRWSJ->ilen), outputpathLog,state);   //img为该buf中的EPDU数据
    cysumlen = _comRWSJ->ilen+*rmlen;
    memcpy(_RWSJout+*rmlen,_comRWSJ->img,_comRWSJ->ilen);   //考虑残余数据的情况   iShiftlen如何变
    EPDUflag=2; //任务数据源包
    //检测到F5F6EB90  4032 第一包数据一定在
    if(UnPack::barkDetect(_RWSJout,cysumlen,0,&iStartPos1))
    {

        type= _RWSJout[iStartPos1+6];
        switch (type)
        {
        //40
        case XJSJ_S:
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(XJSJout,_RWSJout+iStartPos1,datalen+12);
            subtype=_RWSJout[iStartPos1 + 11];
            switch (subtype)
            {
            case (KJBXY_F):
                memcpy(XJWLKJB,_RWSJout+iStartPos1+10,datalen);
                temp_XJWLKJB+=datalen;
                break;
            case (FZBXY_F):
                memcpy(XJWLFZB,_RWSJout+iStartPos1+10,datalen);
                temp_XJWLFZB+=datalen;
                break;
            case (AOSXY_F):
                memcpy(XJWLAOS,_RWSJout+iStartPos1+10,datalen);
                temp_XJWLAOS+=datalen;
                break;
            case (MPDUXY_F):
                memcpy(XJWLMPDU,_RWSJout+iStartPos1+10,datalen);
                temp_XJWLMPDU+=datalen;
                break;
            default:
                break;
            }
            temp_XJSJ+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case DDZT_S:  //41
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(DDZTout,_RWSJout+iStartPos1,datalen+12);
            memcpy(DDZTsubout,_RWSJout+iStartPos1+12,63);
            temp_DDZT+=datalen+12;
            temp_DDZTsub += 63;
            deallen = iStartPos1+datalen+12;
            break;
        case DKZT_S: //42
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(DKZTout,_RWSJout+iStartPos1,datalen+12);
            memcpy(DKZTsubout,_RWSJout+iStartPos1+12,63);
            temp_DKZT+=datalen+12;
            temp_DKZTsub += 63;
            deallen = iStartPos1+datalen+12;
            break;
        case XMSJ_S:  //43
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(XMSJout,_RWSJout+iStartPos1,datalen+12);
            temp_XMSJ+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case GMTLC_S:  //44
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(GXTLCout,_RWSJout+iStartPos1,datalen+12);
            temp_GXTLC+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case XXCLA_S:  //45
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            //memcpy(XXCLAout,_RWSJout+iStartPos1,datalen+12);
            //xxclatype = _RWSJout[iStartPos1+11];
            xxclatype=(_RWSJout[iStartPos1 + 10] <<8 ) | _RWSJout[iStartPos1+11];
            switch (xxclatype) {
            case 0x0905:
                memcpy(XXCLADB,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLADB=temp_XXCLADB+datalen+12;
                break;
            case 0x0A05:
                memcpy(XXCLADPD,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLADPD=temp_XXCLADPD+datalen+12;
                break;
            case 0x0B05:
                memcpy(XXCLACB,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLACB=temp_XXCLACB+datalen+12;
                break;
            case 0x0C05:
                memcpy(XXCLAZCB,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLAZCB=temp_XXCLAZCB+datalen+12;
                break;
            case 0x0933:
                memcpy(XXCLADBBQT,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLADBBQT=temp_XXCLADBBQT+datalen+12;
                break;
            case 0x0A33:
                memcpy(XXCLADPDBQT,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLADPDBQT=temp_XXCLADPDBQT+datalen+12;
                break;
            case 0x0B33:
                memcpy(XXCLACBBQT,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLACBBQT=temp_XXCLACBBQT+datalen+12;
                break;
            case 0x0C33:
                memcpy(XXCLAZCBBQT,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLAZCBBQT=temp_XXCLAZCBBQT+datalen+12;
                break;
            case 0x0505:
                memcpy(XXCLADBDSP,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLADBDSP=temp_XXCLADBDSP+datalen+12;
                break;
            case 0x0605:
                memcpy(XXCLADPDDSP,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLADPDDSP=temp_XXCLADPDDSP+datalen+12;
                break;
            case 0x0705:
                memcpy(XXCLACBDSP,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLACBDSP=temp_XXCLACBDSP+datalen+12;
                break;
            case 0x0805:
                memcpy(XXCLAZCBDSP,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLAZCBDSP= temp_XXCLAZCBDSP+datalen+12;
                break;
            case 0x0D05:
                memcpy(XXCLARH,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLARH=temp_XXCLARH+datalen+12;
                break;
            case 0x0E05:
                memcpy(XXCLADWYHT,_RWSJout+iStartPos1,datalen+12);
                temp_XXCLADWYHJ=temp_XXCLADWYHJ+datalen+12;
                break;
            default:
                break;
            }
            temp_XXCLA+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case NBYK_S: //46
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(NBYKout,_RWSJout+iStartPos1,datalen+12);
            temp_NBYK+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case XXCL_S:  //47
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(XXCLout,_RWSJout+iStartPos1,datalen+12);
            subtype=_RWSJout[iStartPos1+7];
            switch (subtype)
            {
            case 0X88:
                subsubtype=(_RWSJout[iStartPos1+12]<<8)|_RWSJout[iStartPos1+13];
                switch(subsubtype)
                {
                case 0x0c65:
                    memcpy(XXCL101,_RWSJout+iStartPos1,datalen+12);
                    temp_XXCL101+=datalen+12;
                    break;
                case 0x0c66:
                    memcpy(XXCL102,_RWSJout+iStartPos1,datalen+12);
                    temp_XXCL102+=datalen+12;
                    break;
                case 0x0c67:
                    memcpy(XXCL103,_RWSJout+iStartPos1,datalen+12);
                    temp_XXCL103+=datalen+12;
                    break;
                default:
                    if(_RWSJout[iStartPos1+11]==0x82){
                        memcpy(XXCLBXD,_RWSJout+iStartPos1,288);
                        temp_XXCLBXD+=288;

                    }
                    break;
                }
//                memcpy(XXCLBXD,_RWSJout+iStartPos1,288);
//                temp_XXCLBXD+=288;
//                break;
            case 17:
                memcpy(XXCLDKCB,_RWSJout+iStartPos1,920);
                temp_XXCLDKCB+=920;
                break;
            case 0x21:
                memcpy(XXCLDDDB,_RWSJout+iStartPos1,920);
                temp_XXCLDDDB+=920;
                break;
            case 18:
                memcpy(XXCLDKZCB,_RWSJout+iStartPos1,920);
                temp_XXCLDKZCB+=920;
                break;
            case 0x22:
                memcpy(XXCLDDDPD,_RWSJout+iStartPos1,920);
                temp_XXCLDDDPD+=920;
                break;
            case 0x28:
                memcpy(XXCLDDDPDKC,_RWSJout+iStartPos1,920);
                temp_XXCLDDDPDKC+=920;
                break;
            default:
                break;

            }
            temp_XXCL+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case DXXT_S:  //48
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(DXXTout,_RWSJout+iStartPos1,datalen+12);
            subtype=_RWSJout[iStartPos1+11];
            switch (subtype)
            {
            case KJBXY_F :
                memcpy(DXXTKJB,_RWSJout+iStartPos1+10,datalen);
                temp_DXXTKJB+=datalen;
                break;
            case FZBXY_F:
                memcpy(DXXTFZB,_RWSJout+iStartPos1+10,datalen);
                temp_DXXTFZB+=datalen;
                break;
            case AOSXY_F:
                memcpy(DXXTAOS,_RWSJout+iStartPos1+10,datalen);
                temp_DXXTAOS+=datalen;
                break;
            case MPDUXY_F:
                memcpy(DXXTMPDU,_RWSJout+iStartPos1+10,datalen);
                temp_DXXTMPDU+=datalen;
                break;
            default:
                break;

            }
            temp_DXXT+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case XXCLB_S:  //49
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(XXCLBout,_RWSJout+iStartPos1,datalen+12);
            temp_XXCLB+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case RWGH_S: //4A
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(RWGHout,_RWSJout+iStartPos1,datalen+12);
            temp_RWGH+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case Res_1:  //4B
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(Res_1out,_RWSJout+iStartPos1,datalen+12);
            temp_Res_1+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case SXQD_S:  //4C
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(SXQDout,_RWSJout+iStartPos1,datalen+12);
            subtype = _RWSJout[iStartPos1+13];
            switch (subtype) {
            case 0x59:
                memcpy(DKSXQD,_RWSJout+iStartPos1+12,134);
                temp_DKSXQD+=134;
                break;
            case 0x5A:
                memcpy(DDSXQD,_RWSJout+iStartPos1+12,134);
                temp_DDSXQD+=134;
                break;
            case 0x5B:
                memcpy(DKSXQDFZ,_RWSJout+iStartPos1+12,172);
                temp_DKSXQDFZ+=172;
                break;
            case 0x5C:
                memcpy(DDSXQDFZ,_RWSJout+iStartPos1+12,172);
                temp_DDSXQDFZ+=172;
                break;
            default:
                break;
            }
            temp_SXQD+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case XJSC:  //4D
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(XJSCout,_RWSJout+iStartPos1,datalen+12);
            temp_XJSC+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case SJGB:  //4E
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(SJGBout,_RWSJout+iStartPos1,datalen+12);
            temp_SJGB+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case TXCSYC: //50
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(TXCSYCout,_RWSJout+iStartPos1,datalen+12);
            temp_TXCSYC+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        case TXCSSC:  //51
            datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
            memcpy(TXCSSCout,_RWSJout+iStartPos1,datalen+12);
            temp_TXCSSC+=datalen+12;
            deallen = iStartPos1+datalen+12;
            break;
        default:
            //qDebug()<<type<<"weizhiyuanbao";
            deallen=iStartPos1+4;
            break;
        }


        while (deallen+1304<=cysumlen)
        {
            flag = ((_RWSJout[deallen] << 24) | (_RWSJout[deallen+1] << 16) | (_RWSJout[deallen+2] << 8) |_RWSJout[deallen+3]) & 0xffffffff;
            datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
            if(flag == 0xF5F6EB90 && datalen<1291)
            {
                type = _RWSJout[deallen+6];


                switch (type)
                {
                //40
                case XJSJ_S:
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(XJSJout+temp_XJSJ,_RWSJout+deallen,datalen+12);
                    subtype=_RWSJout[deallen + 11];
                    switch (subtype)
                    {
                    case (KJBXY_F):
                        memcpy(XJWLKJB+temp_XJWLKJB,_RWSJout+deallen+10,datalen);
                        temp_XJWLKJB+=datalen;
                        break;
                    case (FZBXY_F):
                        memcpy(XJWLFZB+temp_XJWLFZB,_RWSJout+deallen+10,datalen);
                        temp_XJWLFZB+=datalen;
                        break;
                    case (AOSXY_F):
                        memcpy(XJWLAOS+temp_XJWLAOS,_RWSJout+deallen+10,datalen);
                        temp_XJWLAOS+=datalen;
                        break;
                    case (MPDUXY_F):
                        memcpy(XJWLMPDU+temp_XJWLMPDU,_RWSJout+deallen+10,datalen);
                        temp_XJWLMPDU+=datalen;
                        break;
                    default:
                        break;
                    }
                    temp_XJSJ+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                case DDZT_S:  //41
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(DDZTout+temp_DDZT,_RWSJout+deallen,datalen+12);
                    memcpy(DDZTsubout+temp_DDZTsub,_RWSJout+deallen+12,63);
                    temp_DDZT+=datalen+12;
                    temp_DDZTsub += 63;
                    deallen = deallen+datalen+12;
                    break;
                case DKZT_S: //42
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(DKZTout+temp_DKZT,_RWSJout+deallen,datalen+12);
                    memcpy(DKZTsubout+temp_DKZTsub,_RWSJout+deallen+12,63);
                    temp_DKZT+=datalen+12;
                    temp_DKZTsub += 63;
                    deallen = deallen+datalen+12;
                    break;
                case XMSJ_S:  //43
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(XMSJout+temp_XMSJ,_RWSJout+deallen,datalen+12);
                    temp_XMSJ+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                case GMTLC_S:  //44
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(GXTLCout+temp_GXTLC,_RWSJout+deallen,datalen+12);
                    temp_GXTLC+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                case XXCLA_S:  //45
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    //memcpy(XXCLAout+temp_XXCLA,_RWSJout+deallen,datalen+12);
                    //xxclatype =_RWSJout[deallen + 11];
                    xxclatype =(_RWSJout[deallen + 10] <<8 ) | _RWSJout[deallen+11];
                    switch (xxclatype) {
                    case 0x0905:
                        memcpy(XXCLADB+temp_XXCLADB,_RWSJout+deallen,datalen+12);
                        temp_XXCLADB+=(datalen+12);
                        break;
                    case 0x0A05:
                        memcpy(XXCLADPD+temp_XXCLADPD,_RWSJout+deallen,datalen+12);
                        temp_XXCLADPD+=(datalen+12);
                        break;
                    case 0x0B05:
                        memcpy(XXCLACB+temp_XXCLACB,_RWSJout+deallen,datalen+12);
                        temp_XXCLACB+=(datalen+12);
                        break;
                    case 0x0C05:
                        memcpy(XXCLAZCB+temp_XXCLAZCB,_RWSJout+deallen,datalen+12);
                        temp_XXCLAZCB+=(datalen+12);
                        break;
                    case 0x0933:
                        memcpy(XXCLADBBQT+temp_XXCLADBBQT,_RWSJout+deallen,datalen+12);
                        temp_XXCLADBBQT+=(datalen+12);
                        break;
                    case 0x0A33:
                        memcpy(XXCLADPDBQT+temp_XXCLADPDBQT,_RWSJout+deallen,datalen+12);
                        temp_XXCLADPDBQT+=(datalen+12);
                        break;
                    case 0x0B33:
                        memcpy(XXCLACBBQT+temp_XXCLACBBQT,_RWSJout+deallen,datalen+12);
                        temp_XXCLACBBQT+=(datalen+12);
                        break;
                    case 0x0C33:
                        memcpy(XXCLAZCBBQT+temp_XXCLAZCBBQT,_RWSJout+deallen,datalen+12);
                        temp_XXCLAZCBBQT+=(datalen+12);
                        break;
                    case 0x0505:
                        memcpy(XXCLADBDSP+temp_XXCLADBDSP,_RWSJout+deallen,datalen+12);
                        temp_XXCLADBDSP+=(datalen+12);
                        break;
                    case 0x0605:
                        memcpy(XXCLADPDDSP+temp_XXCLADPDDSP,_RWSJout+deallen,datalen+12);
                        temp_XXCLADPDDSP+=(datalen+12);
                        break;
                    case 0x0705:
                        memcpy(XXCLACBDSP+temp_XXCLACBDSP,_RWSJout+deallen,datalen+12);
                        temp_XXCLACBDSP+=(datalen+12);
                        break;
                    case 0x0805:
                        memcpy(XXCLAZCBDSP+temp_XXCLAZCBDSP,_RWSJout+deallen,datalen+12);
                        temp_XXCLAZCBDSP+=(datalen+12);
                        break;
                    case 0x0D05:
                        memcpy(XXCLARH+temp_XXCLARH,_RWSJout+deallen,datalen+12);
                        temp_XXCLARH+=(datalen+12);
                        break;
                    case 0x0E05:
                        memcpy(XXCLADWYHT+temp_XXCLADWYHJ,_RWSJout+deallen,datalen+12);
                        temp_XXCLADWYHJ+=(datalen+12);
                        break;
                    default:
                        break;
                    }
                    temp_XXCLA+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                case NBYK_S: //46
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(NBYKout+temp_NBYK,_RWSJout+deallen,datalen+12);
                    temp_NBYK+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                case XXCL_S:  //47
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(XXCLout+temp_XXCL,_RWSJout+deallen,datalen+12);
                    subtype=_RWSJout[deallen+7];
                    switch (subtype)
                    {
                    case 0x88:
                        //memcpy(XXCLBXD+temp_XXCLBXD,_RWSJout+deallen,288);
                        //temp_XXCLBXD+=288;
                        //break;
                        subsubtype=(_RWSJout[deallen+12]<<8)|_RWSJout[deallen+13];


                        switch(subsubtype)
                        {
                        case 0x0c65:
                            memcpy(XXCL101+temp_XXCL101,_RWSJout+deallen,datalen+12);
                            temp_XXCL101+=datalen+12;
                            break;
                        case 0x0c66:
                            memcpy(XXCL102+temp_XXCL102,_RWSJout+deallen,datalen+12);
                            temp_XXCL102+=datalen+12;
                            break;
                        case 0x0c67:
                            memcpy(XXCL103+temp_XXCL103,_RWSJout+deallen,datalen+12);
                            temp_XXCL103+=datalen+12;
                            break;
                        default:
                            if(_RWSJout[deallen+11]==0x82){
                                memcpy(XXCLBXD+temp_XXCLBXD,_RWSJout+deallen,288);
                                temp_XXCLBXD+=288;

                            }
                            break;
                        }
                    case 0x11:
                        memcpy(XXCLDKCB+temp_XXCLDKCB,_RWSJout+deallen,920);
                        temp_XXCLDKCB+=920;
                        break;
                    case 0x12:
                        memcpy(XXCLDKZCB+temp_XXCLDKZCB,_RWSJout+deallen,920);
                        temp_XXCLDKZCB+=920;
                        break;
                    case 0x21:
                        memcpy(XXCLDDDB+temp_XXCLDDDB,_RWSJout+deallen,920);
                        temp_XXCLDDDB+=920;
                        break;
                    case 0x22:
                        memcpy(XXCLDDDPD+temp_XXCLDDDPD,_RWSJout+deallen,920);
                        temp_XXCLDDDPD+=920;
                        break;
                    case 0x28:
                        memcpy(XXCLDDDPDKC+temp_XXCLDDDPDKC,_RWSJout+deallen,920);
                        temp_XXCLDDDPDKC=920;
                        break;
                    default:
                        break;
                    }
                    temp_XXCL+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                case DXXT_S:  //48
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(DXXTout+temp_DXXT,_RWSJout+deallen,datalen+12);
                    subtype=_RWSJout[deallen+11];
                    switch (subtype)
                    {
                    case KJBXY_F :
                        memcpy(DXXTKJB+temp_DXXTKJB,_RWSJout+deallen+10,datalen);
                        temp_DXXTKJB+=datalen;
                        break;
                    case FZBXY_F:
                        memcpy(DXXTFZB+temp_DXXTFZB,_RWSJout+deallen+10,datalen);
                        temp_DXXTFZB+=datalen;
                        break;
                    case AOSXY_F:
                        memcpy(DXXTAOS+temp_DXXTAOS,_RWSJout+deallen+10,datalen);
                        temp_DXXTAOS+=datalen;
                        break;
                    case MPDUXY_F:
                        memcpy(DXXTMPDU+temp_DXXTMPDU,_RWSJout+deallen+10,datalen);
                        temp_DXXTMPDU+=datalen;
                        break;
                    default:
                        break;
                    }
                    temp_DXXT+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                case XXCLB_S:  //49
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(XXCLBout+temp_XXCLB,_RWSJout+deallen,datalen+12);
                    temp_XXCLB+=datalen;
                    deallen = deallen+datalen+12;
                    break;
                case RWGH_S: //4A
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(RWGHout+temp_RWGH,_RWSJout+deallen,datalen+12);
                    temp_RWGH+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                case Res_1:  //4B
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(Res_1out+temp_Res_1,_RWSJout+deallen,datalen+12);
                    temp_Res_1+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                case SXQD_S:  //4C
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(SXQDout+temp_SXQD,_RWSJout+deallen,datalen+12);
                    subtype = _RWSJout[deallen+13];
                    switch (subtype) {
                    case 0x59:
                        memcpy(DKSXQD+temp_DKSXQD,_RWSJout+deallen+12,134);
                        temp_DKSXQD+=134;
                        break;
                    case 0x5A:
                        memcpy(DDSXQD+temp_DDSXQD,_RWSJout+deallen+12,134);
                        temp_DDSXQD+=134;
                        break;
                    case 0x5B:
                        memcpy(DKSXQDFZ+temp_DKSXQDFZ,_RWSJout+deallen+12,172);
                        temp_DKSXQDFZ+=172;
                        break;
                    case 0x5C:
                        memcpy(DDSXQDFZ+temp_DDSXQDFZ,_RWSJout+deallen+12,172);
                        temp_DDSXQDFZ+=172;
                        break;
                    default:
                        break;
                    }

                    temp_SXQD+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                case XJSC:  //4D
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(XJSCout+temp_XJSC,_RWSJout+deallen,datalen+12);
                    temp_XJSC+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                case SJGB:  //4E
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(SJGBout+temp_SJGB,_RWSJout+deallen,datalen+12);
                    temp_SJGB+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                case TXCSYC: //50
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(TXCSYCout+temp_TXCSYC,_RWSJout+deallen,datalen+12);
                    temp_TXCSYC+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                case TXCSSC:  //51
                    //datalen = (_RWSJout[deallen + 8] <<8 ) | _RWSJout[deallen+9];
                    memcpy(TXCSSCout+temp_TXCSSC,_RWSJout+deallen,datalen+12);
                    temp_TXCSSC+=datalen+12;
                    deallen = deallen+datalen+12;
                    break;
                default:
                    //qDebug()<<type<<"weizhiyuanbao";
//                    flag = ((_comRWSJ->img[deallen] << 24) | (_comRWSJ->img[deallen+1] << 16) | (_comRWSJ->img[deallen+2] << 8) |_comRWSJ->img[deallen+3]) & 0xffffffff;
//                    qDebug()<<flag;
//                    type = _comRWSJ->img[deallen+7];

//                    type = _comRWSJ->img[deallen+8];

                    //type = _comRWSJ->img[deallen+6];
                    deallen+=4;
                    break;
                }

//                if(type==0X11)
//                {
//                    memcpy(_DKCBout+temp_DKCB, _comDKCB->img + deallen, 920);
//                    temp_DKCB += 920;
//                    //*iZXGC = temp_ZXGC;
//                    deallen = deallen + 920;
//                }
            }
            else
            {
                if(UnPack::barkDetect(_RWSJout, cysumlen, deallen, &iStartPos1))
                {
                    datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];

                    if(iStartPos1+1304<=cysumlen && datalen<1291)
                    {
//                        memcpy(_DKCBout+temp_DKCB, _comDKCB->img + deallen, 920);
//                        temp_DKCB += 920;
//                        //*iZXGC = temp_ZXGC;
//                        deallen = deallen + 920;
                        type = _RWSJout[iStartPos1+6];

                        switch (type)
                        {
                        //40
                        case XJSJ_S:
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(XJSJout+temp_XJSJ,_RWSJout+iStartPos1,datalen+12);
                            subtype=_RWSJout[iStartPos1 + 11];
                            switch (subtype)
                            {
                            case (KJBXY_F):
                                memcpy(XJWLKJB+temp_XJWLKJB,_RWSJout+iStartPos1+10,datalen);
                                temp_XJWLKJB+=datalen;
                                break;
                            case (FZBXY_F):
                                memcpy(XJWLFZB+temp_XJWLFZB,_RWSJout+iStartPos1+10,datalen);
                                temp_XJWLFZB+=datalen;
                                break;
                            case (AOSXY_F):
                                memcpy(XJWLAOS+temp_XJWLAOS,_RWSJout+iStartPos1+10,datalen);
                                temp_XJWLAOS+=datalen;
                                break;
                            case (MPDUXY_F):
                                memcpy(XJWLMPDU+temp_XJWLMPDU,_RWSJout+iStartPos1+10,datalen);
                                temp_XJWLMPDU+=datalen;
                                break;
                            default:
                                break;
                            }
                            temp_XJSJ+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case DDZT_S:  //41
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(DDZTout+temp_DDZT,_RWSJout+iStartPos1,datalen+12);
                            memcpy(DDZTsubout+temp_DDZTsub,_RWSJout+iStartPos1+12,63);
                            temp_DDZT+=datalen+12;
                            temp_DDZTsub += 63;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case DKZT_S: //42
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(DKZTout+temp_DKZT,_RWSJout+iStartPos1,datalen+12);
                            memcpy(DKZTsubout+temp_DKZTsub,_RWSJout+iStartPos1+12,63);
                            temp_DKZT+=datalen+12;
                            temp_DKZTsub += 63;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case XMSJ_S:  //43
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(XMSJout+temp_XMSJ,_RWSJout+iStartPos1,datalen+12);
                            temp_XMSJ+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case GMTLC_S:  //44
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(GXTLCout+temp_GXTLC,_RWSJout+iStartPos1,datalen+12);
                            temp_GXTLC+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case XXCLA_S:  //45
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            //memcpy(XXCLAout+temp_XXCLA,_RWSJout+iStartPos1,datalen+12);
                            xxclatype=(_RWSJout[iStartPos1 + 10] <<8 ) | _RWSJout[iStartPos1+11];
                            switch (xxclatype) {
                            case 0x0905:
                                memcpy(XXCLADB+temp_XXCLADB,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLADB+=(datalen+12);
                                break;
                            case 0x0A05:
                                memcpy(XXCLADPD+temp_XXCLADPD,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLADPD+=(datalen+12);
                                break;
                            case 0x0B05:
                                memcpy(XXCLACB+temp_XXCLACB,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLACB+=(datalen+12);
                                break;
                            case 0x0C05:
                                memcpy(XXCLAZCB+temp_XXCLAZCB,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLAZCB+=(datalen+12);
                                break;
                            case 0x0933:
                                memcpy(XXCLADBBQT+temp_XXCLADBBQT,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLADBBQT+=(datalen+12);
                                break;
                            case 0x0A33:
                                memcpy(XXCLADPDBQT+temp_XXCLADPDBQT,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLADPDBQT+=(datalen+12);
                                break;
                            case 0x0B33:
                                memcpy(XXCLACBBQT+temp_XXCLACBBQT,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLACBBQT+=(datalen+12);
                                break;
                            case 0x0C33:
                                memcpy(XXCLAZCBBQT+temp_XXCLAZCBBQT,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLAZCBBQT+=(datalen+12);
                                break;
                            case 0x0505:
                                memcpy(XXCLADBDSP+temp_XXCLADBDSP,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLADBDSP+=(datalen+12);
                                break;
                            case 0x0605:
                                memcpy(XXCLADPDDSP+temp_XXCLADPDDSP,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLADPDDSP+=(datalen+12);
                                break;
                            case 0x0705:
                                memcpy(XXCLACBDSP+temp_XXCLACBDSP,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLACBDSP+=(datalen+12);
                                break;
                            case 0x0805:
                                memcpy(XXCLAZCBDSP+temp_XXCLAZCBDSP,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLAZCBDSP+=(datalen+12);
                                break;
                            case 0x0D05:
                                memcpy(XXCLARH+temp_XXCLARH,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLARH+=(datalen+12);
                                break;
                            case 0x0E05:
                                memcpy(XXCLADWYHT+temp_XXCLADWYHJ,_RWSJout+iStartPos1,datalen+12);
                                temp_XXCLADWYHJ+=(datalen+12);
                                break;
                            default:
                                break;
                            }
                            temp_XXCLA+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case NBYK_S: //46
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(NBYKout+temp_NBYK,_RWSJout+iStartPos1,datalen+12);
                            temp_NBYK+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case XXCL_S:  //47
                            //datalen = (_RWSJout[iStartPos1+ 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(XXCLout+temp_XXCL,_RWSJout+iStartPos1,datalen+12);
                            subtype=_RWSJout[iStartPos1+7];
                            switch (subtype)
                            {
                            case 0x88:/*
                                memcpy(XXCLBXD+temp_XXCLBXD,_RWSJout+iStartPos1,288);
                                temp_XXCLBXD+=288;
                                break;*/
                                subsubtype=(_RWSJout[iStartPos1+12]<<8)|_RWSJout[iStartPos1+13];


                                switch(subsubtype)
                                {
                                case 0x0c65:
                                    memcpy(XXCL101+temp_XXCL101,_RWSJout+iStartPos1,datalen+12);
                                    temp_XXCL101+=datalen+12;
                                    break;
                                case 0x0c66:
                                    memcpy(XXCL102+temp_XXCL102,_RWSJout+iStartPos1,datalen+12);
                                    temp_XXCL102+=datalen+12;
                                    break;
                                case 0x0c67:
                                    memcpy(XXCL103+temp_XXCL103,_RWSJout+iStartPos1,datalen+12);
                                    temp_XXCL103+=datalen+12;
                                    break;
                                default:
                                    if(_RWSJout[iStartPos1+11]==0x82){
                                        memcpy(XXCLBXD+temp_XXCLBXD,_RWSJout+iStartPos1,288);
                                        temp_XXCLBXD+=288;

                                    }
                                    break;
                                }
                            case 0x11:
                                memcpy(XXCLDKCB+temp_XXCLDKCB,_RWSJout+iStartPos1,920);
                                temp_XXCLDKCB+=920;
                                break;
                            case 0x12:
                                memcpy(XXCLDKZCB+temp_XXCLDKZCB,_RWSJout+iStartPos1,920);
                                temp_XXCLDKZCB+=920;
                                break;
                            case 0x21:
                                memcpy(XXCLDDDB+temp_XXCLDDDB,_RWSJout+iStartPos1,920);
                                temp_XXCLDDDB+=920;
                                break;
                            case 0x22:
                                memcpy(XXCLDDDPD+temp_XXCLDDDPD,_RWSJout+iStartPos1,920);
                                temp_XXCLDDDPD+=920;
                                break;
                            case 0x28:
                                memcpy(XXCLDDDPDKC+temp_XXCLDDDPDKC,_RWSJout+iStartPos1,920);
                                temp_XXCLDDDPDKC=920;
                                break;
                            default:
                                break;
                            }
                            temp_XXCL+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case DXXT_S:  //48
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(DXXTout+temp_DXXT,_RWSJout+iStartPos1,datalen+12);
                            subtype=_RWSJout[iStartPos1+11];
                            switch (subtype)
                            {
                            case KJBXY_F :
                                memcpy(DXXTKJB+temp_DXXTKJB,_RWSJout+iStartPos1+10,datalen);
                                temp_DXXTKJB+=datalen;
                                break;
                            case FZBXY_F:
                                memcpy(DXXTFZB+temp_DXXTFZB,_RWSJout+iStartPos1+10,datalen);
                                temp_DXXTFZB+=datalen;
                                break;
                            case AOSXY_F:
                                memcpy(DXXTAOS+temp_DXXTAOS,_RWSJout+iStartPos1+10,datalen);
                                temp_DXXTAOS+=datalen;
                                break;
                            case MPDUXY_F:
                                memcpy(DXXTMPDU+temp_DXXTMPDU,_RWSJout+iStartPos1+10,datalen);
                                temp_DXXTMPDU+=datalen;
                                break;
                            default:
                                break;
                            }
                            temp_DXXT+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case XXCLB_S:  //49
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(XXCLBout+temp_XXCLB,_RWSJout+iStartPos1,datalen+12);
                            temp_XXCLB+=datalen;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case RWGH_S: //4A
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(RWGHout+temp_RWGH,_RWSJout+iStartPos1,datalen+12);
                            temp_RWGH+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case Res_1:  //4B
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(Res_1out+temp_Res_1,_RWSJout+iStartPos1,datalen+12);
                            temp_Res_1+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case SXQD_S:  //4C
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) |_RWSJout[iStartPos1+9];
                            memcpy(SXQDout+temp_SXQD,_RWSJout+iStartPos1,datalen+12);
                            subtype=_RWSJout[iStartPos1+13];
                            switch (subtype) {
                            case 0x59:
                                memcpy(DKSXQD+temp_DKSXQD,_RWSJout+iStartPos1+12,134);
                                temp_DKSXQD+=134;
                                break;
                            case 0x5A:
                                memcpy(DDSXQD+temp_DDSXQD,_RWSJout+iStartPos1+12,134);
                                temp_DDSXQD+=134;
                                break;
                            case 0x5B:
                                memcpy(DKSXQDFZ+temp_DKSXQDFZ,_RWSJout+iStartPos1+12,172);
                                temp_DKSXQDFZ+=172;
                                break;
                            case 0x5C:
                                memcpy(DDSXQDFZ+temp_DDSXQDFZ,_RWSJout+iStartPos1+12,172);
                                temp_DDSXQDFZ+=172;
                                break;
                            default:
                                break;
                            }
                            temp_SXQD+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case XJSC:  //4D
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(XJSCout+temp_XJSC,_RWSJout+iStartPos1,datalen+12);
                            temp_XJSC+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case SJGB:  //4E
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(SJGBout+temp_SJGB,_RWSJout+iStartPos1,datalen+12);
                            temp_SJGB+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case TXCSYC: //50
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(TXCSYCout+temp_TXCSYC,_RWSJout+iStartPos1,datalen+12);
                            temp_TXCSYC+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        case TXCSSC:  //51
                            //datalen = (_RWSJout[iStartPos1 + 8] <<8 ) | _RWSJout[iStartPos1+9];
                            memcpy(TXCSSCout+temp_TXCSSC,_RWSJout+iStartPos1,datalen+12);
                            temp_TXCSSC+=datalen+12;
                            deallen = iStartPos1+datalen+12;
                            break;
                        default:
                            //qDebug()<<type<<"weizhiyuanbao1";
//                            flag = ((_comRWSJ->img[deallen] << 24) | (_comRWSJ->img[deallen+1] << 16) | (_comRWSJ->img[deallen+2] << 8) |_comRWSJ->img[deallen+3]) & 0xffffffff;
//                            qDebug()<<flag;
//                            type = _comRWSJ->img[deallen+7];

//                            type = _comRWSJ->img[deallen+8];

                            //type =_RWSJout[deallen+9];
                            deallen=iStartPos1+4;
                            break;
                        }

                    }
                    else
                    {
                        if(datalen>1291)
                        {
                            deallen=iStartPos1+4;
                        }
                        else{
                            deallen = iStartPos1;
                        }

                    }
                }
                else{
                    deallen = iStartPos1;
                }

            }

        }


        //写文件
        FILE *fpOut;
        char outwords[200];
        //DATA
        if(temp_XJSJ>0&&state)
        {
            sprintf(fileName, "%s/SSKJWL_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(XJSJout, temp_XJSJ, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
            if(temp_XJWLFZB>0)
            {
                sprintf(fileName, "%s/SSXJWLFZB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XJWLFZB, temp_XJWLFZB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XJWLKJB>0)
            {
                sprintf(fileName, "%s/SSXJWLKJB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XJWLKJB, temp_XJWLKJB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XJWLAOS>0)
            {
                sprintf(fileName, "%s/SSXJWLAOS_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XJWLAOS, temp_XJWLAOS, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XJWLMPDU>0)
            {
                sprintf(fileName, "%s/SSXJWLMPDU_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XJWLFZB, temp_XJWLMPDU, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
        }
        if(temp_DDZT>0&&state)
        {
            sprintf(fileName, "%s/SSDDZT_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DDZTout, temp_DDZT, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;

            sprintf(fileName, "%s/SSDDZT_2711sub.dat", outputpath2711sub);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DDZTsubout, temp_DDZTsub, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;

            unsigned int ddflag1,ddflag2;
            for(int i=0;i<temp_DDZTsub/63;i++){
                if(i==0){
                    ddflag1=((DDZTsubout[3]<<8)|DDZTsubout[4])& 0xFFFF;
                }
                else{
                    ddflag2=((DDZTsubout[3+i*63]<<8)|DDZTsubout[4+i*63])& 0xFFFF;
                    if(ddflag1+1!=ddflag2){
                        //qDebug()<<"bylianxu";
                        sprintf(outwords,"ssDDZT图像连续性检测中，第%d包与第%d包之间不连续bes %d\n",ddflag1,ddflag2,*ddztid);
                        //sprintf(fileName,"%s/image.txt",outputpathLog);
                        sprintf(fileName,"%s/ssDDZTcontinue.txt",outputpathLog);
                        fpOut = fopen(fileName,"ab");
                        if(fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;

                    }
                    ddflag1=ddflag2;
                }

                int check = 0;
                int check1=0;
                for(int j = 21; j < 62; j++)
                {
                    /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                        qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
                    check =(check+  DDZTsubout[63*i+j]);
                    //11.2删
                    //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
                }
                //check=check+datalen;
                check=check&0xff;
                check1=( DDZTsubout[63*i + 62])&0xff;

                if(check != check1)
                {
        //            qDebug()<<"adderror"<<endl;//加和报错
                    sprintf(outwords,"ssddzt图像，%d包检验和错误bes %d\n",ddflag1,*ddztid);
                    //sprintf(fileName,"%s/image.txt",outputpathLog);
                    sprintf(fileName,"ssddztadderror%s.txt",outputpathLog);
                    fpOut = fopen(fileName,"ab");
                    if(fpOut == NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;

                }
                *ddztid+=1;
            }



        }
        if(temp_DKZT>0&&state)
        {
            sprintf(fileName, "%s/SSDKZT_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DKZTout, temp_DKZT, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;

            sprintf(fileName, "%s/SSDKZT_2711sub.dat", outputpath2711sub);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DKZTsubout, temp_DKZTsub, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;

            unsigned int dkflag1,dkflag2;
            for(int i=0;i<temp_DKZTsub/63;i++){
                if(i==0){
                    dkflag1=((DKZTsubout[3]<<8)|DKZTsubout[4])& 0xFFFF;
                }
                else{
                    dkflag2=((DKZTsubout[3+i*63]<<8)|DKZTsubout[4+i*63])& 0xFFFF;
                    if(dkflag1+1!=dkflag2){
                        //qDebug()<<"bylianxu";
                        sprintf(outwords,"ssDKZT图像连续性检测中，第%d包与第%d包之间不连续bes %d\n",dkflag1,dkflag2,*dkztid);
                        //sprintf(fileName,"%s/image.txt",outputpathLog);
                        sprintf(fileName,"%s/ssDKZTcontinue.txt",outputpathLog);
                        fpOut = fopen(fileName,"ab");
                        if(fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;

                    }
                    dkflag1=dkflag2;
                }

                int check = 0;
                int check1=0;
                for(int j = 21; j < 62; j++)
                {
                    /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                        qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
                    check =(check+  DKZTsubout[63*i+j]);
                    //11.2删
                    //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
                }
                //check=check+datalen;
                check=check&0xff;
                check1=( DKZTsubout[63*i + 62])&0xff;

                if(check != check1)
                {
        //            qDebug()<<"adderror"<<endl;//加和报错
                    sprintf(outwords,"ssdkzt图像，%d包检验和错误bes %d\n",dkflag1,*dkztid);
                    //sprintf(fileName,"%s/image.txt",outputpathLog);
                    sprintf(fileName,"ssdkztadderror%s.txt",outputpathLog);
                    fpOut = fopen(fileName,"ab");
                    if(fpOut == NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;

                }
                *dkztid+=1;
            }
        }
        if(temp_XMSJ>0&&state)
        {
            sprintf(fileName, "%s/SSXMSJ_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(XMSJout, temp_XMSJ, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_GXTLC>0&&state)
        {
            sprintf(fileName, "%s/SSGXTLC_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(GXTLCout, temp_GXTLC, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_XXCLA>0&&state)
        {
//            sprintf(fileName, "%s/SSXXCLA_2711.dat", outputpath2711package);
//            fpOut = fopen(fileName, "ab");
//            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
//            fwrite(XXCLAout, temp_XXCLA, 1, fpOut);
//            //DKCBlen += (12 + datalen);
//            fclose(fpOut);
//            fpOut = NULL;

            if(temp_XXCLADB>0){
                sprintf(fileName, "%s/SSXXCLADB.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADB, temp_XXCLADB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLADPD>0){
                sprintf(fileName, "%s/SSXXCLADPD.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADPD, temp_XXCLADPD, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLACB>0){
                sprintf(fileName, "%s/SSXXCLACB.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLACB, temp_XXCLACB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLAZCB>0){
                sprintf(fileName, "%s/SSXXCLAZCB.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLAZCB, temp_XXCLAZCB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLADBBQT>0){
                sprintf(fileName, "%s/SSXXCLABQT.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADBBQT, temp_XXCLADBBQT, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLADPDBQT>0){
                sprintf(fileName, "%s/SSXXCLABQT.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADPDBQT, temp_XXCLADPDBQT, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLACBBQT>0){
                sprintf(fileName, "%s/SSXXCLABQT.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLACBBQT, temp_XXCLACBBQT, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLAZCBBQT>0){
                sprintf(fileName, "%s/SSXXCLABQT.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLAZCBBQT, temp_XXCLAZCBBQT, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLADBDSP>0){
                sprintf(fileName, "%s/SSXXCLADBDSP.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADBDSP, temp_XXCLADBDSP, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLADPDDSP>0){
                sprintf(fileName, "%s/SSXXCLADPDDSP.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADPDDSP, temp_XXCLADPDDSP, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLACBDSP>0){
                sprintf(fileName, "%s/SSXXCLACBDSP.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLACBDSP, temp_XXCLACBDSP, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLAZCBDSP>0){
                sprintf(fileName, "%s/SSXXCLAZCBDSP.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLAZCBDSP, temp_XXCLAZCBDSP, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLARH>0){
                sprintf(fileName, "%s/SSXXCLARH.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLARH, temp_XXCLARH, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLADWYHJ>0){
                sprintf(fileName, "%s/SSXXCLADWYHJ.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADWYHT, temp_XXCLADWYHJ, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
        }
        if(temp_NBYK>0&&state)
        {
            sprintf(fileName, "%s/SSNBYK_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(NBYKout, temp_NBYK, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_XXCL>0&&state)
        {
            sprintf(fileName, "%s/SSXXCL_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(XXCLout, temp_XXCL, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
            if(temp_XXCLBXD>0)
            {
                sprintf(fileName, "%s/SSXXCLBXD_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLBXD, temp_XXCLBXD, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }

            if(temp_XXCL101>0)
            {
                sprintf(fileName, "%s/SSXXCL101_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCL101, temp_XXCL101, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }

            if(temp_XXCL102>0)
            {
                sprintf(fileName, "%s/SSXXCL102_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCL102, temp_XXCL102, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }

            if(temp_XXCL103>0)
            {
                sprintf(fileName, "%s/SSXXCL103_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCL103, temp_XXCL103, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLDKCB>0)
            {
                sprintf(fileName, "%s/SSXXCLDKCB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLDKCB, temp_XXCLDKCB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLDKZCB>0)
            {
                sprintf(fileName, "%s/SSXXCLDKZCB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLDKZCB, temp_XXCLDKZCB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLDDDB>0)
            {
                sprintf(fileName, "%s/SSXXCLDDDB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLDDDB, temp_XXCLDDDB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLDDDPD>0)
            {
                sprintf(fileName, "%s/SSXXCLDDDPD_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLDDDPD, temp_XXCLDDDPD, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLDDDPDKC>0)
            {
                sprintf(fileName, "%s/SSXXCLDDDPDKC_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLDDDPDKC, temp_XXCLDDDPDKC, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
        }
        if(temp_DXXT>0&&state)
        {
            sprintf(fileName, "%s/SSDXXT_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DXXTout, temp_DXXT, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;

            if(temp_DXXTFZB>0)
            {
                sprintf(fileName, "%s/SSDXXTFZB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DXXTFZB, temp_DXXTFZB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_DXXTKJB>0)
            {
                sprintf(fileName, "%s/SSDXXTKJB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DXXTKJB, temp_DXXTKJB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_DXXTAOS>0)
            {
                sprintf(fileName, "%s/SSDXXTAOS_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DXXTAOS, temp_DXXTAOS, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_DXXTMPDU>0)
            {
                sprintf(fileName, "%s/SSDXXTMPDU_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DXXTFZB, temp_DXXTMPDU, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
        }
        if(temp_XXCLB>0&&state)
        {
            sprintf(fileName, "%s/SSXXCLB_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(XXCLBout, temp_XXCLB, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_RWGH>0&&state)
        {
            sprintf(fileName, "%s/SSRWGH_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(RWGHout, temp_RWGH, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_Res_1>0&&state)
        {
            sprintf(fileName, "%s/SSRES_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(Res_1out, temp_Res_1, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_SXQD>0&&state)
        {
            sprintf(fileName, "%s/SSSXQD_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(SXQDout, temp_SXQD, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;

            if(temp_DKSXQD>0){
                sprintf(fileName, "%s/SSDKSXQD_2711.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DKSXQD, temp_DKSXQD, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;

//                for(int i =0;i<temp_DKSXQD/134;i++)
//                {
//                    int check = 0;
//                    int check1 =0;
//                    for(int j=0;j<132;j++)
//                    {
//                        check=(check+DKSXQD[134*i+j]);

//                    }
//                    check=check&0xffff;
//                    check1=(DKSXQD[134*i+132]<<8)+DKSXQD[134*i+133];
//                    if(check!=check1)
//                    {
//                        qDebug()<<check<<check1;
//                    }
//                }
            }
            if(temp_DDSXQD>0){
                sprintf(fileName, "%s/SSDDSXQD_2711.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DDSXQD, temp_DDSXQD, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_DKSXQDFZ>0){
                sprintf(fileName, "%s/SSDKSXQDFZ_2711.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DKSXQDFZ, temp_DKSXQDFZ, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_DDSXQDFZ>0){
                sprintf(fileName, "%s/SSDDSXQDFZ_2711.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DDSXQDFZ, temp_DDSXQDFZ, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
        }
        if(temp_XJSC>0&&state)
        {
            sprintf(fileName, "%s/SSXJSC_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(XJSCout, temp_XJSC, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_SJGB>0&&state)
        {
            sprintf(fileName, "%s/SSSJGB_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(SJGBout, temp_SJGB, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_TXCSYC>0&&state)
        {
            sprintf(fileName, "%s/SSTXCSYC_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(TXCSYCout, temp_TXCSYC, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_TXCSSC>0&&state)
        {
            sprintf(fileName, "%s/SSTXCSSC_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(TXCSSCout, temp_TXCSSC, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }


        if(temp_XJSJ>0&&state==0)
        {
            sprintf(fileName, "%s/KJWL_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(XJSJout, temp_XJSJ, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
            if(temp_XJWLFZB>0)
            {
                sprintf(fileName, "%s/hfXJWLFZB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XJWLFZB, temp_XJWLFZB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XJWLKJB>0)
            {
                sprintf(fileName, "%s/hfXJWLKJB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XJWLKJB, temp_XJWLKJB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XJWLAOS>0)
            {
                sprintf(fileName, "%s/hfXJWLAOS_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XJWLAOS, temp_XJWLAOS, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XJWLMPDU>0)
            {
                sprintf(fileName, "%s/hfXJWLMPDU_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XJWLFZB, temp_XJWLMPDU, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
        }
        if(temp_DDZT>0&&state==0)
        {
            sprintf(fileName, "%s/DDZT_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DDZTout, temp_DDZT, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;

            sprintf(fileName, "%s/DDZT_2711sub.dat", outputpath2711sub);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DDZTsubout, temp_DDZTsub, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;

            unsigned int ddflag1,ddflag2;
            for(int i=0;i<temp_DDZTsub/63;i++){
                if(i==0){
                    ddflag1=((DDZTsubout[3]<<8)|DDZTsubout[4])& 0xFFFF;
                }
                else{
                    ddflag2=((DDZTsubout[3+i*63]<<8)|DDZTsubout[4+i*63])& 0xFFFF;
                    if(ddflag1+1!=ddflag2){
                        //qDebug()<<"bylianxu";
                        sprintf(outwords,"hfDDZT图像连续性检测中，第%d包与第%d包之间不连续bes %d\n",ddflag1,ddflag2,*ddztid);
                        //sprintf(fileName,"%s/image.txt",outputpathLog);
                        sprintf(fileName,"%s/hfDDZTcontinue.txt",outputpathLog);
                        fpOut = fopen(fileName,"ab");
                        if(fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;

                    }
                    ddflag1=ddflag2;
                }

                int check = 0;
                int check1=0;
                for(int j = 21; j < 62; j++)
                {
                    /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                        qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
                    check =(check+  DDZTsubout[63*i+j]);
                    //11.2删
                    //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
                }
                //check=check+datalen;
                check=check&0xff;
                check1=( DDZTsubout[63*i + 62])&0xff;

                if(check != check1)
                {
        //            qDebug()<<"adderror"<<endl;//加和报错
                    sprintf(outwords,"hfddzt图像，%d包检验和错误bes %d\n",ddflag1,*ddztid);
                    //sprintf(fileName,"%s/image.txt",outputpathLog);
                    sprintf(fileName,"hfddztadderror%s.txt",outputpathLog);
                    fpOut = fopen(fileName,"ab");
                    if(fpOut == NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;

                }
                *ddztid+=1;
            }
        }
        if(temp_DKZT>0&&state==0)
        {
            sprintf(fileName, "%s/DKZT_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DKZTout, temp_DKZT, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;

            sprintf(fileName, "%s/DKZT_2711sub.dat", outputpath2711sub);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DKZTsubout, temp_DKZTsub, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;

            unsigned int dkflag1,dkflag2;
            for(int i=0;i<temp_DKZTsub/63;i++){
                if(i==0){
                    dkflag1=((DKZTsubout[3]<<8)|DKZTsubout[4])& 0xFFFF;
                }
                else{
                    dkflag2=((DKZTsubout[3+i*63]<<8)|DKZTsubout[4+i*63])& 0xFFFF;
                    if(dkflag1+1!=dkflag2){
                        //qDebug()<<"bylianxu";
                        sprintf(outwords,"DKZT图像连续性检测中，第%d包与第%d包之间不连续bes %d\n",dkflag1,dkflag2,*dkztid);
                        //sprintf(fileName,"%s/image.txt",outputpathLog);
                        sprintf(fileName,"%s/hfDKZTcontinue.txt",outputpathLog);
                        fpOut = fopen(fileName,"ab");
                        if(fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;

                    }
                    dkflag1=dkflag2;
                }

                int check = 0;
                int check1=0;
                for(int j = 21; j < 62; j++)
                {
                    /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                        qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
                    check =(check+  DKZTsubout[63*i+j]);
                    //11.2删
                    //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
                }
                //check=check+datalen;
                check=check&0xff;
                check1=( DKZTsubout[63*i + 62])&0xff;

                if(check != check1)
                {
        //            qDebug()<<"adderror"<<endl;//加和报错
                    sprintf(outwords,"dkzt图像，%d包检验和错误bes %d\n",dkflag1,*dkztid);
                    //sprintf(fileName,"%s/image.txt",outputpathLog);
                    sprintf(fileName,"hfdkztadderror%s.txt",outputpathLog);
                    fpOut = fopen(fileName,"ab");
                    if(fpOut == NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;

                }
                *dkztid+=1;
            }
        }
        if(temp_XMSJ>0&&state==0)
        {
            sprintf(fileName, "%s/XMSJ_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(XMSJout, temp_XMSJ, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_GXTLC>0&&state==0)
        {
            sprintf(fileName, "%s/GXTLC_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(GXTLCout, temp_GXTLC, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_XXCLA>0&&state==0)
        {
//            sprintf(fileName, "%s/XXCLA_2711.dat", outputpath2711package);
//            fpOut = fopen(fileName, "ab");
//            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
//            fwrite(XXCLAout, temp_XXCLA, 1, fpOut);
//            //DKCBlen += (12 + datalen);
//            fclose(fpOut);
//            fpOut = NULL;

            if(temp_XXCLADB>0){
                sprintf(fileName, "%s/HFXXCLADB.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADB, temp_XXCLADB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLADPD>0){
                sprintf(fileName, "%s/HFXXCLADPD.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADPD, temp_XXCLADPD, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLACB>0){
                sprintf(fileName, "%s/HFXXCLACB.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLACB, temp_XXCLACB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLAZCB>0){
                sprintf(fileName, "%s/HFXXCLAZCB.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLAZCB, temp_XXCLAZCB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLADBBQT>0){
                sprintf(fileName, "%s/HFXXCLABQT.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADBBQT, temp_XXCLADBBQT, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLADPDBQT>0){
                sprintf(fileName, "%s/HFXXCLABQT.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADPDBQT, temp_XXCLADPDBQT, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLACBBQT>0){
                sprintf(fileName, "%s/HFXXCLABQT.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLACBBQT, temp_XXCLACBBQT, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLAZCBBQT>0){
                sprintf(fileName, "%s/HFXXCLABQT.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLAZCBBQT, temp_XXCLAZCBBQT, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLADBDSP>0){
                sprintf(fileName, "%s/HFXXCLADBDSP.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADBDSP, temp_XXCLADBDSP, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLADPDDSP>0){
                sprintf(fileName, "%s/HFXXCLADPDDSP.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADPDDSP, temp_XXCLADPDDSP, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLACBDSP>0){
                sprintf(fileName, "%s/HFXXCLACBDSP.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLACBDSP, temp_XXCLACBDSP, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLAZCBDSP>0){
                sprintf(fileName, "%s/HFXXCLAZCBDSP.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLAZCBDSP, temp_XXCLAZCBDSP, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLARH>0){
                sprintf(fileName, "%s/HFXXCLARH.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLARH, temp_XXCLARH, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLADWYHJ>0){
                sprintf(fileName, "%s/HFXXCLADWYHJ.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLADWYHT, temp_XXCLADWYHJ, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }

        }
        if(temp_NBYK>0&&state==0)
        {
            sprintf(fileName, "%s/NBYK_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(NBYKout, temp_NBYK, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_XXCL>0&&state==0)
        {
            sprintf(fileName, "%s/XXCL_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(XXCLout, temp_XXCL, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
            if(temp_XXCLBXD>0)
            {
                sprintf(fileName, "%s/HFXXCLBXD_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLBXD, temp_XXCLBXD, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCL101>0)
            {
                sprintf(fileName, "%s/hfXXCL101_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCL101, temp_XXCL101, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }

            if(temp_XXCL102>0)
            {
                sprintf(fileName, "%s/hfXXCL102_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCL102, temp_XXCL102, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }

            if(temp_XXCL103>0)
            {
                sprintf(fileName, "%s/hfXXCL103_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCL103, temp_XXCL103, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLDKCB>0)
            {
                sprintf(fileName, "%s/HFXXCLDKCB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLDKCB, temp_XXCLDKCB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLDKZCB>0)
            {
                sprintf(fileName, "%s/HFXXCLDKZCB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLDKZCB, temp_XXCLDKZCB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLDDDB>0)
            {
                sprintf(fileName, "%s/HFXXCLDDDB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLDDDB, temp_XXCLDDDB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLDDDPD>0)
            {
                sprintf(fileName, "%s/HFXXCLDDDPD_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLDDDPD, temp_XXCLDDDPD, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_XXCLDDDPDKC>0)
            {
                sprintf(fileName, "%s/HFXXCLDDDPDKC_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(XXCLDDDPDKC, temp_XXCLDDDPDKC, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
        }
        if(temp_DXXT>0&&state==0)
        {
            sprintf(fileName, "%s/DXXT_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DXXTout, temp_DXXT, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
            if(temp_DXXTFZB>0)
            {
                sprintf(fileName, "%s/HFXXTFZB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DXXTFZB, temp_DXXTFZB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_DXXTKJB>0)
            {
                sprintf(fileName, "%s/HFDXXTKJB_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DXXTKJB, temp_DXXTKJB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_DXXTAOS>0)
            {
                sprintf(fileName, "%s/HFDXXTAOS_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DXXTAOS, temp_DXXTAOS, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_DXXTMPDU>0)
            {
                sprintf(fileName, "%s/HFDXXTMPDU_2711SUB.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DXXTFZB, temp_DXXTMPDU, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
        }
        if(temp_XXCLB>0&&state==0)
        {
            sprintf(fileName, "%s/XXCLB_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(XXCLBout, temp_XXCLB, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_RWGH>0&&state==0)
        {
            sprintf(fileName, "%s/RWGH_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(RWGHout, temp_RWGH, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_Res_1>0&&state==0)
        {
            sprintf(fileName, "%s/RES_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(Res_1out, temp_Res_1, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_SXQD>0&&state==0)
        {
            sprintf(fileName, "%s/SXQD_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(SXQDout, temp_SXQD, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;

            if(temp_DKSXQD>0){
                sprintf(fileName, "%s/HFDKSXQD_2711.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DKSXQD, temp_DKSXQD, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;

//                for(int i =0;i<temp_DKSXQD/134;i++)
//                {
//                    int check = 0;
//                    int check1 =0;
//                    for(int j=0;j<132;j++)
//                    {
//                        check=(check+DKSXQD[134*i+j]);

//                    }
//                    check=check&0xffff;
//                    check1=(DKSXQD[134*i+132]<<8)+DKSXQD[134*i+133];
//                    if(check!=check1)
//                    {
//                        qDebug()<<check<<check1;
//                    }
//                }
            }
            if(temp_DDSXQD>0){
                sprintf(fileName, "%s/HFDDSXQD_2711.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DDSXQD, temp_DDSXQD, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_DKSXQDFZ>0){
                sprintf(fileName, "%s/HFDKSXQDFZ_2711.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DKSXQDFZ, temp_DKSXQDFZ, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            if(temp_DDSXQDFZ>0){
                sprintf(fileName, "%s/HFDDSXQDFZ_2711.dat", outputpath2711sub);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DDSXQDFZ, temp_DDSXQDFZ, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
        }
        if(temp_XJSC>0&&state==0)
        {
            sprintf(fileName, "%s/XJSC_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(XJSCout, temp_XJSC, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_SJGB>0&&state==0)
        {
            sprintf(fileName, "%s/SJGB_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(SJGBout, temp_SJGB, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_TXCSYC>0&&state==0)
        {
            sprintf(fileName, "%s/TXCSYC_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(TXCSYCout, temp_TXCSYC, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_TXCSSC>0&&state==0)
        {
            sprintf(fileName, "%s/TXCSSC_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(TXCSSCout, temp_TXCSSC, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }


//        sprintf(fileName, "%s/DKCB_2711.dat", outputpath2711package);
//        fpOut = fopen(fileName, "ab");
//        //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
//        fwrite(_DKCBout, temp_DKCB, 1, fpOut);
//        //DKCBlen += (12 + datalen);
//        fclose(fpOut);
//        fpOut = NULL;
     }
    *rmlen=cysumlen-deallen;
    memcpy(_RWSJout,_RWSJout+deallen,*rmlen);
    free(XJSJout);XJSJout = NULL;  //1
    free(DDZTout);DDZTout=NULL;
    free(DKZTout);DKZTout = NULL;
    free(XMSJout);XMSJout = NULL;
    free(GXTLCout);GXTLCout =NULL;

    free(NBYKout);NBYKout = NULL;  //6
    free(XXCLout);XXCLout = NULL;
    free(DXXTout);DXXTout =NULL;
    free(XXCLBout);XXCLBout = NULL;
    free(RWGHout);RWGHout = NULL;
    free(Res_1out);Res_1out=NULL;
    free(SXQDout);SXQDout=NULL;
    free(XJSCout);XJSCout=NULL;
    free(SJGBout);SJGBout=NULL;
    free(TXCSYCout);TXCSYCout =NULL;
    free(TXCSSCout);TXCSSCout=NULL;   //16

    free(DDZTsubout);DDZTsubout=NULL;
    free(DKZTsubout);DKZTsubout=NULL;

    free(XXCLADB);XXCLADB = NULL;  //19
    free(XXCLADPD);XXCLADPD = NULL;
    free(XXCLACB);XXCLACB = NULL;
    free(XXCLAZCB);XXCLAZCB = NULL;
    free(XXCLADBBQT);XXCLADBBQT = NULL;
    free(XXCLACBBQT);XXCLACBBQT = NULL;
    free(XXCLADPDBQT);XXCLADPDBQT = NULL;
    free(XXCLAZCBBQT);XXCLAZCBBQT = NULL;
    free(XXCLADBDSP);XXCLADBDSP = NULL;
    free(XXCLADPDDSP);XXCLADPDDSP = NULL;
    free(XXCLACBDSP);XXCLACBDSP = NULL;
    free(XXCLAZCBDSP);XXCLAZCBDSP = NULL;
    free(XXCLARH);XXCLARH = NULL;
    free(XXCLADWYHT);XXCLADWYHT = NULL;

    free(XJWLKJB);XJWLKJB = NULL; //33
    free(XJWLFZB);XJWLFZB = NULL;
    free(XJWLAOS);XJWLAOS = NULL;
    free(XJWLMPDU);XJWLMPDU = NULL;

    free(XXCLBXD);XXCLBXD = NULL;
    free(XXCLDKCB);XXCLDKCB = NULL;
    free(XXCLDKZCB);XXCLDKZCB = NULL;
    free(XXCLDDDB);XXCLDDDB = NULL;
    free(XXCLDDDPDKC);XXCLDDDPDKC = NULL;
    free(XXCLDDDPD);XXCLDDDPD = NULL;
    free(XXCL101);XXCL101=NULL;
    free(XXCL102);XXCL102=NULL;
    free(XXCL103);XXCL103=NULL;

    free(DKSXQD);DKSXQD=NULL;
    free(DDSXQD);DDSXQD=NULL;
    free(DKSXQDFZ);DKSXQDFZ=NULL;
    free(DDSXQDFZ);DDSXQDFZ=NULL;  //44

    free(DXXT201);DXXT201=NULL;
    free(DXXT202);DXXT202=NULL;
    free(DXXT203);DXXT203=NULL;
    free(DXXT204);DXXT204=NULL;
    free(DXXT205);DXXT205=NULL;
    free(DXXT206);DXXT206=NULL;
    free(DXXT207);DXXT207=NULL;
    free(DXXT208);DXXT208=NULL;
    free(DXXT025);DXXT025=NULL;
    free(DXXT026);DXXT026=NULL;    //54

    free(DXXTKJB);DXXTKJB = NULL; //33
    free(DXXTFZB);DXXTFZB = NULL;
    free(DXXTAOS);DXXTAOS = NULL;
    free(DXXTMPDU);DXXTMPDU = NULL;


    return deallen;
}

int DealSourcePackage::dealDKCBPackage(unsigned char *_strDKCB, int _DKCBlen, compressedStream *_comDKCB, SourceStream *_obtainedSourceStream, unsigned char *_DKCBout,unsigned char *_DKCB2711out,int *rmlen,bool state,unsigned int *packnumid,unsigned int *cbid)
{
    __int64         temp_DKCB = 0;

    int EPDUflag;
    int iStartPos1 = 0;

    unsigned int flag;
    int    type = 0x00;
    int    datalen = 0;
    int deallen = 0;
    int cysumlen=0;
    __int64 BUFFSIZE = (128* 1024 * 1024);
    unsigned char	*DKCB2711out= NULL;

    DKCB2711out = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));

    char fileName[fileNameLen];

    unsigned int dkcbpacknum;
    dkcbpacknum=*packnumid;
    unsigned int dkcb2711num=*cbid;
    unpack->unpack1(_strDKCB, _DKCBlen, _comDKCB->img, &(_comDKCB->ilen), outputpathLog,state,&dkcbpacknum);
    //unpack->unpack(_strDKCB, _DKCBlen, _comDKCB->img, &(_comDKCB->ilen), outputpathLog,state);   //img为该buf中的EPDU数据
    *packnumid = dkcbpacknum;
    cysumlen = _comDKCB->ilen+*rmlen;

    memcpy(_DKCBout+*rmlen,_comDKCB->img,_comDKCB->ilen);   //考虑残余数据的情况   iShiftlen如何变
    EPDUflag=3;
    if(UnPack::barkDetect(_DKCBout,cysumlen,0,&iStartPos1))
    {

        type= _DKCBout[iStartPos1+6];  //0x11
        memcpy(DKCB2711out,_DKCBout+iStartPos1,920);
        temp_DKCB+=920;
        deallen = iStartPos1+920;

        while (deallen+920<=cysumlen)
        {
            flag = ((_DKCBout[deallen] << 24) | (_DKCBout[deallen+1] << 16) | (_DKCBout[deallen+2] << 8) |_DKCBout[deallen+3]) & 0xffffffff;
            if(flag == 0xF5F6EB90)
            {
                type = _DKCBout[deallen+6];
                if(type==0X11)
                {
                    memcpy(DKCB2711out+temp_DKCB, _DKCBout + deallen, 920);
                    temp_DKCB += 920;
                    //*iZXGC = temp_ZXGC;
                    deallen = deallen + 920;
                }
                else{
                    deallen+=4;
                }
            }
            else
            {
                if(UnPack::barkDetect(_DKCBout, cysumlen, deallen, &iStartPos1))
                {
                    if(iStartPos1+920<=cysumlen)
                    {
                        if(type==0x11)
                        {
                            memcpy(DKCB2711out+temp_DKCB, _DKCBout + iStartPos1, 920);
                            temp_DKCB += 920;
                            //*iZXGC = temp_ZXGC;
                            deallen = iStartPos1 + 920;
                        }
                    }
                    else
                    {
                        deallen = iStartPos1;
                    }
                }
                else{
                    deallen = iStartPos1;
                }

            }

        }


        if(state){
            continuejudge(DKCB2711out,temp_DKCB,1,&dkcb2711num);
        }
        else{
            continuejudge(DKCB2711out,temp_DKCB,2,&dkcb2711num);
        }

        *cbid=dkcb2711num;

        //写文件
        FILE *fpOut;
        if(state){
            sprintf(fileName, "%s/SSDKCB_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DKCB2711out, temp_DKCB, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        else{
            sprintf(fileName, "%s/DKCB_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DKCB2711out, temp_DKCB, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }

     }
    *rmlen=cysumlen-deallen;
    memcpy(_DKCBout,_DKCBout+deallen,*rmlen);
    memcpy(_DKCB2711out,DKCB2711out,temp_DKCB);
    free(DKCB2711out);DKCB2711out=NULL;
    return temp_DKCB;
}

int DealSourcePackage::dealDDDPDPackage(unsigned char *_strDDDPD, int _DDDPDlen, compressedStream *_comDDDPD, SourceStream *_obtainedSourceStream, unsigned char *_DDDPDout,unsigned char* _DDDPDKCout,int *rmlen,bool state,unsigned int *packnumid,unsigned int *dddpdkclen,unsigned int *pdid,unsigned int *kcid)
{
    __int64         temp_DDDPD = 0,temp_DDDPDKC = 0;

    int EPDUflag;
    int iStartPos1 = 0;
    int cysumlen=0;
    __int64 BUFFSIZE = (128* 1024 * 1024);
    unsigned char	*DDDPD2711out= NULL,*DDDPDKC2711out= NULL;
    //unsigned int insert;//debug

    DDDPD2711out = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    DDDPDKC2711out = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));

    if(NULL==DDDPD2711out || NULL ==DDDPDKC2711out)
    {
        qDebug()<<"malloc failed";
    }

    unsigned int flag;
    int    type = 0x00;
    int    datalen = 0;
    int deallen = 0;

    char fileName[fileNameLen];
    unsigned int dddpdpacknum=*packnumid;
    unsigned int dddpd2711num=*pdid,dddpdkc2711num=*kcid;
    unpack->unpack1(_strDDDPD, _DDDPDlen, _comDDDPD->img, &(_comDDDPD->ilen), outputpathLog,state,&dddpdpacknum);
    *packnumid=dddpdpacknum;
//    unpack->unpack(_strDDDPD, _DDDPDlen, _comDDDPD->img, &(_comDDDPD->ilen), outputpathLog,state);
    cysumlen = _comDDDPD->ilen+*rmlen;

    if(state){
        memcpy(_obtainedSourceStream->SSDDDPDdata+*rmlen,_comDDDPD->img,_comDDDPD->ilen);
        if(UnPack::barkDetect(_obtainedSourceStream->SSDDDPDdata,cysumlen,0,&iStartPos1))
        {
            //insert = (_obtainedSourceStream->SSDDDPDdata[iStartPos1 + 4] <<8 ) | _obtainedSourceStream->SSDDDPDdata[iStartPos1+5];


            type= _obtainedSourceStream->SSDDDPDdata[iStartPos1+6];  //0X22
    //        memcpy(DDDPD2711out,_DDDPDout+iStartPos1,920);
    //        temp_DDDPD+=920;
    //        deallen = iStartPos1+920;
            switch (type)
            {
            //40
            case DDDPD_S: //22
                //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
                memcpy(DDDPD2711out,_obtainedSourceStream->SSDDDPDdata+iStartPos1,920);
                temp_DDDPD+=920;
                deallen = iStartPos1+920;
                break;
            case DDDPDKC_S:  //28
                //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
                memcpy(DDDPDKC2711out,_obtainedSourceStream->SSDDDPDdata+iStartPos1,920);
                temp_DDDPDKC+=920;
                deallen = iStartPos1+920;
                break;
            default:
                deallen+=4;
                break;
            }

            while (deallen+920<=cysumlen)
            {
                flag = ((_obtainedSourceStream->SSDDDPDdata[deallen] << 24) | (_obtainedSourceStream->SSDDDPDdata[deallen+1] << 16) | (_obtainedSourceStream->SSDDDPDdata[deallen+2] << 8) |_obtainedSourceStream->SSDDDPDdata[deallen+3]) & 0xffffffff;
    //            insert = (_obtainedSourceStream->SSDDDPDdata[deallen + 4] <<8 ) | _obtainedSourceStream->SSDDDPDdata[deallen+5];
    //            if(insert==19024){
    //                qDebug()<<insert;
    //            }
                if(flag == 0xF5F6EB90)
                {
                    type = _obtainedSourceStream->SSDDDPDdata[deallen+6];
                    switch (type)
                    {
                    //40
                    case DDDPD_S: //22
                        //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
                        memcpy(DDDPD2711out+temp_DDDPD,_obtainedSourceStream->SSDDDPDdata+deallen,920);
                        temp_DDDPD+=920;
                        deallen = deallen+920;
                        break;
                    case DDDPDKC_S:  //28
                        //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
                        memcpy(DDDPDKC2711out+temp_DDDPDKC,_obtainedSourceStream->SSDDDPDdata+deallen,920);
                        temp_DDDPDKC+=920;
                        deallen = deallen+920;
                        break;
                    default:
                        deallen+=4;
                        break;
                    }

                }
                else
                {
                    if(UnPack::barkDetect(_obtainedSourceStream->SSDDDPDdata, cysumlen, deallen, &iStartPos1))
                    {
                        if(iStartPos1+920<=cysumlen)
                        {
    //                        insert = (_obtainedSourceStream->SSDDDPDdata[iStartPos1 + 4] <<8 ) | _obtainedSourceStream->SSDDDPDdata[iStartPos1+5];
    //                        if(insert==19024){
    //                            qDebug()<<insert;
    //                        }
                            type= _obtainedSourceStream->SSDDDPDdata[iStartPos1+6];
                            switch (type)
                            {
                            case DDDPD_S:
                                memcpy(DDDPD2711out+temp_DDDPD, _obtainedSourceStream->SSDDDPDdata + iStartPos1, 920);
                                temp_DDDPD += 920;
                                //*iZXGC = temp_ZXGC;
                                deallen = iStartPos1 + 920;
                                break;
                            case DDDPDKC_S:
                                memcpy(DDDPDKC2711out+temp_DDDPDKC, _obtainedSourceStream->SSDDDPDdata + iStartPos1, 920);
                                temp_DDDPDKC += 920;
                                //*iZXGC = temp_ZXGC;
                                deallen = iStartPos1 + 920;
                                break;
                            default:
                                deallen =iStartPos1 + 4;
                                break;
                            }

                        }
                        else
                        {
                            deallen = iStartPos1;
                        }
                    }
                    else
                    {
                        deallen = iStartPos1;
                    }
                }

            }

         }

        *rmlen=cysumlen-deallen;
        memcpy(_obtainedSourceStream->SSDDDPDdata,_obtainedSourceStream->SSDDDPDdata+deallen,*rmlen);
        continuejudge(DDDPD2711out, temp_DDDPD,7,&dddpd2711num);
        continuejudge(DDDPDKC2711out, temp_DDDPDKC,9,&dddpdkc2711num);
    }
    else{
        memcpy(_obtainedSourceStream->DDDPDdata+*rmlen,_comDDDPD->img,_comDDDPD->ilen);
        if(UnPack::barkDetect(_obtainedSourceStream->DDDPDdata,cysumlen,0,&iStartPos1))
        {
            //insert = (_obtainedSourceStream->SSDDDPDdata[iStartPos1 + 4] <<8 ) | _obtainedSourceStream->SSDDDPDdata[iStartPos1+5];


            type= _obtainedSourceStream->DDDPDdata[iStartPos1+6];  //0X22
    //        memcpy(DDDPD2711out,_DDDPDout+iStartPos1,920);
    //        temp_DDDPD+=920;
    //        deallen = iStartPos1+920;
            switch (type)
            {
            //40
            case DDDPD_S: //22
                //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
                memcpy(DDDPD2711out,_obtainedSourceStream->DDDPDdata+iStartPos1,920);
                temp_DDDPD+=920;
                deallen = iStartPos1+920;
                break;
            case DDDPDKC_S:  //28
                //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
                memcpy(DDDPDKC2711out,_obtainedSourceStream->DDDPDdata+iStartPos1,920);
                temp_DDDPDKC+=920;
                deallen = iStartPos1+920;
                break;
            default:
                deallen+=4;
                break;
            }

            while (deallen+920<=cysumlen)
            {
                flag = ((_obtainedSourceStream->DDDPDdata[deallen] << 24) | (_obtainedSourceStream->DDDPDdata[deallen+1] << 16) | (_obtainedSourceStream->DDDPDdata[deallen+2] << 8) |_obtainedSourceStream->SSDDDPDdata[deallen+3]) & 0xffffffff;
    //            insert = (_obtainedSourceStream->SSDDDPDdata[deallen + 4] <<8 ) | _obtainedSourceStream->SSDDDPDdata[deallen+5];
    //            if(insert==19024){
    //                qDebug()<<insert;
    //            }
                if(flag == 0xF5F6EB90)
                {
                    type = _obtainedSourceStream->DDDPDdata[deallen+6];
                    switch (type)
                    {
                    //40
                    case DDDPD_S: //22
                        //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
                        memcpy(DDDPD2711out+temp_DDDPD,_obtainedSourceStream->DDDPDdata+deallen,920);
                        temp_DDDPD+=920;
                        deallen = deallen+920;
                        break;
                    case DDDPDKC_S:  //28
                        //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
                        memcpy(DDDPDKC2711out+temp_DDDPDKC,_obtainedSourceStream->DDDPDdata+deallen,920);
                        temp_DDDPDKC+=920;
                        deallen = deallen+920;
                        break;
                    default:
                        deallen+=4;
                        break;
                    }

                }
                else
                {
                    if(UnPack::barkDetect(_obtainedSourceStream->DDDPDdata, cysumlen, deallen, &iStartPos1))
                    {
                        if(iStartPos1+920<=cysumlen)
                        {
    //                        insert = (_obtainedSourceStream->SSDDDPDdata[iStartPos1 + 4] <<8 ) | _obtainedSourceStream->SSDDDPDdata[iStartPos1+5];
    //                        if(insert==19024){
    //                            qDebug()<<insert;
    //                        }
                            type= _obtainedSourceStream->DDDPDdata[iStartPos1+6];
                            switch (type)
                            {
                            case DDDPD_S:
                                memcpy(DDDPD2711out+temp_DDDPD, _obtainedSourceStream->DDDPDdata + iStartPos1, 920);
                                temp_DDDPD += 920;
                                //*iZXGC = temp_ZXGC;
                                deallen = iStartPos1 + 920;
                                break;
                            case DDDPDKC_S:
                                memcpy(DDDPDKC2711out+temp_DDDPDKC, _obtainedSourceStream->DDDPDdata + iStartPos1, 920);
                                temp_DDDPDKC += 920;
                                //*iZXGC = temp_ZXGC;
                                deallen = iStartPos1 + 920;
                                break;
                            default:
                                deallen =iStartPos1 + 4;
                                break;
                            }

                        }
                        else
                        {
                            deallen = iStartPos1;
                        }
                    }
                    else
                    {
                        deallen = iStartPos1;
                    }
                }

            }

         }

        *rmlen=cysumlen-deallen;
        memcpy(_obtainedSourceStream->DDDPDdata,_obtainedSourceStream->DDDPDdata+deallen,*rmlen);
        continuejudge(DDDPD2711out, temp_DDDPD,8,&dddpd2711num);
        continuejudge(DDDPDKC2711out, temp_DDDPDKC,10,&dddpdkc2711num);
    }

    *pdid=dddpd2711num;
    *kcid=dddpdkc2711num;


    EPDUflag = 5;
    //extract_2711(_comDDDPD->img, _comDDDPD->ilen, _DDDPDout,EPDUflag,0);
    //写文件
    FILE *fpOut;
    if(type==0x22&&state)
    {
        sprintf(fileName, "%s/SSDDDPD_2711.dat", outputpath2711package);
        fpOut = fopen(fileName, "ab");
        //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
        fwrite(DDDPD2711out, temp_DDDPD, 1, fpOut);
        //DKCBlen += (12 + datalen);
        fclose(fpOut);
        fpOut = NULL;
    }
    if(type==0x28&&state)
    {
        sprintf(fileName, "%s/SSDDDPDKC_2711.dat", outputpath2711package);
        fpOut = fopen(fileName, "ab");
        //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
        fwrite(DDDPDKC2711out, temp_DDDPDKC, 1, fpOut);
        //DKCBlen += (12 + datalen);
        fclose(fpOut);
        fpOut = NULL;
    }
    if(type==0x22&&state==0)
    {
        sprintf(fileName, "%s/DDDPD_2711.dat", outputpath2711package);
        fpOut = fopen(fileName, "ab");
        //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
        fwrite(DDDPD2711out, temp_DDDPD, 1, fpOut);
        //DKCBlen += (12 + datalen);
        fclose(fpOut);
        fpOut = NULL;
    }
    if(type==0x28&&state==0)
    {
        sprintf(fileName, "%s/DDDPDKC_2711.dat", outputpath2711package);
        fpOut = fopen(fileName, "ab");
        //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
        fwrite(DDDPDKC2711out, temp_DDDPDKC, 1, fpOut);
        //DKCBlen += (12 + datalen);
        fclose(fpOut);
        fpOut = NULL;
    }




    //给快视
    memcpy(_DDDPDout,DDDPD2711out,temp_DDDPD);
    memcpy(_DDDPDKCout,DDDPDKC2711out,temp_DDDPDKC);

    free(DDDPD2711out);DDDPD2711out=NULL;
    free(DDDPDKC2711out);DDDPDKC2711out=NULL;
    *dddpdkclen=temp_DDDPDKC;
    return temp_DDDPD;
}

int DealSourcePackage::dealDDDBPackage(unsigned char *_strDDDB, int _DDDBlen, compressedStream *_comDDDB, SourceStream *_obtainedSourceStream, unsigned char *_DDDBout,unsigned char* _DDDB2711out,int *rmlen,bool state,unsigned int *packnumid,unsigned int *dddbid)
{
    __int64         temp_DDDB = 0;

    int EPDUflag;
    int iStartPos1 = 0;
    int cysumlen =0;
    __int64 BUFFSIZE = (128* 1024 * 1024);
    unsigned char	*DDDB2711out= NULL;

    DDDB2711out = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));

    unsigned int flag;
    int    type = 0x00;
    int    datalen = 0;
    int deallen = 0;

    char fileName[fileNameLen];
    unsigned int dddbpacknum=*packnumid;
    unsigned int dddb2711num=*dddbid;
    unpack->unpack1(_strDDDB, _DDDBlen, _comDDDB->img, &(_comDDDB->ilen), outputpathLog,state,&dddbpacknum);
    *packnumid=dddbpacknum;
//    unpack->unpack(_strDDDB, _DDDBlen, _comDDDB->img, &(_comDDDB->ilen), outputpathLog,state);
    cysumlen = _comDDDB->ilen+*rmlen;

    memcpy(_DDDBout+*rmlen,_comDDDB->img,_comDDDB->ilen);
    EPDUflag = 6;
    //extract_2711(_comDDDPD->img, _comDDDPD->ilen, _DDDPDout,EPDUflag,0);
    if(UnPack::barkDetect(_DDDBout,cysumlen,0,&iStartPos1))
    {

        type= _DDDBout[iStartPos1+6];  //0X22
        memcpy(DDDB2711out,_DDDBout+iStartPos1,920);
        temp_DDDB+=920;
        deallen = iStartPos1+920;

        while (deallen+920<=cysumlen)
        {
            flag = ((_DDDBout[deallen] << 24) | (_DDDBout[deallen+1] << 16) | (_DDDBout[deallen+2] << 8) | _DDDBout[deallen+3]) & 0xffffffff;
            if(flag == 0xF5F6EB90)
            {
                type = _DDDBout[deallen+6];
                if(type==0x21)
                {
                    memcpy(DDDB2711out+temp_DDDB, _DDDBout + deallen, 920);
                    temp_DDDB += 920;
                    //*iZXGC = temp_ZXGC;
                    deallen = deallen + 920;
                }
                else{
                    deallen+=4;
                }
            }
            else
            {
                if(UnPack::barkDetect(_DDDBout, cysumlen, deallen, &iStartPos1))
                {
                    if(iStartPos1+920<=cysumlen)
                    {
                        memcpy(DDDB2711out+temp_DDDB, _DDDBout + iStartPos1, 920);
                        temp_DDDB += 920;
                        //*iZXGC = temp_ZXGC;
                        deallen = iStartPos1 + 920;
                    }
                    else
                    {
                        deallen = iStartPos1;
                    }
                }
                else
                {
                    deallen = iStartPos1;
                }
            }

        }

        if(state)
        {
            continuejudge(DDDB2711out, temp_DDDB,5,&dddb2711num);
        }
        else{
            continuejudge(DDDB2711out, temp_DDDB,6,&dddb2711num);
        }

        *dddbid=dddb2711num;

        //写文件
        FILE *fpOut;
        if(state){
            sprintf(fileName, "%s/SSDDDB_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DDDB2711out, temp_DDDB, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        else{
            sprintf(fileName, "%s/DDDB_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DDDB2711out, temp_DDDB, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }


     }

    *rmlen=cysumlen-deallen;
    memcpy(_DDDBout,_DDDBout+deallen,*rmlen);
    memcpy(_DDDB2711out,DDDB2711out,temp_DDDB);
    free(DDDB2711out);DDDB2711out=NULL;
    return temp_DDDB;
}

int DealSourcePackage::dealDKZCBPackage(unsigned char *_strDKZCB, int _DKZCBlen, compressedStream *_comDKZCB, SourceStream *_obtainedSourceStream, unsigned char *_DKZCBout,unsigned char *_DKZCB2711out,int *rmlen,bool state,unsigned int *packnumid,unsigned int *zcbid)
{
    __int64         temp_DKZCB = 0;

    int EPDUflag;
    int iStartPos1 = 0;
    int cysumlen=0;
    __int64 BUFFSIZE = (128* 1024 * 1024);
    unsigned char	*DKZCB2711out= NULL;

    DKZCB2711out = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));

    unsigned int flag;
    int    type = 0x00;
    int    datalen = 0;
    int deallen = 0;

    char fileName[fileNameLen];

    unsigned int dkzcbpacknum=*packnumid;
    unsigned int dkzcb2711num=*zcbid;
    unpack->unpack1(_strDKZCB, _DKZCBlen, _comDKZCB->img, &(_comDKZCB->ilen), outputpathLog,state,&dkzcbpacknum);
    *packnumid=dkzcbpacknum;
//    unpack->unpack(_strDKZCB, _DKZCBlen, _comDKZCB->img, &(_comDKZCB->ilen), outputpathLog,state);   //img为该buf中的EPDU数据
    //memcpy(_obtainedSourceStream->DKCBdata+iShiftLenDKCB,_comDKCB->img,_DKCBlen);   //考虑残余数据的情况   iShiftlen如何变
    cysumlen = _comDKZCB->ilen+*rmlen;

    memcpy(_DKZCBout+*rmlen,_comDKZCB->img,_comDKZCB->ilen);   //考虑残余数据的情况   iShiftlen如何变
    EPDUflag=4;
    if(UnPack::barkDetect(_DKZCBout,cysumlen,0,&iStartPos1))
    {

        type= _DKZCBout[iStartPos1+6];  //0x11
        memcpy(DKZCB2711out,_DKZCBout+iStartPos1,920);
        temp_DKZCB+=920;
        deallen = iStartPos1+920;

        while (deallen+920<=cysumlen)
        {
            flag = ((_DKZCBout[deallen] << 24) | (_DKZCBout[deallen+1] << 16) | (_DKZCBout[deallen+2] << 8) |_DKZCBout[deallen+3]) & 0xffffffff;
            if(flag == 0xF5F6EB90)
            {
                type = _DKZCBout[deallen+6];
                if(type==0X12)
                {
                    memcpy(DKZCB2711out+temp_DKZCB, _DKZCBout + deallen, 920);
                    temp_DKZCB += 920;
                    //*iZXGC = temp_ZXGC;
                    deallen = deallen + 920;
                }
                else{
                    deallen+=4;
                }
            }
            else
            {
                if(UnPack::barkDetect(_DKZCBout, cysumlen, deallen, &iStartPos1))
                {
                    if(iStartPos1+920<=cysumlen)
                    {
                        memcpy(DKZCB2711out+temp_DKZCB, _DKZCBout + iStartPos1, 920);
                        temp_DKZCB += 920;
                        //*iZXGC = temp_ZXGC;
                        deallen = iStartPos1 + 920;
                    }
                    else
                    {
                        deallen = iStartPos1;
                    }
                }
                else{
                    deallen = iStartPos1;
                }

            }

        }
        *rmlen=cysumlen-deallen;
        memcpy(_DKZCBout,_DKZCBout+deallen,*rmlen);
        if(state)
        {
            continuejudge(DKZCB2711out, temp_DKZCB,3,&dkzcb2711num);
        }
        else{
            continuejudge(DKZCB2711out, temp_DKZCB,4,&dkzcb2711num);
        }
        *zcbid=dkzcb2711num;

        //写文件
        FILE *fpOut;
        if(state){
            sprintf(fileName, "%s/SSDKZCB_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DKZCB2711out, temp_DKZCB, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        else {
            sprintf(fileName, "%s/DKZCB_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(DKZCB2711out, temp_DKZCB, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }

     }
    *rmlen=cysumlen-deallen;
    memcpy(_DKZCBout,_DKZCBout+deallen,*rmlen);
    memcpy(_DKZCB2711out,DKZCB2711out,temp_DKZCB);
    free(DKZCB2711out);DKZCB2711out=NULL;
    return temp_DKZCB;
}

void DealSourcePackage::dealZXGCPackage(unsigned char *_strZXGC, int _ZXGClen, compressedStream *_comZXGC, SourceStream *_obtainedSourceStream, unsigned char *_ZXGCout,int *rmlen,bool state)
{
    __int64         temp_ZXGC = 0;

    int EPDUflag;
    int iStartPos1 = 0;
    int cysumlen=0;
    __int64 BUFFSIZE = (128* 1024 * 1024);
    unsigned char	*ZXGC2711out= NULL;

    ZXGC2711out = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));

    unsigned int flag;
    int    type = 0x00;
    int    datalen = 0;
    int deallen = 0;

    char fileName[fileNameLen];
    unpack->unpackxwgc(_strZXGC, _ZXGClen, _comZXGC->img, &(_comZXGC->ilen), outputpathLog);   //img为该buf中的EPDU数据
    cysumlen = _comZXGC->ilen+*rmlen;

    memcpy(_ZXGCout+*rmlen,_comZXGC->img,_comZXGC->ilen);   //考虑残余数据的情况   iShiftlen如何变
    //memcpy(_obtainedSourceStream->DKCBdata,_comDKCB->img,_DKCBlen);   //考虑残余数据的情况   iShiftlen如何变
    EPDUflag=1;
    //在EPDU域搜索F5F6EB90
    //extract_2711(_comZXGC->img, _comZXGC->ilen, _ZXGCout,EPDUflag,0);
    if(UnPack::xwgcDetect(_ZXGCout,cysumlen,0,&iStartPos1))
    {

        type= _ZXGCout[iStartPos1+4];  //0X71
        if(type==0x71){
            datalen = (_ZXGCout[iStartPos1 + 2] <<8 ) |_ZXGCout[iStartPos1+3];
            memcpy(ZXGC2711out,_ZXGCout+iStartPos1,datalen+8);
            temp_ZXGC+=datalen+8;
            deallen = iStartPos1+datalen+8;
        }
        else{
            deallen =iStartPos1+2;
        }


        //xwgc最大长度600+8
        while (deallen+608<=cysumlen)
        {
            flag = ((_ZXGCout[deallen] << 8) | (_ZXGCout[deallen+1]) ) & 0xffff;
            if(flag == 0xEB90)
            {
                //type = _comZXGC->img[deallen+6];
                type= _ZXGCout[deallen+4];
                datalen = (_ZXGCout[deallen + 2] <<8 ) | _ZXGCout[deallen+3];
//                if(datalen>600)
//                {
//                    break;
//                }
                if(deallen+8+datalen<cysumlen)
                {
                    if(type==0x71 )
                    {
                        memcpy(ZXGC2711out+temp_ZXGC, _ZXGCout + deallen, datalen+8);
                        temp_ZXGC += datalen+8;
                        //*iZXGC = temp_ZXGC;
                        deallen = deallen + datalen+8;
                    }
                    else{
                        deallen+=2;
                    }
                }
                else{
                    break;
                }


            }
            else
            {
                if(UnPack::xwgcDetect(_ZXGCout, cysumlen, deallen, &iStartPos1))
                {
                    if(iStartPos1+608<=cysumlen)
                    {
                        type= _ZXGCout[iStartPos1+4];
                        if(iStartPos1+8+datalen<cysumlen)
                        {
                            if(type==0x71 )
                            {
                                memcpy(ZXGC2711out+temp_ZXGC, _ZXGCout + iStartPos1, datalen+8);
                                temp_ZXGC += datalen+8;
                                //*iZXGC = temp_ZXGC;
                                deallen = iStartPos1 + datalen+8;
                            }
                            else{
                                deallen = iStartPos1+2;
                            }
                        }
                        else{
                            break;
                        }

                    }
                    else
                    {
                        deallen = iStartPos1;
                    }
                }
                else
                {
                    deallen = iStartPos1;
                }
            }

        }

        //如果能找到下一个EB90
        while(UnPack::xwgcDetect(_ZXGCout, cysumlen, deallen, &iStartPos1))
        {
            type= _ZXGCout[iStartPos1+4];
            datalen = (_ZXGCout[iStartPos1 + 2] <<8 ) | _ZXGCout[iStartPos1+3];
//            if(type==0x71 )
//            {
//                memcpy(_ZXGCout+temp_ZXGC, _obtainedSourceStream->ZXGCdata + deallen, datalen+8);
//                temp_ZXGC += datalen+8;
//                //*iZXGC = temp_ZXGC;
//                deallen = deallen + datalen+8;
//            }
//            else{
//                break;
//            }
            if(iStartPos1+8+datalen<cysumlen){
                if(type==0x71 )
                {
                    memcpy(ZXGC2711out+temp_ZXGC, _ZXGCout + iStartPos1, datalen+8);
                    temp_ZXGC += datalen+8;
                    //*iZXGC = temp_ZXGC;
                    deallen = iStartPos1 + datalen+8;
                }
                else{
                    deallen =iStartPos1+2;
                }
            }
            else{
                break;
            }
        }



        //写文件
        FILE *fpOut;
        if(state){
            sprintf(fileName, "%s/SSZXGC_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(ZXGC2711out, temp_ZXGC, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        else{
            sprintf(fileName, "%s/ZXGC_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(ZXGC2711out, temp_ZXGC, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }


     }
    *rmlen=cysumlen-deallen;
    memcpy(_ZXGCout,_ZXGCout+deallen,*rmlen);
    free(ZXGC2711out);ZXGC2711out=NULL;
}

void DealSourcePackage::dealXJCSPackage(unsigned char *_strXJCS, int _XJCSlen, compressedStream *_comXJCS, SourceStream *_obtainedSourceStream, unsigned char *_XJCSout,int *rmlen,bool state,unsigned int *packnumid)
{
    __int64         temp_DK = 0,temp_DD=0;

    int cysumlen=0;

    //为2711包分配空间
    __int64 BUFFSIZE = (128* 1024 * 1024);
    unsigned char	*DKout= NULL, *DDout= NULL;    

    DKout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    DDout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));



    //补充完整
    if(NULL==DDout||NULL==DDout)
    {
        MainWindow::fakeUi->setLinetext(QString("内存分配fail!\n"));
    }



    int EPDUflag;
    int iStartPos1 = 0;

    unsigned int flag;
    int    type = 0x00;
    int    datalen = 0;
    int deallen = 0;

    char fileName[fileNameLen];

    unsigned int xjcspacknum = *packnumid;
    unpack->unpack1(_strXJCS, _XJCSlen, _comXJCS->img, &(_comXJCS->ilen), outputpathLog,state,&xjcspacknum);   //img为该buf中的EPDU数据
    *packnumid = xjcspacknum;
//    unpack->unpack(_strXJCS, _XJCSlen, _comXJCS->img, &(_comXJCS->ilen), outputpathLog,state);   //img为该buf中的EPDU数据
    //memcpy(_obtainedSourceStream->DKCBdata+iShiftLenDKCB,_comDKCB->img,_DKCBlen);   //考虑残余数据的情况   iShiftlen如何变
    cysumlen = _comXJCS->ilen+*rmlen;

    memcpy(_obtainedSourceStream->XJCSdata+*rmlen,_comXJCS->img,_comXJCS->ilen);   //考虑残余数据的情况   iShiftlen如何变
    EPDUflag=7;
    //检测到F5F6EB90
    if(UnPack::barkDetect(_obtainedSourceStream->XJCSdata,cysumlen,0,&iStartPos1))
    {

        type= _obtainedSourceStream->XJCSdata[iStartPos1+6];
        switch (type)
        {
        //40
        case DK_S: //14
            //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
            memcpy(DKout,_obtainedSourceStream->XJCSdata+iStartPos1,920);
            temp_DK+=920;
            deallen = iStartPos1+920;
            break;
        case DD_S:  //24
            //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
            memcpy(DDout,_obtainedSourceStream->XJCSdata+iStartPos1,920);
            temp_DD+=920;
            deallen = iStartPos1+920;
            break;
        default:
            //qDebug()<<type<<"weizhiyuanbao";
            deallen=iStartPos1+4;
            break;
        }


        while (deallen+920<=cysumlen)
        {
            flag = ((_obtainedSourceStream->XJCSdata[deallen] << 24) | (_obtainedSourceStream->XJCSdata[deallen+1] << 16) | (_obtainedSourceStream->XJCSdata[deallen+2] << 8) |_obtainedSourceStream->XJCSdata[deallen+3]) & 0xffffffff;
            if(flag == 0xF5F6EB90)
            {
                type = _obtainedSourceStream->XJCSdata[deallen+6];
                switch (type)
                {
                //40
                case DK_S:
                    //datalen = (_comRWSJ->img[deallen + 8] <<8 ) | _comRWSJ->img[deallen+9];
                    memcpy(DKout+temp_DK,_obtainedSourceStream->XJCSdata+deallen,920);
                    temp_DK+=920;
                    deallen = deallen+920;
                    break;
                case DD_S:
                    //datalen = (_comXJCS->img[deallen + 8] <<8 ) | _comXJCS->img[deallen+9];
                    memcpy(DDout+temp_DD,_obtainedSourceStream->XJCSdata+deallen,920);
                    temp_DD+=920;
                    deallen = deallen+920;
                    break;

                default:
                    //qDebug()<<type<<"weizhiyuanbao";
//                    flag = ((_comRWSJ->img[deallen] << 24) | (_comRWSJ->img[deallen+1] << 16) | (_comRWSJ->img[deallen+2] << 8) |_comRWSJ->img[deallen+3]) & 0xffffffff;
//                    qDebug()<<flag;
//                    type = _comRWSJ->img[deallen+7];

//                    type = _comRWSJ->img[deallen+8];

                    //type = _comRWSJ->img[deallen+6];
                    deallen +=4;
                    break;
                }

//                if(type==0X11)
//                {
//                    memcpy(_DKCBout+temp_DKCB, _comDKCB->img + deallen, 920);
//                    temp_DKCB += 920;
//                    //*iZXGC = temp_ZXGC;
//                    deallen = deallen + 920;
//                }
            }
            else
            {
                if(UnPack::barkDetect(_obtainedSourceStream->XJCSdata, cysumlen, deallen, &iStartPos1))
                {

                    if(iStartPos1+920<=cysumlen)
                    {
//                        memcpy(_DKCBout+temp_DKCB, _comDKCB->img + deallen, 920);
//                        temp_DKCB += 920;
//                        //*iZXGC = temp_ZXGC;
//                        deallen = deallen + 920;
                        type = _obtainedSourceStream->XJCSdata[iStartPos1+6];
                        switch (type)
                        {
                        case DK_S:
                            //datalen = (_comRWSJ->img[iStartPos1 + 8] <<8 ) | _comRWSJ->img[iStartPos1+9];
                            memcpy(DKout+temp_DK,_obtainedSourceStream->XJCSdata+iStartPos1,920);
                            temp_DK+=920;
                            deallen = iStartPos1+920;
                            break;
                        case DD_S:
                            //datalen = (_comRWSJ->img[iStartPos1 + 8] <<8 ) | _comRWSJ->img[iStartPos1+9];
                            memcpy(DDout+temp_DD,_obtainedSourceStream->XJCSdata+iStartPos1,920);
                            temp_DD+=920;
                            deallen = iStartPos1+920;
                            break;
                        default:
                            //qDebug()<<type<<"weizhiyuanbao1";
//                            flag = ((_comRWSJ->img[deallen] << 24) | (_comRWSJ->img[deallen+1] << 16) | (_comRWSJ->img[deallen+2] << 8) |_comRWSJ->img[deallen+3]) & 0xffffffff;
//                            qDebug()<<flag;
//                            type = _comRWSJ->img[deallen+7];

//                            type = _comRWSJ->img[deallen+8];

                            //type = _obtainedSourceStream->XJCSdata[iStartPos1+6];
                            deallen=iStartPos1+4;
                            break;
                        }

                    }
                    else
                    {
                        deallen = iStartPos1;
                    }
                }
                else{
                    deallen = iStartPos1;
                }

            }

        }
        FILE *fpOut;
        char outwords[200];
        //连续性判断，数字位7
        if(temp_DD>0)
        {
            unsigned int ddflag1,ddflag2;
            for(int i=0;i<temp_DD/920;i++){
                if(i==0){
                    ddflag1=((DDout[12]<<8)|DDout[13])& 0xFFFF;
                }
                else{
                    ddflag2=((DDout[12+i*920]<<8)|DDout[13+i*920])& 0xFFFF;
                    if(ddflag1+1!=ddflag2){
                        //qDebug()<<"bylianxu";
                        sprintf(outwords,"DDXJCS图像连续性检测中，第%d包与第%d包之间不连续\n",ddflag1,ddflag2);
                        //sprintf(fileName,"%s/image.txt",outputpathLog);
                        sprintf(fileName,"%s/DDXJCScontinue.txt",outputpathLog);
                        fpOut = fopen(fileName,"ab");
                        if(fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;

                    }
                    ddflag1=ddflag2;
                }

                int check = 0;
                int check1=0;
                for(int j = 8; j < 918; j++)
                {
                    /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                        qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
                    check =(check+DDout[920*i+j]);
                    //11.2删
                    //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
                }
                //check=check+datalen;
                check=check&0xffff;
                check1=((DDout[920*i + 918] << 8) | DDout[920*i + 919])&0xffff;

                if(check != check1)
                {
        //            qDebug()<<"adderror"<<endl;//加和报错
                    sprintf(outwords,"ddxjcs图像，%d包检验和错误\n",ddflag1);
                    //sprintf(fileName,"%s/image.txt",outputpathLog);
                    sprintf(fileName,"ddxjcsadderror%s.txt",outputpathLog);
                    fpOut = fopen(fileName,"ab");
                    if(fpOut == NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;

                }
            }
        }
        if(temp_DK>0)
        {
            unsigned int dkflag1,dkflag2;
            for(int i=0;i<temp_DK/920;i++){
                if(i==0){
                    dkflag1=((DKout[12]<<8)|DKout[13])& 0xFFFF;
                    //((Inputcode[12+i*920]<<8)|Inputcode[13+i*920])& 0xFFFF
                }
                else{
                    dkflag2=((DKout[12+i*920]<<8)|DKout[13+i*920])& 0xFFFF;
                    if(dkflag1+1!=dkflag2){
                        //qDebug()<<"bylianxu";
                        sprintf(outwords,"DDXJCS图像连续性检测中，第%d包与第%d包之间不连续\n",dkflag1,dkflag2);
                        //sprintf(fileName,"%s/image.txt",outputpathLog);
                        sprintf(fileName,"%s/DkXJCScontinue.txt",outputpathLog);
                        fpOut = fopen(fileName,"ab");
                        if(fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;

                    }
                    dkflag1=dkflag2;
                }

                int check = 0;
                int check1=0;
                for(int j = 8; j < 918; j++)
                {
                    /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                        qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
                    check =(check+DKout[920*i+j]);
                    //11.2删
                    //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
                }
                //check=check+datalen;
                check=check&0xffff;
                check1=((DKout[920*i + 918] << 8) | DKout[920*i + 919])&0xffff;

                if(check != check1)
                {
        //            qDebug()<<"adderror"<<endl;//加和报错
                    sprintf(outwords,"dKxjcs图像，%d包检验和错误\n",dkflag1);
                    //sprintf(fileName,"%s/image.txt",outputpathLog);
                    sprintf(fileName,"dKxjcsadderror%s.txt",outputpathLog);
                    fpOut = fopen(fileName,"ab");
                    if(fpOut == NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;

                }
            }
        }



        //写文件

        if(temp_DK>0)
        {
            if(state){
                sprintf(fileName, "%s/ssDK_2711.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DKout, temp_DK, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            else{
                sprintf(fileName, "%s/DK_2711.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DKout, temp_DK, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }

        }
        if(temp_DD>0)
        {
            if(state){
                sprintf(fileName, "%s/ssDD_2711.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DDout, temp_DD, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            else{
                sprintf(fileName, "%s/DD_2711.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(DDout, temp_DD, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }

        }



//        sprintf(fileName, "%s/DKCB_2711.dat", outputpath2711package);
//        fpOut = fopen(fileName, "ab");
//        //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
//        fwrite(_DKCBout, temp_DKCB, 1, fpOut);
//        //DKCBlen += (12 + datalen);
//        fclose(fpOut);
//        fpOut = NULL;
     }
    *rmlen=cysumlen-deallen;
    memcpy(_obtainedSourceStream->XJCSdata,_obtainedSourceStream->XJCSdata+deallen,*rmlen);
    free(DKout);DKout = NULL;
    free(DDout);DDout = NULL;
}

void DealSourcePackage::dealJGCSPackage(unsigned char *_strJGCS, int _JGCSlen, compressedStream *_comJGCS, SourceStream *_obtainedSourceStream, unsigned char *_JGCSout,int *rmlen,unsigned int *packnumid)
{
    __int64         temp_JGHW = 0,temp_JGCJFSJZ=0,temp_JGCJJSJZ=0;

    //为2711包分配空间
    __int64 BUFFSIZE = (128* 1024 * 1024);
    unsigned char	*JGHWout= NULL, *JGCJFSJZout= NULL, *JGCJJSJZout= NULL;

    JGHWout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    JGCJFSJZout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    JGCJJSJZout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));


    //补充完整
    if(NULL==JGHWout||NULL==JGCJFSJZout||JGCJJSJZout)
    {
        MainWindow::fakeUi->setLinetext(QString("内存分配fail!\n"));
    }



    int EPDUflag;
    int iStartPos1 = 0;
    int cysumlen =0;

    unsigned int flag;
    int    type = 0x00;
    int    datalen = 0;
    int deallen = 0;

    char fileName[fileNameLen];

    unsigned int jgcspacknum=*packnumid;
    unpack->unpack1(_strJGCS, _JGCSlen, _comJGCS->img, &(_comJGCS->ilen), outputpathLog,1,&jgcspacknum);   //img为该buf中的EPDU数据
    *packnumid = jgcspacknum;
//    unpack->unpack(_strJGCS, _JGCSlen, _comJGCS->img, &(_comJGCS->ilen), outputpathLog,1);   //img为该buf中的EPDU数据
    //memcpy(_obtainedSourceStream->DKCBdata+iShiftLenDKCB,_comDKCB->img,_DKCBlen);   //考虑残余数据的情况   iShiftlen如何变
    cysumlen = _comJGCS->ilen+*rmlen;

    memcpy(_obtainedSourceStream->JGCSdata+*rmlen,_comJGCS->img,_comJGCS->ilen);
    EPDUflag=8;
    //检测到F5F6EB90
    if(UnPack::barkDetect(_obtainedSourceStream->JGCSdata,cysumlen,0,&iStartPos1))
    {

        type= _obtainedSourceStream->JGCSdata[iStartPos1+6];
        switch (type)
        {
        //40
        case JGHW_S: //31
            //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
            memcpy(JGHWout,_obtainedSourceStream->JGCSdata+iStartPos1,920);
            temp_JGHW+=920;
            deallen = iStartPos1+920;
            break;
        case JGCJFSJZ_S:  //34
            //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
            memcpy(JGCJFSJZout,_obtainedSourceStream->JGCSdata+iStartPos1,920);
            temp_JGCJFSJZ+=920;
            deallen = iStartPos1+920;
            break;
        case JGCJJSJZ_S:  //34
            //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
            memcpy(JGCJJSJZout,_obtainedSourceStream->JGCSdata+iStartPos1,920);
            temp_JGCJJSJZ+=920;
            deallen = iStartPos1+920;
            break;
        default:
            //qDebug()<<type<<"weizhiyuanbao";
            deallen=iStartPos1+4;
            break;
        }


        while (deallen+920<=cysumlen)
        {
            flag = ((_obtainedSourceStream->JGCSdata[deallen] << 24) | (_obtainedSourceStream->JGCSdata[deallen+1] << 16) | (_obtainedSourceStream->JGCSdata[deallen+2] << 8) |_obtainedSourceStream->JGCSdata[deallen+3]) & 0xffffffff;
            if(flag == 0xF5F6EB90)
            {
                type = _obtainedSourceStream->JGCSdata[deallen+6];
                switch (type)
                {
                //40
                case JGHW_S:
                    //datalen = (_comRWSJ->img[deallen + 8] <<8 ) | _comRWSJ->img[deallen+9];
                    memcpy(JGHWout+temp_JGHW,_obtainedSourceStream->JGCSdata+deallen,920);
                    temp_JGHW+=920;
                    deallen = deallen+920;
                    break;
                case JGCJFSJZ_S:
                    //datalen = (_comXJCS->img[deallen + 8] <<8 ) | _comXJCS->img[deallen+9];
                    memcpy(JGCJFSJZout+temp_JGCJFSJZ,_obtainedSourceStream->JGCSdata+deallen,920);
                    temp_JGCJFSJZ+=920;
                    deallen = deallen+920;
                    break;

                case JGCJJSJZ_S:
                    //datalen = (_comXJCS->img[deallen + 8] <<8 ) | _comXJCS->img[deallen+9];
                    memcpy(JGCJJSJZout+temp_JGCJJSJZ,_obtainedSourceStream->JGCSdata+deallen,920);
                    temp_JGCJJSJZ+=920;
                    deallen = deallen+920;
                    break;
                default:
                    //qDebug()<<type<<"weizhiyuanbao";
//                    flag = ((_comRWSJ->img[deallen] << 24) | (_comRWSJ->img[deallen+1] << 16) | (_comRWSJ->img[deallen+2] << 8) |_comRWSJ->img[deallen+3]) & 0xffffffff;
//                    qDebug()<<flag;
//                    type = _comRWSJ->img[deallen+7];

//                    type = _comRWSJ->img[deallen+8];

                    //type = _comRWSJ->img[deallen+6];
                    deallen+=4;
                    break;
                }

//                if(type==0X11)
//                {
//                    memcpy(_DKCBout+temp_DKCB, _comDKCB->img + deallen, 920);
//                    temp_DKCB += 920;
//                    //*iZXGC = temp_ZXGC;
//                    deallen = deallen + 920;
//                }
            }
            else
            {
                if(UnPack::barkDetect(_obtainedSourceStream->JGCSdata, cysumlen, deallen, &iStartPos1))
                {

                    if(iStartPos1+920<=cysumlen)
                    {
//                        memcpy(_DKCBout+temp_DKCB, _comDKCB->img + deallen, 920);
//                        temp_DKCB += 920;
//                        //*iZXGC = temp_ZXGC;
//                        deallen = deallen + 920;
                        type = _obtainedSourceStream->JGCSdata[iStartPos1+6];
                        switch (type)
                        {
                        case JGHW_S:
                            //datalen = (_comRWSJ->img[iStartPos1 + 8] <<8 ) | _comRWSJ->img[iStartPos1+9];
                            memcpy(JGHWout+temp_JGHW,_obtainedSourceStream->JGCSdata+iStartPos1,920);
                            temp_JGHW+=920;
                            deallen = iStartPos1+920;
                            break;
                        case JGCJFSJZ_S:
                            //datalen = (_comRWSJ->img[iStartPos1 + 8] <<8 ) | _comRWSJ->img[iStartPos1+9];
                            memcpy(JGCJFSJZout+temp_JGCJFSJZ,_obtainedSourceStream->JGCSdata+iStartPos1,920);
                            temp_JGCJFSJZ+=920;
                            deallen = iStartPos1+920;
                            break;
                        case JGCJJSJZ_S:
                            //datalen = (_comRWSJ->img[iStartPos1 + 8] <<8 ) | _comRWSJ->img[iStartPos1+9];
                            memcpy(JGCJJSJZout+temp_JGCJJSJZ,_obtainedSourceStream->JGCSdata+iStartPos1,920);
                            temp_JGCJJSJZ+=920;
                            deallen = iStartPos1+920;
                            break;
                        default:
                            //qDebug()<<type<<"weizhiyuanbao1";
//                            flag = ((_comRWSJ->img[deallen] << 24) | (_comRWSJ->img[deallen+1] << 16) | (_comRWSJ->img[deallen+2] << 8) |_comRWSJ->img[deallen+3]) & 0xffffffff;
//                            qDebug()<<flag;
//                            type = _comRWSJ->img[deallen+7];

//                            type = _comRWSJ->img[deallen+8];

                            //type = _obtainedSourceStream->JGCSdata[iStartPos1+6];
                            deallen=iStartPos1+4;
                            break;
                        }

                    }
                    else
                    {
                        deallen = iStartPos1;
                    }
                }
                else{
                    deallen = iStartPos1;
                }

            }

        }


        //写文件
        FILE *fpOut;
        if(temp_JGHW>0)
        {
            continuejudgejgcj(JGHWout, temp_JGHW,11);
            sprintf(fileName, "%s/JGHW_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(JGHWout, temp_JGHW, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_JGCJFSJZ>0)
        {
            continuejudgejgcj(JGCJFSJZout, temp_JGCJFSJZ,12);
            sprintf(fileName, "%s/JGCJFSJZ_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(JGCJFSJZout, temp_JGCJFSJZ, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_JGCJJSJZ>0)
        {
            continuejudgejgcj(JGCJJSJZout, temp_JGCJJSJZ,13);
            sprintf(fileName, "%s/JGCJJSJZ_2711.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(JGCJJSJZout, temp_JGCJJSJZ, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }



//        sprintf(fileName, "%s/DKCB_2711.dat", outputpath2711package);
//        fpOut = fopen(fileName, "ab");
//        //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
//        fwrite(_DKCBout, temp_DKCB, 1, fpOut);
//        //DKCBlen += (12 + datalen);
//        fclose(fpOut);
//        fpOut = NULL;
     }
    *rmlen=cysumlen-deallen;
    memcpy(_obtainedSourceStream->JGCSdata,_obtainedSourceStream->JGCSdata+deallen,*rmlen);
    free(JGHWout);JGHWout=NULL;
    free(JGCJFSJZout);JGCJFSJZout = NULL;
    free(JGCJJSJZout);JGCJJSJZout = NULL;
}

void DealSourcePackage::dealJGYYPackage(unsigned char *_strJGYY, int _JGYYlen, compressedStream *_comJGYY, SourceStream *_obtainedSourceStream, unsigned char *_JGYYout,int *rmlen,bool state,unsigned int *packnumid)
{
    __int64         temp_JGCJGZHB = 0,temp_JGCJGZ=0,temp_JGCJJG=0;

    //为2711包分配空间
    __int64 BUFFSIZE = (128* 1024 * 1024);
    unsigned char	*JGCJGZHBout= NULL, *JGCJGZout= NULL, *JGCJJGout= NULL;

    JGCJGZHBout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    JGCJGZout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    JGCJJGout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));


    //补充完整
    if(NULL==JGCJGZHBout||NULL==JGCJGZout||JGCJJGout)
    {
        MainWindow::fakeUi->setLinetext(QString("内存分配fail!\n"));
    }



    int EPDUflag;
    int iStartPos1 = 0;
    int cysumlen =0;

    unsigned int flag;
    int    type = 0x00;
    int    datalen = 0;
    int deallen = 0;

    char fileName[fileNameLen];

    unsigned int jgyypacknum=*packnumid;
    unpack->unpack1(_strJGYY, _JGYYlen, _comJGYY->img, &(_comJGYY->ilen), outputpathLog,state,&jgyypacknum);   //img为该buf中的EPDU数据
    *packnumid=jgyypacknum;
//    unpack->unpack(_strJGYY, _JGYYlen, _comJGYY->img, &(_comJGYY->ilen), outputpathLog,state);   //img为该buf中的EPDU数据
    //memcpy(_obtainedSourceStream->DKCBdata+iShiftLenDKCB,_comDKCB->img,_DKCBlen);   //考虑残余数据的情况   iShiftlen如何变
    cysumlen = _comJGYY->ilen+*rmlen;

    memcpy(_obtainedSourceStream->JGYYdata+*rmlen,_comJGYY->img,_comJGYY->ilen);   //考虑残余数据的情况   iShiftlen如何变
    EPDUflag=9;
    //检测到F5F6EB90
    if(UnPack::barkDetect(_obtainedSourceStream->JGYYdata,cysumlen,0,&iStartPos1))
    {

        type= _obtainedSourceStream->JGYYdata[iStartPos1+6];
        switch (type)
        {
        //40
        case JGCJGZHB: //38
            //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
            memcpy(JGCJGZHBout,_obtainedSourceStream->JGYYdata+iStartPos1,920);
            temp_JGCJGZHB+=920;
            deallen = iStartPos1+920;
            break;
        case JGCJGZ:  //3B
            //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
            memcpy(JGCJGZout,_obtainedSourceStream->JGYYdata+iStartPos1,920);
            temp_JGCJGZ+=920;
            deallen = iStartPos1+920;
            break;
        case JGCJJG:  //4F
            //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
            memcpy(JGCJJGout,_obtainedSourceStream->JGYYdata+iStartPos1,920);
            temp_JGCJJG+=920;
            deallen = iStartPos1+920;
            break;
        default:
            //qDebug()<<type<<"weizhiyuanbao";
            deallen=iStartPos1+4;
            break;
        }


        while (deallen+920<=cysumlen)
        {
            flag = ((_obtainedSourceStream->JGYYdata[deallen] << 24) | (_obtainedSourceStream->JGYYdata[deallen+1] << 16) | (_obtainedSourceStream->JGYYdata[deallen+2] << 8) |_obtainedSourceStream->JGYYdata[deallen+3]) & 0xffffffff;
            if(flag == 0xF5F6EB90)
            {
                type = _obtainedSourceStream->JGYYdata[deallen+6];
                switch (type)
                {
                //40
                case JGCJGZHB:
                    //datalen = (_comRWSJ->img[deallen + 8] <<8 ) | _comRWSJ->img[deallen+9];
                    memcpy(JGCJGZHBout+temp_JGCJGZHB,_obtainedSourceStream->JGYYdata+deallen,920);
                    temp_JGCJGZHB+=920;
                    deallen = deallen+920;
                    break;
                case JGCJGZ:  //41
                    //datalen = (_comXJCS->img[deallen + 8] <<8 ) | _comXJCS->img[deallen+9];
                    memcpy(JGCJGZout+temp_JGCJGZ,_obtainedSourceStream->JGYYdata+deallen,920);
                    temp_JGCJGZ+=920;
                    deallen = deallen+920;
                    break;

                case JGCJJSJZ_S:  //41
                    //datalen = (_comXJCS->img[deallen + 8] <<8 ) | _comXJCS->img[deallen+9];
                    memcpy(JGCJJGout+temp_JGCJJG,_obtainedSourceStream->JGYYdata+deallen,920);
                    temp_JGCJJG+=920;
                    deallen = deallen+920;
                    break;
                default:
                    //qDebug()<<type<<"weizhiyuanbao";
//                    flag = ((_comRWSJ->img[deallen] << 24) | (_comRWSJ->img[deallen+1] << 16) | (_comRWSJ->img[deallen+2] << 8) |_comRWSJ->img[deallen+3]) & 0xffffffff;
//                    qDebug()<<flag;
//                    type = _comRWSJ->img[deallen+7];

//                    type = _comRWSJ->img[deallen+8];

                    //type = _comRWSJ->img[deallen+6];
                    deallen+=4;
                    break;
                }

//                if(type==0X11)
//                {
//                    memcpy(_DKCBout+temp_DKCB, _comDKCB->img + deallen, 920);
//                    temp_DKCB += 920;
//                    //*iZXGC = temp_ZXGC;
//                    deallen = deallen + 920;
//                }
            }
            else
            {
                if(UnPack::barkDetect(_obtainedSourceStream->JGYYdata,cysumlen, deallen, &iStartPos1))
                {

                    if(iStartPos1+920<=cysumlen)
                    {
//                        memcpy(_DKCBout+temp_DKCB, _comDKCB->img + deallen, 920);
//                        temp_DKCB += 920;
//                        //*iZXGC = temp_ZXGC;
//                        deallen = deallen + 920;
                        type = _obtainedSourceStream->JGYYdata[iStartPos1+6];
                        switch (type)
                        {
                        case JGCJGZHB:
                            //datalen = (_comRWSJ->img[iStartPos1 + 8] <<8 ) | _comRWSJ->img[iStartPos1+9];
                            memcpy(JGCJGZHBout+temp_JGCJGZHB,_obtainedSourceStream->JGYYdata+iStartPos1,920);
                            temp_JGCJGZHB+=920;
                            deallen = iStartPos1+920;
                            break;
                        case JGCJGZ:  //41
                            //datalen = (_comRWSJ->img[iStartPos1 + 8] <<8 ) | _comRWSJ->img[iStartPos1+9];
                            memcpy(JGCJGZout+temp_JGCJGZ,_obtainedSourceStream->JGYYdata+iStartPos1,920);
                            temp_JGCJGZ+=920;
                            deallen = iStartPos1+920;
                            break;
                        case JGCJJG:  //41
                            //datalen = (_comRWSJ->img[iStartPos1 + 8] <<8 ) | _comRWSJ->img[iStartPos1+9];
                            memcpy(JGCJJGout+temp_JGCJJG,_obtainedSourceStream->JGYYdata+iStartPos1,920);
                            temp_JGCJJG+=920;
                            deallen = iStartPos1+920;
                            break;
                        default:
                            //qDebug()<<type<<"weizhiyuanbao1";
//                            flag = ((_comRWSJ->img[deallen] << 24) | (_comRWSJ->img[deallen+1] << 16) | (_comRWSJ->img[deallen+2] << 8) |_comRWSJ->img[deallen+3]) & 0xffffffff;
//                            qDebug()<<flag;
//                            type = _comRWSJ->img[deallen+7];

//                            type = _comRWSJ->img[deallen+8];

                            //type = _obtainedSourceStream->JGYYdata[iStartPos1+6];
                            deallen = iStartPos1+4;
                            break;
                        }

                    }
                    else
                    {
                        deallen = iStartPos1;
                    }
                }
                else{
                    deallen = iStartPos1;
                }

            }

        }


        //写文件
        FILE *fpOut;

        char outwords[200];
        //连续性判断，数字位3
        if(temp_JGCJGZ>0)
        {
            unsigned int gzflag1,gzflag2;
            for(int i=0;i<temp_JGCJGZ/920;i++){
                if(i==0){
                    gzflag1=((JGCJGZout[4]<<8)|JGCJGZout[5])& 0xFFFF;
                }
                else{
                    gzflag2=((JGCJGZout[4+i*920]<<8)|JGCJGZout[5+i*920])& 0xFFFF;
                    if(gzflag1+1!=gzflag2){
                        //qDebug()<<"bylianxu";
                        sprintf(outwords,"JGCJGZ图像连续性检测中，第%d包与第%d包之间不连续\n",gzflag1,gzflag2);
                        //sprintf(fileName,"%s/image.txt",outputpathLog);
                        sprintf(fileName,"%s/JGCJGZcontinue.txt",outputpathLog);
                        fpOut = fopen(fileName,"ab");
                        if(fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;

                    }
                    gzflag1=gzflag2;
                }
                int check = 0;
                int check1=0;
                for(int j = 8; j < 918; j++)
                {
                    /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                        qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
                    check =(check+  JGCJGZout[920*i+j]);
                    //11.2删
                    //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
                }
                //check=check+datalen;
                check=check&0xffff;
                check1=((JGCJGZout[920*i + 918] << 8) | JGCJGZout[920*i + 919])&0xffff;

                if(check != check1)
                {
        //            qDebug()<<"adderror"<<endl;//加和报错
                    sprintf(outwords,"jgcjgz图像，%d包检验和错误\n",gzflag1);
                    //sprintf(fileName,"%s/image.txt",outputpathLog);
                    sprintf(fileName,"jgcjgzadderror%s.txt",outputpathLog);
                    fpOut = fopen(fileName,"ab");
                    if(fpOut == NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;

                }

            }
        }
        if(temp_JGCJGZHB>0)
        {
            unsigned int hbflag1,hbflag2;
            for(int i=0;i<temp_JGCJGZ/920;i++){
                if(i==0){
                    hbflag1=((JGCJGZHBout[4]<<8)|JGCJGZHBout[5])& 0xFFFF;
                }
                else{
                    hbflag2=((JGCJGZHBout[4+i*920]<<8)|JGCJGZHBout[5+i*920])& 0xFFFF;
                    if(hbflag1+1!=hbflag2){
                        //qDebug()<<"bylianxu";
                        sprintf(outwords,"JGCJGZHB图像连续性检测中，第%d包与第%d包之间不连续\n",hbflag1,hbflag2);
                        //sprintf(fileName,"%s/image.txt",outputpathLog);
                        sprintf(fileName,"%s/JGCJGZHBcontinue.txt",outputpathLog);
                        fpOut = fopen(fileName,"ab");
                        if(fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;

                    }
                    hbflag1=hbflag2;
                }

                int check = 0;
                int check1=0;
                for(int j = 8; j < 918; j++)
                {
                    /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                        qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
                    check =(check+  JGCJGZHBout[920*i+j]);
                    //11.2删
                    //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
                }
                //check=check+datalen;
                check=check&0xffff;
                check1=((JGCJGZHBout[920*i + 918] << 8) | JGCJGZHBout[920*i + 919])&0xffff;

                if(check != check1)
                {
        //            qDebug()<<"adderror"<<endl;//加和报错
                    sprintf(outwords,"jgcjgzhb图像，%d包检验和错误\n",hbflag1);
                    //sprintf(fileName,"%s/image.txt",outputpathLog);
                    sprintf(fileName,"jgcjgzhbadderror%s.txt",outputpathLog);
                    fpOut = fopen(fileName,"ab");
                    if(fpOut == NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;

                }
            }
        }

        if(temp_JGCJJG>0)
        {
            unsigned int jgflag1,jgflag2;
            for(int i=0;i<temp_JGCJJG/920;i++){
                if(i==0){
                    jgflag1=((JGCJJGout[4]<<8)|JGCJJGout[5])& 0xFFFF;
                }
                else{
                    jgflag2=((JGCJJGout[4+i*920]<<8)|JGCJJGout[5+i*920])& 0xFFFF;
                    if(jgflag1+1!=jgflag2){
                        //qDebug()<<"bylianxu";
                        sprintf(outwords,"JGCJJG图像连续性检测中，第%d包与第%d包之间不连续\n",jgflag1,jgflag2);
                        //sprintf(fileName,"%s/image.txt",outputpathLog);
                        sprintf(fileName,"%s/JGCJJGcontinue.txt",outputpathLog);
                        fpOut = fopen(fileName,"ab");
                        if(fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;

                    }
                    jgflag1=jgflag2;
                }

                int check = 0;
                int check1=0;
                for(int j = 8; j < 918; j++)
                {
                    /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                        qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
                    check =(check+  JGCJJGout[920*i+j]);
                    //11.2删
                    //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
                }
                //check=check+datalen;
                check=check&0xffff;
                check1=((JGCJJGout[920*i + 918] << 8) | JGCJJGout[920*i + 919])&0xffff;

                if(check != check1)
                {
        //            qDebug()<<"adderror"<<endl;//加和报错
                    sprintf(outwords,"jgcjjg图像，%d包检验和错误\n",jgflag1);
                    //sprintf(fileName,"%s/image.txt",outputpathLog);
                    sprintf(fileName,"jgcjjgadderror%s.txt",outputpathLog);
                    fpOut = fopen(fileName,"ab");
                    if(fpOut == NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;

                }
            }
        }
        //data
        if(temp_JGCJGZHB>0)
        {
            if(state){
                sprintf(fileName, "%s/ssJGCJGZHB_2711.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(JGCJGZHBout, temp_JGCJGZHB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            else {
                sprintf(fileName, "%s/JGCJGZHB_2711.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(JGCJGZHBout, temp_JGCJGZHB, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }

        }
        if(temp_JGCJGZ>0)
        {
            if(state){
                sprintf(fileName, "%s/ssJGCJGZ_2711.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(JGCJGZout, temp_JGCJGZ, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            else{
                sprintf(fileName, "%s/JGCJGZ_2711.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(JGCJGZout, temp_JGCJGZ, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }

        }
        if(temp_JGCJJG>0)
        {
            if(state){
                sprintf(fileName, "%s/ssJGCJJSJZ_2711.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(JGCJJGout, temp_JGCJJG, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }
            else{
                sprintf(fileName, "%s/JGCJJSJZ_2711.dat", outputpath2711package);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(JGCJJGout, temp_JGCJJG, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
            }

        }



//        sprintf(fileName, "%s/DKCB_2711.dat", outputpath2711package);
//        fpOut = fopen(fileName, "ab");
//        //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
//        fwrite(_DKCBout, temp_DKCB, 1, fpOut);
//        //DKCBlen += (12 + datalen);
//        fclose(fpOut);
//        fpOut = NULL;
     }
    *rmlen=cysumlen-deallen;
    memcpy(_obtainedSourceStream->JGYYdata,_obtainedSourceStream->JGYYdata+deallen,*rmlen);
    free(JGCJGZHBout);JGCJGZHBout =NULL;
    free(JGCJGZout);JGCJGZout = NULL;
    free(JGCJJGout);JGCJJGout = NULL;
}


int DealSourcePackage::dealGYPackage(unsigned char *_strGY, int _GYlen, compressedStream *_comGY, unsigned char *_GYout,unsigned char* GYout,unsigned char * GY21out,unsigned char * GY41out, int *rmlen, int Pack_flag,unsigned int *packnumid,struct RZid *rzid)
{
    //to do
    //在函数上增加三个参数，gyid,gy21id,gy41id;
    // done
    //图像数据 压缩数据 数量   GY是正常数据，GY21 和GY41是压缩数据
    __int64         temp_GY = 0,temp_GY21=0,temp_GY41=0;
    int iStartPos1 = 0;
    int cysumlen=0;
    __int64 BUFFSIZE = (8 * 1024 * 1024);//调试一下buffsize
//    unsigned char	*GYout= NULL,*GY21out= NULL,*GY41out= NULL;

//    GYout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
//    GY21out = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
//    GY41out = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));

    if(NULL==GYout || NULL ==GY21out|| NULL ==GY41out)
    {
        qDebug()<<"gy malloc failed";
    }

    unsigned int flag;
    int    type = 0x00;
    int    datalen = 0;
    int deallen = 0;

    char fileName[fileNameLen];
    unsigned int gypacknum=*packnumid;
    //unsigned int packnum=0;
    //unsigned int dddpd2711num=*pdid,dddpdkc2711num=*kcid;

    //todo
    unsigned int GYAnum = rzid->GYAid,GYA21num = rzid->GYA21id,GYA41num = rzid->GYA41id;
    unsigned int GYBnum = rzid->GYBid,GYB21num = rzid->GYB21id,GYB41num = rzid->GYB41id;
    unsigned int GYCnum = rzid->GYCid,GYC21num = rzid->GYC21id,GYC41num = rzid->GYC41id;
    unsigned int GYpronum = rzid->GYproid,GYpro21num = rzid->GYpro21id,GYpro41num = rzid->GYpro41id;
    //done

    //unpack->unpack1(_strDDDPD, _DDDPDlen, _comDDDPD->img, &(_comDDDPD->ilen), outputpathLog,state,&dddpdpacknum);
    unpack->newunpack(_strGY, _GYlen, _comGY->img, &(_comGY->ilen), outputpathLog,&gypacknum);
    *packnumid=gypacknum;
    cysumlen = _comGY->ilen+*rmlen;
    //gyout存储的是加残余数据的情况，这里可能还需要修改 避免残余数据冲突  11.28
    memcpy(_GYout+*rmlen,_comGY->img,_comGY->ilen);   //考虑残余数据的情况   iShiftlen如何变
    if(Pack_flag == 1)
    {
        rzid->errorgyadata += unpack->geterrornum();
    }
    else if(Pack_flag == 2)
    {
        rzid->errorgybdata += unpack->geterrornum();
    }
    else if(Pack_flag == 3)
    {
        rzid->errorgycdata += unpack->geterrornum();
    }
    else if(Pack_flag == 4)
    {
        rzid->errorgyprodata += unpack->geterrornum();
    }
    //在EPDU域搜索EB90EB90
    if(UnPack::gyDetect(_GYout,cysumlen,0,&iStartPos1))
    {

        type= _GYout[iStartPos1+4];
        //初步认为 11 图像数据 21 41 压缩数据
        if(type==0x11){
            //图像数据长度为17816
            datalen = (_GYout[iStartPos1 + 8] <<8 ) |_GYout[iStartPos1+9]+12;
            if(iStartPos1 + datalen <= cysumlen)
            {
                memcpy(GYout,_GYout+iStartPos1,datalen);
                temp_GY+=datalen;
                deallen = iStartPos1+datalen;
            }
        }
        else if(type==0x33){
            //这个datalen每次都要判定 帧头辅助信息和压缩数据长度不同
            datalen = (_GYout[iStartPos1 + 8] <<8 ) |_GYout[iStartPos1+9]+12;
            if(iStartPos1 + datalen <= cysumlen)
            {
                memcpy(GY21out,_GYout+iStartPos1,datalen);
                temp_GY21+=datalen;
                deallen = iStartPos1+datalen;
            }
        }
        else if(type==0x55){
            datalen = (_GYout[iStartPos1 + 8] <<8 ) |_GYout[iStartPos1+9]+12;
            memcpy(GY41out,_GYout+iStartPos1,datalen);
            temp_GY41+=datalen;
            deallen = iStartPos1+datalen;
        }
        else{
            deallen =iStartPos1+4;
        }


        while (deallen+datalen<=cysumlen)
        {
            flag = ((_GYout[deallen] << 24) | (_GYout[deallen+1]<<16)|(_GYout[deallen+2] << 8) | (_GYout[deallen+3]) ) & 0xffffffff;
            if(flag == 0xEB90EB90)
            {
                //type = _comZXGC->img[deallen+6];
                type= _GYout[deallen+4];
                datalen = (_GYout[deallen + 8] <<8 ) | _GYout[deallen+9]+12;
                // 0x1111
                // bool flag has 0x1111
                // G_LEN = 0 + 8908 * 2
                //
                //这个判断要加的原因是datalen在变化
                if(deallen+datalen<cysumlen)
                {
                    if(type==0x11)
                    {
                        memcpy(GYout+temp_GY, _GYout + deallen, datalen);
                        temp_GY+= datalen;
                        //*iZXGC = temp_ZXGC;
                        deallen = deallen + datalen;
                    }else if(type==0x33){
                        memcpy(GY21out+temp_GY21, _GYout + deallen, datalen);
                        temp_GY21+= datalen;
                        //*iZXGC = temp_ZXGC;
                        deallen = deallen + datalen;
                    }else if(type==0x55){
                        memcpy(GY41out+temp_GY41, _GYout + deallen, datalen);
                        temp_GY41+= datalen;
                        //*iZXGC = temp_ZXGC;
                        deallen = deallen + datalen;
                    }
                    else{
                        deallen+=4;
                    }
                }
                else{
                    break;
                }


            }
            else
            {
                if(UnPack::gyDetect(_GYout, cysumlen, deallen, &iStartPos1))
                {
                    if(iStartPos1+10<cysumlen)
                    {
                        type= _GYout[deallen+4];
                        datalen = (_GYout[deallen + 8] <<8 ) | _GYout[deallen+9]+12;
                        if(deallen+datalen<cysumlen){
                            if(type==0x11)
                            {
                                memcpy(GYout+temp_GY, _GYout + iStartPos1, datalen);
                                temp_GY += datalen;
                                //*iZXGC = temp_ZXGC;
                                deallen = iStartPos1 + datalen;
                            }else if(type==0x33){
                                memcpy(GY21out+temp_GY21, _GYout + iStartPos1, datalen);
                                temp_GY21 += datalen;
                                //*iZXGC = temp_ZXGC;
                                deallen = iStartPos1 + datalen;
                            }else if(type==0x55){
                                memcpy(GY41out+temp_GY41, _GYout + iStartPos1, datalen);
                                temp_GY41 += datalen;
                                //*iZXGC = temp_ZXGC;
                                deallen = iStartPos1 + datalen;
                            }
                            else{
                                deallen = iStartPos1+4;
                            }
                        }else{
                            break;
                        }

                    }
                    else{
                        break;
                    }
                }
                else
                {
                    deallen = iStartPos1;
                }
            }

        }

        //如果能找到下一个EB90
        while(UnPack::gyDetect(_GYout, cysumlen, deallen, &iStartPos1))
        {
            type= _GYout[iStartPos1+4];
            datalen = (_GYout[iStartPos1 + 9] <<8 ) | _GYout[iStartPos1+10]+12;

            if(iStartPos1+datalen<cysumlen){
                if(type==0x11)
                {
                    memcpy(GYout+temp_GY, _GYout + iStartPos1, datalen);
                    temp_GY += datalen;

                    deallen = iStartPos1 + datalen;
                }else if(type==0x33){
                    memcpy(GY21out+temp_GY21, _GYout + iStartPos1, datalen);
                    temp_GY21 += datalen;

                    deallen = iStartPos1 + datalen;
                }else if(type==0x55){
                    memcpy(GY41out+temp_GY41, _GYout + iStartPos1, datalen);
                    temp_GY41 += datalen;

                    deallen = iStartPos1 + datalen;
                }
                else{
                    //错误包的情况
                    deallen =iStartPos1+4;
                }
            }
            else{
                break;
            }
        }



        //写文件
        FILE *fpOut;
        if(temp_GY>0){
            if(Pack_flag==1){
               sprintf(fileName, "%s/GYA.dat", outputpath2711package);
            }else if(Pack_flag==2){
                sprintf(fileName, "%s/GYB.dat", outputpath2711package);
            }else if(Pack_flag==3){
                sprintf(fileName, "%s/GYC.dat", outputpath2711package);
            }else if(Pack_flag==4){
                sprintf(fileName, "%s/GYpro.dat", outputpath2711package);
            }

            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(GYout, temp_GY, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_GY21>0){
            if(Pack_flag==1){
               sprintf(fileName, "%s/GYA21.dat", outputpath2711package);
            }else if(Pack_flag==2){
                sprintf(fileName, "%s/GYB21.dat", outputpath2711package);
            }else if(Pack_flag==3){
                sprintf(fileName, "%s/GYC21.dat", outputpath2711package);
            }else if(Pack_flag==4){
                sprintf(fileName, "%s/GYpro21.dat", outputpath2711package);
            }
            //sprintf(fileName, "%s/GY21.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(GY21out, temp_GY21, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }
        if(temp_GY41>0){
            if(Pack_flag==1){
               sprintf(fileName, "%s/GYA41.dat", outputpath2711package);
            }else if(Pack_flag==2){
                sprintf(fileName, "%s/GYB41.dat", outputpath2711package);
            }else if(Pack_flag==3){
                sprintf(fileName, "%s/GYC41.dat", outputpath2711package);
            }else if(Pack_flag==4){
                sprintf(fileName, "%s/GYpro41.dat", outputpath2711package);
            }
            //sprintf(fileName, "%s/GY41.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(GY41out, temp_GY41, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;
        }

     }
//    qDebug()<<temp_GY;

    //todo,需要区分GYABC以及原始数据和压缩数据
    //根据pack_flag区分ABC,continuejuedge的第三个参数用来区分内部数据类型
      if(Pack_flag == 1)
      {
        if(temp_GY >0)
        {
          rzid->errorGYAid += continuejudgegy(GYout,temp_GY,11,&GYAnum);
        }
        else if(temp_GY21 > 0)
        {
          rzid->errorGYA21id += continuejudgegy(GY21out,temp_GY21,12,&GYA21num);
        }
        else if(temp_GY41 > 0)
        {
          rzid->errorGYA41id += continuejudgegy(GY41out,temp_GY41,14,&GYA41num);
        }
      }
      else if(Pack_flag ==2)
      {
        if(temp_GY >0){
          rzid->errorGYBid += continuejudgegy(GYout,temp_GY,21,&GYBnum);
        }
        else if(temp_GY21 > 0){
          rzid->errorGYB21id += continuejudgegy(GY21out,temp_GY21,22,&GYB21num);
        }
        else if(temp_GY41 > 0){
          rzid->errorGYB41id += continuejudgegy(GY41out,temp_GY41,24,&GYB41num);
        }
      }
      else if(Pack_flag == 3)
      {
        if(temp_GY >0){
          rzid->errorGYCid += continuejudgegy(GYout,temp_GY,31,&GYCnum);
        }
        else if(temp_GY21 > 0){
          rzid->errorGYC21id += continuejudgegy(GY21out,temp_GY21,32,&GYC21num);
        }
        else if(temp_GY41 > 0){
          rzid->errorGYC41id += continuejudgegy(GY41out,temp_GY41,34,&GYC41num);
        }
      }
      else if(Pack_flag == 4)
      {
        if(temp_GY >0){
           rzid->errorGYproid += continuejudgegy(GYout,temp_GY,41,&GYpronum);
        }
        else if(temp_GY21 > 0){
           rzid->errorGYpro21id += continuejudgegy(GY21out,temp_GY21,42,&GYpro21num);
        }
        else if(temp_GY41 > 0){
           rzid->errorGYpro41id += continuejudgegy(GY41out,temp_GY41,44,&GYpro41num);
        }
      }
     //DONE
      rzid->GYAid = GYAnum;
      rzid->GYA21id = GYA21num;
      rzid->GYA41id = GYA41num;
      rzid->GYBid = GYBnum;
      rzid->GYB21id = GYB21num;
      rzid->GYB41id = GYB41num;
      rzid->GYCid = GYCnum;
      rzid->GYC21id = GYC21num;
      rzid->GYC41id = GYC41num;
      rzid->GYproid = GYpronum;
      rzid->GYpro21id = GYpro21num;
      rzid->GYpro41id = GYpro41num;


    *rmlen=cysumlen-deallen;
    memcpy(_GYout,_GYout+deallen,*rmlen);

//    free(GYout);GYout=NULL;
//    free(GY21out);GY21out=NULL;
//    free(GY41out);GY41out=NULL;
    return temp_GY;//
}

int DealSourcePackage::dealJGPackage(unsigned char *_strJG, int _JGlen, compressedStream *_comJG, unsigned char *_JGout,unsigned char * JGout, int *rmlen,unsigned int *packnumid,struct RZid *rzid)
{
    //图像数据 压缩数据 数量
    unsigned int lineid  = 0;
    __int64         temp_JG= 0;
    int iStartPos1 = 0,iStartPos2 = 0,iStartPos = 0;
    int cysumlen=0;
    __int64 BUFFSIZE = (8* 1024 * 1024);
//    unsigned char	*JGout= NULL;

//    JGout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));

//    if(NULL==JGout)
//    {
//        qDebug()<<"jg malloc failed";
//    }

    unsigned int flag;
    unsigned int packid;
    int    datalen = 3316;//1.14号更改
    int deallen = 0;
    bool JGhead = false;
    bool JGline = false;
    char fileName[fileNameLen];
    unsigned int jgpacknum=*packnumid;
    //这个参数维护的是日志里的总包数
    unsigned int jgnum = rzid->JGid;
    unpack->newunpack(_strJG, _JGlen, _comJG->img, &(_comJG->ilen), outputpathLog,&jgpacknum);
    *packnumid=jgpacknum;
    cysumlen = _comJG->ilen+*rmlen;
    rzid->errorjgxjdata += unpack->geterrornum();
    //gyout存储的是加残余数据的情况，这里可能还需要修改 避免残余数据冲突  11.28
    memcpy(_JGout+*rmlen,_comJG->img,_comJG->ilen);  //考虑残余数据的情况   iShiftlen如何变
    //在EPDU域搜索EB90EB90
    JGhead = UnPack::jgDetect(_JGout,cysumlen,0,&iStartPos1);
    JGline = UnPack::jginDetect(_JGout,cysumlen,0,&iStartPos2);
    if(JGhead||JGline)
    {
        if(iStartPos1<iStartPos2){
            //先检测到帧辅助信息
            packid = ((_JGout[iStartPos2+24] << 8) | (_JGout[iStartPos2+25])) & 0xffff;
            memcpy(JGout,_JGout+iStartPos1,datalen);
            temp_JG+=datalen;
            deallen = iStartPos1+datalen;
        }
        else{
            //先检测到有效数据信息
            //行计数
            lineid = ((_JGout[iStartPos2+16] << 8) | (_JGout[iStartPos2+17])) & 0xffff;//1.16更改
            memcpy(JGout,_JGout+iStartPos2,datalen);
            temp_JG+=datalen;
            deallen = iStartPos2+datalen;
        }


        while (deallen+datalen<=cysumlen)
        {
            flag = ((_JGout[deallen] <<24) | (_JGout[deallen+1]<<16)| (_JGout[deallen+2]<<8)| (_JGout[deallen+3])) & 0xffffffff;
            if(flag == 0x49940000)//1.16更改
            {
                //这里可以judge连续性
                memcpy(JGout+temp_JG, _JGout + deallen, datalen);
                temp_JG+= datalen;
                //*iZXGC = temp_ZXGC;
                deallen = deallen + datalen;

            }else if((_JGout[deallen] == 0x49) && (_JGout[deallen + 1] == 0x54) && (_JGout[deallen + 2] == 0x92) && (_JGout[deallen + 3] == 0x64)
                     && (_JGout[deallen + 4] == 0x04)&& (_JGout[deallen + 5] == 0x00)&& (_JGout[deallen + 6] == 0x00)&& (_JGout[deallen + 7] == 0x01)){
                memcpy(JGout+temp_JG, _JGout + deallen, datalen);
                temp_JG+= datalen;
                //*iZXGC = temp_ZXGC;
                deallen = deallen + datalen;
            }
            else
            {
                JGhead = UnPack::jgDetect(_JGout,cysumlen,deallen,&iStartPos1);
                JGline = UnPack::jginDetect(_JGout,cysumlen,deallen,&iStartPos2);
                if(JGhead || JGline)
                {
                    if(iStartPos1<iStartPos2&&iStartPos1+datalen<cysumlen){
                        //帧头辅助数据 维护帧参数
                        memcpy(JGout+temp_JG, _JGout + iStartPos1, datalen);
                        temp_JG += datalen;
                        deallen = iStartPos1 + datalen;
                    }else if(iStartPos2+datalen<cysumlen){
                        //帧内有效图像 维护行参数
                        memcpy(JGout+temp_JG, _JGout + iStartPos2, datalen);
                        temp_JG += datalen;
                        deallen = iStartPos2 + datalen;
                    }
                    else{
                        break;
                    }
                }
                else
                {
                    deallen = iStartPos1;
                }
            }

        }





        //写文件
        FILE *fpOut;
        sprintf(fileName, "%s/JGXJ.dat", outputpath2711package);
        fpOut = fopen(fileName, "ab");
        fwrite(JGout, temp_JG, 1, fpOut);
        fclose(fpOut);
        fpOut = NULL;


        rzid->errorJGid += continuejudgejg(JGout,temp_JG,1,&jgnum);
        rzid->JGid = jgnum;

     }

    *rmlen=cysumlen-deallen;
    memcpy(_JGout,_JGout+deallen,*rmlen);
//    free(JGout);JGout=NULL;
    return temp_JG;
}

void DealSourcePackage::dealXSCLPackage(unsigned char *_strXSCL, int _XSCLlen, compressedStream *_comXSCL, unsigned char *_XSCLout, int *rmlen,int Pack_flag,unsigned int *packnumid,struct RZid * rzid)
{
    //l 7.05
    //todo
    //函数需增加11个显示参数
    //星上处理数据 数量    留三个备用
    __int64         temp_GYIPD = 0,temp_JGIPD=0,temp_GYTWDW=0,temp_JGTWDW=0,temp_GYGTW=0,temp_GYYDXX=0,temp_SJCL=0,temp_TWDW=0,temp_YD=0;
    __int64         temp_GYYDXXXX = 0, temp_JGTXCLRZ = 0;//24.0605补
    int iStartPos1 = 0;
    int cysumlen=0;
    __int64 BUFFSIZE = (8 * 1024 * 1024);//空间分配失败，调小
    unsigned char	*GYIPDout= NULL,*JGIPDout= NULL,*GYTWDWout= NULL,*JGTWDW= NULL,*JGTWDWout= NULL,*GYGTWout= NULL,*GYYDXXout= NULL,*SJCLout= NULL,*TWDWout= NULL,*YDout= NULL;
    unsigned char *GYYDXXXXout=NULL,*JGTXCLRZout = NULL;//补
    //SJCL是GY图像处理日志
    GYIPDout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    JGIPDout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    GYTWDWout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    JGTWDWout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    GYGTWout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    GYYDXXout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    SJCLout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    TWDWout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    YDout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));
    GYYDXXXXout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));//补
    JGTXCLRZout = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));

    if(NULL == GYYDXXXXout || NULL == JGTXCLRZout ||NULL==GYIPDout || NULL ==GYTWDWout||NULL==JGIPDout || NULL ==JGTWDWout||NULL==GYIPDout || NULL ==GYGTWout||NULL==GYYDXXout || NULL ==SJCLout||NULL==TWDWout || NULL ==YDout)
    {
        qDebug()<<"xscl malloc failed";
    }

    unsigned int flag;
    int    type = 0x00;
    int    datalen = 0;
    datalen=1024;
    int deallen = 0;
    char fileName[fileNameLen];
//    unsigned int dddpdpacknum=*packnumid;
    //unsigned int packnum=0;
    unsigned int packnum=*packnumid;

    //l 7.05
    //todo
    unsigned int GYIPDnum = rzid->GYIPDid , JGIPDnum = rzid->JGIPDid;
    unsigned int GYTWDW01num = rzid->GYTWDW01id,GYTWDW02num = rzid->GYTWDW02id,JGTWDW01num = rzid->JGTWDW01id,JGTWDW02num = rzid->JGTWDW02id;
    unsigned int GYGTWnum = rzid->GYGTWid , GYYDXXnum = rzid->GYYDXXid, GYYDXXXX01num = rzid->GYYDXXXX01id, GYYDXXXX02num = rzid->GYYDXXXX02id,GYTXCLRZnum = rzid->GYTXCLRZid;
    unsigned int TWDWRZnum = rzid->TWDWRZid , YDGZRZnum = rzid->YDGZRZid,JGTXCLRZnum = rzid->JGTXCLRZid;
    //done
    //unsigned int dddpd2711num=*pdid,dddpdkc2711num=*kcid;
    //unpack->unpack1(_strDDDPD, _DDDPDlen, _comDDDPD->img, &(_comDDDPD->ilen), outputpathLog,state,&dddpdpacknum);
    unpack->newunpack(_strXSCL, _XSCLlen, _comXSCL->img, &(_comXSCL->ilen), outputpathLog,&packnum);
    *packnumid=packnum;
    cysumlen = _comXSCL->ilen+*rmlen;
    if(Pack_flag == 1 )
    {
        rzid->errorxscl01 += unpack->geterrornum();
    }
    else if(Pack_flag == 2)
    {
        rzid->errorxscl02 += unpack->geterrornum();
    }
    //gyout存储的是加残余数据的情况，这里可能还需要修改 避免残余数据冲突  11.28
    memcpy(_XSCLout+*rmlen,_comXSCL->img,_comXSCL->ilen);   //考虑残余数据的情况   iShiftlen如何变
    //在EPDU域搜索F5F6EB90
    if(UnPack::barkDetect(_XSCLout,cysumlen,0,&iStartPos1))
    {

/*        type= _XSCLout[iStartPos1+6]*/;
           type= _XSCLout[iStartPos1+7];//
        switch(type){
        case 0x11:
//            datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+16;
/*            datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+12;*///星上处理的数据长度为1024字节，其中有效数据为1008字节，所以要加上16字节
            memcpy(GYIPDout,_XSCLout+iStartPos1,datalen);
            temp_GYIPD+=datalen;
            deallen = iStartPos1+datalen;
            break;
        case 0x12:
//             datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+16;
//            datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+12;
            memcpy(JGIPDout,_XSCLout+iStartPos1,datalen);
            temp_JGIPD+=datalen;
            deallen = iStartPos1+datalen;
            break;
        case 0x21:
//             datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+16;
//            datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+12;
            memcpy(GYTWDWout,_XSCLout+iStartPos1,datalen);
            temp_GYTWDW+=datalen;
            deallen = iStartPos1+datalen;
            break;
        case 0x22:
//             datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+16;
//            datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+12;
            memcpy(JGTWDWout,_XSCLout+iStartPos1,datalen);
            temp_JGTWDW+=datalen;
            deallen = iStartPos1+datalen;
            break;
        case 0x28:
//             datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+16;
//            datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+12;
            memcpy(GYGTWout,_XSCLout+iStartPos1,datalen);
            temp_GYGTW+=datalen;
            deallen = iStartPos1+datalen;
            break;
        case 0x31:
//             datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+16;
//            datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+12;
            memcpy(GYYDXXout,_XSCLout+iStartPos1,datalen);
            temp_GYYDXX+=datalen;
            deallen = iStartPos1+datalen;
            break;
        case 0x3B:
//             datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+16;
//            datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+12;
            memcpy(GYYDXXXXout,_XSCLout+iStartPos1,datalen);
            temp_GYYDXXXX+=datalen;
            deallen = iStartPos1+datalen;
            break;
        case 0x32:
//             datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+16;
//            datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+12;
            memcpy(SJCLout,_XSCLout+iStartPos1,datalen);//GY图像处理日志
            temp_SJCL+=datalen;
            deallen = iStartPos1+datalen;
            break;
        case 0x34:
//             datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+16;
//            datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+12;
            memcpy(TWDWout,_XSCLout+iStartPos1,datalen);
            temp_TWDW+=datalen;
            deallen = iStartPos1+datalen;
            break;
        case 0x38:
//             datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+16;
//            datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+12;
            memcpy(YDout,_XSCLout+iStartPos1,datalen);
            temp_YD+=datalen;
            deallen = iStartPos1+datalen;
            break;
        case 0x3D:
//             datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+16;
//            datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+12;
            memcpy(JGTXCLRZout,_XSCLout+iStartPos1,datalen);
            temp_JGTXCLRZ+=datalen;
            deallen = iStartPos1+datalen;
            break;
        default:
            deallen = iStartPos1+4;
            break;
        }


        while (deallen+datalen<=cysumlen)
        {
            flag = ((_XSCLout[deallen] << 24) | (_XSCLout[deallen+1]<<16)|(_XSCLout[deallen+2] << 8) | (_XSCLout[deallen+3]) ) & 0xffffffff;
            if(flag == 0xF5F6EB90)
            {

                if(deallen+datalen<cysumlen)
                {
                    type= _XSCLout[deallen+7];//这里应该是第七字节
//                    datalen = (_XSCLout[deallen + 8] <<8 ) | _XSCLout[deallen+9]+12;
//                     datalen = (_XSCLout[deallen + 8] <<8 ) | _XSCLout[deallen+9]+16;
                    switch(type){
                    case 0x11:

                        memcpy(GYIPDout+temp_GYIPD,_XSCLout+deallen,datalen);
                        temp_GYIPD+=datalen;
                        deallen = deallen+datalen;
                        break;
                    case 0x12:

                        memcpy(JGIPDout+temp_JGIPD,_XSCLout+deallen,datalen);
                        temp_JGIPD+=datalen;
                        deallen = deallen+datalen;
                        break;
                    case 0x21:

                        memcpy(GYTWDWout+temp_GYTWDW,_XSCLout+deallen,datalen);
                        temp_GYTWDW+=datalen;
                        deallen = deallen+datalen;
                        break;
                    case 0x22:

                        memcpy(JGTWDWout+temp_JGTWDW,_XSCLout+deallen,datalen);
                        temp_JGTWDW+=datalen;
                        deallen = deallen+datalen;
                        break;
                    case 0x28:

                        memcpy(GYGTWout+temp_GYGTW,_XSCLout+deallen,datalen);
                        temp_GYGTW+=datalen;
                        deallen = deallen+datalen;
                        break;
                    case 0x31:

                        memcpy(GYYDXXout+temp_GYYDXX,_XSCLout+deallen,datalen);
                        temp_GYYDXX+=datalen;
                        deallen = deallen+datalen;
                        break;
                    case 0x3B:

                        memcpy(GYYDXXXXout+temp_GYYDXXXX,_XSCLout+deallen,datalen);
                        temp_GYYDXXXX+=datalen;
                        deallen = deallen+datalen;
                        break;
                    case 0x32:

                        memcpy(SJCLout+temp_SJCL,_XSCLout+deallen,datalen);
                        temp_SJCL+=datalen;
                        deallen = deallen+datalen;
                        break;
                    case 0x34:

                        memcpy(TWDWout+temp_TWDW,_XSCLout+deallen,datalen);
                        temp_TWDW+=datalen;
                        deallen = deallen+datalen;
                        break;
                    case 0x38:

                        memcpy(YDout+temp_YD,_XSCLout+deallen,datalen);
                        temp_YD+=datalen;
                        deallen = deallen+datalen;
                        break;
                    case 0x3D:

                        memcpy(JGTXCLRZout+temp_JGTXCLRZ,_XSCLout+deallen,datalen);
                        temp_JGTXCLRZ+=datalen;
                        deallen = deallen+datalen;
                        break;
                    default:
                        deallen = deallen+4;
                        break;
                    }


                }
                else{
                    break;
                }


            }
            else
            {
                if(UnPack::barkDetect(_XSCLout, cysumlen, deallen, &iStartPos1))
                {
                    if(iStartPos1+datalen<cysumlen)
                    {
     /*                   type= _XSCLout[iStartPos1+6];*///type的类型位置错了
                        type= _XSCLout[iStartPos1+7];
//                        datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+12;
//                        datalen = (_XSCLout[iStartPos1 + 8] <<8 ) |_XSCLout[iStartPos1+9]+16;
                        switch(type){
                        case 0x11:

                            memcpy(GYIPDout+temp_GYIPD,_XSCLout+iStartPos1,datalen);
                            temp_GYIPD+=datalen;
                            deallen = iStartPos1+datalen;
                            break;
                        case 0x12:

                            memcpy(JGIPDout+temp_JGIPD,_XSCLout+iStartPos1,datalen);
                            temp_JGIPD+=datalen;
                            deallen = iStartPos1+datalen;
                            break;
                        case 0x21:

                            memcpy(GYTWDWout+temp_GYTWDW,_XSCLout+iStartPos1,datalen);
                            temp_GYTWDW+=datalen;
                            deallen = iStartPos1+datalen;
                            break;
                        case 0x22:

                            memcpy(JGTWDWout+temp_JGTWDW,_XSCLout+iStartPos1,datalen);
                            temp_JGTWDW+=datalen;
                            deallen = iStartPos1+datalen;
                            break;
                        case 0x28:

                            memcpy(GYGTWout+temp_GYGTW,_XSCLout+iStartPos1,datalen);
                            temp_GYGTW+=datalen;
                            deallen = iStartPos1+datalen;
                            break;
                        case 0x31:

                            memcpy(GYYDXXout+temp_GYYDXX,_XSCLout+iStartPos1,datalen);
                            temp_GYYDXX+=datalen;
                            deallen = iStartPos1+datalen;
                            break;
                        case 0x3B:

                            memcpy(GYYDXXXXout+temp_GYYDXXXX,_XSCLout+iStartPos1,datalen);
                            temp_GYYDXXXX+=datalen;
                            deallen = iStartPos1+datalen;
                            break;
                        case 0x32:

                            memcpy(SJCLout+temp_SJCL,_XSCLout+iStartPos1,datalen);
                            temp_SJCL+=datalen;
                            deallen = iStartPos1+datalen;
                            break;
                        case 0x34:

                            memcpy(TWDWout+temp_TWDW,_XSCLout+iStartPos1,datalen);
                            temp_TWDW+=datalen;
                            deallen = iStartPos1+datalen;
                            break;
                        case 0x38:

                            memcpy(YDout+temp_YD,_XSCLout+iStartPos1,datalen);
                            temp_YD+=datalen;
                            deallen = iStartPos1+datalen;
                            break;
                        case 0x3D:

                            memcpy(JGTXCLRZout+temp_JGTXCLRZ,_XSCLout+iStartPos1,datalen);
                            temp_JGTXCLRZ+=datalen;
                            deallen = iStartPos1+datalen;
                            break;
                        default:
                            deallen = deallen+4;
                            break;
                        }

                    }
                    else{
                        break;
                    }


                }
                else
                {
                    deallen = iStartPos1;
                }
            }

        }

        //如果能找到下一个EB90   本次循环是为了应对不同datalen的问题
        while(UnPack::barkDetect(_XSCLout, cysumlen, deallen, &iStartPos1))
        {
//            type= _XSCLout[iStartPos1+6];
            type= _XSCLout[iStartPos1+7];
//            datalen = (_XSCLout[iStartPos1 + 9] <<8 ) | _XSCLout[iStartPos1+10]+12;
/*            datalen = (_XSCLout[iStartPos1 + 8] <<8 ) | _XSCLout[iStartPos1+9]+16;*///位置有问题，应该是第八和第九字节，且应该加16字节

            if(iStartPos1+datalen<cysumlen){
                switch(type){
                case 0x11:

                    memcpy(GYIPDout+temp_GYIPD,_XSCLout+iStartPos1,datalen);
                    temp_GYIPD+=datalen;
                    deallen = iStartPos1+datalen;
                    break;
                case 0x12:

                    memcpy(JGIPDout+temp_JGIPD,_XSCLout+iStartPos1,datalen);
                    temp_JGIPD+=datalen;
                    deallen = iStartPos1+datalen;
                    break;
                case 0x21:

                    memcpy(GYTWDWout+temp_GYTWDW,_XSCLout+iStartPos1,datalen);
                    temp_GYTWDW+=datalen;
                    deallen = iStartPos1+datalen;
                    break;
                case 0x22:

                    memcpy(JGTWDWout+temp_JGTWDW,_XSCLout+iStartPos1,datalen);
                    temp_JGTWDW+=datalen;
                    deallen = iStartPos1+datalen;
                    break;
                case 0x28:

                    memcpy(GYGTWout+temp_GYGTW,_XSCLout+iStartPos1,datalen);
                    temp_GYGTW+=datalen;
                    deallen = iStartPos1+datalen;
                    break;
                case 0x31:

                    memcpy(GYYDXXout+temp_GYYDXX,_XSCLout+iStartPos1,datalen);
                    temp_GYYDXX+=datalen;
                    deallen = iStartPos1+datalen;
                    break;
                case 0x3B:

                    memcpy(GYYDXXXXout+temp_GYYDXXXX,_XSCLout+iStartPos1,datalen);
                    temp_GYYDXXXX+=datalen;
                    deallen = iStartPos1+datalen;
                    break;
                case 0x32:

                    memcpy(SJCLout+temp_SJCL,_XSCLout+iStartPos1,datalen);
                    temp_SJCL+=datalen;//GY图像处理日志
                    deallen = iStartPos1+datalen;
                    break;
                case 0x34:

                    memcpy(TWDWout+temp_TWDW,_XSCLout+iStartPos1,datalen);
                    temp_TWDW+=datalen;
                    deallen = iStartPos1+datalen;
                    break;
                case 0x38:

                    memcpy(YDout+temp_YD,_XSCLout+iStartPos1,datalen);
                    temp_YD+=datalen;
                    deallen = iStartPos1+datalen;
                    break;
                case 0x3D:

                    memcpy(JGTXCLRZout+temp_JGTXCLRZ,_XSCLout+iStartPos1,datalen);
                    temp_JGTXCLRZ+=datalen;
                    deallen = iStartPos1+datalen;
                    break;
                default:
                    deallen = deallen+4;
                    break;
                }
            }
            else{
                break;
            }
        }


       //l 7.05
        //todo
        //写文件
        FILE *fpOut;
//用于检测类型的区分
        if(temp_GYIPD>0)
        {
            sprintf(fileName, "%s/GYIPD.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            fwrite(GYIPDout, temp_GYIPD, 1, fpOut);
            fclose(fpOut);
            fpOut = NULL;
            rzid->errorGYIPDid += continuejudgexscl(GYIPDout,temp_GYIPD,1,&GYIPDnum);

        }
        if(temp_JGIPD>0)
        {
            sprintf(fileName, "%s/JGIPD.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            fwrite(JGIPDout, temp_JGIPD, 1, fpOut);
            fclose(fpOut);
            fpOut = NULL;
            rzid->errorJGIPDid += continuejudgexscl(JGIPDout,temp_JGIPD,2,&JGIPDnum);

        }
        if(temp_GYTWDW>0)
        {
            if(Pack_flag ==1){
                sprintf(fileName, "%s/GYTWDW01.dat", outputpath2711package);
                rzid->errorGYTWDW01id += continuejudgexscl(GYGTWout,temp_GYTWDW,31,&GYTWDW01num);
            }else if(Pack_flag==2){
                sprintf(fileName, "%s/GYTWDW02.dat", outputpath2711package);
                rzid->errorGYTWDW02id += continuejudgexscl(GYGTWout,temp_GYTWDW,32,&GYTWDW02num);
            }
//            sprintf(fileName, "%s/GYTWDW.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            fwrite(GYTWDWout, temp_GYTWDW, 1, fpOut);
            fclose(fpOut);
            fpOut = NULL;

        }
        if(temp_JGTWDW>0)
        {
            if(Pack_flag ==1){
                sprintf(fileName, "%s/JGTWDW01.dat", outputpath2711package);
                rzid->errorJGTWDW01id +=  continuejudgexscl(JGTWDWout,temp_JGTWDW,41,&JGTWDW01num);
            }else if(Pack_flag==2){
                sprintf(fileName, "%s/JGTWDW02.dat", outputpath2711package);
                rzid->errorJGTWDW02id += continuejudgexscl(JGTWDWout,temp_JGTWDW,41,&JGTWDW02num);
            }
            fpOut = fopen(fileName, "ab");
            fwrite(JGTWDWout, temp_JGTWDW, 1, fpOut);
            fclose(fpOut);
            fpOut = NULL;

        }
        if(temp_GYGTW>0)
        {
            sprintf(fileName, "%s/GYGTW.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            fwrite(GYGTWout, temp_GYGTW, 1, fpOut);
            fclose(fpOut);
            fpOut = NULL;
            rzid->errorGYGTWid += continuejudgexscl(GYGTWout,temp_GYGTW,5,&GYGTWnum);

        }
        if(temp_GYYDXX >0)
        {
            sprintf(fileName,"%s/GYYDXX02.dat",outputpath2711package);
            fpOut = fopen(fileName, "ab");
            fwrite(GYYDXXout, temp_GYYDXX, 1, fpOut);
            fclose(fpOut);
            fpOut = NULL;
            rzid->errorGYYDXXid += continuejudgexscl(GYYDXXout,temp_GYYDXX,6,&GYYDXXnum);

        }
        if(temp_GYYDXXXX>0)
        {
            if(Pack_flag ==1){
                sprintf(fileName, "%s/GYYDXX01.dat", outputpath2711package);
                rzid->errorGYYDXXXX01id += continuejudgexscl(GYYDXXXXout,temp_GYYDXXXX,71,&GYYDXXXX01num);
            }else if(Pack_flag==2){
                sprintf(fileName, "%s/GYYDXXXX.dat", outputpath2711package);
                rzid->errorGYYDXXXX02id += continuejudgexscl(GYYDXXXXout,temp_GYYDXXXX,72,&GYYDXXXX02num);
            }
            fpOut = fopen(fileName, "ab");
            fwrite(GYYDXXXXout, temp_GYYDXXXX, 1, fpOut);
            fclose(fpOut);
            fpOut = NULL;

        }

        if(temp_SJCL>0)
        {
            sprintf(fileName, "%s/GYTXCLRZ.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            fwrite(SJCLout, temp_SJCL, 1, fpOut);
            fclose(fpOut);
            fpOut = NULL;
            rzid->errorGYTXCLRZid += continuejudgexscl(SJCLout,temp_SJCL,8,&GYTXCLRZnum);

        }
        if(temp_TWDW>0)
        {
            sprintf(fileName, "%s/TWDWRZ.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            fwrite(TWDWout, temp_TWDW, 1, fpOut);
            fclose(fpOut);
            fpOut = NULL;
            rzid->errorTWDWRZid += continuejudgexscl(TWDWout,temp_TWDW,9,&TWDWRZnum);
        }
        if(temp_YD>0)
        {
            sprintf(fileName, "%s/YDGZRZ.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            fwrite(YDout, temp_YD, 1, fpOut);
            fclose(fpOut);
            fpOut = NULL;
            rzid->errorYDGZRZid += continuejudgexscl(YDout,temp_YD,10,&YDGZRZnum);
        }
        if(temp_JGTXCLRZ>0)
        {
            sprintf(fileName, "%s/JGTXCLRZ.dat", outputpath2711package);
            fpOut = fopen(fileName, "ab");
            fwrite(JGTXCLRZout, temp_JGTXCLRZ, 1, fpOut);
            fclose(fpOut);
            fpOut = NULL;
            rzid->errorJGTXCLRZid += continuejudgexscl(JGTXCLRZout,temp_JGTXCLRZ,11,&JGTXCLRZnum);
        }
        rzid->GYIPDid = GYIPDnum;
        rzid->JGIPDid = JGIPDnum;
        rzid->GYTWDW01id = GYTWDW01num;
        rzid->GYTWDW02id = GYTWDW02num;
        rzid->JGTWDW01id = JGTWDW01num;
        rzid->JGTWDW02id = JGTWDW02num;
        rzid->GYGTWid = GYGTWnum;
        rzid->GYYDXXid = GYYDXXnum;
        rzid->GYYDXXXX01id = GYYDXXXX01num;
        rzid->GYYDXXXX02id = GYYDXXXX02num;
        rzid->GYTXCLRZid = GYTXCLRZnum;
        rzid->TWDWRZid = TWDWRZnum;
        rzid->YDGZRZid = YDGZRZnum;
        rzid->JGTXCLRZid = JGTXCLRZnum;


     }
    *rmlen=cysumlen-deallen;
    memcpy(_XSCLout,_XSCLout+deallen,*rmlen);
    free(GYIPDout);GYIPDout=NULL;
    free(GYTWDWout);GYTWDWout=NULL;
    free(JGIPDout);JGIPDout=NULL;
    free(JGTWDWout);JGTWDWout=NULL;
    free(GYGTWout);GYGTWout=NULL;
    free(GYYDXXout);GYYDXXout=NULL;
    free(TWDWout);TWDWout=NULL;
    free(SJCLout);SJCLout=NULL;
    free(YDout);YDout=NULL;
    free(GYYDXXXXout);GYYDXXXXout = NULL;
    free(JGTXCLRZout);JGTXCLRZout = NULL;

}

void DealSourcePackage::dealJG100Package(unsigned char *_strJG100, int _JG100len, compressedStream *_comJG100, unsigned char *_JG100out, int *rmlen,unsigned int *packnumid ,struct RZid *rzid)
{
    //图像数据 压缩数据 数量
    __int64         temp_JG100 = 0;
    int iStartPos1 = 0;
    int cysumlen=0;
    __int64 BUFFSIZE = (8* 1024 * 1024);
    unsigned char	*JG100out= NULL;

    JG100out = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));

    if(NULL==JG100out)
    {
        qDebug()<<"jg100 malloc failed";
    }

    unsigned int flag;
    int    datalen = 100;
    int deallen = 0;

    char fileName[fileNameLen];
//    unsigned int dddpdpacknum=*packnumid;
    //该参数用来记录总包数序列
    //unsigned int packnum=0;
    unsigned int packnum=*packnumid;
    unsigned int jg100num = rzid->ZTid;
    //unsigned int dddpd2711num=*pdid,dddpdkc2711num=*kcid;
    //unpack->unpack1(_strDDDPD, _DDDPDlen, _comDDDPD->img, &(_comDDDPD->ilen), outputpathLog,state,&dddpdpacknum);
    unpack->newunpack(_strJG100, _JG100len, _comJG100->img, &(_comJG100->ilen), outputpathLog,&packnum);
    *packnumid=packnum;
    cysumlen = _comJG100->ilen+*rmlen;
    rzid->errorztdata += unpack->geterrornum();
    //gyout存储的是加残余数据的情况，这里可能还需要修改 避免残余数据冲突  11.28
    memcpy(_JG100out+*rmlen,_comJG100->img,_comJG100->ilen);   //考虑残余数据的情况   iShiftlen如何变
    //在EPDU域搜索55AA
    if(UnPack::jg100Detect(_JG100out,cysumlen,0,&iStartPos1))
    {
        if(_JG100out[iStartPos1+99]==0xFF){
            memcpy(JG100out,_JG100out+iStartPos1,datalen);
            temp_JG100+=datalen;
            deallen = iStartPos1+datalen;
        }else{
            deallen = iStartPos1+2;
        }

        while (deallen+datalen<=cysumlen)
        {
            flag = ((_JG100out[deallen] << 8) | (_JG100out[deallen+1]) ) & 0xffff;
            if(flag == 0x55AA)
            {
                if(deallen+datalen<cysumlen)
                {
                    if(_JG100out[deallen+99]==0xFF)
                    {
                        memcpy(JG100out+temp_JG100, _JG100out + deallen, datalen);
                        temp_JG100+= datalen;
                        deallen = deallen + datalen;
                    }
                    else{
                        deallen+=2;
                    }
                }
                else{
                    break;
                }


            }
            else
            {
                if(UnPack::jg100Detect(_JG100out, cysumlen, deallen, &iStartPos1))
                {
                    if(iStartPos1+datalen<cysumlen)
                    {
                        if(_JG100out[iStartPos1+99]==0xFF)
                        {
                            memcpy(JG100out+temp_JG100, _JG100out + iStartPos1, datalen);
                            temp_JG100 += datalen;
                            //*iZXGC = temp_ZXGC;
                            deallen = iStartPos1 + datalen;
                        }
                        else{
                            deallen = iStartPos1+2;
                        }
                    }
                    else{
                        break;
                    }
                }
                else
                {
                    //没有巴克码会返回本次码流的末尾
                    deallen = iStartPos1;
                }
            }

        }

        //连续性

        //写文件
        FILE *fpOut;
        sprintf(fileName, "%s/ZT.dat", outputpath2711package);
        fpOut = fopen(fileName, "ab");
        //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
        fwrite(JG100out, temp_JG100, 1, fpOut);
        //DKCBlen += (12 + datalen);
        fclose(fpOut);
        fpOut = NULL;

        rzid->errorZTid += continuejudgejg100(JG100out,temp_JG100,1,&jg100num);
        rzid->ZTid = jg100num;

     }
    *rmlen=cysumlen-deallen;
    memcpy(_JG100out,_JG100out+deallen,*rmlen);
    free(JG100out);JG100out=NULL;
}
//暂时缺省
void DealSourcePackage::dealXWGCPackage(unsigned char *_strXWGC, int _XWGClen, compressedStream *_comXWGC, unsigned char *_XWGCout, int *rmlen, int Pack_flag,unsigned int *packnumid,struct RZid *rzid)
{
       __int64         temp_XWGC = 0 , temp_SSXWGC = 0 ;
       int iStartPos1 = 0;
       int cysumlen=0;
       __int64 BUFFSIZE = (8* 1024 * 1024);//调试一下buffsize
       unsigned int flag;
       int    type = 0x00;
       int    datalen = 0;
       int deallen = 0;
       char fileName[fileNameLen];
       FILE *fpOut;
       unsigned int xwgcpacknum,ssxwgcpacknum;
      if(Pack_flag == 1)
      {
          ssxwgcpacknum=*packnumid;
          unpack->newunpackxwgc(_strXWGC, _XWGClen, _comXWGC->img, &(_comXWGC->ilen), outputpathLog,&ssxwgcpacknum);
          memcpy(_XWGCout,_comXWGC->img,_comXWGC->ilen);
          temp_SSXWGC = _comXWGC->ilen;
          *packnumid=ssxwgcpacknum;
          if(temp_SSXWGC > 0)
          {
             sprintf(fileName,"%s/SSXWGC.dat",outputpath2711package);
             rzid->errorssxwgc += unpack->geterrornum();
             fpOut = fopen(fileName, "ab");
             if(NULL == fpOut)
             {
                 qDebug()<<"failed to open file SSXWGC";
             }
             fwrite(_XWGCout, temp_SSXWGC, 1, fpOut);
             fclose(fpOut);
             fpOut = NULL;
          }
      }
      else if(Pack_flag == 2){
          xwgcpacknum=*packnumid;
          unpack->newunpack(_strXWGC, _XWGClen, _comXWGC->img, &(_comXWGC->ilen), outputpathLog,&xwgcpacknum);
          memcpy(_XWGCout,_comXWGC->img,_comXWGC->ilen);
          temp_XWGC = _comXWGC->ilen;
          *packnumid=xwgcpacknum;
          if(temp_XWGC > 0)
          {
             sprintf(fileName,"%s/XWGC.dat",outputpath2711package);
             rzid->errorhfxwgc += unpack->geterrornum();
             fpOut = fopen(fileName, "ab");
             fwrite(_XWGCout, temp_XWGC, 1, fpOut);
             fclose(fpOut);
             fpOut = NULL;
          }
      }

}

void DealSourcePackage::undddpd(unsigned char *_strDDDPD, int _DDDPDlen, compressedStream *_comDDDPD, unsigned char *_DDDPDout, int *rmlen)
{
    __int64         temp_DDDPD = 0;

    //int EPDUflag;
    int iStartPos1 = 0,iendPos=0;
    unsigned int start = 0,end=0;
    int cysumlen=0;
    __int64 BUFFSIZE = (128* 1024 * 1024);
    unsigned char	*DDDPD2711out= NULL;

    DDDPD2711out = (unsigned char*)malloc(40*BUFFSIZE * sizeof(unsigned char));   //存放解压缩数据
    if (NULL == DDDPD2711out)
    {
        MainWindow::fakeUi->setLinetext(QString("check: failed to apply for UNDDDPD space!!\n"));
        qDebug()<<"fail malloc";
        return;
    }

    unsigned int flag,synflag;
    int    type = 0x00;
    int    datalen = 0;
    int deallen = 0;

    //解压缩的参数
    unsigned int lCompressLength = 0;
    unsigned int lDeCompressLength=0;
    unsigned char *pDeCompress=NULL;
    pDeCompress=(unsigned char*)malloc(0.25*BUFFSIZE * sizeof(unsigned char));    //存放单次解压缩数据
    if (NULL == pDeCompress)
    {
        MainWindow::fakeUi->setLinetext(QString("check: failed to apply for UNDDDPD space!!\n"));
        qDebug()<<"fail malloc2";
        return;
    }
    //char pDecErrorDes;
    char* pMessage = (char*)malloc(2048 * sizeof(char));
    int lResult;

    char fileName[fileNameLen];
    //提取EPDU域
    unpack->unpack(_strDDDPD, _DDDPDlen, _comDDDPD->img, &(_comDDDPD->ilen), outputpathLog,1);
    cysumlen = _comDDDPD->ilen+*rmlen;

    //将EPDU域拷贝到有残留数据的空间
    memcpy(_DDDPDout+*rmlen,_comDDDPD->img,_comDDDPD->ilen);

    //EPDUflag = 5;
    //检测到F5F6EB90
    if(UnPack::barkDetect(_DDDPDout,cysumlen,0,&iStartPos1))
    {

        //type= _DDDPDout[iStartPos1+6];  //数据类型 0X22
        synflag = ((_DDDPDout[iStartPos1+920] << 24) | (_DDDPDout[iStartPos1+921] << 16) | (_DDDPDout[iStartPos1+922] << 8) |_DDDPDout[iStartPos1+923]) & 0xffffffff;

        //压缩帧头 ffd8ff77 压缩帧尾 e0e0e0e0
        if(synflag==0xffd8fff7 && UnPack::endDetect(_DDDPDout,cysumlen,924,&iendPos)){
            start = iStartPos1;
            end = iendPos;
            lCompressLength=iendPos-iStartPos1;//压缩数据的长度

            //写一下压缩的数据
            FILE *fpOut;
            sprintf(fileName, "%s/compressedDDDPD_2711.dat", outputpathLog);
            fpOut = fopen(fileName, "ab");
            //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
            fwrite(_DDDPDout+iStartPos1, lCompressLength, 1, fpOut);
            //DKCBlen += (12 + datalen);
            fclose(fpOut);
            fpOut = NULL;

            //DeCompressMap(_DDDPDout+iStartPos1,lCompressLength,&lDeCompressLength,pDeCompress,&pDecErrorDes);



            //解压缩文件 新版可能改变
            //lResult = DeCompressMap(_DDDPDout+iStartPos1,lCompressLength,&lDeCompressLength,pDeCompress,pMessage);


            //qDebug() << "pMessage:" << pMessage << endl;
            //解压缩的状态  0
            if(lResult==0)
            {
                memcpy(DDDPD2711out,pDeCompress,lDeCompressLength);
                temp_DDDPD+=lDeCompressLength;
                deallen = start + lCompressLength;
            }
            else
            {
                qDebug() << "lResult:" << lResult << endl;
                FILE *fpOut;
                sprintf(fileName, "%s/unDDDPD_2711.txt", outputpathLog);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(pMessage, strlen(pMessage), 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;
                deallen=end;
            }

        }
        //int sum=0;
        //如果能找到下一个帧头和帧尾,要保证帧尾在后面
        //while(UnPack::barkDetect(_DDDPDout,cysumlen,deallen,&iStartPos1)&&UnPack::endDetect(_DDDPDout,cysumlen,deallen,&iendPos))
        while(UnPack::barkDetect(_DDDPDout,cysumlen,deallen,&iStartPos1))
        {
            start = iStartPos1;
            if(start+1850>cysumlen){
                break;
            }
            synflag = ((_DDDPDout[iStartPos1+920] << 24) | (_DDDPDout[iStartPos1+921] << 16) | (_DDDPDout[iStartPos1+922] << 8) |_DDDPDout[iStartPos1+923]) & 0xffffffff;
            if(synflag==0xffd8fff7 &&UnPack::endDetect(_DDDPDout,cysumlen,1844+start,&iendPos)){
                end = iendPos;

                lCompressLength=iendPos-iStartPos1;//压缩数据的长度

                //写一下压缩的数据
                FILE *fpOut;
                sprintf(fileName, "%s/compressedDDDPD_2711.dat", outputpathLog);
                fpOut = fopen(fileName, "ab");
                //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                fwrite(_DDDPDout+iStartPos1, lCompressLength, 1, fpOut);
                //DKCBlen += (12 + datalen);
                fclose(fpOut);
                fpOut = NULL;

                //DeCompressMap(_DDDPDout+iStartPos1,lCompressLength,&lDeCompressLength,pDeCompress,&pDecErrorDes);
                //2021.1.4 注释下一行
                //lResult = DeCompressMap(_DDDPDout+iStartPos1,lCompressLength,&lDeCompressLength,pDeCompress,pMessage);
                if(lResult==0)
                {
                    memcpy(DDDPD2711out+temp_DDDPD,pDeCompress,lDeCompressLength);
                    temp_DDDPD+=lDeCompressLength;
                    deallen = end;
                }
                else{
                    qDebug() << "lResult:" << lResult << endl;
                    FILE *fpOut;
                    sprintf(fileName, "%s/unDDDPD_2711.txt", outputpathLog);
                    fpOut = fopen(fileName, "ab");
                    //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
                    fwrite(pMessage, strlen(pMessage), 1, fpOut);
                    //DKCBlen += (12 + datalen);
                    fclose(fpOut);
                    fpOut = NULL;
                    deallen=end;
                }
            }
            else if(synflag==0xffd8fff7){
                break;
            }

        }
//        switch (type)
//        {
//        //40
//        case DDDPD_S: //14
//            //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
//            memcpy(_DDDPDout,_comDDDPD->img+iStartPos1,920);
//            temp_DDDPD+=920;
//            deallen = iStartPos1+920;
//            break;
//        case DDDPDKC_S:  //24
//            //datalen = (_comXJCS->img[iStartPos1 + 8] <<8 ) | _comXJCS->img[iStartPos1+9];
//            memcpy(_DDDPDout,_comDDDPD->img+iStartPos1,920);
//            temp_DDDPDKC+=920;
//            deallen = iStartPos1+920;
//            break;
//        default:
//            //qDebug()<<type<<"weizhiyuanbao";
//            break;
//        }



        //写文件
        FILE *fpOut;
        sprintf(fileName, "%s/unDDDPD_2711.dat", outputpath2711package);
        fpOut = fopen(fileName, "ab");
        //                fwrite(srcpackage + i, 12 + datalen, 1, fpOut);
        fwrite(DDDPD2711out, temp_DDDPD, 1, fpOut);
        //DKCBlen += (12 + datalen);
        fclose(fpOut);
        fpOut = NULL;


     }
    *rmlen=cysumlen-deallen;
    memcpy(_DDDPDout,_DDDPDout+deallen,*rmlen);

    free(DDDPD2711out);DDDPD2711out=NULL;
    free(pDeCompress);pDeCompress=NULL;
}

//参数三 总包数，参数4包序 参数5 帧序
int DealSourcePackage::judge(unsigned char *Inputcode, int Inputlength, unsigned int *sumpack, int *packflag, int *frameflag)
{
    unsigned int zflag1=0,zflag2=0,type=0,bflag=0,bflag2=0,sumflag=0;
    bool startb =0; //一幅图像检测开始
    int packid=0,lineid=0;  //包序


    for (int i=0;i<Inputlength/920;i++)
    {
        *sumpack+=1;
        //记录首包数据序列计数
        if(i==0){
            zflag1=((Inputcode[12+i*920]<<8)|Inputcode[13+i*920])& 0xFFFF;   //帧计数
            bflag =((Inputcode[16+i*920]<<8)|Inputcode[17+i*920])& 0xFFFF;   //包计数
            //不等于0的状态判断包与包的状态
            if(*packflag!=0&&*frameflag!=0){
                type=((Inputcode[10+i*920]<<8)|Inputcode[11+i*920])& 0xFFFF;
                if(type==0XBBBB)
                {
                    if(*frameflag+1 != zflag1){
                        qDebug()<<zflag1<<"AND"<<zflag2<<"FRAME!"<<*sumpack;
                    }
                }
                else if(type==0XAAAA){
                    if(*packflag+1 != bflag){
                        qDebug()<<bflag<<"AND"<<bflag2<<"PACK"<<*sumpack;
                    }
                }
            }
        }
        else
        {
            type=((Inputcode[10+i*920]<<8)|Inputcode[11+i*920])& 0xFFFF;
            if(type==0xBBBB){
                zflag2=((Inputcode[12+i*920]<<8)|Inputcode[13+i*920])& 0xFFFF;   //帧计数
                if ((zflag1 + 1) != zflag2)
                {
                    qDebug()<<zflag1<<"AND"<<zflag2<<"FRAME!"<<*sumpack;
                }
                zflag1=zflag2;
                bflag=0;
            }
            else if(type==0xAAAA)
            {
                bflag2 =((Inputcode[16+i*920]<<8)|Inputcode[17+i*920])& 0xFFFF;   //包计数
                if ((bflag+ 1) != bflag2)
                {
                    qDebug()<<bflag<<"AND"<<bflag2<<"PACK"<<*sumpack;
                }
                bflag=bflag2;

            }
            else{
                qDebug()<<"包类型错误!!!";
            }

       }

        if(i==Inputlength/920-1){
            *packflag=((Inputcode[16+i*920]<<8)|Inputcode[17+i*920])& 0xFFFF;
            *frameflag=((Inputcode[12+i*920]<<8)|Inputcode[13+i*920])& 0xFFFF;
        }

    }
}
//不判断循环与循环之间相连接的部分的简单版本
int DealSourcePackage::continuejudge(unsigned char *Inputcode,int Inputlength,int imagetypeflag,unsigned int *lineid)
{
    char   fileName[fileNameLen];
    FILE   *fpOut;
    char outwords[200];
    unsigned int zflag1=0,zflag2=0,type=0,bflag=0,bflag2=0;
    char dataname[20];    //日志文件
    if(imagetypeflag == 1)
    {
        sprintf(dataname,"ssdkcb2711");
    }
    else if(imagetypeflag ==2){
        sprintf(dataname,"hfdkcb2711");
    }
    else if(imagetypeflag ==3){
        sprintf(dataname,"ssdkzcb2711");
    }
    else if(imagetypeflag ==4){
        sprintf(dataname,"hfdkzcb2711");
    }
    else if(imagetypeflag ==5){
        sprintf(dataname,"ssdddb2711");
    }
    else if(imagetypeflag ==6){
        sprintf(dataname,"hfdddb2711");
    }
    else if(imagetypeflag ==7){
        sprintf(dataname,"ssdddpd2711");
    }
    else if(imagetypeflag ==8){
        sprintf(dataname,"hfdddpd2711");
    }
    else if(imagetypeflag ==9){
        sprintf(dataname,"ssdddpdkc2711");
    }
    else if(imagetypeflag ==10){
        sprintf(dataname,"hfdddpdkc2711");
    }
    else {
        sprintf(dataname,"unknown");
    }

    for (int i=0;i<Inputlength/920;i++)
    {
        //*sumpack+=1;
        //记录首包数据序列计数
        if(i==0){
            zflag1=((Inputcode[12+i*920]<<8)|Inputcode[13+i*920])& 0xFFFF;   //帧计数
            bflag =((Inputcode[16+i*920]<<8)|Inputcode[17+i*920])& 0xFFFF;   //包计数

        }
        else
        {
            type=((Inputcode[10+i*920]<<8)|Inputcode[11+i*920])& 0xFFFF;
            if(type==0xBBBB){
                zflag2=((Inputcode[12+i*920]<<8)|Inputcode[13+i*920])& 0xFFFF;   //帧计数
                if ((zflag1 + 1) != zflag2 && (zflag1 + 2) != zflag2)
                {
                    //qDebug()<<zflag1<<"AND"<<zflag2<<"FRAME not continune!";
                    sprintf(outwords,"%s/图像连续性检测中，第%d包与第%d包之间不连续bes %d \n",dataname,zflag1,zflag2,*lineid);
                    //sprintf(fileName,"%s/image.txt",outputpathLog);
                    sprintf(fileName,"%s/image%s.txt",outputpathLog,dataname);
                    fpOut = fopen(fileName,"ab");
                    if(fpOut == NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;
                }
                zflag1=zflag2;
                bflag=0;
            }
            else if(type==0xAAAA)
            {
                zflag2=((Inputcode[12+i*920]<<8)|Inputcode[13+i*920])& 0xFFFF;
                if(zflag2!=zflag1){
                    sprintf(outwords,"%s/图像连续性检测中，第%d包与第%d包之间不连续bes %d \n",dataname,zflag1,zflag2,*lineid);
                    //sprintf(fileName,"%s/image.txt",outputpathLog);
                    sprintf(fileName,"%s/image%s.txt",outputpathLog,dataname);
                    fpOut = fopen(fileName,"ab");
                    if(fpOut == NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;
                    zflag1=zflag2;
                    bflag=((Inputcode[16+i*920]<<8)|Inputcode[17+i*920])& 0xFFFF;
                }
                else{
                    bflag2 =((Inputcode[16+i*920]<<8)|Inputcode[17+i*920])& 0xFFFF;   //包计数
                    if ((bflag+ 1) != bflag2)
                    {
                        //qDebug()<<bflag<<"AND"<<bflag2<<"PACK";
                        sprintf(outwords,"%s/图像连续性检测中，%d包第%d行与第%d行之间不连续\n",dataname,zflag1,bflag,bflag2);
                        //sprintf(fileName,"%s/image.txt",outputpathLog);
                        sprintf(fileName,"%s/image%s.txt",outputpathLog,dataname);
                        fpOut = fopen(fileName,"ab");
                        if(fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;
                    }
                    bflag=bflag2;

                }

            }
            else{
                qDebug()<<"包类型错误!!!";
            }

       }

        int check = 0;
        int check1=0;
        for(int j = 8; j < 918; j++)
        {
            /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
            check =(check+Inputcode[920*i+j]);
            //11.2删
            //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
        }
        //check=check+datalen;
        check=check&0xffff;
        check1=((Inputcode[920*i + 918] << 8) | Inputcode[920*i + 919])&0xffff;

        if(check != check1)
        {
//            qDebug()<<"adderror"<<endl;//加和报错
            sprintf(outwords,"%s/图像，%d包第%d行检验和错误bes %d\n",dataname,zflag1,bflag,*lineid);
            //sprintf(fileName,"%s/image.txt",outputpathLog);
            sprintf(fileName,"%s/adderror%s.txt",outputpathLog,dataname);
            fpOut = fopen(fileName,"ab");
            if(fpOut == NULL)
            {
                MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
            }
            fwrite(outwords,strlen(outwords),1,fpOut);
            fclose(fpOut);
            fpOut=NULL;

        }

        *lineid=*lineid+1;
    }
}

int DealSourcePackage::continuejudgejgcj(unsigned char *Inputcode, int Inputlength, int imagetypeflag)
{
    char   fileName[fileNameLen];
    FILE   *fpOut;
    char outwords[200];
    unsigned int zflag1=0,zflag2=0,type=0,bflag=0,bflag2=0;
    char dataname[20];    //日志文件
    if(imagetypeflag ==11){
        sprintf(dataname,"jgcjcbzf2711");
    }
    else if(imagetypeflag ==12){
        sprintf(dataname,"jgcjfsjz2711");
    }
    else if(imagetypeflag ==13){
        sprintf(dataname,"jgcjjsjz2711");
    }
    else {
        sprintf(dataname,"unknown");
    }

    for (int i=0;i<Inputlength/920;i++)
    {
        //*sumpack+=1;
        //记录首包数据序列计数
        if(i==0){
            zflag1=((Inputcode[12+i*920]<<8)|Inputcode[13+i*920])& 0xFFFF;   //帧计数
            bflag =((Inputcode[16+i*920]<<8)|Inputcode[17+i*920])& 0xFFFF;   //包计数

        }
        else
        {
            type=((Inputcode[10+i*920]<<8)|Inputcode[11+i*920])& 0xFFFF;
            if(type==0xBBBB){
                zflag2=((Inputcode[12+i*920]<<8)|Inputcode[13+i*920])& 0xFFFF;   //帧计数
                if ((zflag1 + 1) != zflag2)
                {
                    //qDebug()<<zflag1<<"AND"<<zflag2<<"FRAME not continune!";
                    sprintf(outwords,"%s/图像连续性检测中，第%d包与第%d包之间不连续\n",dataname,zflag1,zflag2);
                    //sprintf(fileName,"%s/image.txt",outputpathLog);
                    sprintf(fileName,"%s/image%s.txt",outputpathLog,dataname);
                    fpOut = fopen(fileName,"ab");
                    if(fpOut == NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;
                }
                zflag1=zflag2;
                bflag=0;
            }
            else if(type==0xAAAA)
            {
                bflag2 =((Inputcode[16+i*920]<<8)|Inputcode[17+i*920])& 0xFFFF;   //包计数
                if ((bflag+ 1) != bflag2)
                {
                    //qDebug()<<bflag<<"AND"<<bflag2<<"PACK";
                    sprintf(outwords,"%s/图像连续性检测中，%d包第%d行与第%d行之间不连续\n",dataname,zflag1,bflag,bflag2);
                    //sprintf(fileName,"%s/image.txt",outputpathLog);
                    sprintf(fileName,"%s/image%s.txt",outputpathLog,dataname);
                    fpOut = fopen(fileName,"ab");
                    if(fpOut == NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;
                }
                bflag=bflag2;

            }
            else{
                qDebug()<<"包类型错误!!!";
            }

       }

        int check = 0;
        int check1=0;
        for(int j = 8; j < 918; j++)
        {
            /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
            check =(check+Inputcode[920*i+j]);
            //11.2删
            //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
        }
        //check=check+datalen;
        check=check&0xffff;
        check1=((Inputcode[920*i + 918] << 8) | Inputcode[920*i + 919])&0xffff;

        if(check != check1)
        {
//            qDebug()<<"adderror"<<endl;//加和报错
            sprintf(outwords,"%s/图像，%d包第%d行检验和错误\n",dataname,zflag1,bflag);
            //sprintf(fileName,"%s/image.txt",outputpathLog);
            sprintf(fileName,"%s/adderror%s.txt",outputpathLog,dataname);
            fpOut = fopen(fileName,"ab");
            if(fpOut == NULL)
            {
                MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
            }
            fwrite(outwords,strlen(outwords),1,fpOut);
            fclose(fpOut);
            fpOut=NULL;

        }


    }
}

int DealSourcePackage::continuejudgegy(unsigned char *Inputcode,int Inputlength, int imagetypeflag,unsigned int *lineid)
{
    int errornum = 0;
    char   fileName[fileNameLen];
    FILE   *fpOut;
    char outwords[200];
//    unsigned int zflag=0,zflag2=0,type=0,bflag=0,bflag2=0,hflag=0,hflag2=0;
    unsigned int type = 0;
    char dataname[20];    //日志文件
    //todo
    //根据数据类型进行修改
      if(imagetypeflag == 11)
      {
         sprintf(dataname,"GYA");
      }
      else if(imagetypeflag == 12)
      {
         sprintf(dataname,"GYA21");
      }
      else if(imagetypeflag == 14)
      {
         sprintf(dataname,"GYA41");
      }
      else if(imagetypeflag == 21)
      {
         sprintf(dataname,"GYB");
      }
      else if(imagetypeflag == 22)
      {
         sprintf(dataname,"GYB21");
      }
      else if(imagetypeflag == 24)
      {
         sprintf(dataname,"GYB41");
      }
      else if(imagetypeflag == 31)
      {
         sprintf(dataname,"GYC");
      }
      else if(imagetypeflag == 32)
      {
         sprintf(dataname,"GYC21");
      }
      else if(imagetypeflag == 34)
      {
         sprintf(dataname,"GYC41");
      }
      else if(imagetypeflag == 41)
      {
         sprintf(dataname,"GYPRO");
      }
      else if(imagetypeflag == 42)
      {
         sprintf(dataname,"GYPRO21");
      }
      else if(imagetypeflag == 44)
      {
         sprintf(dataname,"GYPRO41");
      }
      else
      {
         sprintf(dataname,"unknow");
      }
     //DONE

    //todo
    //此处检测需要修改
    //包计数可额外判断，帧计数和行计数根据逻辑判断，一包其实就是一行
    //图像示意图
    /**包计数**********帧计数***********行计数**********
     *  0              0                0
     *  1              0                1
     *  2              0                2
     * ..............................................
     * 8900            0               8900
     * 8901            1                 0
     * 8902            1                 1
     * 8903            1                 2
     * .........
     * *************************************************/
    //原始GY图像数据长度17816
    for (int i=0;i< Inputlength/17816;i++)
    {
        //*sumpack+=1;
        //记录首包数据序列计数
        if(flags_gy.headflag == true)//fLAG
        {
            //不用改
            flags_gy.bflag =((Inputcode[5+i*17816]<<16)|(Inputcode[6+i*17816]<<8)|Inputcode[7+i*17816])&0xFFFFFF;    //包计数
            flags_gy.zflag=((Inputcode[10+i*17816]<<8)|Inputcode[11+i*17816])&0xFFFF;   //帧计数
            flags_gy.hflag=((Inputcode[12+i*17816]<<8)|Inputcode[13+i*17816])& 0xFFFF;   //行计数
            flags_gy.headflag = false;
        }
        else
        {
            //这里要改
            //按要求判断包计数/帧计数/行计数
            flags_gy.bflag2=((Inputcode[5+i*17816]<<16)|(Inputcode[6+i*17816]<<8)|Inputcode[7+i*17816])&0xFFFFFF;
            if((flags_gy.bflag+1) != flags_gy.bflag2)
            {
               if(flags_gy.bflag != 16777215 || flags_gy.bflag2 != 0)
               {
                   errornum ++;
                   sprintf(outwords,"%s/图像连续性检测中，第%d包与第%d包之间不连续bes %d \n",dataname,flags_gy.bflag,flags_gy.bflag2,*lineid);
//                     sprintf(outwords,"%s/图像连续性检测中，第%d包与第%d包之间不连续bes \n",dataname,flags_gy.bflag,flags_gy.bflag2);
                   //sprintf(fileName,"%s/image.txt",outputpathLog);
                   sprintf(fileName,"%s/ImageContinue%s.txt",outputpathLog,dataname);
                   fpOut = fopen(fileName,"ab");
                   if(fpOut == NULL)
                   {
                       MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                   }
                   fwrite(outwords,strlen(outwords),1,fpOut);
                   fclose(fpOut);
                   fpOut=NULL;
               }
            }
            flags_gy.bflag = flags_gy.bflag2;
            //判断行连续
            type=((Inputcode[36+i*17816]<<8)|Inputcode[37+i*17816])& 0xFFFF;//判断辅助数据和图像数据
            if(type==0x1111)
            {
                flags_gy.zflag2=((Inputcode[10+i*17816]<<8)|Inputcode[11+i*17816])&0xFFFF;
                if((flags_gy.zflag+1)!=flags_gy.zflag2)
                {
                    if(flags_gy.zflag != 65535 || flags_gy.zflag2 != 0)
                    {
                        sprintf(outwords,"%s图像连续性检测中,第%d包的第%d帧与第%d帧之间不连续bes %d \n",dataname,flags_gy.bflag,flags_gy.zflag,flags_gy.zflag2,*lineid);
                        sprintf(fileName,"%s/ImageContinue%s.txt",outputpathLog,dataname);
                        fpOut=fopen(fileName,"ab");
                        if(fpOut==NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;
                    }
                }
                flags_gy.zflag=flags_gy.zflag2;
                flags_gy.hflag=0;
            }
            else
            {
                flags_gy.zflag2=((Inputcode[10+i*17816]<<8)|Inputcode[11+i*17816])&0xFFFF;
                if(flags_gy.zflag!=flags_gy.zflag2)
                {
                    sprintf(outwords,"%s图像连续性检测中,第%d帧与第%d帧之间不连续bes %d\n",dataname,flags_gy.zflag,flags_gy.zflag2,*lineid);
                    sprintf(fileName,"%s/ImageContinue%s.txt",outputpathLog,dataname);
                    fpOut=fopen(fileName,"ab");
                    if(fpOut==NULL)
                    {
                        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                    }
                    fwrite(outwords,strlen(outwords),1,fpOut);
                    fclose(fpOut);
                    fpOut=NULL;
                    flags_gy.zflag=flags_gy.zflag2;
                    flags_gy.hflag=((Inputcode[12+i*17816]<<8)|Inputcode[13+i*17816])& 0xFFFF;
                }
                else
                {
                     flags_gy.hflag2=((Inputcode[12+i*17816]<<8)|Inputcode[13+i*17816])& 0xFFFF;
                     if((flags_gy.hflag+1)!=flags_gy.hflag2)
                     {
                         if(flags_gy.hflag != 65535 || flags_gy.hflag2 !=0)
                         {
                             sprintf(outwords,"%s图像连续性检测中，第%d帧的第%d行与第%d行之间不连续bes  %d\n",dataname,flags_gy.zflag,flags_gy.hflag,flags_gy.hflag2,*lineid);
                             sprintf(fileName,"%s/ImageContinue%s.txt",outputpathLog,dataname);
                             fpOut=fopen(fileName,"ab");
                             if(fpOut==NULL)
                             {
                                 MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                             }
                             fwrite(outwords,strlen(outwords),1,fpOut);
                             fclose(fpOut);
                             fpOut=NULL;
                         }
                     }
                     flags_gy.hflag=flags_gy.hflag2;
                }
             }
            //done

       }

        //todo  校验和检测应该是好的，单保险起见还是核对一下
//累加校验和，双字节累加
        int check = 0;
        int check1=0;
        for(int j = 0; j < 17814; j+=2)//1.12号修改：出校验和外所有字符双字节累加
        {
            /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
            if(j+1<17814)
            {
                check=check+(Inputcode[17816*i+j]<<8)+Inputcode[17816*i+j+1];
            }
            else
            {
                check=check+(Inputcode[17816*i+j]<<8)+0x00;
            }

        }
        //check=check+datalen;
        check=check&0xffff;
        check1=((Inputcode[17816*i + 17814] << 8) | Inputcode[17816*i + 17815])&0xffff;

        if(check != check1)
        {
//            qDebug()<<"adderror"<<endl;//加和报错
            sprintf(outwords,"%s/图像，%d包第%d帧第%d行检验和错误bes %d\n",dataname,flags_gy.bflag,flags_gy.zflag,flags_gy.hflag,*lineid);
            sprintf(fileName,"%s/ImageAdderror%s.txt",outputpathLog,dataname);
            fpOut = fopen(fileName,"ab");
            if(fpOut == NULL)
            {
                MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
            }
            fwrite(outwords,strlen(outwords),1,fpOut);
            fclose(fpOut);
            fpOut=NULL;

        }

        *lineid=*lineid+1;
    }
    return errornum;
}
int DealSourcePackage::continuejudgejg(unsigned char *Inputcode,int Inputlength,int imagetypeflag,unsigned int *lineid)
{
    int errornum = 0;
    char   fileName[fileNameLen];
    FILE   *fpOut;
    char outwords[200];
//    unsigned int zflag1=0,zflag2=0,type=0,hflag=0,hflag2=0;
    unsigned int type;
    char dataname[20];    //日志文件
    int datalen = 3316;
    if(imagetypeflag == 1)
    {
        sprintf(dataname,"JG");
    }
    else {
        sprintf(dataname,"unknown");
    }
    for (int i=0;i<Inputlength/datalen;i++)
    {
        //*sumpack+=1;
        //记录首包数据序列计数
        if(flags_jg.headflag == true)
        {
            if((Inputcode[i*datalen]==0x49)&&(Inputcode[i*datalen+1]==0x54)&&(Inputcode[i*datalen+2]==0x92)&&(Inputcode[i*datalen+3]==0x64)&&(Inputcode[i*datalen+4]==0x04)&&(Inputcode[i*datalen+5]==0x00)&&(Inputcode[i*datalen+6]==0x00)&&(Inputcode[i*datalen+7]==0x01))
            {
                flags_jg.zflag=((Inputcode[24+i*datalen]<<8)|Inputcode[25+i*datalen])& 0xFFFF;//帧计数
            }
            else if((Inputcode[i*datalen]==0x49)&&(Inputcode[1+i*datalen]==0x94)&&(Inputcode[2+i*datalen]==0x00)&&(Inputcode[3+i*datalen]==0x00))
            {
                flags_jg.zflag=((Inputcode[10+i*datalen]<<8)|Inputcode[11+i*datalen])& 0xFFFF;//帧计数
                flags_jg.hflag=((Inputcode[12+i*datalen]<<8)|Inputcode[13+i*datalen])& 0xFFFF;//行计数
            }
            flags_jg.headflag = false;
        }
        else
        {
            if((Inputcode[i*datalen]==0x49)&&(Inputcode[i*datalen+1]==0x54)&&(Inputcode[i*datalen+2]==0x92)&&(Inputcode[i*datalen+3]==0x64)&&(Inputcode[i*datalen+4]==0x04)&&(Inputcode[i*datalen+5]==0x00)&&(Inputcode[i*datalen+6]==0x00)&&(Inputcode[i*datalen+7]==0x01))
            {
                flags_jg.zflag2=((Inputcode[24+i*datalen]<<8)|Inputcode[25+i*datalen])& 0xFFFF;   //帧计数
                if ((flags_jg.zflag + 1) != flags_jg.zflag2 )
                {
                    if(flags_jg.zflag != 65535 || flags_jg.zflag2 != 0)
                    {
                        sprintf(outwords,"%s/图像连续性检测中，第%d帧与第%d帧之间不连续bes %d \n",dataname,flags_jg.zflag,flags_jg.zflag2,*lineid);
    //                    sprintf(outwords,"%s/图像连续性检测中，第%d帧与第%d帧之间不连续bes \n",dataname,flags_jg.zflag,flags_jg.zflag2);
                        sprintf(fileName,"%s/ImageContinue%s.txt",outputpathLog,dataname);
                        fpOut = fopen(fileName,"ab");
                        if(fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;
                        errornum++;
                    }
                }
                flags_jg.zflag=flags_jg.zflag2;
                flags_jg.hflag=0;
            }
            else if((Inputcode[i*datalen]==0x49)&&(Inputcode[1+i*datalen]==0x94)&&(Inputcode[2+i*datalen]==0x00)&&(Inputcode[3+i*datalen]==0x00))
            {
                 flags_jg.zflag2=((Inputcode[10+i*datalen]<<8)|Inputcode[11+i*datalen])& 0xFFFF;//帧计数
                 if(flags_jg.zflag2 != flags_jg.zflag)
                 {
                     sprintf(outwords,"%s/图像连续性检测中，第%d帧与第%d帧之间不连续bes %d \n",dataname,flags_jg.zflag,flags_jg.zflag2,*lineid);
                     sprintf(fileName,"%s/ImageContinue%s.txt",outputpathLog,dataname);
                     fpOut = fopen(fileName,"ab");
                     if(fpOut == NULL)
                     {
                         MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                     }
                     fwrite(outwords,strlen(outwords),1,fpOut);
                     fclose(fpOut);
                     fpOut=NULL;
                     errornum++;
                     flags_jg.zflag=flags_jg.zflag2;
                     flags_jg.hflag=((Inputcode[12+i*datalen]<<8)|Inputcode[13+i*datalen])& 0xFFFF;
                 }
                 else{
                      flags_jg.hflag2 =((Inputcode[12+i*datalen]<<8)|Inputcode[13+i*datalen])& 0xFFFF;//4.10修改
                      if ((flags_jg.hflag+ 1) != flags_jg.hflag2)
                      {
                          if(flags_jg.hflag != 65535 || flags_jg.hflag2 != 0)
                          {
                             //qDebug()<<flags_gy.bflag<<"AND"<<flags_gy.bflag2<<"PACK";
     //                        sprintf(outwords,"%s/图像连续性检测中，%d帧第%d行与第%d行之间不连续 %\n",dataname,flags_jg.zflag,flags_jg.hflag,flags_jg.hflag2);
                             sprintf(outwords,"%s/图像连续性检测中，%d帧第%d行与第%d行之间不连续 %d\n",dataname,flags_jg.zflag,flags_jg.hflag,flags_jg.hflag2,*lineid);
                             //sprintf(fileName,"%s/image.txt",outputpathLog);
                             sprintf(fileName,"%s/ImageContinue%s.txt",outputpathLog,dataname);
                             fpOut = fopen(fileName,"ab");
                             if(fpOut == NULL)
                             {
                                 MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                             }
                             fwrite(outwords,strlen(outwords),1,fpOut);
                             fclose(fpOut);
                             fpOut=NULL;
                             errornum ++;
                          }
                       }
                         flags_jg.hflag=flags_jg.hflag2;
                 }

            }
            else{
                qDebug()<<"包类型错误!!!";
            }

       }
//双字节累加校验和
        int check = 0;
        int check1=0;
        for(int j = 0; j < 3314; j+=2)
        {
            /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
            if(j+1 < 3314)
            {
                check=check+(Inputcode[datalen*i+j]<<8)+Inputcode[datalen*i+j+1];
            }
            else
            {
                check=check+(Inputcode[datalen*i+j]<<8)+0x00;
            }
            //11.2删
            //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
        }
        //check=check+datalen;
        check=check&0xffff;
        check1=((Inputcode[datalen*i + 3314] << 8) | Inputcode[datalen*i + 3315])&0xffff;

        if(check != check1)
        {
//            qDebug()<<"adderror"<<endl;//加和报错
            sprintf(outwords,"%s/图像，%d帧第%d行检验和错误bes %d\n",dataname,flags_jg.zflag,flags_jg.hflag,*lineid);
//            sprintf(outwords,"%s/图像，%d包第%d行检验和错误bes %d\n",dataname,flags_jg.zflag,flags_jg.hflag,*lineid);
            sprintf(fileName,"%s/ImageAdderror%s.txt",outputpathLog,dataname);
            fpOut = fopen(fileName,"ab");
            if(fpOut == NULL)
            {
                MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
            }
            fwrite(outwords,strlen(outwords),1,fpOut);
            fclose(fpOut);
            fpOut=NULL;

        }

        *lineid=*lineid+1;
    }
    return errornum;
}
int DealSourcePackage::continuejudgejg100(unsigned char *Inputcode,int Inputlength, int imagetypeflag,unsigned int *lineid)
{
    int errornum = 0;
    char   fileName[fileNameLen];
    FILE   *fpOut;
    char outwords[200];
//    unsigned int zflag=0,zflag2=0,type=0,bflag=0,bflag2=0,hflag=0,hflag2=0;
    int datalen=100;
    char dataname[20];    //日志文件
    if(imagetypeflag == 1)
    {
        sprintf(dataname,"ZT");
    }
    else {
        sprintf(dataname,"unknown");
    }
    //JG100图像数据长度为100
    for (int i=0;i<Inputlength/datalen;i++)
    {
        //*sumpack+=1;
        //记录首包数据序列计数
        if(flags_zt.headflag == true)
        {
            flags_zt.bflag =((Inputcode[3+i*datalen]<<8)|(Inputcode[4+i*datalen]))&0xFFFF;    //包计数
            flags_zt.headflag = false;
        }
        else
        {
           if((Inputcode[i*datalen]==0x55)&&(Inputcode[1+i*datalen]==0xAA)&&(Inputcode[99+i*datalen]==0xFF))
           {
               flags_zt.bflag2=((Inputcode[3+i*datalen]<<8)|(Inputcode[4+i*datalen]))&0xFFFF;
                    if((flags_zt.bflag+1) != flags_zt.bflag2)
                    {
                        sprintf(outwords,"%s图像连续性检测中,第%d包与第%d包之间不连续bes %d\n",dataname,flags_zt.bflag,flags_zt.bflag2,*lineid);
                        sprintf(fileName,"%s/ImageContinue%s.txt",outputpathLog,dataname);
                        fpOut=fopen(fileName,"ab");
                        if(fpOut==NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;
                        errornum++;
                    }
                   flags_zt.bflag = flags_zt.bflag2;
           }
        }
        int check = 0;
        int check1=0;
        for(int j = 3; j < (datalen-2); j++)//单字节累加取低字节
        {
            /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
            check =(check+Inputcode[datalen*i+j]);
            //11.2删
            //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
        }
        //check=check+datalen;
        check=check&0xff;
        check1=(Inputcode[datalen*i +98])&0xff;

        if(check != check1)
        {
//            qDebug()<<"adderror"<<endl;//加和报错
            sprintf(outwords,"%s/图像，%d包检验和错误bes %d\n",dataname,flags_zt.bflag,*lineid);
//             sprintf(outwords,"%s/图像，%d包第%d行检验和错误bes \n",dataname,flags_zt.bflag,zflag);
            //sprintf(fileName,"%s/image.txt",outputpathLog);
            sprintf(fileName,"%s/ImageAdderror%s.txt",outputpathLog,dataname);
            fpOut = fopen(fileName,"ab");
            if(fpOut == NULL)
            {
                MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
            }
            fwrite(outwords,strlen(outwords),1,fpOut);
            fclose(fpOut);
            fpOut=NULL;

        }

        *lineid=*lineid+1;
    }
    return errornum;
}
int DealSourcePackage::continuejudgexscl(unsigned char *Inputcode,int Inputlength, int imagetypeflag,unsigned int *lineid)
{
    int errornum = 0;
    char   fileName[fileNameLen];
    FILE   *fpOut;
    char outwords[200];
//    unsigned int zflag=0,zflag2=0,type=0,bflag=0,bflag2=0,hflag=0,hflag2=0;
    int datalen=1024;
    char dataname[20];    //日志文件
    if(imagetypeflag == 1)
    {
        sprintf(dataname,"GYIPD");
    }
    else if(imagetypeflag == 2)
    {
        sprintf(dataname,"JGIPD");
    }
    else if(imagetypeflag == 31)
    {
        sprintf(dataname,"GYTWDW01 ");
    }
    else if(imagetypeflag == 32)
    {
        sprintf(dataname,"GYTWDW02 ");
    }
    else if(imagetypeflag == 41)
    {
        sprintf(dataname,"JGTWDW01 ");
    }
    else if(imagetypeflag == 42)
    {
        sprintf(dataname,"JGTWDW02 ");
    }
    else if(imagetypeflag == 5)
    {
        sprintf(dataname,"GYGTW");
    }
    else if(imagetypeflag == 6)
    {
        sprintf(dataname,"GYYDXX02 ");
    }
    else if(imagetypeflag == 71)
    {
        sprintf(dataname,"GYYDXX01");
    }
    else if(imagetypeflag == 72)
    {
        sprintf(dataname,"GYYDXXXX");
    }
    else if(imagetypeflag == 8)
    {
        sprintf(dataname,"GYTXCLRZ  ");
    }
    else if(imagetypeflag == 9)
    {
        sprintf(dataname,"TWDWRZ");
    }
    else if(imagetypeflag == 10)
    {
        sprintf(dataname,"YDGZRZ");
    }
    else if(imagetypeflag == 11)
    {
        sprintf(dataname," JGTXCLRZ  ");
    }

    else {
        sprintf(dataname,"unknown");
    }
    //星上处理图像数据长度为1024
    for (int i=0;i<Inputlength/datalen;i++)
    {
        //*sumpack+=1;
        //记录首包数据序列计数
        if(i==0)
        {
            flags_xscl.bflag =((Inputcode[4+i*datalen]<<8)|(Inputcode[5+i*datalen]))&0xFFFF;    //包计数
        }
        else
        {
           if((Inputcode[i*datalen]==0xF5)&&(Inputcode[1+i*datalen]==0xF6)&&(Inputcode[2+i*datalen]==0xEB)&&(Inputcode[3+i*datalen]==0x90))
           {
              flags_xscl.bflag2=((Inputcode[4+i*datalen]<<8)|(Inputcode[5+i*datalen]))&0xFFFF;
                if((flags_xscl.bflag+1) != flags_xscl.bflag2)
                {
                    if(flags_xscl.bflag !=65535 || flags_xscl.bflag2 != 0)
                    {
                        sprintf(outwords,"%s图像连续性检测中,第%d包与第%d包之间不连续bes %d\n",dataname,flags_xscl.bflag,flags_xscl.bflag2,*lineid);
                        sprintf(fileName,"%s/ImageContinue%s.txt",outputpathLog,dataname);
                        fpOut=fopen(fileName,"ab");
                        if(fpOut==NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
                        }
                        fwrite(outwords,strlen(outwords),1,fpOut);
                        fclose(fpOut);
                        fpOut=NULL;
                        errornum++;
                    }
                }
             flags_xscl.bflag = flags_xscl.bflag2;
           }
        }
        int check = 0;
        int check1=0;
        for(int j = 4; j < (datalen-2); j++)//单字节累加取双字节
        {
            check =(check+Inputcode[datalen*i+j]);
            //11.2删
            //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
        }
        //check=check+datalen;
        check=check&0xffff;
        check1=((Inputcode[datalen*i + 1022] << 8) | Inputcode[datalen*i + 1023])&0xffff;

        if(check != check1)
        {
//            qDebug()<<"adderror"<<endl;//加和报错
            sprintf(outwords,"%s/图像，%d包检验和错误bes %d\n",dataname,flags_xscl.bflag,*lineid);
//             sprintf(outwords,"%s/图像，%d包第%d行检验和错误bes \n",dataname,flags_xscl.bflag,zflag);
            //sprintf(fileName,"%s/image.txt",outputpathLog);
            sprintf(fileName,"%s/ImageAdderror%s.txt",outputpathLog,dataname);
            fpOut = fopen(fileName,"ab");
            if(fpOut == NULL)
            {
                MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(fileName)));
            }
            fwrite(outwords,strlen(outwords),1,fpOut);
            fclose(fpOut);
            fpOut=NULL;

        }

        *lineid=*lineid+1;
    }
    return errornum;
}

