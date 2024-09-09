
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QString>
#include "mainwindow.h"
#include "unpack.h"
#include "myInclude.h"

extern char outputpathLog[fileNameLen];

UnPack::UnPack(QObject *parent) : QObject(parent)
{

}
int UnPack::errornum = 0;
//y输入：参数1 待检测数据类型为unsigned char* buffer，例为RHWdata还是许多4032长，存储源包类型构成
//      参数2 待检测数据长度单位字节 例为iProcLenRHW
//      参数3 相对于RHWdata起始位置的偏移
//输出： 参数4 巴克码的位置，如果没有则是末尾
//	     返回值：这里为PackFlag 1找到0未找到
//寻找包头标志
int UnPack::headDetect(unsigned char* buffer, int bufferlen, int buffertmp, int* iStartPos)
{
    int i;
    unsigned char find = 0;//找到包头的标记

    for (i = buffertmp; i < bufferlen; i++)
    {
        if ((buffer[i] == 0xE2) && (buffer[i + 1] == 0x25))
        {
            find = 1;
            break;
        }
    }
    *iStartPos = i;//没有包头的话，返回本次码流的末尾

    if (find == 1)
        return 1;
    else
        return 0;
}

//寻找帧头巴克码
//输入: 参数1 输入待处理数据
//	    参数2 输入待处理数据长度
//      参数3 开始检测的位置，即相对于起始位置的偏移
//输出：参数4  如果有返回检测到的巴克码的开头，如果没有返回本次码流的末尾
//		返回值：这里为PackFlag 1找到0未找到
int UnPack::barkDetect(unsigned char* buffer, int bufferlen, int buffertmp, int* iStartPos)
{
    int i;
    unsigned char find = 0;//找到帧头的标记
    //qDebug()<<" 找到包头 F5F6EB90"<<endl;
    for (i = buffertmp; i < bufferlen-3; i++)
    {
        if ((buffer[i] == 0xF5) && (buffer[i + 1] == 0xF6) && (buffer[i + 2] == 0xEB) && (buffer[i + 3] == 0x90))//各种图像的帧头F5F6EB90
        {
            find = 1;
            break;
        }
    }
    *iStartPos = i;//没有巴克码的话，返回本次码流的末尾

    if (find == 1)
        return 1;
    else
        return 0;
}

int UnPack::xwgcDetect(unsigned char *buffer, int bufferlen, int buffertmp, int *iStartPos)
{
    int i;
    unsigned char find = 0;//找到帧头的标记
    //qDebug()<<" 找到包头 F5F6EB90"<<endl;
    for (i = buffertmp; i < bufferlen-1; i++)
    {
        //if ((buffer[i] == 0x09) && (buffer[i + 1] == 0xD7) && (buffer[i + 2] == 0xEB) && (buffer[i + 3] == 0x90))//帧头EB90
        if ((buffer[i] == 0xEB) && (buffer[i + 1] == 0x90))
        {
            find = 1;
            break;
        }
    }
    *iStartPos = i;//没有巴克码的话，返回本次码流的末尾

    if (find == 1)
        return 1;
    else
        return 0;
}

int UnPack::gyDetect(unsigned char *buffer, int bufferlen, int buffertmp, int *iStartPos)
{
    int i;
    unsigned char find = 0;//找到帧头的标记
    for (i = buffertmp; i < bufferlen-3; i++)
    {
        if ((buffer[i] == 0xEB) && (buffer[i + 1] == 0x90) && (buffer[i + 2] == 0xEB) && (buffer[i + 3] == 0x90))//帧头EB90
        //if ((buffer[i] == 0xEB) && (buffer[i + 1] == 0x90))
        {
            find = 1;
            break;
        }
    }
    *iStartPos = i;//没有巴克码的话，返回本次码流的末尾

    if (find == 1)
        return 1;
    else
        return 0;
}

int UnPack::jgDetect(unsigned char *buffer, int bufferlen, int buffertmp, int *iStartPos)
{
    int i;
    unsigned char find = 0;//找到帧头的标记
    for (i = buffertmp; i < bufferlen-7; i++)
    {
        if ((buffer[i] == 0x49) && (buffer[i + 1] == 0x54) && (buffer[i + 2] == 0x92) && (buffer[i + 3] == 0x64)
                && (buffer[i + 4] == 0x04)&& (buffer[i + 5] == 0x00)&& (buffer[i + 6] == 0x00)&& (buffer[i + 7] == 0x01))//帧头EB90
        //if ((buffer[i] == 0xEB) && (buffer[i + 1] == 0x90))
        {
            find = 1;
            break;
        }
    }
    *iStartPos = i;//没有巴克码的话，返回本次码流的末尾

    if (find == 1)
        return 1;
    else
        return 0;
}

//本函数检测JG有效图像数据的行标识
int UnPack::jginDetect(unsigned char *buffer, int bufferlen, int buffertmp, int *iStartPos)
{
    int i;
    unsigned char find = 0;//找到帧头的标记
    for (i = buffertmp; i < bufferlen-3; i++)
    {
        if ((buffer[i] == 0x49) && (buffer[i + 1] == 0x94)&& (buffer[i + 2] == 0x00) && (buffer[i + 3] == 0x00)  )
        //if ((buffer[i] == 0xEB) && (buffer[i + 1] == 0x90))
        {
            find = 1;
            break;
        }
    }
    *iStartPos = i;//没有巴克码的话，返回本次码流的末尾

    if (find == 1)
        return 1;
    else
        return 0;
}

int UnPack::jg100Detect(unsigned char *buffer, int bufferlen, int buffertmp, int *iStartPos)
{
    int i;
    unsigned char find = 0;//找到帧头的标记
    for (i = buffertmp; i < bufferlen-1; i++)
    {

        if ((buffer[i] == 0x55) && (buffer[i + 1] == 0xAA))
        {
            find = 1;
            break;
        }
    }
    *iStartPos = i;//没有巴克码的话，返回本次码流的末尾

    if (find == 1)
        return 1;
    else
        return 0;
}

int UnPack::endDetect(unsigned char *buffer, int bufferlen, int buffertmp, int *iStartPos)
{
    int i;
    unsigned char find = 0;//找到帧头的标记
    //qDebug()<<" 找到包头 F5F6EB90"<<endl;
    for (i = buffertmp; i < bufferlen-3; i++)
    {
        if ((buffer[i] == 0xE0) && (buffer[i + 1] == 0xE0) && (buffer[i + 2] == 0xE0) && (buffer[i + 3] == 0xE0))//帧尾
        //if ((buffer[i] == 0xEB) && (buffer[i + 1] == 0x90))
        {
            find = 1;
            break;
        }
    }
    *iStartPos = i+4;//没有巴克码的话，返回本次码流的末尾

    if (find == 1)
        return 1;
    else
        return 0;
}

//寻找帧头巴克码
//输入: 参数1 输入待处理数据
//	    参数2 输入待处理数据的长度,因为BUFFSIZE的大小是256M故参数2最大也是这个，不超过int的表示范围2G
//      参数3 开始检测的位置
//输出：参数4  如果有返回检测到的巴克码的开头，如果没有返回本次码流的末尾
//		参数5 输出数据类型
//      返回值：这里为PackFlag 1找到0未找到
int UnPack::barkDetectMode2(unsigned char* buffer, int bufferlen, int buffertmp, int* iStartPos, int *_dataType)
{
    int i;
    unsigned char find = 0;//找到帧头的标记

    for (i = buffertmp; i < bufferlen - 6; i++)
    {
        if ((buffer[i] == 0xF5) && (buffer[i + 1] == 0xF6) && (buffer[i + 2] == 0xEB) && (buffer[i + 3] == 0x90))
        {
            find = 1;
            *_dataType = buffer[i + 6];
            break;
        }
    }
    *iStartPos = i;

    if (find == 1)
        return 1;
    else
        return 0;
}

//寻找合适的一帧结尾
//输入: 参数1 输入待处理数据
//	    参数2 输入待处理数据的长度,因为BUFFSIZE的大小是256M故参数2最大也是这个，不超过int的表示范围2G
//输出：参数4
//      返回值：不含OxEF的数据长度
int UnPack::checkFinal(unsigned char* buffer, int bufferlen)
{
    long long supposeLen;//帧头记录的整帧码流长度

    if (bufferlen <= 0)
    {
        return 0;
    }
    supposeLen = (buffer[8] << 24 | buffer[9] << 16 | buffer[10] << 8 | buffer[11]) & 0xFFFFFFFF;
    if (supposeLen > bufferlen)
    {
        //CASE_SID::fakeUi->setLinetext(QString("checkFinal error: supposeLen>bufferlen frame %1\n").arg(unpackFrameNum));
        return bufferlen;
    }
    return supposeLen;
}

//y 输入：参数1 data对应一帧图像数据压缩码流
//		  参数2 dataLen为一帧图像数据压缩码流的长度
//		  参数3 mode为 "RHW" "WGMZ" "WGYJ" "DGP"
//		  参数4 日志文件的输出路径
//		  参数5 一帧压缩码流的输出路径
//16比特累加和校验
int UnPack::checkFrame(unsigned char *data, int dataLen, char* mode, char* pathLog, char* pathMiddle, struct testCompressedStream* p)
{
    __int64 sum = 0;				  //16比特累加
    unsigned int sum16bit, checkSums, inFrameNum = 0;

    FILE		 *fpwrite;
    char		 outputfileName[fileNameLen];  //日志文件的输出路径
    char		 outwords[100];		  //存到文档中的内容

    (p->frameNum)++;
    unpackNum++;

    sprintf(outputfileName, "%s/unpackFrame.txt", pathLog);

    for (int i = 0; i < dataLen - 2; i += 2)
    {
        sum = sum + (data[i] << 8);//先加高字节
        sum = sum + data[i + 1];
    }
    sum16bit = sum & 0xffff;
    checkSums = (data[dataLen - 2] << 8) | data[dataLen - 1];

    if (sum16bit == checkSums)
    {
        (p->correctNum)++;
        sprintf(outwords, "序号：%2d %2s    帧校验和正确    帧序号%d\n", unpackFrameNum, mode, inFrameNum);
        //CASE_SID::fakeUi->setLinetext(QString("%1").arg(outwords));

        fpwrite = fopen(outputfileName, "ab");
        fwrite(outwords, strlen(outwords), 1, fpwrite);
        fclose(fpwrite);
        fpwrite = NULL;
    }
    else//帧和校验出错
    {
        (p->errorNum)++;
        errorUnpackNum++;

        sprintf(outwords, "序号：%2d %2s    帧校验和错误    帧序号%d   错误序号为：%d\n", unpackFrameNum, mode, inFrameNum, unpackFrameNum);
        //CASE_SID::fakeUi->setLinetext(QString("%1").arg(outwords));

        fpwrite = fopen(outputfileName, "ab");
        fwrite(outwords, strlen(outwords), 1, fpwrite);
        fclose(fpwrite);
        fpwrite = NULL;
    }

    unpackFrameNum++;
    return dataLen;
}

int UnPack::unpack1(unsigned char *pInputCode, int InputLen, unsigned char *pout, int *Outputlen, char *pathLog,bool state, unsigned int *numid)
{
    int				i;
//    unsigned int	group, data_len;
    int				temp = 0;
    int				frm_cnt = 0;
    int				frm_pos;

    int				flag1, flag2, flag;            //用于检测存储源包连续性,flag是确定哪种数据
    char	        outputfileName[fileNameLen];   //合并后的文件输出路径
    char            outwords[100];		           //存到日志文档中的话
    FILE			*fpOut;
    //int				flagSize = 0;
    unsigned int	group;
    unsigned int	data_len=4016;
    char packname[20];

    flag = (pInputCode[2] << 8 | pInputCode[3]) & 0xFFFF;
    if(state){
        switch (flag)
        {
        //
        case ZXGC:
    //        sprintf(outwords, "ZXGC");
            sprintf(packname, "ssZXGC");
            //flagSize = strlen("ZXGC");
            sprintf(outputfileName, "%s/ssXWGCBPDU.txt", pathLog);
            break;
        case RWSJ:
            sprintf(packname, "RWSJ");
            //flagSize = strlen("RWSJ");
            sprintf(outputfileName, "%s/ssRWSJBPDU.txt", pathLog);
            break;
        case DKCB:
            sprintf(packname, "ssDKCB");
            //flagSize = strlen("DKCB");
            sprintf(outputfileName, "%s/ssDKCBBPDU.txt", pathLog);
            break;
        case DKZCB:
            sprintf(packname, "ssDKZCB");
            //flagSize = strlen("DKZCB");
            sprintf(outputfileName, "%s/ssDKZCBBPDU.txt", pathLog);
            break;
        case DDDPD:
            sprintf(packname, "ssDDDPD");
            //flagSize = strlen("DDDPD");
            sprintf(outputfileName, "%s/ssDDDPDBPDU.txt", pathLog);
            break;
        case DDDB:
            sprintf(packname, "ssDDDB");
            //flagSize = strlen("DDDB");
            sprintf(outputfileName, "%s/ssDDDBBPDU.txt", pathLog);
            break;
        case XJCS:
            sprintf(packname, "ssXJCS");
            //flagSize = strlen("XJCS");
            sprintf(outputfileName, "%s/ssXJCSBPDU.txt", pathLog);
            break;
        case JGCS:
            sprintf(packname, "JGCS");
            //flagSize = strlen("JGCS");
            sprintf(outputfileName, "%s/JGCSBPDU.txt", pathLog);
            break;
        case JGYY:
            sprintf(packname, "ssJGYY");
            //flagSize = strlen("JGYY");
            sprintf(outputfileName, "%s/ssJGYYBPDU.txt", pathLog);
            break;
        default:
            sprintf(packname, "error");
            //flagSize = strlen("error");

            //CASE_SID::fakeUi->setLinetext(QString("存储源包 void pack \n"));
            break;
        }
    }
    else{
        switch (flag)
        {
        case ZXGC:
    //        sprintf(outwords, "ZXGC");
            sprintf(packname, "ZXGC");
            //flagSize = strlen("ZXGC");
            sprintf(outputfileName, "%s/XWGCBPDU.txt", pathLog);
            break;
        case RWSJ:
            sprintf(packname, "RWSJ");
            //flagSize = strlen("RWSJ");
            sprintf(outputfileName, "%s/RWSJBPDU.txt", pathLog);
            break;
        case DKCB:
            sprintf(packname, "DKCB");
            //flagSize = strlen("DKCB");
            sprintf(outputfileName, "%s/DKCBBPDU.txt", pathLog);
            break;
        case DKZCB:
            sprintf(packname, "DKZCB");
            //flagSize = strlen("DKZCB");
            sprintf(outputfileName, "%s/DKZCBBPDU.txt", pathLog);
            break;
        case DDDPD:
            sprintf(packname, "DDDPD");
            //flagSize = strlen("DDDPD");
            sprintf(outputfileName, "%s/DDDPDBPDU.txt", pathLog);
            break;
        case DDDB:
            sprintf(packname, "DDDB");
            //flagSize = strlen("DDDB");
            sprintf(outputfileName, "%s/DDDBBPDU.txt", pathLog);
            break;
        case XJCS:
            sprintf(packname, "XJCS");
            //flagSize = strlen("XJCS");
            sprintf(outputfileName, "%s/XJCSBPDU.txt", pathLog);
            break;
        case JGCS:
            sprintf(packname, "JGCS");
            //flagSize = strlen("JGCS");
            sprintf(outputfileName, "%s/JGCSBPDU.txt", pathLog);
            break;
//        case JGYY:
//            sprintf(packname, "JGYY");
//            //flagSize = strlen("JGYY");
//            sprintf(outputfileName, "%sJGYYBPDU.txt", pathLog);
//            break;
        default:
            sprintf(packname, "error");
            //flagSize = strlen("error");

            //CASE_SID::fakeUi->setLinetext(QString("存储源包 void pack \n"));
            break;
        }
    }


    *Outputlen = 0;
    //sprintf(outputfileName, "%s/BPDU.txt", pathLog);
    for (i = 0; i < InputLen / 4032; i++)
    {

        //存储源包连续性判断
        //外面这个判断是不是不需要
        if (i != InputLen / 4032)
        {
            if (i==0)
            {
                //flag1包序控制=分组标志（2位）+包序列计数（14位）
                flag1 = (pInputCode[i * 4032 + 4] << 8 | pInputCode[i * 4032 + 5]) & 0x3FFF;
            }
            else{
                flag2 = (pInputCode[i * 4032 + 4] << 8 | pInputCode[i * 4032 + 5]) & 0x3FFF;
                if ((flag1 + 1) != flag2)
                {
                    if(flag1 != 16383 || flag2 !=0) //摩根定律，同时这里存储源包只有14位计数2^14=16384
                    {
                        //sprintf(outwords + flagSize, "存储源包数据在 %d 帧与 %d 帧之间不连续\n", flag1, flag2); //outwords + flagSize这是啥啊？
                        sprintf(outwords, "存储源包<%s>数据在 %d 帧与 %d 帧之间不连续 %d 行\n",packname,flag1, flag2,*numid);
                        //CASE_SID::fakeUi->setLinetext(QString("%1").arg(outwords));

                        fpOut = fopen(outputfileName, "ab");
                        if (fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("error:can not open %1\n").arg(outputfileName));
                            return -1;
                        }
                        fwrite(outwords, strlen(outwords), 1, fpOut);
                        fclose(fpOut);
                        fpOut = NULL;
                    }
                }
                flag1 = flag2;

            }
            *numid=*numid+1;
        }

        group = pInputCode[i * 4032 + 4] >> 6 & 0x03; //获得其分组标志

        //group对应的是存储源包格式的分组标识，要知道一组图像数据压缩码流是由好几个数据源包组成
        //如果group为2，即是最后一个源包，则其可能数据不满会补充(这里为0xEF待确认)。
        if (group == 2)//最后一包
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;//包数据长度 =4024-8
            memcpy(pout + temp, pInputCode + i * 4032 + 16, data_len);//提取E-PDU数据域数据
            temp += data_len;

            *Outputlen = temp;
            return (i + 1) * 4032;
        }
        else if(group==3)
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
            memcpy(pout + temp, pInputCode + i * 4032 + 16, data_len);
            temp += data_len;
            *Outputlen = temp;

        }
        else if (barkDetect(pInputCode, (i + 1) * 4032, i * 4032, &frm_pos))//帧头 F5F6EB90
        {
            frm_cnt++;

            if (frm_cnt == 1)
            {
                //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
                memcpy(pout + temp, pInputCode + i * 4032 + 16, data_len);
                temp += data_len;

            }
            else if (frm_cnt == 2)
            {
                return i * 4032;
            }
        }

        else//中间包
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
            memcpy(pout + temp, pInputCode + i * 4032 + 16, data_len);
            temp += data_len;

        }
    }

    //如果从这里退出函数,代表这包数据找不到10即结尾包,长度*Outputlen相当于未赋值为0
    MainWindow::fakeUi->setLinetext(QString("退出函数: error\n"));
    //CASE_SID::fakeUi->setLinetext_detect(QString("unpackFrameNum is %1\n").arg(unpackFrameNum));
    return i * 4032;
    //return 0;
}


//y 输入：参数1 pInputCode存储源包类型,例为RHWdata还是许多4032长
//		  参数2 InputLen 小while即本小轮需要处理的长度 即本大轮RHW存储源包数据需要处理的长度减去上一小轮已经处理长度
//		  参数5 pathLog 输出日志文件路径
//输出：  参数3 pout一帧RHW图像数据压缩码流 根据存储源包格式的分组标识，来判断一帧RHW图像数据压缩码流是否提取完 EPDU数据区
//		  参数4 Outputlen实参imgRHW 显然为一帧RHW图像数据压缩码流的长度
//		  返回值 对应我们已经处理的存储源包长度
//实现根据存储源包的分组标志，从存储源包提取出一帧图像压缩数据。对不同数据的存储源包进行分类。实现存储源包连续性检查
//疑惑：  要知道一帧RHW图像数据压缩码流是由好几个数据源包组成，会不会出现RHWdata(或者说RHWlen)比较小,
//它对第一帧RHW图像数据压缩码流提取不完，即只能包括前几个数据源包
//XWGC不需要判断连续性
//int UnPack::unpack(unsigned char* pInputCode, int InputLen, unsigned char* pout, int* Outputlen, char *pathLog,unsigned int *numid)
int UnPack::unpack(unsigned char* pInputCode, int InputLen, unsigned char* pout, int* Outputlen, char *pathLog,bool state)
{
    int				i;
//    unsigned int	group, data_len;
    int				temp = 0;
    int				frm_cnt = 0;
    int				frm_pos;

    int				flag1, flag2, flag;            //用于检测存储源包连续性,flag是确定哪种数据
    char	        outputfileName[fileNameLen];   //合并后的文件输出路径
    char            outwords[100];		           //存到日志文档中的话
    FILE			*fpOut;
    //int				flagSize = 0;
    unsigned int	group;
    unsigned int	data_len=4016;
    char packname[20];

    flag = (pInputCode[2] << 8 | pInputCode[3]) & 0xFFFF;
    if(state){
        switch (flag)
        {
        case ZXGC:
    //        sprintf(outwords, "ZXGC");
            sprintf(packname, "ssZXGC");
            //flagSize = strlen("ZXGC");
            sprintf(outputfileName, "%s/ssXWGCBPDU.txt", pathLog);
            break;
        case RWSJ:
            sprintf(packname, "RWSJ");
            //flagSize = strlen("RWSJ");
            sprintf(outputfileName, "%s/ssRWSJBPDU.txt", pathLog);
            break;
        case DKCB:
            sprintf(packname, "ssDKCB");
            //flagSize = strlen("DKCB");
            sprintf(outputfileName, "%s/ssDKCBBPDU.txt", pathLog);
            break;
        case DKZCB:
            sprintf(packname, "ssDKZCB");
            //flagSize = strlen("DKZCB");
            sprintf(outputfileName, "%s/ssDKZCBBPDU.txt", pathLog);
            break;
        case DDDPD:
            sprintf(packname, "ssDDDPD");
            //flagSize = strlen("DDDPD");
            sprintf(outputfileName, "%s/ssDDDPDBPDU.txt", pathLog);
            break;
        case DDDB:
            sprintf(packname, "ssDDDB");
            //flagSize = strlen("DDDB");
            sprintf(outputfileName, "%s/ssDDDBBPDU.txt", pathLog);
            break;
        case XJCS:
            sprintf(packname, "ssXJCS");
            //flagSize = strlen("XJCS");
            sprintf(outputfileName, "%s/ssXJCSBPDU.txt", pathLog);
            break;
        case JGCS:
            sprintf(packname, "JGCS");
            //flagSize = strlen("JGCS");
            sprintf(outputfileName, "%s/JGCSBPDU.txt", pathLog);
            break;
        case JGYY:
            sprintf(packname, "ssJGYY");
            //flagSize = strlen("JGYY");
            sprintf(outputfileName, "%s/ssJGYYBPDU.txt", pathLog);
            break;
        default:
            sprintf(packname, "error");
            //flagSize = strlen("error");

            //CASE_SID::fakeUi->setLinetext(QString("存储源包 void pack \n"));
            break;
        }
    }
    else{
        switch (flag)
        {
        case ZXGC:
    //        sprintf(outwords, "ZXGC");
            sprintf(packname, "ZXGC");
            //flagSize = strlen("ZXGC");
            sprintf(outputfileName, "%s/XWGCBPDU.txt", pathLog);
            break;
        case RWSJ:
            sprintf(packname, "RWSJ");
            //flagSize = strlen("RWSJ");
            sprintf(outputfileName, "%s/RWSJBPDU.txt", pathLog);
            break;
        case DKCB:
            sprintf(packname, "DKCB");
            //flagSize = strlen("DKCB");
            sprintf(outputfileName, "%s/DKCBBPDU.txt", pathLog);
            break;
        case DKZCB:
            sprintf(packname, "DKZCB");
            //flagSize = strlen("DKZCB");
            sprintf(outputfileName, "%s/DKZCBBPDU.txt", pathLog);
            break;
        case DDDPD:
            sprintf(packname, "DDDPD");
            //flagSize = strlen("DDDPD");
            sprintf(outputfileName, "%s/DDDPDBPDU.txt", pathLog);
            break;
        case DDDB:
            sprintf(packname, "DDDB");
            //flagSize = strlen("DDDB");
            sprintf(outputfileName, "%s/DDDBBPDU.txt", pathLog);
            break;
        case XJCS:
            sprintf(packname, "XJCS");
            //flagSize = strlen("XJCS");
            sprintf(outputfileName, "%s/XJCSBPDU.txt", pathLog);
            break;
        case JGCS:
            sprintf(packname, "JGCS");
            //flagSize = strlen("JGCS");
            sprintf(outputfileName, "%s/JGCSBPDU.txt", pathLog);
            break;
//        case JGYY:
//            sprintf(packname, "JGYY");
//            //flagSize = strlen("JGYY");
//            sprintf(outputfileName, "%sJGYYBPDU.txt", pathLog);
//            break;
        default:
            sprintf(packname, "error");
            //flagSize = strlen("error");

            //CASE_SID::fakeUi->setLinetext(QString("存储源包 void pack \n"));
            break;
        }
    }


    *Outputlen = 0;
    //sprintf(outputfileName, "%s/BPDU.txt", pathLog);
    for (i = 0; i < InputLen / 4032; i++)
    {
        //存储源包连续性判断
        //外面这个判断是不是不需要
        if (i != InputLen / 4032)
        {
            if (i==0)
            {
                //flag1包序控制=分组标志（2位）+包序列计数（14位）
                flag1 = (pInputCode[i * 4032 + 4] << 8 | pInputCode[i * 4032 + 5]) & 0x3FFF;
            }
            else {
                flag2 = (pInputCode[i * 4032 + 4] << 8 | pInputCode[i * 4032 + 5]) & 0x3FFF;
                if ((flag1 + 1) != flag2)
                {
                    if(flag1 != 16383 || flag2 !=0) //摩根定律，同时这里存储源包只有14位计数2^14=16384
                    {
                        //sprintf(outwords + flagSize, "存储源包数据在 %d 帧与 %d 帧之间不连续\n", flag1, flag2); //outwords + flagSize这是啥啊？
                        sprintf(outwords, "存储源包<%s>数据在 %d 帧与 %d 帧之间不连续 %d 行\n",packname,flag1, flag2);
                        //CASE_SID::fakeUi->setLinetext(QString("%1").arg(outwords));

                        fpOut = fopen(outputfileName, "ab");
                        if (fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("error:can not open %1\n").arg(outputfileName));
                            return -1;
                        }
                        fwrite(outwords, strlen(outwords), 1, fpOut);
                        fclose(fpOut);
                        fpOut = NULL;
                    }
                }
                flag1 = flag2;
            }

        }

        group = pInputCode[i * 4032 + 4] >> 6 & 0x03; //获得其分组标志

        //group对应的是存储源包格式的分组标识，要知道一组图像数据压缩码流是由好几个数据源包组成
        //如果group为2，即是最后一个源包，则其可能数据不满会补充(这里为0xEF待确认)。
        if (group == 2)//最后一包
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;//包数据长度 =4024-8
            memcpy(pout + temp, pInputCode + i * 4032 + 16, data_len);//提取E-PDU数据域数据
            temp += data_len;

            *Outputlen = temp;
            return (i + 1) * 4032;
        }
        else if(group==3)
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
            memcpy(pout + temp, pInputCode + i * 4032 + 16, data_len);
            temp += data_len;
            *Outputlen = temp;

        }
        else if (barkDetect(pInputCode, (i + 1) * 4032, i * 4032, &frm_pos))//帧头 F5F6EB90
        {
            frm_cnt++;

            if (frm_cnt == 1)
            {
                //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
                memcpy(pout + temp, pInputCode + i * 4032 + 16, data_len);
                temp += data_len;

            }
            else if (frm_cnt == 2)
            {
                return i * 4032;
            }
        }

        else//中间包
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
            memcpy(pout + temp, pInputCode + i * 4032 + 16, data_len);
            temp += data_len;

        }
    }

    //如果从这里退出函数,代表这包数据找不到10即结尾包,长度*Outputlen相当于未赋值为0
    MainWindow::fakeUi->setLinetext(QString("退出函数: error\n"));
    //CASE_SID::fakeUi->setLinetext_detect(QString("unpackFrameNum is %1\n").arg(unpackFrameNum));
    return i * 4032;
    //return 0;
}

//因星务工参不需判断连续性，所以重写提取EPDU函数
int UnPack::unpackxwgc(unsigned char *pInputCode, int InputLen, unsigned char *pout, int *Outputlen, char *pathLog)
{
    int				i;
//    unsigned int	group, data_len;
    int				temp = 0;
    int				frm_cnt = 0;
    int				frm_pos;
    unsigned int	group;
    unsigned int	data_len=4016;

    *Outputlen = 0;
    //sprintf(outputfileName, "%s/BPDU.txt", pathLog);
    for (i = 0; i < InputLen / 4032; i++)
    {
        group = pInputCode[i * 4032 + 4] >> 6 & 0x03; //获得其分组标志

        //group对应的是存储源包格式的分组标识，要知道一组图像数据压缩码流是由好几个数据源包组成
        //如果group为2，即是最后一个源包，则其可能数据不满会补充(这里为0xEF待确认)。
        if (group == 2)//最后一包
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;//包数据长度 =4024-8
            memcpy(pout + temp, pInputCode + i * 4032 + 16, data_len);//提取E-PDU数据域数据
            temp += data_len;

            *Outputlen = temp;
            return (i + 1) * 4032;
        }
        else if(group==3)
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
            memcpy(pout + temp, pInputCode + i * 4032 + 16, data_len);
            temp += data_len;
            *Outputlen = temp;

        }
        else if (barkDetect(pInputCode, (i + 1) * 4032, i * 4032, &frm_pos))//帧头 F5F6EB90
        {
            frm_cnt++;

            if (frm_cnt == 1)
            {
                //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
                memcpy(pout + temp, pInputCode + i * 4032 + 16, data_len);
                temp += data_len;

            }
            else if (frm_cnt == 2)
            {
                return i * 4032;
            }
        }

        else//中间包
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
            memcpy(pout + temp, pInputCode + i * 4032 + 16, data_len);
            temp += data_len;

        }
    }

    //如果从这里退出函数,代表这包数据找不到10即结尾包,长度*Outputlen相当于未赋值为0
    MainWindow::fakeUi->setLinetext(QString("退出函数: error\n"));
    //CASE_SID::fakeUi->setLinetext_detect(QString("unpackFrameNum is %1\n").arg(unpackFrameNum));
    return i * 4032;
    //return 0;
}

int UnPack::newunpack(unsigned char *pInputCode, int InputLen, unsigned char *pout, int *Outputlen, char *pathLog, unsigned int *numid)
{
    errornum = 0;
    unsigned int				i;
//    unsigned int	group, data_len;
    int				temp = 0;
    int				frm_cnt = 0;
    int				frm_pos;

    int				flag1, flag2, flag,flag3;            //用于检测存储源包连续性,flag是确定哪种数据
    char	        outputfileName[fileNameLen];   //合并后的文件输出路径
    char            outwords[100];		           //存到日志文档中的话
    FILE			*fpOut;
    //int				flagSize = 0;
    unsigned int	group;
    //有效数据长度
    unsigned int	data_len=3548;

    unsigned int pack_len = 3568;
    char packname[20];

    flag = (pInputCode[2] << 8 | pInputCode[3]) & 0xFFFF;

    switch (flag)
    {
    case HF0187:
        sprintf(packname, "XWGC");
        //flagSize = strlen("ZXGC");
        sprintf(outputfileName, "%s/XWGCdata.txt", pathLog);
        break;
    case HF01A2:
        sprintf(packname, "XSCL");

        sprintf(outputfileName, "%s/XSCLdata01.txt", pathLog);
        break;
    case HF02B1:
//        sprintf(packname, "02B1");
        sprintf(packname, "XSCL");
        //flagSize = strlen("DKCB");
        sprintf(outputfileName, "%s/XSCLdata02.txt", pathLog);
        break;
    case HF02C1:
        sprintf(packname, "ZT");
        //flagSize = strlen("DKZCB");
        sprintf(outputfileName, "%s/ZTdata.txt", pathLog);
        break;
    case HF0218:
        sprintf(packname, "JG");
        //flagSize = strlen("DDDPD");
        sprintf(outputfileName, "%s/JGXJdata.txt", pathLog);
        break;
    case HF032E:
        sprintf(packname, "GYA");
        //flagSize = strlen("DDDB");
        sprintf(outputfileName, "%s/GYAdata.txt", pathLog);
        break;
    case HF033D:
        sprintf(packname, "GYB");
        //flagSize = strlen("XJCS");
        sprintf(outputfileName, "%s/GYBdata.txt", pathLog);
        break;
    case HF034D:
        sprintf(packname, "GYC");
        //flagSize = strlen("JGCS");
        sprintf(outputfileName, "%s/GYCdata.txt", pathLog);
        break;
    case HF045E:
        sprintf(packname, "GYpro");
        //flagSize = strlen("JGYY");
        sprintf(outputfileName, "%s/GYprodata.txt", pathLog);
        break;
    default:
        sprintf(packname, "error");
        break;
    }



    *Outputlen = 0;
    //sprintf(outputfileName, "%s/BPDU.txt", pathLog);
    for (i = 0; i < InputLen / pack_len; i++)
    {

        //存储源包连续性判断
        //外面这个判断是不是不需要
        if (i != InputLen / pack_len)
        {
            if (i==0)
            {
                //flag1包序控制=分组标志（2位）+包序列计数（14位）
                flag1 = (pInputCode[i * pack_len + 4] << 8 | pInputCode[i * pack_len + 5]) & 0x3FFF;
            }
            else{
                flag2 = (pInputCode[i * pack_len + 4] << 8 | pInputCode[i * pack_len + 5]) & 0x3FFF;
                if ((flag1 + 1) != flag2)
                {
                    if(flag1 != 16383 || flag2 !=0) //摩根定律，同时这里存储源包只有14位计数2^14=16384
                    {
                        //sprintf(outwords + flagSize, "存储源包数据在 %d 帧与 %d 帧之间不连续\n", flag1, flag2); //outwords + flagSize这是啥啊？
                        sprintf(outwords, "存储源包<%s>数据在 %d 帧与 %d 帧之间不连续 %d 行\n",packname,flag1, flag2,*numid);
                        //CASE_SID::fakeUi->setLinetext(QString("%1").arg(outwords));

                        fpOut = fopen(outputfileName, "ab");
                        if (fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("error:can not open %1\n").arg(outputfileName));
                            return -1;
                        }
                        fwrite(outwords, strlen(outwords), 1, fpOut);
                        fclose(fpOut);
                        fpOut = NULL;
                        errornum = errornum +1;
                    }
                }
                flag3 = flag1;
                flag1 = flag2;


            }
            //判断校验和24.0605修改（单字节累加，结果为双字节）
           int check = 0;
           int check1=0;
           for(int j = 0; j < pack_len - 2 ; j++)
           {

              check =(check+pInputCode[pack_len*i+j]);
               //11.2删
               //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
           }
           //check=check+datalen;
           check=check&0xffff;
           check1=((pInputCode[pack_len*i + 3566] << 8) | pInputCode[pack_len*i + 3567])&0xffff;

           if(check != check1)
           {
   //            qDebug()<<"adderror"<<endl;//加和报错
               sprintf(outwords,"存储源包<%s>数据在第%d帧检验和错误bes %d\n",packname,flag1,*numid);
               sprintf(outputfileName,"%s/adderror%s.txt",outputpathLog,packname);
               fpOut = fopen(outputfileName,"ab");
               if(fpOut == NULL)
               {
                   MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(outputfileName)));
               }
               fwrite(outwords,strlen(outwords),1,fpOut);
               fclose(fpOut);
               fpOut=NULL;

           }

            *numid=*numid+1;
        }

        group = pInputCode[i * pack_len + 4] >> 6 & 0x03; //获得其分组标志

        //group对应的是存储源包格式的分组标识，要知道一组图像数据压缩码流是由好几个数据源包组成
        //如果group为2，即是最后一个源包，则其可能数据不满会补充(这里为0xEF待确认)。
        if (group == 2)//最后一包
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;//包数据长度 =4024-8
            memcpy(pout + temp, pInputCode + i * pack_len + 16, data_len);//提取E-PDU数据域数据
            temp += data_len;

            *Outputlen = temp;
            return (i + 1) * pack_len;
        }
        else if(group==3)
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
            memcpy(pout + temp, pInputCode + i * pack_len + 16, data_len);
            temp += data_len;
            *Outputlen = temp;

        }
        else if (barkDetect(pInputCode, (i + 1) * pack_len, i * pack_len, &frm_pos))//帧头 F5F6EB90
        {
            frm_cnt++;

            if (frm_cnt == 1)
            {
                //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
                memcpy(pout + temp, pInputCode + i * pack_len + 16, data_len);
                temp += data_len;

            }
            else if (frm_cnt == 2)
            {
                return i * pack_len;
            }
        }

        else//中间包
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
            memcpy(pout + temp, pInputCode + i * pack_len + 16, data_len);
            temp += data_len;

        }
    }

    //如果从这里退出函数,代表这包数据找不到10即结尾包,长度*Outputlen相当于未赋值为0
    MainWindow::fakeUi->setLinetext(QString("退出函数: error\n"));
    //CASE_SID::fakeUi->setLinetext_detect(QString("unpackFrameNum is %1\n").arg(unpackFrameNum));
    return i * pack_len;
}
//因vc1和vc2都包含星无工参，且内置标识符相同，需要重xwgc函数
int UnPack::newunpackxwgc(unsigned char* pInputCode, int InputLen, unsigned char* pout, int* Outputlen, char *pathLog,unsigned int *numid)
{
    errornum = 0;
    unsigned int				i;
//    unsigned int	group, data_len;
    int				temp = 0;
    int				frm_cnt = 0;
    int				frm_pos;

    int				flag1, flag2, flag,flag3;            //用于检测存储源包连续性,flag是确定哪种数据
    char	        outputfileName[fileNameLen];   //合并后的文件输出路径
    char            outwords[100];		           //存到日志文档中的话
    FILE			*fpOut;
    //int				flagSize = 0;
    unsigned int	group;
    //有效数据长度
    unsigned int	data_len=3548;

    unsigned int pack_len = 3568;
    char packname[20];
    int test = 0;
    flag = (pInputCode[2] << 8 | pInputCode[3]) & 0xFFFF;

    switch (flag)
    {
    case HF0187:
        sprintf(packname, "SSXWGC");
        sprintf(outputfileName, "%s/SSXWGCdata.txt", pathLog);
        break;
    default:
        sprintf(packname, "error");
        break;
    }



    *Outputlen = 0;
    //sprintf(outputfileName, "%s/BPDU.txt", pathLog);
    for (i = 0; i < InputLen / pack_len; i++)
    {

        //存储源包连续性判断
        //外面这个判断是不是不需要
        if (i != InputLen / pack_len)
        {
            if (i==0)
            {
                //flag1包序控制=分组标志（2位）+包序列计数（14位）
                flag1 = (pInputCode[i * pack_len + 4] << 8 | pInputCode[i * pack_len + 5]) & 0x3FFF;
            }
            else{
                flag2 = (pInputCode[i * pack_len + 4] << 8 | pInputCode[i * pack_len + 5]) & 0x3FFF;
                if ((flag1 + 1) != flag2)
                {
                    if(flag1 != 16383 || flag2 !=0) //摩根定律，同时这里存储源包只有14位计数2^14=16384
                    {
                        //sprintf(outwords + flagSize, "存储源包数据在 %d 帧与 %d 帧之间不连续\n", flag1, flag2); //outwords + flagSize这是啥啊？
                        sprintf(outwords, "存储源包<%s>数据在 %d 帧与 %d 帧之间不连续 %d 行\n",packname,flag1, flag2,*numid);
                        //CASE_SID::fakeUi->setLinetext(QString("%1").arg(outwords));

                        fpOut = fopen(outputfileName, "ab");
                        if (fpOut == NULL)
                        {
                            MainWindow::fakeUi->setLinetext(QString("error:can not open %1\n").arg(outputfileName));
                            return -1;
                        }
                        fwrite(outwords, strlen(outwords), 1, fpOut);
                        fclose(fpOut);
                        fpOut = NULL;
                        errornum = errornum +1;
                    }
                }
                flag3 = flag1;
                flag1 = flag2;


            }
            //判断校验和24.0605修改（单字节累加，结果为双字节）
           int check = 0;
           int check1=0;
           for(int j = 0; j < pack_len - 2 ; j++)
           {
               /*check =(check+(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]);
                                   qDebug()<<"加数："<<(srcpackage[i+10+j]<<8)+srcpackage[i+11+j]<<"    累加和："<<check<<endl;*/
//                           if(j+1 < pack_len)
//                           {
//                               check=check+(pInputCode[pack_len*i+j]<<8)+pInputCode[pack_len*i+j+1];
//                           }
//                           else
//                           {
//                               check=check+(pInputCode[pack_len*i+j]<<8)+0x00;
//                           }
              check =(check+pInputCode[pack_len*i+j]);
               //11.2删
               //qDebug()<<"加数："<<srcpackage[i+10+j]<<"    累加和："<<check<<endl;
           }
           //check=check+datalen;
           check=check&0xffff;
           check1=((pInputCode[pack_len*i + 3566] << 8) | pInputCode[pack_len*i + 3567])&0xffff;

           if(check != check1)
           {
   //            qDebug()<<"adderror"<<endl;//加和报错
               sprintf(outwords,"存储源包<%s>数据在第%d帧检验和错误bes %d\n",packname,flag1,*numid);
//               sprintf(outputfileName,"%s/adderror%s.txt",outputpathLog,packname);
               fpOut = fopen(outputfileName,"ab");
               if(fpOut == NULL)
               {
                   MainWindow::fakeUi->setLinetext(QString("EXTRACT_2711 error: can not open %!\n").arg(QString(outputfileName)));
               }
               fwrite(outwords,strlen(outwords),1,fpOut);
               fclose(fpOut);
               fpOut=NULL;

           }

            *numid=*numid+1;
        }

        group = pInputCode[i * pack_len + 4] >> 6 & 0x03; //获得其分组标志

        //group对应的是存储源包格式的分组标识，要知道一组图像数据压缩码流是由好几个数据源包组成
        //如果group为2，即是最后一个源包，则其可能数据不满会补充(这里为0xEF待确认)。
        if (group == 2)//最后一包
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;//包数据长度 =4024-8
            memcpy(pout + temp, pInputCode + i * pack_len + 16, data_len);//提取E-PDU数据域数据
            temp += data_len;

            *Outputlen = temp;
            return (i + 1) * pack_len;
        }
        else if(group==3)
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
            memcpy(pout + temp, pInputCode + i * pack_len + 16, data_len);
            temp += data_len;
            *Outputlen = temp;

        }
        else if (barkDetect(pInputCode, (i + 1) * pack_len, i * pack_len, &frm_pos))//帧头 F5F6EB90
        {
            frm_cnt++;

            if (frm_cnt == 1)
            {
                //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
                memcpy(pout + temp, pInputCode + i * pack_len + 16, data_len);
                temp += data_len;

            }
            else if (frm_cnt == 2)
            {
                return i * pack_len;
            }
        }

        else//中间包
        {
            //data_len = (pInputCode[i * 4032 + 6] << 8 | pInputCode[i * 4032 + 7]) - 8 + 1;
            memcpy(pout + temp, pInputCode + i * pack_len + 16, data_len);
            temp += data_len;

        }
    }

    //如果从这里退出函数,代表这包数据找不到10即结尾包,长度*Outputlen相当于未赋值为0
    MainWindow::fakeUi->setLinetext(QString("退出函数: error\n"));
    //CASE_SID::fakeUi->setLinetext_detect(QString("unpackFrameNum is %1\n").arg(unpackFrameNum));
    return i * pack_len;
}
