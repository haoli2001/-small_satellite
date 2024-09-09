#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QString>

#include "mainwindow.h"
#include "Extract_BPDU.h"
#include "myInclude.h"

//输入：参数1 Inputcode为对应VCID的AOS帧组如其是ZHSJData
//     参数2 Inputlen为对应VCID的AOS帧组的长度如其是ZHSJlen
//     参数4 irecord一个AOS的长度
//     参数5 pathLog 输出日志文件路径
//输出：参数3 pBPDU为提取的BPDU
//返回值 serialflag1 这一轮中ZHSJ的不连续帧的个数 serialflag2为本次输入的文件中ZHSJ的AOS帧不连续个数
//实现从AOS帧提取BPDU数据，同时对ZHSJ的AOS帧进行了连续性检查

int Extract_BPDU(unsigned char* Inputcode, int Inputlen, unsigned char* pBPDU, int irecord, char *pathLog, int AOSdataFlag,unsigned int *vcnumid)
{
    //unsigned int flag4, flag5;
    unsigned int flag4;
    unsigned int flag1, flag2;
    int     flag3 = 0;
    char	outputfileName[fileNameLen]= "";     //合并后的文件输出路径
    char    outwords[100];       //存到日志文档中的话
    FILE	*fpOut;

//    sprintf(outputfileName, "%s/AOS.txt", pathLog);

//    int i = 0;
//    int num = 0;
    char dataname[20];
    if(AOSdataFlag == 1)
        sprintf(dataname, "实时RW数据");
    else if(AOSdataFlag == 2)
        sprintf(dataname, "实时星务工程参数数据");
    else if(AOSdataFlag == 3)
        sprintf(dataname, "实时载荷数据");
    else if(AOSdataFlag == 4)
        sprintf(dataname, "回放分区数据");
    else if(AOSdataFlag == 5)
        sprintf(dataname, "回放载荷数据");
    else if(AOSdataFlag == 6)
        sprintf(dataname, "填充帧数据");

    //int truenum,errornum=0;
    for (int i = 0; i < Inputlen / irecord; i++)
    {
        *vcnumid+=1;
        //帧连续性判断
        if (i == 0)
        {
            flag1 = (Inputcode[i * irecord + 6] << 16 | Inputcode[i * irecord + 7] << 8 | Inputcode[i * irecord + 8]) & 0xFFFFFF;
        }
        else
        {
            flag2 = (Inputcode[i * irecord + 6] << 16 | Inputcode[i * irecord + 7] << 8 | Inputcode[i * irecord + 8]) & 0xFFFFFF;             

            if ((flag1 + 1) != flag2 &&flag2!=0)
            {
                flag3++;
                fpOut = NULL;
                sprintf(outputfileName, "%s/AOS.txt", pathLog);
                sprintf(outwords, "帧连续性检测： %s 在 %d 帧与 %d 帧之间不连续,%d 行\n", dataname, flag1, flag2,*vcnumid);
                //CASE_SID::fakeUi->setLinetext_1(QString("%1").arg(outwords));
                fpOut = fopen(outputfileName, "ab");
                if (fpOut == NULL)
                {
                    MainWindow::fakeUi->setLinetext(QString("Extract_BPDU error:can not open %1\n").arg(QString(outputfileName)));
                    return -1;
                }
                fwrite(outwords, strlen(outwords), 1, fpOut);
                fclose(fpOut);
                fpOut = NULL;
            }
            flag1 = flag2;
        }

        //帧有效性判断,flag4版本号,flag5航天器标识符
        flag4 = (Inputcode[i * irecord] << 24 |Inputcode[i * irecord + 1] << 16 | Inputcode[i * irecord + 2] << 8 |
                Inputcode[i * irecord + 3]) & 0xFFFFFFFF;

//        flag5 = ((Inputcode[i * irecord + 2] << 8 | Inputcode[i * irecord + 3]) >> 6) & 0x00FF;

        if(flag4 != 0x1ACFFC1D)
        {
            fpOut = NULL;
            sprintf(outputfileName, "%s\\AOS.txt", pathLog);
            sprintf(outwords, "帧有效性检测：AOS帧中 %s 在 %d 帧同步头错误,实际内容为   %d   \n", dataname, flag1, flag4);
            //CASE_SID::fakeUi->setLinetext(QString("AOS帧中载荷数据在 %d 帧同步头错误,实际内容为   %d   \n").arg(flag1).arg(flag4));
            //CASE_SID::fakeUi->setLinetext(QString("%1").arg(outwords));

            fpOut = fopen(outputfileName, "ab");
            if (fpOut == NULL)
            {
                MainWindow::fakeUi->setLinetext(QString("Extract_BPDU error:can not open %1\n").arg(QString(outputfileName)));
            }
            fwrite(outwords, strlen(outwords), 1, fpOut);
            fclose(fpOut);
            fpOut = NULL;
        }


        //提取BPDU数据域数据
        memcpy(pBPDU + i * 850, Inputcode + i * irecord + 44, 850);//现数据BPDU数据长度850字节，前有12+32=44字节其他数据
//        memcpy(pBPDU + i * 848, Inputcode + i * irecord + 44, 848);//现数据BPDU数据长度850字节，前有12+32=44字节其他数据

    }
    //num = i;

    return flag3;
}



int Extract_GC(unsigned char* Inputcode, int Inputlen, unsigned char* pGC)
{
    int			k = 0;
    int			flag_head = 0;
    int			flag_end = 0;
    int			codeLen = 0;
    int			sumLen = 0;

    for (int i = 0; i < Inputlen; i++)
    {
        if ((Inputcode[i] == 0xE2) && (Inputcode[i + 1] == 0x25) && (Inputcode[i + 2] == 0x08) && (Inputcode[i + 3] == 0x13))
        {
            k = k + 1;

            if (k == 1)
            {
                flag_head = i;
            }

            if (k >= 2)
            {
                flag_end = i;
                codeLen = flag_end - flag_head - 16;
                memcpy(pGC + sumLen, Inputcode + (flag_head + 16), codeLen);
                sumLen += codeLen;
                flag_head = flag_end;
            }

            if (i == Inputlen - 1)
            {
                codeLen = Inputlen - flag_head - 16;
                memcpy(pGC + sumLen, Inputcode + (flag_head + 16), codeLen);
                sumLen += codeLen;
            }
        }
    }

    return sumLen;
}

//uint16_t crc16ccittfalse(uint8_t *ptr, uint16_t len)
//{
//    unsigned short  crc = 0xffff; // initial value
//    unsigned short  polynomial = 0x1021; // poly value
//    for (int index = 0; index < len; index++)
//    {
//        unsigned short b = ptr[index];
//        for (int i = 0; i < 8; i++) {
//            unsigned short bit = ((b >> (7 - i) & 1) == 1);
//            unsigned short c15 = ((crc >> 15 & 1) == 1);
//            crc <<= 1;
//            if (c15 ^ bit)
//                crc ^= polynomial;
//        }
//    }
//    crc &= 0xffff;
//    return crc;

//}
