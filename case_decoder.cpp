 #include "case_decoder.h"

#include "Extract_BPDU.h"
#include "pack_classify.h"
#include "mainwindow.h"
#include "myInclude.h"

#include <QDebug>
#include <QThread>
#include <ctime>
#include <fstream>
#include <sstream>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <winsock2.h> //加的
#include <windows.h>
#include <sys/stat.h>
#include <QDateTime>
#include <QTextCodec>
#include <QMutexLocker>
#include <sys/time.h>


CASE_Decoder::CASE_Decoder(bool *isRUNNING_DECODER, QObject *parent) :
    QThread(parent), mch1(""), mch2(""), savepath(""), isRUNNING_DECODER(isRUNNING_DECODER)
{

    qRegisterMetaType<QItemSelection>("QItemSelection");
}

//从界面的参数配置框中读取参数
void CASE_Decoder::OnRunPara(QList<QString> slist)
{
    mch1 = slist.at(0);
    mch2 = slist.at(1);
    savepath = slist.at(2);       
}

void CASE_Decoder::cyclestart()
{
    sended=1;//sended 用来控制解包线程和传递的异步，可以在发送数据之前将sended置为false，发完之后置为true
}

//注意这里全局变量数组大小变了，各个文件中extern的也要变
extern char outputpathLog[fileNameLen];  //输出日志路径
extern char	outputpath[fileNameLen]; //输出数据路径

char outputpathAOS[fileNameLen]; //输出AOS帧数传包数据路径
char outputpathSourcepackage[fileNameLen]; //输出源包数据路径
char outputpath2711package[fileNameLen]; //输出2711源包数据路径
char outputpath2711sub[fileNameLen]; //输出2711子包数据路径
char outputpath2711subsub[fileNameLen]; //输出2711子子包路径


void CASE_Decoder::run()
{

    if(mch1.isEmpty() || mch2.isEmpty())
    {
        return;
    }



    //解压缩部分
    //int             RealtimeFLAG;
    char			inputfile1[200];
    char			inputfile2[200];
    char			outputfile[fileNameLen];	   //输出文件名
    char			outputpath[200];
    char			outtest[fileNameLen];//by creat report.txt,ensure out path right！
    char			outputfileLog[fileNameLen];    //帧和校验文件的输出路径
    char			outwords[100];		 //存到文档中的内容

    //第一层参数
    FILE			*fpIn1, *fpIn2, *fptest, *fpOut;
    __int64			filelength1 = -1, filelength2 = -1, BUFFSIZE, PROCESSSIZE;
    __int64			iSumLen1 = 0, iProcLen1 = 0, iShiftLen1 = 0;
    __int64			iSumLen2 = 0, iProcLen2 = 0, iShiftLen2 = 0;

    //__int64     	SSRWlen, SSGClen, SSZHlen, HFGClen, HFZHlen, TCZlen,XJSJlen,BPDUlen = 0;
    __int64     	SSlen, HFlen, TCZlen,BPDUlen = 0;
    //__int64     	SSRWlen = 0, SSGClen = 0, SSZHlen = 0, HFGClen = 0, HFZHlen = 0, BPDUlen = 0;
    //__int64			nSSRWsum = 0, nSSGCsum = 0, nSSZHsum = 0, nHFGCsum = 0, nHFZHsum = 0,nTCZsum = 0,nXJSJsum = 0;//用于统计AOS帧6种数据各自的长度字节  6.10
    __int64			nSSsum = 0, nHFsum = 0, nTCZsum = 0;
    __int64			remainlen1, remainlen2;

    //源包
    int rmSSXWGClen=0,rmHFXWGClen=0,rm01A1len=0,rm02B1len=0,rm02C1len=0,rm0218len=0,rm032Elen=0,rm033Dlen=0,rm034Dlen=0,rm045Elen=0;
    //int             rmRWSJlen=0,rmDKCBlen=0,rmDDDPDlen=0,rmDDDBlen=0,rmDKZCBlen=0,rmZXGClen=0,rmXJCSlen=0,rmJGCSlen=0,rmJGYYlen=0;
    //int             rmSSRWSJlen=0,rmSSDKCBlen=0,rmSSDDDPDlen=0,rmSSDDDBlen=0,rmSSDKZCBlen=0,rmSSZXGClen=0,rmSSXJCSlen=0,rmSSJGYYlen=0;
    //__int64			iShiftLenRWSJ = 0,iShiftLenDKCB = 0,iShiftLenDDDPD = 0,iShiftLenDDDB = 0,iShiftLenDKZCB = 0,iShiftLenZXGC = 0,iShiftLenXJCS = 0,iShiftLenJGCS = 0,iShiftLenJGYY = 0;
    //unsigned int dddpdkclen;
    unsigned int synvc=0;
    int synflag=1;

    //连续性行数显示参数
    unsigned int ssid=0,hfid=0,tczid=0;
    //unsigned int ssrwid=0,sszhid=0,ssgcid=0,hfgcid=0,hfzhid=0,tczid=0;

    //unsigned int ssrwsjid=0,ssxwgcid=0,ssdkcbid=0,ssdkzcbid=0,ssdddbid=0,ssdddpdid=0,ssjgyyid=0,ssxjcsid=0;     //xwgc经确认后删除掉
    //unsigned int hfxwgcid=0,hfrwsjid=0,hfdkcbid=0,hfdkzcbid=0,hfdddbid=0,hfdddpdid=0,hfxjcsid=0,hfjgcsid=0,hfjgyyid=0;

    //l 7.15
    //这种数据用来写日志 象征该数据在所有数据中的顺序id
    /*****************************************************日志书写参数列表************************************************/
    /****第二层参数***/
    unsigned int  SSXWGCid=0,HFXWGCid=0,HF01A2id=0,HF02B1id=0,HF02C1id=0,HF0218id=0,HF032Eid=0,HF033Did=0,HF034Did=0,HF045Eid=0;
    /****第三层参数*****/
    /*SSXWGC,HFXWGC*/
    /*星务工参去格式存盘即可，没有第三层*/
    /*GY数据*/
//    unsigned int GYAid = 0 , GYA21id = 0, GYA41id = 0;
//    unsigned int GYBid = 0 , GYB21id = 0, GYB41id = 0;
//    unsigned int GYCid = 0 , GYC21id = 0, GYC41id = 0;
//    unsigned int GYproid = 0, GYpro21id = 0, GYpro41id = 0;

    struct RZid rzid ={};
    unpack = new UnPack;   //新建一个unpack对象
    dealSourcePackage = new DealSourcePackage(unpack);
    //y存放从fpIn1读取到的数据，AOS
    unsigned char	*strIn1= NULL, *strIn2= NULL;
    //remaincode1 这次读进文件1中（即str1）没有通过combine合并成功的数据
    unsigned char	*remaincode1= NULL, *remaincode2= NULL;
    unsigned char	*strremain1= NULL, *strremain2= NULL;
    //unsigned char	*SSRWdata= NULL, *SSGCdata= NULL, *SSZHdata= NULL, *HFGCdata= NULL, *HFZHdata= NULL, *TCZdata = NULL,*XJSJdata = NULL,*BPDUdata= NULL;
    unsigned char *SSdata= NULL,*HFdata= NULL, *TCZdata = NULL,*BPDUdata= NULL;
//    BUFFSIZE = (128* 1024 * frame_len);//y 256*1024*1024 256M 原128->16，64-48可
//    PROCESSSIZE=(128*1024*frame_len);

    BUFFSIZE = (8* 1024 * frame_len);//y 256*1024*1024 256M 原128->16，64-48可
    PROCESSSIZE=(8*1024*frame_len);//根据电脑可分配内存修改

    int AOSdataFlag = 0; //数传包数据类型标志


    //第二层 将存储源包数据分类 RHW DGP..
    //iProcLen3为strBPDU的长度
    //__int64			iSumLen3 = 0, iProcLen3 = 0, iShiftLen3 = 0;
    //__int64			iProcLen3 = 0, iShiftLen3 = 0;
    //__int64			iProcLen3 = 0, iShiftLenssrw = 0, iShiftLenssgc = 0, iShiftLensszh = 0, iShiftLenhfgc = 0, iShiftLenhfzh = 0;
    __int64			iProcLen3 = 0, iShiftLenss = 0, iShiftLenhf = 0;
    //unsigned char	*strssrw= NULL,*strssgc= NULL,*strsszh= NULL,*strhfgc= NULL,*strhfzh= NULL;
    unsigned char	*strss= NULL,*strhf= NULL;

    unsigned char	*strBPDU= NULL, *strXWGC= NULL;
    unsigned char	*str0187= NULL, *str01A2= NULL, *str02B1= NULL, *str02C1= NULL, *str0218= NULL, *str032E= NULL, *str033D= NULL, *str034D= NULL, *str045E= NULL;
    //unsigned char   *strSSZXGC= NULL, *strSSRWSJ= NULL, *strSSDKCB= NULL, *strSSDKZCB= NULL, *strSSDDDPD= NULL, *strSSDDDB= NULL, *strSSXJCS= NULL, *strSSJGYY= NULL;
    int				serialflag1 = 0;
    int XWGClen=0;
    int				HF0187len = 0, HF01A2len = 0,HF02B1len = 0,HF02C1len = 0,HF0218len = 0, HF032Elen = 0, HF033Dlen = 0, HF034Dlen = 0, HF045Elen = 0;
    //int				SSZXGClen = 0, SSRWSJlen = 0, SSDKCBlen = 0, SSDKZCBlen = 0, SSDDDPDlen = 0, SSDDDBlen = 0, SSXJCSlen = 0, SSJGYYlen = 0;
    int				pclen;

    struct SourceStream obtainedSourceStream;

    //第三层 参数
    struct compressedStream comZXGC, comRWSJ, comDKCB, comDKZCB, comDDDPD, comDDDB, comXJCS, comJGCS, comJGYY;//对压缩码流处理时需要的参数
    unsigned char *ZXGCout= NULL, *RWSJout= NULL, *DKCBout= NULL, *DKZCBout= NULL, *DDDPDout= NULL, *DDDBout= NULL, *XJCSout= NULL, *JGCSout= NULL, *JGYYout= NULL;

    struct compressedStream comSSZXGC, comSSRWSJ, comSSDKCB, comSSDKZCB, comSSDDDPD, comSSDDDB, comSSXJCS, comSSJGYY;//对压缩码流处理时需要的参数
    unsigned char *SSZXGCout= NULL, *SSRWSJout= NULL, *SSDKCBout= NULL, *SSDKZCBout= NULL, *SSDDDPDout= NULL, *SSDDDBout= NULL, *SSXJCSout= NULL, *SSJGYYout= NULL;
    unsigned char *DDDPDKC2711out=NULL,*DDDB2711out=NULL,*DKCB2711out=NULL,*DKZCB2711out=NULL;


    //第三层参数new
    struct compressedStream comSSXWGC, comXWGC, comGY, comJG, comJG100, comXSCL;//对压缩码流处理时需要的参数
    //GY
    unsigned char *SSXWGCout= NULL, *XWGCout= NULL, *_GYAout= NULL,*_GYBout= NULL, *_GYCout= NULL, *_JGout= NULL, *_JG100out= NULL, *XSCL01out= NULL, *XSCL02out= NULL;
    //受保护的GY相机图像
    unsigned char *_GYproout= NULL;

    //源包数据参数GY相机(可传入快是连接）
    unsigned char * GYAout = NULL, *GYA21out = NULL,*GYA41out = NULL;
    unsigned char * GYBout = NULL, *GYB21out = NULL,*GYB41out = NULL;
    unsigned char * GYCout = NULL, *GYC21out = NULL,*GYC41out = NULL;
    unsigned char * GYproout = NULL, *GYpro21out = NULL,*GYpro41out = NULL;
    unsigned char * JGout = NULL,*JG100out = NULL;


    //返回的数据值,处理时的每次处理数据值
     __int64 GYA_len = 0,GYB_len = 0, GYC_len = 0, GYpro_len = 0 ,JGXJ_len = 0, ZT_len = 0;


    strIn1 = (unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));//
    strIn2 = (unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));//
    strremain1 = (unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));//
    strremain2 = (unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));//

    //20210330 kj
    //这之后
    SSdata = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));//
    //SSGCdata = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));//
    //SSZHdata = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));//
    HFdata = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));//
    //HFZHdata = (unsigned char*)malloc(2* BUFFSIZE * sizeof(unsigned char));//
    TCZdata = (unsigned char*)malloc(2* BUFFSIZE * sizeof(unsigned char));
    //XJSJdata = (unsigned char*)malloc(2* BUFFSIZE * sizeof(unsigned char));

    remaincode1 = (unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));//
    remaincode2 = (unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));//

    BPDUdata = (unsigned char*)malloc( 2*PROCESSSIZE * sizeof(unsigned char));//
    strBPDU = (unsigned char*)malloc( 2*PROCESSSIZE * sizeof(unsigned char));//
//    strssrw = (unsigned char*)malloc( 4032 * sizeof(unsigned char));
//    strssgc = (unsigned char*)malloc( 4032 * sizeof(unsigned char));
//    strsszh = (unsigned char*)malloc( 4032 * sizeof(unsigned char));
//    strhfgc = (unsigned char*)malloc( 4032 * sizeof(unsigned char));
//    strhfzh = (unsigned char*)malloc( 4032 * sizeof(unsigned char));
    strss = (unsigned char*)malloc( 3568 * sizeof(unsigned char));
    strhf = (unsigned char*)malloc( 3568 * sizeof(unsigned char));

    strXWGC = (unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));//
    str0187 = (unsigned char*)malloc( 2*PROCESSSIZE * sizeof(unsigned char));//
    str01A2 = (unsigned char*)malloc( 2*BUFFSIZE * sizeof(unsigned char));//
    str02B1 = (unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));//
    str02C1 = (unsigned char*)malloc(2*BUFFSIZE * sizeof(unsigned char));//
    str0218 = (unsigned char*)malloc( 2*PROCESSSIZE * sizeof(unsigned char));//
    str032E = (unsigned char*)malloc( 2*PROCESSSIZE * sizeof(unsigned char));//
    str033D = (unsigned char*)malloc( 2*PROCESSSIZE * sizeof(unsigned char));//
    str034D = (unsigned char*)malloc(2* PROCESSSIZE * sizeof(unsigned char));//
    str045E = (unsigned char*)malloc(2* PROCESSSIZE * sizeof(unsigned char));


    SSXWGCout=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    XWGCout=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    _GYAout=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    _GYBout=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    _GYCout=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    _GYproout=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    _JGout=(unsigned char*)malloc(4*PROCESSSIZE * sizeof(unsigned char));//l
    _JG100out=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    XSCL01out=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    XSCL02out=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));

    GYAout=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    GYA21out=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    GYA41out=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    GYBout=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    GYB21out=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    GYB41out=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    GYCout=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    GYC21out=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    GYC41out=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    GYproout=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    GYpro21out=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    GYpro41out=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));
    JGout=(unsigned char*)malloc(4*PROCESSSIZE * sizeof(unsigned char));//l
    JG100out=(unsigned char*)malloc(2*PROCESSSIZE * sizeof(unsigned char));

    std::string     inputfile1_stdstr, inputfile2_stdstr;

    QString data_time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");//这一次运行的时间
    //保存路径的格式
    if(savepath.endsWith("\\"))
    {
        savepath = savepath + "backdisplay-" + data_time;
    }
    else
    {
        savepath = savepath + "\\" + "backdisplay-" + data_time;
    }

    strcpy(outputpath, savepath.toStdString().c_str());
    mkdir(outputpath);

    //y接收数据完成
    MainWindow::fakeUi->setLinetext(QString(""
                                          ""
                                          "firm !!! "));

    QTextCodec *textCodec = QTextCodec::codecForName("gb18030");
    if (textCodec == NULL)
    {
        emit stateSig("error", "AOS帧文件打开失败！");
        return;
    }

    inputfile1_stdstr = textCodec->fromUnicode(mch1).data();
    inputfile2_stdstr = textCodec->fromUnicode(mch2).data();

    //检测文件是不是空
    fpIn1 = fopen(inputfile1_stdstr.c_str(), "rb");
    fpIn2 = fopen(inputfile2_stdstr.c_str(), "rb");
    if (fpIn1 == NULL)
    {
        MainWindow::fakeUi->setLinetext(QString("File %1 cannot found.").arg(inputfile1) );
        return;
    }
    if (fpIn2 == NULL)
    {
        MainWindow::fakeUi->setLinetext(QString("File %1 cannot found.").arg(inputfile2));
        return;
    }

    filelength1 = filesize64(fpIn1); //y计算文件1长度
    filelength2 = filesize64(fpIn2);

    if (-1 == filelength1 || -1 == filelength2)
    {
        MainWindow::fakeUi->setLinetext(QString("check : error get filelength\n"));
        return;
    }

    MainWindow::fakeUi->setLinetext(QString("文件1码流长度为 %1 ,文件2码流长度为 %2").arg(filelength1).arg(filelength2));
    emit stateSig("success", QString("文件打开成功! 文件1码流长度为 %1 , 文件2码流长度为 %2").arg(filelength1).arg(filelength2));

    *isRUNNING_DECODER = true;

    //sprintf(outputpathLog, "%s/log", outputpath);
    sprintf(outputpathLog, "%s\\log", outputpath);
    mkdir(outputpathLog);

    sprintf(outputpathAOS, "%s/AOS", outputpath);
    mkdir(outputpathAOS);
    sprintf(outputpathSourcepackage, "%s/Sourcepackage", outputpath);
    mkdir(outputpathSourcepackage);
    sprintf(outputpath2711package, "%s/Imgpackage", outputpath);
    mkdir(outputpath2711package);
    sprintf(outputpath2711sub, "%s/2711sub", outputpath);
    mkdir(outputpath2711sub);
    sprintf(outputpath2711subsub, "%s/2711subsub", outputpath);
    mkdir(outputpath2711subsub);


    sprintf(outtest, "%s/report.txt", outputpathLog);
    fptest = fopen(outtest, "wb");
    if (fptest == NULL)
    {
        perror("File opening failed");
        MainWindow::fakeUi->setLinetext(QString("outputpath: %1").arg(EXIT_FAILURE));
        *isRUNNING_DECODER = false;
        return;
    }
    fclose(fptest);
    fptest = NULL;


    if (NULL == strIn1 || NULL == strIn2 || NULL == strremain1 || NULL == strremain2)
    {
        MainWindow::fakeUi->setLinetext(QString("check: failed to apply for AOS input space!!\n"));
        return;
    }
    //20210330 kj
    if (NULL == SSdata || NULL == HFdata || NULL == TCZdata  || NULL == remaincode1 || NULL == remaincode2)
    {
        MainWindow::fakeUi->setLinetext(QString("check: failed to apply for AOSdata space!!\n"));
        return;
    }
    //改
    if (NULL == BPDUdata || NULL == strBPDU || NULL == strXWGC || NULL == str0187  || NULL == str01A2 || NULL == str02B1 || NULL == str02C1 || NULL == str0218 || NULL == str032E || NULL == str033D || NULL == str034D || NULL == str045E)
    {
        MainWindow::fakeUi->setLinetext(QString("check: failed to apply for strBPDU && strRHW && str01A2... input space!!\n"));
        return;
    }

    if (NULL == strss || NULL == strhf)
    {
        MainWindow::fakeUi->setLinetext(QString("check: failed to apply for strvc input space!!\n"));
        return;
    }
    if( NULL == _GYAout || NULL == _GYBout||  NULL == _GYCout|| NULL == _GYproout||NULL == _JGout)
    {
        MainWindow::fakeUi->setLinetext(QString("check: failed to apply for _GYAout && _GYBout... input space!!\n"));
        return;
    }
    if(NULL == GYAout||NULL == GYA21out||NULL == GYA41out||NULL == GYCout||NULL == GYC21out||NULL == GYC41out|| NULL == GYBout || NULL == GYB21out || NULL == GYB41out || NULL == GYproout ||NULL == GYpro21out ||NULL == GYpro41out || NULL == JGout)
    {
        MainWindow::fakeUi->setLinetext(QString("check: failed to apply for GYAout && GYBout... input space!!\n"));
        return;
    }


    //初始化，分配空间
   //dealSourcePackage->initDealSourcePackage(&obtainedSourceStream, BUFFSIZE);
   //dealSourcePackage->initDealCompressedStream(&comZXGC, &comRWSJ, &comDKCB, &comDKZCB, &comDDDPD, &comDDDB, &comXJCS, &comJGCS, &comJGYY, &comSSZXGC, &comSSRWSJ, &comSSDKCB, &comSSDKZCB, &comSSDDDPD, &comSSDDDB, &comSSXJCS, &comSSJGYY,BUFFSIZE);
   //六种包
   dealSourcePackage->initDealStream(&comSSXWGC,&comXWGC,&comGY,&comJG,&comJG100,&comXSCL,BUFFSIZE);
    //这是好的
    //y iSumLen1对于一个文件数据已处理多长 filelength1一个文件数据长度
    //iProcLen1当前需处理数据长度，最大为buffsize
    //BUFFSIZE一次处理文件数据的大小，学长这里就是想设大一点，一次多处理点数据
   int a = 0 ;
    while ((iSumLen1 < filelength1 || iSumLen2 < filelength2))
    {
        if(sended)
        {
            mutex.lock();
            bool temp = *isRUNNING_DECODER;
            mutex.unlock();
            if(!temp)
            {
                autoexit = true;
                break;
            }
            QMutexLocker locker(&m_mutex);
            //初始值为1
            if (firstflag == 1)
            {
                //移动文件读写位置
//                fseek(fpIn1, skip_len, SEEK_SET);
//                fseek(fpIn2, skip_len, SEEK_SET);
                fseek(fpIn1, 0, SEEK_SET);
                fseek(fpIn2, 0, SEEK_SET);
                firstflag = 0;
//                iSumLen1 += skip_len;
//                iSumLen2 += skip_len;
            }
            //第二次循环开始后进行判断的
            else
            {
                //y
//                if (iShiftLen1 == BUFFSIZE && iShiftLen2 == 0)
//                    contFlag++;
//                else if (iShiftLen1 == 0 && iShiftLen2 == BUFFSIZE)
//                    contFlag++;
//                else
//                    contFlag = 0;

//                if (contFlag == 5)
//                    break;

                if (iSumLen1 + BUFFSIZE < filelength1)
                    iProcLen1 = BUFFSIZE;
                else
                {
                    iProcLen1 = filelength1 - iSumLen1;
                    synflag=3;
                }

                if (iSumLen2 + BUFFSIZE < filelength2)
                    iProcLen2 = BUFFSIZE;
                else
                {
                    iProcLen2 = filelength2 - iSumLen2;
                    synflag=3;
                }

                //把数据从文件流fpIn1读到strIn1所在位置
                //iShiftLen1为剩下数据长度，即上一次1通道会剩下一些数据没有合并，如1，3，5，7和2，4则剩下7
                //fread第二个参数为读取数据长度，这里我们为满足其长度一直为BUFFSIZE，故随着有剩余数据则减去
                fread(strIn1 + iShiftLen1, iProcLen1 - iShiftLen1, 1, fpIn1);
                fread(strIn2 + iShiftLen2, iProcLen2 - iShiftLen2, 1, fpIn2);

                //新增修改内容
                //            combine(strIn1, iProcLen1, strIn2, iProcLen2, SSRWdata, SSGCdata, SSZHdata, HFGCdata, HFZHdata,
                //                     &SSRWlen, &SSGClen, &SSZHlen, &HFGClen, &HFZHlen,
                //                     remaincode1, remaincode2, &remainlen1, &remainlen2, 0, record_len, frame_len, outputpath,selectvcid);
//                combine(strIn1, iProcLen1, strIn2, iProcLen2, SSRWdata, SSGCdata, SSZHdata, HFGCdata, HFZHdata,TCZdata,XJSJdata,
//                        &SSRWlen, &SSGClen, &SSZHlen, &HFGClen, &HFZHlen,&TCZlen,&XJSJlen,
//                        remaincode1, remaincode2, &remainlen1, &remainlen2, 0, record_len, frame_len, outputpath,vcNum,vcstate,&synvc,&synflag);

                newcombine(strIn1, iProcLen1, strIn2, iProcLen2,
                             SSdata,HFdata,TCZdata,
                             &SSlen, &HFlen,&TCZlen,
                             remaincode1,remaincode2,&remainlen1,&remainlen2,
                             1024, 1024,outputpath,&synvc,&synflag);


                iShiftLen1 = remainlen1;
                iShiftLen2 = remainlen2;
                iSumLen1 += (iProcLen1 - iShiftLen1);
                iSumLen2 += (iProcLen2 - iShiftLen2);
                MainWindow::fakeUi->setLinetext(QString("该次执行buff中文件1剩余 %1,文件2剩余 %2").arg(iShiftLen1).arg(iShiftLen2));
                MainWindow::fakeUi->setLinetext(QString("该次执行后文件1总执行量为 %1,文件2总执行量为 %2").arg(iSumLen1).arg(iSumLen2));
                MainWindow::fakeUi->setLinetext(QString("该次执行后文件1总执行量剩余 %1,文件2总执行量剩余 %2").arg(filelength1 - iSumLen1).arg(filelength2 - iSumLen2));

                memcpy(strIn1, remaincode1, iShiftLen1);
                memcpy(strIn2, remaincode2, iShiftLen2);


                //从AOS帧分别提取了SS、HF数据，下面提取源包数据

                //5886 VC1实时数据
                if (SSlen > 0)
                {
                    isDealing = true;
                    //SSGCsum += SSGClen;
                    sprintf(outputfile, "%s\\SSSJ.dat", outputpathAOS);
                    if (NULL == (fpOut = fopen(outputfile, "ab")))
                    {
                        perror("File opening failed");
                        MainWindow::fakeUi->setLinetext(QString("SSGC: %1").arg(EXIT_FAILURE));
                        *isRUNNING_DECODER = false;
                        return;
                    }
                    else
                    {
                        fwrite(SSdata, SSlen, 1, fpOut);
                        fclose(fpOut);
                        fpOut = NULL;
                    }
                    BPDUlen = (SSlen / 1024) * 850;
                    //BPDUlen = (SSGClen / record_len) * 848;
                    iProcLen3 = BPDUlen + iShiftLenss; //y iProcLen3为strBPDU的长度

                    AOSdataFlag = 2;
                    serialflag1 = Extract_BPDU(SSdata, SSlen, BPDUdata, 1024, outputpathLog, AOSdataFlag,&ssid);
                    //ssgcid=ssgcid;
                    if(serialflag1 == -1)
                    {
                        *isRUNNING_DECODER = false;
                        return;
                    }
                    nSSsum+=serialflag1;

                    memcpy(strBPDU, strss, iShiftLenss);
                    memcpy(strBPDU + iShiftLenss, BPDUdata, BPDUlen);


                    pclen = vc1pack_classify(strBPDU, iProcLen3, strXWGC, &XWGClen);


                    iShiftLenss = iProcLen3 - pclen;
                    memcpy(strss, strBPDU + pclen, iShiftLenss);

                    if(XWGClen>0){
                        //xwgc 缺省
                        //dealSourcePackage->dealZXGCPackage(strZXGC, ZXGClen,&comSSZXGC,&obtainedSourceStream,SSZXGCout,&rmSSXWGClen,1);
                       dealSourcePackage->dealXWGCPackage(strXWGC,XWGClen,&comSSXWGC,XWGCout,&rmSSXWGClen,1,&SSXWGCid,&rzid);//pack_flag为1时解SSXWGC数据
                    }


                }

                isDealing = false;


                if (HFlen > 0)//回放数据处理
                {
                    isDealing = true;
                    //HFGCsum += HFGClen;
                    sprintf(outputfile, "%s\\HFSJ.dat", outputpathAOS);
                    //CASE_SID::fakeUi->setLinetext(QString("Write HFGC to file %1\n").arg(outputfile));
                    if (NULL == (fpOut = fopen(outputfile, "ab")))
                    {
                        perror("File opening failed");
                        MainWindow::fakeUi->setLinetext(QString("HFGC: %1").arg(EXIT_FAILURE));
                        *isRUNNING_DECODER = false;
                        return;
                    }
                    else
                    {
                        fwrite(HFdata, HFlen, 1, fpOut);
                        fclose(fpOut);
                        fpOut = NULL;
                    }
                    BPDUlen = (HFlen / 1024) * 850;//BPDU位流数据区长度，为回放数据帧的个数乘以每帧有850字节的数据区
                    iProcLen3 = BPDUlen + iShiftLenhf; //y iProcLen3为strBPDU的长度

                    AOSdataFlag = 4;


                    serialflag1 = Extract_BPDU(HFdata, HFlen, BPDUdata, 1024, outputpathLog, AOSdataFlag,&hfid);
                    //hfgcid=hfgcid;
                    if(serialflag1 == -1)
                    {
                        *isRUNNING_DECODER = false;
                        return;
                    }
                    nHFsum+=serialflag1;
//                    serialflag2 += serialflag1;
//                    sprintf(outwords, "数传包<回放工程参数数据>数据计数为: %d , 失序数为: %d \n", HFGClen/1024, serialflag2);
//                    CASE_SID::fakeUi->setLinetext_1(QString("%1").arg(outwords));

                    memcpy(strBPDU, strhf, iShiftLenhf);
                    memcpy(strBPDU + iShiftLenhf, BPDUdata, BPDUlen);

                    pclen = pack_classify(strBPDU, iProcLen3, str0187, &HF0187len, str01A2, &HF01A2len, str02B1, &HF02B1len,
                                          str02C1, &HF02C1len, str0218, &HF0218len, str032E, &HF032Elen, str033D, &HF033Dlen,
                                          str034D, &HF034Dlen, str045E, &HF045Elen);

                    iShiftLenhf = iProcLen3 - pclen;
                    memcpy(strhf, strBPDU + pclen, iShiftLenhf);

                    //这里需要注意的是 文件都是按照可追加的方式写的 需要把不同的GY数据区分开
                    //星上处理数据也需要区分开 可以传递一个Packflag区分不同的源包
                    //不同的残留数据也不能混杂在一起处理 不同包维护不同的空间和残留数据长度
                    if(HF0187len>0)
                    {
                        //XWGC
                        dealSourcePackage->dealXWGCPackage(str0187,HF0187len,&comXWGC,XWGCout,&rmHFXWGClen,2,&HFXWGCid,&rzid);
                    }
                    if(HF01A2len>0){
                        //XSCL
                        dealSourcePackage->dealXSCLPackage(str01A2,HF01A2len,&comXSCL,XSCL01out,&rm01A1len,1,&HF01A2id,&rzid);

                    }
                    if(HF02B1len>0){
                        //XSCL
                        dealSourcePackage->dealXSCLPackage(str02B1,HF02B1len,&comXSCL,XSCL02out,&rm01A1len,2,&HF02B1id,&rzid);
                    }
                    if(HF02C1len>0){
                        //jg100
                        dealSourcePackage->dealJG100Package(str02C1,HF02C1len,&comJG100,JG100out,&rm02C1len,&HF02C1id,&rzid);
                    }
                    if(HF0218len>0){
                        //JG
                        JGXJ_len = dealSourcePackage->dealJGPackage(str0218,HF0218len,&comJG,_JGout,JGout,&rm0218len,&HF0218id,&rzid);
                        sended = false;
                        emit newimageready(JGout,JGXJ_len,JGXJport);
                    }
                    if(HF032Elen>0){
                        //GYA
                        GYA_len = dealSourcePackage->dealGYPackage(str032E,HF032Elen,&comGY,_GYAout,GYAout,GYA21out,GYA41out,&rm032Elen,1,&HF032Eid,&rzid);
                        sended = false;
                        emit newimageready(GYAout,GYA_len,GYAport);

                    }
                    if(HF033Dlen>0){
                        //GYB
                        GYB_len=dealSourcePackage->dealGYPackage(str033D,HF033Dlen,&comGY,_GYBout,GYBout,GYB21out,GYB41out,&rm033Dlen,2,&HF033Did,&rzid);
                        sended = false;
                        emit newimageready(GYBout,GYB_len,GYBport);

                    }
                    if(HF034Dlen>0){
                        //GYC
                        GYC_len=dealSourcePackage->dealGYPackage(str034D,HF034Dlen,&comGY,_GYCout,GYCout,GYC21out,GYC41out,&rm034Dlen,3,&HF034Did,&rzid);
                        sended = false;
                        emit newimageready(GYCout,GYC_len,GYCport);

                    }
                    if(HF045Elen>0){
                        //GYprotected
                        GYpro_len = dealSourcePackage->dealGYPackage(str045E,HF045Elen,&comGY,_GYproout,GYproout,GYpro21out,GYpro41out,&rm045Elen,4,&HF045Eid,&rzid);
                        sended = false;
                        emit newimageready(GYproout,GYpro_len,GYproport);
                    }


                }
                isDealing = false;


                if(TCZlen > 0)
                {
                    isDealing = true;
                    sprintf(outputfile, "%s\\TCZ.dat", outputpathAOS);
                    //CASE_SID::fakeUi->setLinetext(QString("Write TCZ to file %1\n").arg(outputfile));
                    if (NULL == (fpOut = fopen(outputfile, "ab")))
                    {
                        perror("File opening failed");
                        MainWindow::fakeUi->setLinetext(QString("TCZ: %1").arg(EXIT_FAILURE));
                        *isRUNNING_DECODER = false;
                        return;
                    }
                    else
                    {
                        fwrite(TCZdata, TCZlen, 1, fpOut);
                        fclose(fpOut);
                        fpOut = NULL;
                    }

                    unsigned int flag1, flag2 ;//24.0605取消帧连续性判断
                    unsigned int flag4;
                    for (int i = 0; i < TCZlen / 1024; i++)
                    {
                        tczid+=1;
                        //帧连续性判断
                        if (i == 0)
                        {
                            flag1 = (TCZdata[i * 1024 + 6] << 16 | TCZdata[i * 1024 + 7] << 8 | TCZdata[i * 1024 + 8]) & 0xFFFFFF;
                        }
                        else
                        {
                            flag2 = (TCZdata[i * 1024 + 6] << 16 | TCZdata[i * 1024 + 7] << 8 |TCZdata[i * 1024 + 8]) & 0xFFFFFF;

//                            if ((flag1 + 1) != flag2 &&flag2!=0)
//                            {
//                                //flag3++;
//                                //tcz不连续个数
//                                fpOut = NULL;
//                                sprintf(outputfile, "%s/AOS.txt", outputpathLog);
//                                sprintf(outwords, "帧连续性检测： tcz 在 %d 帧与 %d 帧之间不连续,%d 行\n",  flag1, flag2,tczid);
//                                //CASE_SID::fakeUi->setLinetext_1(QString("%1").arg(outwords));
//                                fpOut = fopen(outputfile, "ab");
//                                if (fpOut == NULL)
//                                {
//                                    MainWindow::fakeUi->setLinetext(QString("Extract_BPDU error:can not open %1\n").arg(QString(outputfile)));
//                                }
//                                fwrite(outwords, strlen(outwords), 1, fpOut);
//                                fclose(fpOut);
//                                fpOut = NULL;
//                            }
                            flag1 = flag2;
                        }

                        //帧有效性判断,flag4版本号,flag5航天器标识符
                        flag4 = (TCZdata[i * 1024] << 24 |TCZdata[i * 1024 + 1] << 16 | TCZdata[i * 1024 + 2] << 8 |
                                TCZdata[i * 1024 + 3]) & 0xFFFFFFFF;

                //        flag5 = ((Inputcode[i * irecord + 2] << 8 | Inputcode[i * irecord + 3]) >> 6) & 0x00FF;

                        if(flag4 != 0x1ACFFC1D)
                        {
                            fpOut = NULL;
                            sprintf(outputfile, "%s\\AOS.txt", outputpathLog);
                            sprintf(outwords, "帧有效性检测：AOS帧中tcz在 %d 帧同步头错误,实际内容为   %d  bes%d 行 \n", flag1, flag4,tczid);
                            //CASE_SID::fakeUi->setLinetext(QString("AOS帧中载荷数据在 %d 帧同步头错误,实际内容为   %d   \n").arg(flag1).arg(flag4));
                            //CASE_SID::fakeUi->setLinetext(QString("%1").arg(outwords));

                            fpOut = fopen(outputfile, "ab");
                            if (fpOut == NULL)
                            {
                                MainWindow::fakeUi->setLinetext(QString("Extract_BPDU error:can not open %1\n").arg(QString(outputfile)));
                            }
                            fwrite(outwords, strlen(outwords), 1, fpOut);
                            fclose(fpOut);
                            fpOut = NULL;
                        }


                    }


            }
                isDealing = false;
        }
    }
    }
//    if (serialflag2 == 0)
//    {
//        CASE_SID::fakeUi->setLinetext("该次处理数据AOS帧完全连续\n");
//    }
    //满足THREADNUM个数的会被置为-1，其初值也为-1。而其值大于0又跳出了大while循环表示其是未满足我们多线程内一起输出条件的，故在此一起输出！！
    //写report文件
    sprintf(outwords,"****************解数传帧统计结果****************\n");
    fpOut = fopen(outtest,"ab");
    if(fpOut == NULL)
    {
        MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(outtest)));
    }
    fwrite(outwords,strlen(outwords),1,fpOut);
    if(ssid>0){
        if(nSSsum==0){
            sprintf(outwords,"SSAOS共计 %d,解析正确\n",ssid);
        }
        else{
            sprintf(outwords,"SSAOS 共计 %d,不连续个数%d,详见AOS.txt\n",ssid,nSSsum);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(hfid>0){
        if(nHFsum==0){
            sprintf(outwords,"HFAOS共计 %d,解析正确\n",hfid);
        }
        else{
            sprintf(outwords,"HFAOS 共计 %d,不连续个数%d,详见AOS.txt\n",hfid,nHFsum);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }

    if(tczid>0){
        if(nTCZsum==0){
            sprintf(outwords,"TCZ 共计 %d,解析正确\n",tczid);
        }
        else{
            sprintf(outwords,"TCZ 共计 %d,不连续个数%d,详见AOS.txt\n",tczid,nTCZsum);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    sprintf(outwords,"****************解数传包统计结果****************\n");
    fwrite(outwords,strlen(outwords),1,fpOut);
    if(SSXWGCid > 0)
    {
        if(rzid.errorssxwgc == 0)
        {
            sprintf(outwords,"SSXWGCdata 共计 %d,解析正确\n",SSXWGCid);
        }
        else
        {
           sprintf(outwords,"SSXWGCdata 共计 %d,不连续个数%d,详见SSXWGCdata.txt\n",SSXWGCid,rzid.errorssxwgc);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(HF01A2id > 0)
    {
        if(rzid.errorxscl01 == 0)
        {
            sprintf(outwords,"XSCLdata01 共计 %d,解析正确\n",HF01A2id);
        }
        else
        {
           sprintf(outwords,"XSCLdata01 共计 %d,不连续个数%d,详见XSCLdata01.txt\n",HF01A2id,rzid.errorxscl01);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(HF02B1id > 0)
    {
        if(rzid.errorxscl02 == 0)
        {
            sprintf(outwords,"XSCLdata02 共计 %d,解析正确\n",HF02B1id);
        }
        else
        {
           sprintf(outwords,"XSCLdata02 共计 %d,不连续个数%d,详见XSCLdata02.txt\n",HF02B1id,rzid.errorxscl02);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(HF02C1id > 0)
    {
        if(rzid.errorztdata == 0)
        {
            sprintf(outwords,"ZTdata 共计 %d,解析正确\n",HF02C1id);
        }
        else
        {
           sprintf(outwords,"ZTdata 共计 %d,不连续个数%d,详见ZTdata.txt\n",HF02C1id,rzid.errorztdata);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(HF0218id > 0)
    {
        if(rzid.errorjgxjdata == 0)
        {
            sprintf(outwords,"JGXJdata 共计 %d,解析正确\n",HF0218id);
        }
        else
        {
           sprintf(outwords,"JGXJdata 共计 %d,不连续个数%d,详见JGXJdata.txt\n",HF0218id,rzid.errorjgxjdata);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(HFXWGCid > 0)
    {
        if(rzid.errorhfxwgc == 0)
        {
            sprintf(outwords,"HFXWGCdata 共计 %d,解析正确\n",HFXWGCid);
        }
        else
        {
           sprintf(outwords,"HFXWGCdata 共计 %d,不连续个数%d,详见XWGCdata.txt\n",HFXWGCid,rzid.errorhfxwgc);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(HF032Eid > 0)
    {
        if(rzid.errorgyadata == 0)
        {
            sprintf(outwords,"GYAdata 共计 %d,解析正确\n",HF032Eid);
        }
        else
        {
           sprintf(outwords,"GYAdata 共计 %d,不连续个数%d,详见GYAdata.txt\n",HF032Eid,rzid.errorgyadata);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(HF033Did > 0)
    {
        if(rzid.errorgybdata == 0)
        {
            sprintf(outwords,"GYBdata 共计 %d,解析正确\n",HF033Did);
        }
        else
        {
           sprintf(outwords,"GYBdata 共计 %d,不连续个数%d,详见GYBdata.txt\n",HF033Did,rzid.errorgybdata);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(HF034Did > 0)
    {
        if(rzid.errorgycdata == 0)
        {
            sprintf(outwords,"GYCdata 共计 %d,解析正确\n",HF034Did);
        }
        else
        {
           sprintf(outwords,"GYCdata 共计 %d,不连续个数%d,详见GYCdata.txt\n",HF034Did,rzid.errorgycdata);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(HF045Eid > 0)
    {
        if(rzid.errorgyprodata == 0)
        {
            sprintf(outwords,"GYprodata 共计 %d,解析正确\n",HF045Eid);
        }
        else
        {
           sprintf(outwords,"GYprodata 共计 %d,不连续个数%d,详见GYprodata.txt\n",HF045Eid,rzid.errorgyprodata);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    sprintf(outwords,"****************解载荷源包统计结果****************\n");
    fwrite(outwords,strlen(outwords),1,fpOut);
    if(rzid.GYAid >0)
    {
        if(rzid.errorGYAid == 0)
        {
            sprintf(outwords,"GYA 共计 %d,解析正确\n",rzid.GYAid);
        }
        else
        {
           sprintf(outwords,"GYA 共计 %d,不连续包数%d,详见ImageContinueGYA.txt\n",rzid.GYAid,rzid.errorGYAid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.GYBid >0)
    {
        if(rzid.errorGYBid == 0)
        {
            sprintf(outwords,"GYB 共计 %d,解析正确\n",rzid.GYBid);
        }
        else
        {
           sprintf(outwords,"GYB 共计 %d,不连续包数%d,详见ImageContinueGYB.txt\n",rzid.GYBid,rzid.errorGYBid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.GYCid >0)
    {
        if(rzid.errorGYCid == 0)
        {
            sprintf(outwords,"GYC 共计 %d,解析正确\n",rzid.GYCid);
        }
        else
        {
           sprintf(outwords,"GYC 共计 %d,不连续包数%d,详见ImageContinueGYC.txt\n",rzid.GYCid,rzid.errorGYCid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.GYproid >0)
    {
        if(rzid.errorGYproid == 0)
        {
            sprintf(outwords,"GYpro 共计 %d,解析正确\n",rzid.GYproid);
        }
        else
        {
           sprintf(outwords,"GYpro 共计 %d,不连续包数%d,详见ImageContinueGYpro.txt\n",rzid.GYproid,rzid.errorGYproid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.JGid >0)
    {
        if(rzid.errorJGid == 0)
        {
            sprintf(outwords,"JG 共计 %d,解析正确\n",rzid.JGid);
        }
        else
        {
           sprintf(outwords,"JG 共计 %d,不连续包数%d,详见ImageContinueJG.txt\n",rzid.JGid,rzid.errorJGid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.ZTid >0)
    {
        if(rzid.errorZTid == 0)
        {
            sprintf(outwords,"ZT 共计 %d,解析正确\n",rzid.ZTid);
        }
        else
        {
           sprintf(outwords,"ZT 共计 %d,不连续包数%d,详见ImageContinueZT.txt\n",rzid.ZTid,rzid.errorZTid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.GYIPDid >0)
    {
        if(rzid.errorGYIPDid == 0)
        {
            sprintf(outwords,"GYIPD 共计 %d,解析正确\n",rzid.GYIPDid);
        }
        else
        {
           sprintf(outwords,"GYIPD 共计 %d,不连续包数%d,详见ImageContinueGYIPD.txt\n",rzid.GYIPDid,rzid.errorGYIPDid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.JGIPDid >0)
    {
        if(rzid.errorJGIPDid == 0)
        {
            sprintf(outwords,"JGIPD 共计 %d,解析正确\n",rzid.JGIPDid);
        }
        else
        {
           sprintf(outwords,"JGIPD 共计 %d,不连续包数%d,详见ImageContinueJGIPD.txt\n",rzid.JGIPDid,rzid.errorJGIPDid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.GYTWDW01id >0)
    {
        if(rzid.errorGYTWDW01id == 0)
        {
            sprintf(outwords,"GYTWDW01 共计 %d,解析正确\n",rzid.GYTWDW01id);
        }
        else
        {
           sprintf(outwords,"GYTWDW01 共计 %d,不连续包数%d,详见ImageContinueGYTWDW01.txt\n",rzid.GYTWDW01id,rzid.errorGYTWDW01id);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.GYTWDW02id >0)
    {
        if(rzid.errorGYTWDW02id == 0)
        {
            sprintf(outwords,"GYTWDW02 共计 %d,解析正确\n",rzid.GYTWDW02id);
        }
        else
        {
           sprintf(outwords,"GYTWDW02 共计 %d,不连续包数%d,详见ImageContinueGYTWDW02.txt\n",rzid.GYTWDW02id,rzid.errorGYTWDW02id);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.JGTWDW01id >0)
    {
        if(rzid.errorJGTWDW01id == 0)
        {
            sprintf(outwords,"JGTWDW01 共计 %d,解析正确\n",rzid.JGTWDW01id);
        }
        else
        {
           sprintf(outwords,"JGTWDW01 共计 %d,不连续包数%d,详见ImageContinueJGTWDW01.txt\n",rzid.JGTWDW01id,rzid.errorJGTWDW01id);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.JGTWDW02id >0)
    {
        if(rzid.errorJGTWDW02id == 0)
        {
            sprintf(outwords,"JGTWDW02 共计 %d,解析正确\n",rzid.JGTWDW02id);
        }
        else
        {
           sprintf(outwords,"JGTWDW02 共计 %d,不连续包数%d,详见ImageContinueJGTWDW02.txt\n",rzid.JGTWDW02id,rzid.errorJGTWDW02id);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.GYGTWid >0)
    {
        if(rzid.errorGYGTWid == 0)
        {
            sprintf(outwords,"GYGTW 共计 %d,解析正确\n",rzid.GYGTWid);
        }
        else
        {
           sprintf(outwords,"GYGTW 共计 %d,不连续包数%d,详见ImageContinueGYGTW.txt\n",rzid.GYGTWid,rzid.errorGYGTWid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.GYYDXXid >0)
    {
        if(rzid.errorGYYDXXid == 0)
        {
            sprintf(outwords,"GYYDXX 共计 %d,解析正确\n",rzid.GYYDXXid);
        }
        else
        {
           sprintf(outwords,"GYYDXX 共计 %d,不连续包数%d,详见ImageContinueGYYDXX.txt\n",rzid.GYYDXXid,rzid.errorGYYDXXid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.GYYDXXXX01id >0)
    {
        if(rzid.errorGYYDXXXX01id == 0)
        {
            sprintf(outwords,"GYYDXXXX01 共计 %d,解析正确\n",rzid.GYYDXXXX01id);
        }
        else
        {
           sprintf(outwords,"GYYDXXXX01 共计 %d,不连续包数%d,详见ImageContinueGYYDXXXX01.txt\n",rzid.GYYDXXXX01id,rzid.errorGYYDXXXX01id);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.GYYDXXXX02id >0)
    {
        if(rzid.errorGYYDXXXX02id == 0)
        {
            sprintf(outwords,"GYYDXXXX02 共计 %d,解析正确\n",rzid.GYYDXXXX02id);
        }
        else
        {
           sprintf(outwords,"GYYDXXXX02 共计 %d,不连续包数%d,详见ImageContinueGYYDXXXX02.txt\n",rzid.GYYDXXXX02id,rzid.errorGYYDXXXX02id);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.GYTXCLRZid >0)
    {
        if(rzid.errorGYTXCLRZid == 0)
        {
            sprintf(outwords,"GYTXCLRZ 共计 %d,解析正确\n",rzid.GYTXCLRZid);
        }
        else
        {
           sprintf(outwords,"GYTXCLRZ 共计 %d,不连续包数%d,详见ImageContinueGYTXCLRZ.txt\n",rzid.GYTXCLRZid,rzid.errorGYTXCLRZid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.TWDWRZid >0)
    {
        if(rzid.errorTWDWRZid == 0)
        {
            sprintf(outwords,"TWDWRZ 共计 %d,解析正确\n",rzid.TWDWRZid);
        }
        else
        {
           sprintf(outwords,"TWDWRZ 共计 %d,不连续包数%d,详见ImageContinueTWDWRZ.txt\n",rzid.TWDWRZid,rzid.errorTWDWRZid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.YDGZRZid >0)
    {
        if(rzid.errorYDGZRZid == 0)
        {
            sprintf(outwords,"YDGZRZ 共计 %d,解析正确\n",rzid.YDGZRZid);
        }
        else
        {
           sprintf(outwords,"YDGZRZ 共计 %d,不连续包数%d,详见ImageContinueYDGZRZ.txt\n",rzid.YDGZRZid,rzid.errorYDGZRZid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    if(rzid.JGTXCLRZid >0)
    {
        if(rzid.errorJGTXCLRZid == 0)
        {
            sprintf(outwords,"JGTXCLRZ 共计 %d,解析正确\n",rzid.JGTXCLRZid);
        }
        else
        {
           sprintf(outwords,"JGTXCLRZ 共计 %d,不连续包数%d,详见ImageContinueJGTXCLRZ.txt\n",rzid.JGTXCLRZid,rzid.errorJGTXCLRZid);
        }
        fwrite(outwords,strlen(outwords),1,fpOut);
    }
    sprintf(outwords,"****************解2711sub统计结果****************\n");
    fwrite(outwords,strlen(outwords),1,fpOut);
    fclose(fpOut);
    fpOut=NULL;



    fclose(fpIn1);fpIn1 = NULL;
    fclose(fpIn2);fpIn2 = NULL;
    free(remaincode1);remaincode1 =NULL;
    free(remaincode2);remaincode2 = NULL;
    free(strIn1);strIn1 = NULL;
    free(strIn2);strIn2 = NULL;
    free(strremain1);strremain1 = NULL;
    free(strremain2);strremain2 = NULL;

    free(strBPDU);strBPDU = NULL;

    free(strss);strss = NULL;
    free(strhf);strhf = NULL;



    free(BPDUdata);BPDUdata=NULL;
    free(SSdata);SSdata = NULL;
    free(HFdata);HFdata = NULL;
    free(TCZdata);TCZdata = NULL;


    free(strXWGC);strXWGC= NULL;
    free(str0187);str0187 = NULL;
    free(str01A2);str01A2 = NULL;
    free(str02B1);str02B1 = NULL;
    free(str02C1);str02C1 =NULL;
    free(str0218);str0218 =NULL;
    free(str032E);str032E =NULL;
    free(str033D);str033D =NULL;
    free(str034D);str034D =NULL;
    free(str045E);str045E =NULL;

    free(ZXGCout);ZXGCout =NULL;
    free(RWSJout);RWSJout =NULL;
    free(DKCBout);DKCBout=NULL;
    free(DKZCBout);DKZCBout =NULL;
    free(DDDPDout);DDDPDout =NULL;
    free(DDDBout);DDDBout =NULL;
    free(XJCSout);XJCSout=NULL;
    free(JGCSout);JGCSout =NULL;
    free(JGYYout);JGYYout =NULL;

    free(SSZXGCout);SSZXGCout =NULL;
    free(SSRWSJout);SSRWSJout =NULL;
    free(SSDKCBout);SSDKCBout=NULL;
    free(SSDKZCBout);SSDKZCBout =NULL;
    free(SSDDDPDout);SSDDDPDout =NULL;
    free(SSDDDBout);SSDDDBout =NULL;
    free(SSXJCSout);SSXJCSout=NULL;
    //free(JGCSout);JGCSout =NULL;
    free(SSJGYYout);SSJGYYout =NULL;

    free(DDDPDKC2711out);DDDPDKC2711out=NULL;
    free(DDDB2711out);DDDB2711out=NULL;
    free(DKZCB2711out);DKZCB2711out=NULL;
    free(DKCB2711out);DKCB2711out=NULL;

    free(SSXWGCout);SSXWGCout=NULL;
    free(XWGCout);XWGCout=NULL;
    free(_GYAout);_GYAout=NULL;
    free(_GYBout);_GYBout=NULL;
    free(_GYCout);_GYCout=NULL;
    free(_GYproout);_GYproout=NULL;
    free(_JGout);_JGout=NULL;
    free(_JG100out);_JG100out=NULL;
    free(XSCL01out);XSCL01out=NULL;
    free(XSCL02out);XSCL02out=NULL;

    free(GYAout);GYAout = NULL;
    free(GYA21out); GYA21out = NULL;
    free(GYA41out); GYA41out = NULL;
    free(GYBout);GYBout = NULL;
    free(GYB21out); GYB21out = NULL;
    free(GYB41out); GYB41out = NULL;
    free(GYCout);GYCout = NULL;
    free(GYC21out); GYC21out = NULL;
    free(GYC41out); GYC41out = NULL;
    free(GYproout);GYproout = NULL;
    free(GYpro21out); GYpro21out = NULL;
    free(GYpro41out); GYpro41out = NULL;
    free(JGout);JGout=NULL;
    free(JG100out);JG100out=NULL;

//    free(GYAdata);GYAdata=NULL;
//    free(GYA21data);GYA21data=NULL;
//    free(GYA41data);GYA41data=NULL;
//    free(GYBdata);GYBdata=NULL;
//    free(GYB21data);GYB21data=NULL;
//    free(GYB41data);GYB41data=NULL;
//    free(GYCdata);GYCdata=NULL;
//    free(GYC21data);GYC21data=NULL;
//    free(GYC41data);GYC41data=NULL;
    //dealSourcePackage->freeSourcePackage(&obtainedSourceStream);
    //dealSourcePackage->freeCompressedStream(&comZXGC, &comRWSJ, &comDKCB, &comDKZCB, &comDDDPD, &comDDDB, &comXJCS, &comJGCS, &comJGYY,&comSSZXGC, &comSSRWSJ, &comSSDKCB, &comSSDKZCB, &comSSDDDPD, &comSSDDDB, &comSSXJCS, &comSSJGYY);
    dealSourcePackage->freeStream(&comSSXWGC, &comXWGC, &comGY, &comJG, &comJG100, &comXSCL);

    delete unpack;

    if(!autoexit)
        *isRUNNING_DECODER = false;


    if(!autoexit)
    {
        emit endSig("完成", "本次解压缩任务完成！");

    }


        //emit finished();
    return;

}

