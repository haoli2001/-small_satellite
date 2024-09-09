#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QString>
#include "mainwindow.h"
#include "pack_classify.h"
#include "unpack.h"


extern char	outputpathLog[400];  //输出日志路径
extern char	outputpathSourcepackage[400]; //输出源包数据路径

//输入：参数1 pInputCode为存储源包格式3568长，新一包BPDUdata加上上一轮剩余的BPDUdata
//      参数2 InputLen为该次处理长度，这轮新处理BPDU与上轮剩余BPDU长度之和
//输出： 参数3 pZXGC为存储源包格式，但这些数据都为ZXGC数据
//      参数4 iZXGC为返回的ZXGC存储源包数据的长度
//		 同理如下参数
//返回值deallen(pclen)为处理的长度i * 3568
//实现BPDU数据分为RHW存储源包数据，DGPA存储源包数据.....
int pack_classify(unsigned char* pInputCode, int InputLen, unsigned char* p0187, int* i0187, unsigned char* p01A2, int* i01A2,
                  unsigned char* p02B1, int* i02B1, unsigned char* p02C1, int* i02C1, unsigned char* p0218, int* i0218,
                  unsigned char* p032E, int* i032E, unsigned char* p033D, int* i033D, unsigned char* p034D, int* i034D,
                  unsigned char* p045E, int* i045E)
{

    unsigned int	flag1, flag2;
    int				temp_0187 = 0, temp_01A2 = 0;
    int				temp_02B1 = 0, temp_02C1 = 0, temp_0218 = 0, temp_032E = 0;
    int				temp_033D = 0, temp_034D = 0, temp_045E = 0;
    int				data_len = 3568;
    int				deallen = 0;
    int				pos;

    if (UnPack::headDetect(pInputCode, InputLen, 0, &pos)) //返回值：这里为PackFlag 1找到0未找到 E225  POS为包头位置
    {
        flag1 = (pInputCode[pos + 2] << 8 | pInputCode[pos + 3]) & 0xFFFF;//应用过程标识符
        if(pos+3568>InputLen){
            *i0187 = temp_0187;
            *i01A2 = temp_01A2;
            *i01A2 = temp_01A2;
            *i02B1 = temp_02B1;
            *i02C1 = temp_02C1;
            *i0218 = temp_0218;
            *i032E = temp_032E;
            *i033D = temp_033D;
            *i034D = temp_034D;
            *i045E = temp_045E;
            return pos;
        }

        switch (flag1)
        {
        //0x040B
        case HF0187:
            memcpy(p0187 + temp_0187, pInputCode + pos, data_len);
            temp_0187 += data_len;
//            *iZXGC = temp_ZXGC;
            deallen = pos + data_len;
            break;
        //0x020C
        case HF01A2:
            memcpy(p01A2 + temp_01A2, pInputCode + pos, data_len);
            temp_01A2 += data_len;
//            *iRWSJ = temp_RWSJ;
            deallen = pos + data_len;
            break;
        //0x0087
        case HF02B1:
            memcpy(p02B1 + temp_02B1, pInputCode + pos, data_len);
            temp_02B1 += data_len;
//            *iDKCB = temp_DKCB;
            deallen = pos + data_len;
            break;
        //0x0094
        case HF02C1:
            memcpy(p02C1 + temp_02C1, pInputCode + pos, data_len);
            temp_02C1 += data_len;
//            *iDKZCB = temp_DKZCB;
            deallen = pos + data_len;
            break;
        //0x013F
        case HF0218:
            memcpy(p0218 + temp_0218, pInputCode + pos, data_len);
            temp_0218 += data_len;
            //*iDDDPD = temp_DDDPD;
            deallen = pos + data_len;
            break;
        //0x015C
        case HF032E:
            memcpy(p032E + temp_032E, pInputCode + pos, data_len);
            temp_032E += data_len;
//            *iDDDB = temp_DDDB;
            deallen = pos + data_len;
            break;
        //0x0109
        case HF033D:
            memcpy(p033D + temp_033D, pInputCode + pos, data_len);
            temp_033D += data_len;
//            *iXJCS = temp_XJCS;
            deallen = pos + data_len;
            break;
        //0x00B1
        case HF034D:
            memcpy(p034D + temp_034D, pInputCode + pos, data_len);
            temp_034D += data_len;
            //*iJGCS = temp_JGCS;
            deallen = pos + data_len;
            break;
        //0x00A2
        case HF045E:
            memcpy(p045E + temp_045E, pInputCode + pos, data_len);
            temp_045E += data_len;
//            *iJGYY = temp_JGYY;
            deallen = pos + data_len;
            break;
        default:
            deallen = pos + 2;
            break;
        }
    }
    else
        deallen = pos;

    while (deallen + data_len <= InputLen)
    {
        flag2 = (pInputCode[deallen] << 8 | pInputCode[deallen + 1]) & 0xFFFF;

            if (flag2 == 0xe225)
            {
                flag1 = (pInputCode[deallen + 2] << 8 | pInputCode[deallen + 3]) & 0xFFFF;

                switch (flag1)
                {
                case 0X0087:
                    memcpy(p0187 + temp_0187, pInputCode + deallen, data_len);
                    temp_0187 += data_len;
                    //*iZXGC = temp_ZXGC;
                    deallen += data_len;
                    break;
                case HF01A2:
                    memcpy(p01A2 + temp_01A2, pInputCode + deallen, data_len);
                    temp_01A2 += data_len;
                    //*iRWSJ = temp_RWSJ;
                    deallen += data_len;
                    break;
                case HF02B1:
                    memcpy(p02B1 + temp_02B1, pInputCode + deallen, data_len);
                    temp_02B1 += data_len;
                    //*iDKCB = temp_DKCB;
                    deallen += data_len;
                    break;
                case HF02C1:
                    memcpy(p02C1 + temp_02C1, pInputCode + deallen, data_len);
                    temp_02C1 += data_len;
                    //*iDKZCB = temp_DKZCB;
                    deallen += data_len;
                    break;
                case HF0218:
                    memcpy(p0218 + temp_0218, pInputCode + deallen, data_len);
                    temp_0218 += data_len;
                    //*iDDDPD = temp_DDDPD;
                    deallen += data_len;
                    break;
                case HF032E:
                    memcpy(p032E + temp_032E, pInputCode + deallen, data_len);
                    temp_032E += data_len;
                    //*iDDDB = temp_DDDB;
                    deallen += data_len;
                    break;
                case HF033D:
                    memcpy(p033D + temp_033D, pInputCode + deallen, data_len);
                    temp_033D += data_len;
                    //*iXJCS = temp_XJCS;
                    deallen += data_len;
                    break;
                case HF034D:
                    memcpy(p034D + temp_034D, pInputCode + deallen, data_len);
                    temp_034D += data_len;
                    //*iJGCS = temp_JGCS;
                    deallen += data_len;
                    break;
                case HF045E:
                    memcpy(p045E + temp_045E, pInputCode + deallen, data_len);
                    temp_045E += data_len;
                    //*iJGYY = temp_JGYY;
                    deallen += data_len;
                    break;
                default:
                    deallen += 2;
                    break;
                }
            }
            else//+3568 未找到e225
            {
                if (UnPack::headDetect(pInputCode, InputLen, deallen, &pos))
                {
                    if(pos+data_len<=InputLen)
                    {
                        flag1 = (pInputCode[pos + 2] << 8 | pInputCode[pos + 3]) & 0xFFFF;

                        switch (flag1)
                        {
                        case 0X0087:
                            memcpy(p0187 + temp_0187, pInputCode + pos, data_len);
                            temp_0187 += data_len;
                            //*iZXGC = temp_ZXGC;
                            deallen = pos + data_len;
                            break;
                        case HF01A2:
                            memcpy(p01A2 + temp_01A2, pInputCode + pos, data_len);
                            temp_01A2 += data_len;
                            //*iRWSJ = temp_RWSJ;
                            deallen = pos + data_len;
                            break;
                        case HF02B1:
                            memcpy(p02B1 + temp_02B1, pInputCode + pos, data_len);
                            temp_02B1 += data_len;
                            //*iDKCB = temp_DKCB;
                            deallen = pos + data_len;
                            break;
                        case HF02C1:
                            memcpy(p02C1 + temp_02C1, pInputCode + pos, data_len);
                            temp_02C1 += data_len;
                            //*iDKZCB = temp_DKZCB;
                            deallen = pos + data_len;
                            break;
                        case HF0218:
                            memcpy(p0218 + temp_0218, pInputCode + pos, data_len);
                            temp_0218 += data_len;
                            //*iDDDPD = temp_DDDPD;
                            deallen = pos + data_len;
                            break;
                        case HF032E:
                            memcpy(p032E + temp_032E, pInputCode + pos, data_len);
                            temp_032E += data_len;
                            //*iDDDB = temp_DDDB;
                            deallen = pos + data_len;
                            break;
                        case HF033D:
                            memcpy(p033D + temp_033D, pInputCode + pos, data_len);
                            temp_033D += data_len;
                            //*iXJCS = temp_XJCS;
                            deallen = pos + data_len;
                            break;
                        case HF034D:
                            memcpy(p034D + temp_034D, pInputCode + pos, data_len);
                            temp_034D += data_len;
                            //*iJGCS = temp_JGCS;
                            deallen = pos + data_len;
                            break;
                        case HF045E:
                            memcpy(p045E + temp_045E, pInputCode + pos, data_len);
                            temp_045E += data_len;
                            //*iJGYY = temp_JGYY;
                            deallen = pos + data_len;
                            break;
                        default:
                            deallen = pos + 2;
                            break;
                        }
                    }
                    else
                        deallen = pos;
                }
                else
                    deallen = pos;
            }
    }

    //将分类后的数据源包数据输出成文件并保存至本地
    FILE *fpOut;
    char outputfilename[200];
    if(temp_0187 > 0)
    {
//        sprintf(outputfilename, "%s/HFXWGC_sourpackage.dat", outputpathSourcepackage);
        sprintf(outputfilename, "%s/XWGCdata.dat", outputpathSourcepackage);
        fpOut = fopen(outputfilename, "ab");
        fwrite(p0187,temp_0187, 1, fpOut);
        fclose(fpOut);
        fpOut = NULL;
    }
    if(temp_01A2 > 0)
    {
//        sprintf(outputfilename, "%s/HF01A2_sourpackage.dat", outputpathSourcepackage);
                sprintf(outputfilename, "%s/XJLLdata.dat", outputpathSourcepackage);
        fpOut = fopen(outputfilename, "ab");
        fwrite(p01A2, temp_01A2, 1, fpOut);
        fclose(fpOut);
        fpOut = NULL;
    }

    if(temp_02B1 > 0)
    {
//        sprintf(outputfilename, "%s/HF02B1_sourpackage.dat", outputpathSourcepackage);
        sprintf(outputfilename, "%s/XSCLdata.dat", outputpathSourcepackage);
        fpOut = fopen(outputfilename, "ab");
        fwrite(p02B1, temp_02B1, 1, fpOut);
        fclose(fpOut);
        fpOut = NULL;
    }
    if(temp_02C1 > 0)
    {
//        sprintf(outputfilename, "%s/HF02C1_sourpackage.dat", outputpathSourcepackage);
                sprintf(outputfilename, "%s/ZTdata.dat", outputpathSourcepackage);
        fpOut = fopen(outputfilename, "ab");
        fwrite(p02C1,temp_02C1, 1, fpOut);
        fclose(fpOut);
        fpOut = NULL;
    }
    if(temp_0218 > 0)
    {
//        sprintf(outputfilename, "%s/HF0218_sourpackage.dat", outputpathSourcepackage);
                sprintf(outputfilename, "%s/JGXJdata.dat", outputpathSourcepackage);
        fpOut = fopen(outputfilename, "ab");
        fwrite(p0218,temp_0218, 1, fpOut);
        fclose(fpOut);
        fpOut = NULL;
    }
    if(temp_032E > 0)
    {
//        sprintf(outputfilename, "%s/HF032E_sourpackage.dat", outputpathSourcepackage);
                sprintf(outputfilename, "%s/GYAdata.dat", outputpathSourcepackage);
        fpOut = fopen(outputfilename, "ab");
        fwrite(p032E, temp_032E, 1, fpOut);
        fclose(fpOut);
        fpOut = NULL;
    }

    if(temp_033D> 0)
    {
//        sprintf(outputfilename, "%s/HF033D_sourpackage.dat", outputpathSourcepackage);
                sprintf(outputfilename, "%s/GYBdata.dat", outputpathSourcepackage);
        fpOut = fopen(outputfilename, "ab");
        fwrite(p033D, temp_033D, 1, fpOut);
        fclose(fpOut);
        fpOut = NULL;
    }
    if(temp_034D > 0)
    {
//        sprintf(outputfilename, "%s/HF034D_sourpackage.dat", outputpathSourcepackage);
                sprintf(outputfilename, "%s/GYCdata.dat", outputpathSourcepackage);
        fpOut = fopen(outputfilename, "ab");
        fwrite(p034D, temp_034D, 1, fpOut);
        fclose(fpOut);
        fpOut = NULL;
    }
    if(temp_045E > 0)
    {
        sprintf(outputfilename, "%s/HF045E_sourpackage.dat", outputpathSourcepackage);
        fpOut = fopen(outputfilename, "ab");
        fwrite(p045E, temp_045E, 1, fpOut);
        fclose(fpOut);
        fpOut = NULL;
    }

    *i0187 = temp_0187;
    *i01A2 = temp_01A2;
    *i01A2 = temp_01A2;
    *i02B1 = temp_02B1;
    *i02C1 = temp_02C1;
    *i0218 = temp_0218;
    *i032E = temp_032E;
    *i033D = temp_033D;
    *i034D = temp_034D;
    *i045E = temp_045E;

    return deallen;
}


//void writedatatofile(FILE *fpOut, unsigned char* pdata, int datalen, char* outputpath, char* mode)
//{
//    char outputfilename[200];
//    if(datalen > 0)
//    {
//        sprintf(outputfilename, "%s/%s_sourpackage.dat", outputpath, mode);
//        fpOut = fopen(outputfilename, "ab");
//        fwrite(pdata, datalen, 1, fpOut);
//        fclose(fpOut);
//        fpOut = NULL;
//    }

//}

int vc1pack_classify(unsigned char *pInputCode, int InputLen, unsigned char *pXWGC, int *iXWGC)
{
    unsigned int	flag1, flag2;
    int				temp_XWGC = 0;
    int				data_len = 3568;
    int				deallen = 0;
    int				pos;

    if (UnPack::headDetect(pInputCode, InputLen, 0, &pos)) //返回值：这里为PackFlag 1找到0未找到 E225  POS为包头位置
    {
        flag1 = (pInputCode[pos + 2] << 8 | pInputCode[pos + 3]) & 0xFFFF;//应用过程标识符
        if(pos+3568>InputLen){

            *iXWGC = temp_XWGC;
            return pos;
        }

        switch (flag1)
        {
        //0x040B
        case HF0187:
            memcpy(pXWGC + temp_XWGC, pInputCode + pos, data_len);
            temp_XWGC += data_len;
            deallen = pos + data_len;
            break;
        default:
            deallen = pos + 2;
            break;
        }
    }
    else
        deallen = pos;

    while (deallen + data_len <= InputLen)
    {
        flag2 = (pInputCode[deallen] << 8 | pInputCode[deallen + 1]) & 0xFFFF;

            if (flag2 == 0xe225)
            {
                flag1 = (pInputCode[deallen + 2] << 8 | pInputCode[deallen + 3]) & 0xFFFF;

                switch (flag1)
                {
                case 0X0087:
                    memcpy(pXWGC + temp_XWGC, pInputCode + deallen, data_len);
                    temp_XWGC += data_len;

                    deallen += data_len;
                    break;

                default:
                    deallen += 2;
                    break;
                }
            }
            else//+4032 未找到e225
            {
                if (UnPack::headDetect(pInputCode, InputLen, deallen, &pos))
                {
                    if(pos+data_len<=InputLen)
                    {
                        flag1 = (pInputCode[pos + 2] << 8 | pInputCode[pos + 3]) & 0xFFFF;

                        switch (flag1)
                        {
                        case 0X0087:
                            memcpy(pXWGC + temp_XWGC, pInputCode + pos, data_len);
                            temp_XWGC += data_len;
                            //*iZXGC = temp_ZXGC;
                            deallen = pos + data_len;
                            break;

                        default:
                            deallen = pos + 2;
                            break;
                        }
                    }
                    else
                        deallen = pos;
                }
                else
                    deallen = pos;
            }
    }

    //将分类后的数据源包数据输出成文件并保存至本地
    FILE *fpOut;
    char outputfilename[200];
    if(temp_XWGC > 0)
    {
        sprintf(outputfilename, "%s/SSXWGCdata.dat", outputpathSourcepackage);//l 0724
        fpOut = fopen(outputfilename, "ab");
        fwrite(pXWGC,temp_XWGC, 1, fpOut);
        fclose(fpOut);
        fpOut = NULL;
    }

    *iXWGC = temp_XWGC;

    return deallen;
}
