
#include "myInclude.h"
#include "mainwindow.h"
#include <QString>
#include <QDebug>

__int64 filesize64(FILE* stream)
{
    __int64 curpos, length;
    curpos = _ftelli64(stream);
    _fseeki64(stream, 0L, SEEK_END);
    length = _ftelli64(stream);
    _fseeki64(stream, curpos, SEEK_SET);
    return length;
}


extern char outputpathLog[fileNameLen];
void outputLog(struct testCompressedStream* p, const char* word)
{
    FILE *fpout;
    char outwords[200], outFileName[fileNameLen];

    sprintf(outFileName, "%s\\report.txt", outputpathLog);
    fpout = fopen(outFileName, "a");

    sprintf(outwords, "%s压缩码流帧统计结果如下:\n",word);
    fwrite(outwords, strlen(outwords), 1, fpout);
    sprintf(outwords, "    1.%s压缩码流帧共有%d帧\n",word, p->frameNum);
    fwrite(outwords, strlen(outwords), 1, fpout);
    sprintf(outwords, "    3.%s压缩码流帧校验和正确计数                     %d帧\n", word, p->correctNum);
    fwrite(outwords, strlen(outwords), 1, fpout);
    sprintf(outwords, "    4.%s压缩码流帧校验和错误计数                     %d帧\n", word, p->errorNum);
    fwrite(outwords, strlen(outwords), 1, fpout);

    fclose(fpout);
    fpout = NULL;
    return;
}

//20210330 kj 新的合并函数(虚拟信道)
//void combine(unsigned char* Inputcode1, int Inputlen1, unsigned char* Inputcode2, int Inputlen2,
//             unsigned char* SSRWdata, unsigned char* SSGCdata,
//             unsigned char* SSZHdata, unsigned char* HFGCdata, unsigned char* HFZHdata,
//             long long* SSRWlen, long long* SSGClen, long long* SSZHlen, long long* HFGClen, long long* HFZHlen,
//             unsigned char* remaincode1, unsigned char* remaincode2, long long* remainlen1, long long* remainlen2,
//             int ibypass, int irecord, int iactual, char outputpath[200],bool *vcstate)
void combine(unsigned char* Inputcode1, int Inputlen1, unsigned char* Inputcode2, int Inputlen2,
             unsigned char* SSRWdata, unsigned char* SSGCdata,
             unsigned char* SSZHdata, unsigned char* HFGCdata, unsigned char* HFZHdata,unsigned char* TCZdata,unsigned char* XJSJdata,
             long long* SSRWlen, long long* SSGClen, long long* SSZHlen, long long* HFGClen, long long* HFZHlen,long long* TCZlen,long long* XJSJlen,
             unsigned char* remaincode1, unsigned char* remaincode2, long long* remainlen1, long long* remainlen2,
             int ibypass, int irecord, int iactual, char outputpath[200],int vcNum,bool * vcflag,unsigned int *synvc,int *synflag)
{
    *SSRWlen = *SSGClen = *SSZHlen = *HFGClen = *HFZHlen = 0,*TCZlen = 0,*XJSJlen = 0;
//    unsigned char	 *Brightdata, *Densedata, *databuff;
    unsigned char	 *databuff;
    __int64         BUFFSIZE;


    //vcflag[1]=vcflag[2]=vcflag[3]=vcflag[4]=vcflag[5]=vcflag[6]=vcflag[0]=true;

//    for(int i=0;i<vcNum;i++)
//    {
//        qDebug()<<i<<vcflag[i];
//    }

    //count1 1通道 数据的个数
    //data1_c Inputcode1处理的AOS个数 data3_c合并的AOS帧个数
    //flag1帧分类标识符，flag2-9明密判别标识符
    //compar1代表 1通道虚拟信道帧计数， compar3 帧计数周期
    int				count1, count2;
    int				data1_c = 0, data2_c = 0, data3_c = 0;
//    unsigned int	flag1, flag2;
    unsigned int	flag1, synflag1;
    unsigned int	compar1, compar2, compar3, compar4;
    int             num0 = 0,num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0,num6 = 0;//对应类型数据AOS个数
    unsigned int compar5,compar6,compar7;//应对Vc不同，但compar3=compar4的情况

    char    outwords[100];       //存到日志文档中的话

    int errornum1=0,errornum2=0;
    unsigned int errorpos1,errorpos2;


    //BUFFSIZE = (24 * 1024 * iactual);
    BUFFSIZE = (260 * 1024 * iactual);//为啥这里是260MB

    //存储合帧后的数据
    databuff = (unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    //存储判别明密后的数据
//    Brightdata = (unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
//    Densedata = (unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));

    if (NULL == databuff)
    {
        printf("check: failed to apply for databuff space in combine!!\n");
        getchar();
        exit(0);
    }

    compar7= *synvc;
    if(*synflag!=3)
    {synflag1=*synflag;}


    //通道 数据的个数
    count1 = Inputlen1 / iactual;
    count2 = Inputlen2 / iactual;

    while (count1 > 0 && count2 > 0)
    {
        //通过从输入数据流的当前帧中读取第5,6字节，并将它们合成为一个16位的无符号整数。
        //为版本号
        compar5 = (Inputcode1[data1_c * iactual + 4] << 8 | Inputcode1[data1_c * iactual + 5]) & 0xFFFF;
        compar6 = (Inputcode2[data2_c * iactual + 4] << 8 | Inputcode2[data2_c * iactual + 5]) & 0xFFFF;

        //剔除掉错误帧 后续错误排查
        //版本号比较
        while(compar5!=22659 && compar5!=22662 && compar5!=22668 && compar5!=22673 && compar5!=22690 && compar5!=22719 && count1>0)
        {
//            if(compar5 == 0)
//            {
//                data1_c=data1_c +1;
//            }
            errornum1 = errornum1+1;
//            if(errornum1 == 1)
//            {
//                errorpos1 = (Inputcode1[(data1_c-1) * iactual + 6] << 16 | Inputcode1[(data1_c-1) * iactual + 7] << 8 | Inputcode1[(data1_c-1) * iactual + 8]) & 0xFFFFFF;
//                //qDebug()<<"1pos:"<<errorpos1+1;
//            }
            //qDebug()<<"channel1errorsum:"<<errornum1;
            data1_c=data1_c+1;
            count1--;
//            break;
            compar5 = (Inputcode1[data1_c * iactual + 4] << 8 | Inputcode1[data1_c * iactual + 5]) & 0xFFFF;

        }

        while(compar6!=22659 && compar6!=22662 && compar6!=22668 && compar6!=22673 && compar6!=22690 && compar6!=22719 && count2>0)
        {
//            if(count2==0)
//            {
//                break;
//            }
            errornum2 = errornum2+1;
//            if(errornum2 == 1)
//            {
//                errorpos2 = (Inputcode2[(data2_c-1) * iactual + 6] << 16 | Inputcode2[(data2_c-1) * iactual + 7] << 8 | Inputcode2[(data2_c-1) * iactual + 8]) & 0xFFFFFF;
//                //qDebug()<<"2pos:"<<errorpos2+1;
//            }
            //qDebug()<<"channel2errorsum:"<<errornum2;
            data2_c=data2_c+1;
            count2--;
//            break;
            compar6 = (Inputcode2[data2_c * iactual + 4] << 8 | Inputcode2[data2_c * iactual + 5]) & 0xFFFF;

        }
        //如果错误帧到最后
        if(count1==0||count2==0){
            compar7=0;
            break;
        }

        //compar1代表通道1虚拟信道帧计数，compar2代表通道2虚拟信道帧计数，compar3 通道1帧计数周期
        //databuff 合并后的帧，irecord记录帧长，
        //iactual实际帧长，我们理解这里是AOS帧实际长度即可为1024，1040这样
        //参数1 Inputcode1 读到内存的1通道的AOS帧数据 Inputlen1 为读取长度
        //data1_c Inputcode1处理的AOS个数 data3_c合并的AOS帧个数
        compar1 = (Inputcode1[data1_c * iactual + 6] << 16 | Inputcode1[data1_c * iactual + 7] << 8 | Inputcode1[data1_c * iactual + 8]) & 0xFFFFFF;
        compar2 = (Inputcode2[data2_c * iactual + 6] << 16 | Inputcode2[data2_c * iactual + 7] << 8 | Inputcode2[data2_c * iactual + 8]) & 0xFFFFFF;
//        compar3 = Inputcode1[data1_c * iactual + 9] & 0x0F;
//        compar4 = Inputcode2[data2_c * iactual + 9] & 0x0F;
        compar3 = Inputcode1[data1_c * iactual + 9]&0x0F;  //计数周期是0-F
        compar4 = Inputcode2[data2_c * iactual + 9]&0x0F;
//        compar5 = (Inputcode1[data1_c * iactual + 4] << 8 | Inputcode1[data1_c * iactual + 5]) & 0xFFFF;
//        compar6 = (Inputcode2[data2_c * iactual + 4] << 8 | Inputcode2[data2_c * iactual + 5]) & 0xFFFF;

//        if(count1==0&&count2==0)
//        {
//            break;
//        }

//        if(compar2==114635){
//            compar2 =114635;
//        }
        if(compar5 == compar6)
        {
            if (compar3 == compar4)
            {
                //交替将双通道的数据拷贝到databuff
                if (compar1 < compar2)
                {
                    //memcpy(void *str1, const void *str2, size_t n)
                    //* str1 -- 指向用于存储复制内容的目标数组，类型强制转换为 void* 指针。
                    //* str2 -- 指向要复制的数据源，类型强制转换为 void* 指针。
                    //* n -- 要被复制的字节数。
                    memcpy(databuff + data3_c * irecord, Inputcode1 + data1_c * iactual, irecord);
                    data1_c++; //1通道处理位置
                    count1--;  //1通道待处理
                    data3_c++; //合帧个数
                    synflag1 = 1;
                }
                else
                {
                    memcpy(databuff + data3_c * irecord, Inputcode2 + data2_c * iactual, irecord);
                    data2_c++;
                    count2--;
                    data3_c++;
                    synflag1 =2;
                }
            }
            else if(compar3==0XF&&compar4==0){
                memcpy(databuff + data3_c * irecord, Inputcode1 + data1_c * iactual, irecord);
                data1_c++; //1通道处理位置
                count1--;  //1通道待处理
                data3_c++; //合帧个数
                synflag1 = 1;
            }
            else if(compar4==0XF&&compar3==0){
                memcpy(databuff + data3_c * irecord, Inputcode2 + data2_c * iactual, irecord);
                data2_c++;
                count2--;
                data3_c++;
                synflag1 =2;
            }
            //帧计数周期回到0时，计数周期加一，所以先处理周期小的信道
            else if (compar3 > compar4) //1通道帧周期大于2通道，则处理2通道
            {
                memcpy(databuff + data3_c * irecord, Inputcode2 + data2_c * iactual, irecord);
                data2_c++;
                count2--;
                data3_c++;
                synflag1=2;

            }
            else if (compar3 < compar4)//1通道帧周期小于2通道，则处理1通道
            {
                memcpy(databuff + data3_c * irecord, Inputcode1 + data1_c * iactual, irecord);//pout合并通道
                data1_c++; //1通道处理位置
                count1--;  //1通道待处理
                data3_c++;
                synflag1 = 1;
            }
            compar7=compar5;
        }
//        else if(compar5 == compar7)
//        {
//            memcpy(databuff + data3_c * irecord, Inputcode1 + data1_c * iactual, irecord);//pout合并通道
//            data1_c++; //1通道处理位置
//            count1--;  //1通道待处理
//            data3_c++;
//            synflag1 = 1;
//        }
//        else if(compar6 ==compar7)
//        {
//            memcpy(databuff + data3_c * irecord, Inputcode2 + data2_c * iactual, irecord);
//            data2_c++;
//            count2--;
//            data3_c++;
//            synflag1 =2;
//        }
        else{
            if(synflag1 ==1)
            {
                memcpy(databuff + data3_c * irecord, Inputcode2 + data2_c * iactual, irecord);
                data2_c++;
                count2--;
                data3_c++;
                synflag1 =2;
            }
            else if(synflag1 ==2)
            {
                memcpy(databuff + data3_c * irecord, Inputcode1 + data1_c * iactual, irecord);//pout合并通道
                data1_c++; //1通道处理位置
                count1--;  //1通道待处理
                data3_c++;
                synflag1 = 1;
            }
            else{
                break;
                qDebug()<<"合并数据有问题!!!";
            }

        }

    }

    //边界处理
    if (count2 == 0 && count1 == 1)
    {
        memcpy(databuff + data3_c * irecord, Inputcode1 + data1_c * iactual, irecord);
        data1_c++;
        count1--;
        data3_c++;
    }
    else if (count1 == 0 && count2 == 1)
    {
        memcpy(databuff + data3_c * irecord, Inputcode2 + data2_c * iactual, irecord);
        data2_c++;
        count2--;
        data3_c++;
    }
//    else if(compar5==0&&compar6 ==0)
//    {
//        count1 =0;
//        count2=0;
//    }
//    if(compar7==0){
//        if(count1==0){
//            memcpy(databuff+data3_c*irecord,Inputcode2+data2_c*iactual,count2*1024);
//            count2=0;
//        }
//        else{
//            memcpy(databuff+data3_c*irecord,Inputcode1+data1_c*iactual,count1*1024);
//            count1=0;
//        }
//    }

    if(*synflag==3){
        if(count1==0){
            memcpy(databuff+data3_c*irecord,Inputcode2+data2_c*iactual,count2*1024);
            count2=0;
        }
        else{
            memcpy(databuff+data3_c*irecord,Inputcode1+data1_c*iactual,count1*1024);
            count1=0;
        }
    }

    //将合并后的传输帧数据输出成文件并保存至本地
    FILE *fpOut;
    char outputfilename[200];
    sprintf(outputfilename, "%s/combinedata.dat", outputpath);
    fpOut = fopen(outputfilename, "ab");
    fwrite(databuff, data3_c * irecord, 1, fpOut);
    fclose(fpOut);
    fpOut = NULL;


    //剩余
    if (count2 == 0 && count1 > 0)
    {
        memcpy(remaincode1, Inputcode1 + data1_c * iactual, count1 * iactual);
    }
    else if (count1 == 0 && count2 > 0)
    {
        memcpy(remaincode2, Inputcode2 + data2_c * iactual, count2 * iactual);
    }

//    if(count1 ==-1)
//    {
//        count1=0;
//    }
//    if(count2==-1)
//    {
//        count2=0;
//    }

    *remainlen1 = count1 * iactual;
    *remainlen2 = count2 * iactual;

    *synflag = synflag1;
    *synvc = compar7;

//    //判断明密(不需要)
//    for (int i = 0; i < data3_c; i++)
//    {
//        flag2 = (databuff[i * iactual + 9] & 0xF0);
//        if (flag2 == 0x10 | flag2 == 0x90)
//        {
//            //明态
//            memcpy(Brightdata + count1 * iactual, databuff + i * iactual, iactual);
//            count1++;
//        }
//        else if (flag2 == 0x70 | flag2 == 0xF0)
//        {
//            //密态
//            memcpy(Brightdata + count2 * iactual, databuff + i * iactual, iactual);
//            //调用密态数据解密处理函数
//            count2++;
//        }
//    }

    //    //帧提取分类
    //    for (int i = 0; i < data3_c; i++)
    //    {
    //        //iactual实际帧长，我们理解这里是AOS帧实际长度即可为1024，1040这样
    //        flag1 = (Brightdata[i * iactual + 4] << 8 | Brightdata[i * iactual + 5]) & 0xFFFF;

    //        if (flag1 == VC1 && vcflag[1])
    //        //if (flag1 == VC1)
    //        {
    //            memcpy(SSRWdata + num1 * iactual, Brightdata + i * iactual, iactual);
    //            num1++;
    //            *SSRWlen = num1 * iactual;
    //        }
    //        if (flag1 == VC2 && vcflag[2])
    //        //if (flag1 == VC2)
    //        {
    //            memcpy(SSGCdata + num2 * iactual, Brightdata + i * iactual, iactual);
    //            num2++;
    //            *SSGClen = num2 * iactual;
    //        }
    //        if (flag1 == VC3 && vcflag[3])
    //        //if (flag1 == 22668)
    //        //if (flag1 == VC3)
    //        {
    //            memcpy(SSZHdata + num3 * iactual, Brightdata + i * iactual, iactual);
    //            num3++;
    //            *SSZHlen = num3 * iactual;
    //        }
    //        //if (flag1 == VC4)
    //        if (flag1 == VC4 && vcflag[4])
    //        {
    //            memcpy(HFGCdata + num4 * iactual, Brightdata + i * iactual, iactual);
    //            num4++;
    //            *HFGClen = num4 * iactual;
    //        }
    //        //if (flag1 == VC5)
    //        if (flag1 == VC5 && vcflag[5])
    //        {
    //            memcpy(HFZHdata + num5 * iactual, Brightdata + i * iactual, iactual);
    //            num5++;
    //            *HFZHlen = num5 * iactual;
    //        }

    //    }

    //帧提取分类
    for (int i = 0; i < data3_c; i++)
    {
        //iactual实际帧长，我们理解这里是AOS帧实际长度即可为1024，1040这样
        flag1 = (databuff[i * iactual + 4] << 8 | databuff[i * iactual + 5]) & 0xFFFF;

        if (flag1 == VC0 && vcflag[0])
        //if (flag1 == VC1)
        {
            memcpy(XJSJdata + num0 * iactual, databuff + i * iactual, iactual);
            num0++;
            *XJSJlen = num0 * iactual;
        }
        if (flag1 == VC1 && vcflag[1])
        //if (flag1 == VC1)
        {
            memcpy(SSRWdata + num1 * iactual, databuff + i * iactual, iactual);
            num1++;
            *SSRWlen = num1 * iactual;
        }
        if (flag1 == VC2 && vcflag[2])
        //if (flag1 == VC2)
        {
            memcpy(SSGCdata + num2 * iactual, databuff + i * iactual, iactual);
            num2++;
            *SSGClen = num2 * iactual;
        }
        if (flag1 == VC3 && vcflag[3])
        //if (flag1 == 22668)
        //if (flag1 == VC3)
        {
            memcpy(SSZHdata + num3 * iactual, databuff + i * iactual, iactual);
            num3++;
            *SSZHlen = num3 * iactual;
        }
        //if (flag1 == VC4)
        if (flag1 == VC4 && vcflag[4])
        {
            memcpy(HFGCdata + num4 * iactual, databuff + i * iactual, iactual);
            num4++;
            *HFGClen = num4 * iactual;
        }
        //if (flag1 == VC5)
        if (flag1 == VC5 && vcflag[5])
        {
            memcpy(HFZHdata + num5 * iactual, databuff + i * iactual, iactual);
            num5++;
            *HFZHlen = num5 * iactual;
        }

        if (flag1 == VC63 && vcflag[6])
        {
            memcpy(TCZdata + num6 * iactual, databuff + i * iactual, iactual);
            num6++;
            *TCZlen = num6 * iactual;
        }

    }






//    //在界面上显示数传包帧计数
//    CASE_SID::fakeUi->setLinetext_1(QString("数传包帧计数如下:\n"));
//    sprintf(outwords, "数传包<实时RW数据>数据计数为: %d \n", num1);
//    CASE_SID::fakeUi->setLinetext_1(QString("%1").arg(outwords));
//    sprintf(outwords, "数传包<实时卫星工程参数数据>数据计数为: %d \n", num2);
//    CASE_SID::fakeUi->setLinetext_1(QString("%1").arg(outwords));
//    sprintf(outwords, "数传包<实时载荷数据>数据计数为: %d \n", num3);
//    CASE_SID::fakeUi->setLinetext_1(QString("%1").arg(outwords));
//    sprintf(outwords, "数传包<回放工程参数数据>数据计数为: %d \n", num4);
//    CASE_SID::fakeUi->setLinetext_1(QString("%1").arg(outwords));
//    sprintf(outwords, "数传包<回放载荷数据>数据计数为: %d \n", num5);
//    CASE_SID::fakeUi->setLinetext_1(QString("%1").arg(outwords));


    free(databuff);
//    free(Brightdata);
//    free(Densedata);

    return; //返回合并数据的长度
}

void combine_one(unsigned char* Inputcode1, int Inputlen1,
             unsigned char* SSRWdata, unsigned char* SSGCdata, unsigned char* SSZHdata, unsigned char* HFGCdata, unsigned char* HFZHdata,unsigned char* TCZdata,unsigned char* XJSJdata,
             long long* SSRWlen, long long* SSGClen, long long* SSZHlen, long long* HFGClen, long long* HFZHlen,long long* TCZlen,long long* XJSJlen,
             unsigned char* remaincode1, long long* remainlen1,
             int ibypass, int irecord, int iactual, int vcNum,bool * vcflag)
{
    *SSRWlen = *SSGClen = *SSZHlen = *HFGClen = *HFZHlen = *TCZlen = *XJSJlen = 0;

    //vcflag[1]=vcflag[2]=vcflag[3]=vcflag[4]=vcflag[5]=vcflag[6]=vcflag[0]=true;

//    for(int i=0;i<vcNum;i++)
//    {
//        qDebug()<<i<<vcflag[i];
//    }



    //count1 1通道 数据的个数
    //flag1帧分类标识符
    int				count1;
    unsigned int	flag1;
    int             num0 = 0,num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0,num6 = 0;//对应类型数据AOS个数

    count1 = Inputlen1 / iactual;

    *remainlen1 = 0;

    //帧提取分类
    for (int i = 0; i < count1; i++)
    {
        //iactual实际帧长，我们理解这里是AOS帧实际长度即可为1024，1040这样
        //y 执行位运算
        flag1 = (Inputcode1[i * iactual + 4] << 8 | Inputcode1[i * iactual + 5]) & 0xFFFF;

        if (flag1 == VC0 && vcflag[0])
        //if (flag1 == VC1)
        {
            memcpy(XJSJdata + num0 * iactual, Inputcode1 + i * iactual, iactual);
            num0++;
            *XJSJlen = num0 * iactual;
        }
        if (flag1 == VC1 && vcflag[1])
        //if (flag1 == VC1)
        {
            memcpy(SSRWdata + num1 * iactual, Inputcode1 + i * iactual, iactual);
            num1++;
            *SSRWlen = num1 * iactual;
        }
        if (flag1 == VC2 && vcflag[2])
        //if (flag1 == VC2)
        {
            memcpy(SSGCdata + num2 * iactual, Inputcode1 + i * iactual, iactual);
            num2++;
            *SSGClen = num2 * iactual;
        }
        if (flag1 == VC3 && vcflag[3])
        //if (flag1 == 22668)
        //if (flag1 == VC3)
        {
            memcpy(SSZHdata + num3 * iactual, Inputcode1 + i * iactual, iactual);
            num3++;
            *SSZHlen = num3 * iactual;
        }
        //if (flag1 == VC4)
        if (flag1 == VC4 && vcflag[4])
        {
            memcpy(HFGCdata + num4 * iactual, Inputcode1 + i * iactual, iactual);
            num4++;
            *HFGClen = num4 * iactual;
        }
        //if (flag1 == VC5)
        if (flag1 == VC5 && vcflag[5])
        {
            memcpy(HFZHdata + num5 * iactual, Inputcode1 + i * iactual, iactual);
            num5++;
            *HFZHlen = num5 * iactual;
        }
        if (flag1 == VC63 && vcflag[6])
        {
            memcpy(TCZdata + num6 * iactual, Inputcode1 + i * iactual, iactual);
            num6++;
            *TCZlen = num6 * iactual;
        }

    }

    //free(Inputcode1);

    //return; //返回合并数据的长度
}
/*
 * Inputcode1, Inputcode2: 输入数据流1和数据流2的指针。
Inputlen1, Inputlen2: 输入数据流1和数据流2的长度。
SSdata, HFdata, TCZdata: 存储分类后的数据。
SSlen, HFlen, TCZlen: 存储分类后数据的长度。
remaincode1, remaincode2: 存储剩余未处理的数据。
remainlen1, remainlen2: 剩余数据的长度。
irecord, iactual: 记录帧长和实际帧长。
outputpath: 合并后数据的输出路径。
synvc, synflag: 用于同步的虚拟信道和标志。
 * */
void newcombine(unsigned char *Inputcode1, int Inputlen1, unsigned char *Inputcode2, int Inputlen2,
                unsigned char *SSdata, unsigned char *HFdata, unsigned char *TCZdata,
                long long *SSlen, long long *HFlen, long long *TCZlen,
                unsigned char *remaincode1, unsigned char *remaincode2, long long *remainlen1, long long *remainlen2,
                int irecord, int iactual, char outputpath[], unsigned int *synvc, int *synflag)
{
    *SSlen = *HFlen = *TCZlen = 0;
    unsigned char	 *databuff;
    __int64         BUFFSIZE;

    //count1 1通道 数据的个数
    //data1_c Inputcode1处理的AOS个数 data3_c合并的AOS帧个数
    //flag1帧分类标识符，flag2-9明密判别标识符
    //compar1代表 1通道虚拟信道帧计数， compar3 帧计数周期
    int				count1, count2;
    int				data1_c = 0, data2_c = 0, data3_c = 0;
//    unsigned int	flag1, flag2;
    unsigned int	flag1, synflag1;//注意初始化
    unsigned int	compar1, compar2, compar3, compar4;
    int             num0 = 0,num1 = 0, num63 = 0;//对应类型数据AOS个数
    unsigned int compar5,compar6,compar7;//应对Vc不同，但compar3=compar4的情况

    char    outwords[100];       //存到日志文档中的话

    int errornum1=0,errornum2=0;

    BUFFSIZE = (20 * 1024 * iactual);//

    //存储合帧后的数据
    databuff = (unsigned char*)malloc(BUFFSIZE * sizeof(unsigned char));
    if (NULL == databuff)
    {
        MainWindow::fakeUi->setLinetext(QString("check: failed to apply for databuff input space!!(combine)\n"));
        return;
    }

    //计算输入数据流的帧数
    count1 = Inputlen1 / iactual;
    count2 = Inputlen2 / iactual;

    if(*synflag != 3)
    {
        synflag1 = *synflag;
    }
    while (count1 > 0 && count2 > 0) // 比较和同步操作
    {
        //从当前帧的第5个字节开始读取。
        //通过从输入数据流的当前帧中读取两个字节，并将它们合成为一个16位的无符号整数。这里为版本号+航天器标识符+虚拟信道标识符
        compar5 = (Inputcode1[data1_c * iactual + 4] << 8 | Inputcode1[data1_c * iactual + 5]) & 0xFFFF;
        compar6 = (Inputcode2[data2_c * iactual + 4] << 8 | Inputcode2[data2_c * iactual + 5]) & 0xFFFF;

        //剔除掉错误帧 后续错误排查//5.20日修改
        while(compar5!=24902 &&compar5!=24966 && compar5!=24930 && compar5!=24994 && compar5!=24959 && compar5!=25023 && count1>0)
        {
            errornum1 = errornum1+1;
            data1_c=data1_c+1;
            count1--;
            compar5 = (Inputcode1[data1_c * iactual + 4] << 8 | Inputcode1[data1_c * iactual + 5]) & 0xFFFF;

        }

        while(compar6!=24902 &&compar6!=24966 && compar6!=24930 && compar6!=24994 && compar6!=24959 && compar6!=25023 && count2>0)
        {

            errornum2 = errornum2+1;
            data2_c=data2_c+1;
            count2--;
            compar6 = (Inputcode2[data2_c * iactual + 4] << 8 | Inputcode2[data2_c * iactual + 5]) & 0xFFFF;

        }
        //如果错误帧到最后
        if(count1==0||count2==0){
            compar7=0;
            break;
        }

        //compar1代表通道1虚拟信道帧计数，compar2代表通道2虚拟信道帧计数，compar3 通道1帧计数周期
        //databuff 合并后的帧，irecord记录帧长，
        //iactual实际帧长，我们理解这里是AOS帧实际长度即可为1024，1040这样
        //参数1 Inputcode1 读到内存的1通道的AOS帧数据 Inputlen1 为读取长度
        //data1_c Inputcode1处理的AOS个数 data3_c合并的AOS帧个数


        compar1 = (Inputcode1[data1_c * iactual + 6] << 16 | Inputcode1[data1_c * iactual + 7] << 8 | Inputcode1[data1_c * iactual + 8]) & 0xFFFFFF;//VCDU计数器
        compar2 = (Inputcode2[data2_c * iactual + 6] << 16 | Inputcode2[data2_c * iactual + 7] << 8 | Inputcode2[data2_c * iactual + 8]) & 0xFFFFFF;//VCDU计数器
        compar3 = Inputcode1[data1_c * iactual + 9]&0x0F;  //计数周期是0-F
        compar4 = Inputcode2[data2_c * iactual + 9]&0x0F;
//        if(compar1==187838||compar2==187838){
//            qDebug()<<compar1;
//        }
        if(compar5 == compar6)//版本号+航天器标识符+虚拟信道标识符相同的话
        {
            if (compar3 == compar4)//计数周期相同
            {
                //交替将双通道的数据拷贝到databuff
                if (compar1 < compar2)//虚拟信道帧计数比较
                {
                    //memcpy(void *str1, const void *str2, size_t n)
                    //* str1 -- 指向用于存储复制内容的目标数组，类型强制转换为 void* 指针。
                    //* str2 -- 指向要复制的数据源，类型强制转换为 void* 指针。
                    //* n -- 要被复制的字节数。
                    memcpy(databuff + data3_c * irecord, Inputcode1 + data1_c * iactual, irecord);
                    data1_c++; //1通道处理位置
                    count1--;  //1通道待处理
                    data3_c++; //合帧个数
                    synflag1 = 1;
                }
                else
                {
                    memcpy(databuff + data3_c * irecord, Inputcode2 + data2_c * iactual, irecord);
                    data2_c++;
                    count2--;
                    data3_c++;
                    synflag1 =2;
                }
            }
            else if(compar3==0XF&&compar4==0){
                memcpy(databuff + data3_c * irecord, Inputcode1 + data1_c * iactual, irecord);
                data1_c++; //1通道处理位置
                count1--;  //1通道待处理
                data3_c++; //合帧个数
                synflag1 = 1;
            }
            else if(compar4==0XF&&compar3==0){
                memcpy(databuff + data3_c * irecord, Inputcode2 + data2_c * iactual, irecord);
                data2_c++;
                count2--;
                data3_c++;
                synflag1 =2;
            }
            //帧计数周期回到0时，计数周期加一，所以先处理周期小的信道
            else if (compar3 > compar4) //1通道帧周期大于2通道，则处理2通道
            {
                memcpy(databuff + data3_c * irecord, Inputcode2 + data2_c * iactual, irecord);
                data2_c++;
                count2--;
                data3_c++;
                synflag1=2;

            }
            else if (compar3 < compar4)//1通道帧周期小于2通道，则处理1通道
            {
                memcpy(databuff + data3_c * irecord, Inputcode1 + data1_c * iactual, irecord);//pout合并通道
                data1_c++; //1通道处理位置
                count1--;  //1通道待处理
                data3_c++;
                synflag1 = 1;
            }
            compar7=compar5;
        }
        else{
            if(synflag1 ==1)
            {
                memcpy(databuff + data3_c * irecord, Inputcode2 + data2_c * iactual, irecord);
                data2_c++;
                count2--;
                data3_c++;
                synflag1 =2;
            }
            else if(synflag1 ==2)
            {
                memcpy(databuff + data3_c * irecord, Inputcode1 + data1_c * iactual, irecord);//pout合并通道
                data1_c++; //1通道处理位置
                count1--;  //1通道待处理
                data3_c++;
                synflag1 = 1;
            }
            else{
                break;
                qDebug()<<"合并数据有问题!!!";
            }

        }

    }

    //边界处理
    if (count2 == 0 && count1 == 1)
    {
        memcpy(databuff + data3_c * irecord, Inputcode1 + data1_c * iactual, irecord);
        data1_c++;
        count1--;
        data3_c++;
    }
    else if (count1 == 0 && count2 == 1)
    {
        memcpy(databuff + data3_c * irecord, Inputcode2 + data2_c * iactual, irecord);
        data2_c++;
        count2--;
        data3_c++;
    }

//    if(*synflag==3){
//        if(count1==0 ){
//            memcpy(databuff+data3_c*irecord,Inputcode2+data2_c*iactual,count2*1024);
//            count2=0;
//        }
//        else{
//            memcpy(databuff+data3_c*irecord,Inputcode1+data1_c*iactual,count1*1024);
//            count1=0;
//        }
//    }
    if(*synflag==3){
        while(count1==0 && count2 >0){
            compar6 = (Inputcode2[data2_c * iactual + 4] << 8 | Inputcode2[data2_c * iactual + 5]) & 0xFFFF;
            while(compar6!=24902 &&compar6!=24966 && compar6!=24930 && compar6!=24994 && compar6!=24959 && compar6!=25023 && count2>0)
            {

                errornum2 = errornum2+1;
                data2_c=data2_c+1;
                count2--;
                compar6 = (Inputcode2[data2_c * iactual + 4] << 8 | Inputcode2[data2_c * iactual + 5]) & 0xFFFF;

            }
            if(count2 == 0) break;
            memcpy(databuff + data3_c * irecord, Inputcode2 + data2_c * iactual, irecord);
            data2_c++;
            count2--;
            data3_c++;
            synflag1 =2;

        }
        while(count2 == 0 && count1 > 0){
            compar5 = (Inputcode1[data1_c * iactual + 4] << 8 | Inputcode1[data1_c * iactual + 5]) & 0xFFFF;
            while(compar5!=24902 &&compar5!=24966 && compar5!=24930 && compar5!=24994 && compar5!=24959 && compar5!=25023 && count1>0)
            {
                errornum1 = errornum1+1;
                data1_c=data1_c+1;
                count1--;
                compar5 = (Inputcode1[data1_c * iactual + 4] << 8 | Inputcode1[data1_c * iactual + 5]) & 0xFFFF;

            }
            if(count1 == 0) break;
            memcpy(databuff + data3_c * irecord, Inputcode1 + data1_c * iactual, irecord);//pout合并通道
            data1_c++; //1通道处理位置
            count1--;  //1通道待处理
            data3_c++;
            synflag1 = 1;

        }
    }

    //将合并后的传输帧数据输出成文件并保存至本地
    FILE *fpOut;
    char outputfilename[200];
    sprintf(outputfilename, "%s/combinedata.dat", outputpath);
    fpOut = fopen(outputfilename, "ab");
    fwrite(databuff, data3_c * irecord, 1, fpOut);
    fclose(fpOut);
    fpOut = NULL;


    //剩余
    if (count2 == 0 && count1 > 0)
    {
        memcpy(remaincode1, Inputcode1 + data1_c * iactual, count1 * iactual);
    }
    else if (count1 == 0 && count2 > 0)
    {
        memcpy(remaincode2, Inputcode2 + data2_c * iactual, count2 * iactual);
    }

    *remainlen1 = count1 * iactual;
    *remainlen2 = count2 * iactual;

    *synflag = synflag1;
    *synvc = compar7;


    //帧提取分类，分类为相同类别的帧拼接在一起
    for (int i = 0; i < data3_c; i++)
    {
        //iactual实际帧长，我们理解这里是AOS帧实际长度即可为1024，1040这样
        flag1 = (databuff[i * iactual + 4] << 8 | databuff[i * iactual + 5]) & 0xFFFF;

        if (flag1 == VC_1_02 || flag1 == VC_1_03)
        //if (flag1 == VC1)
        {
            memcpy(SSdata + num0 * iactual, databuff + i * iactual, iactual);//实时数据
            num0++;
            *SSlen = num0 * iactual;
        }
        if (flag1 == VC_2_02 || flag1 == VC_2_03)
        //if (flag1 == VC1)
        {
            memcpy(HFdata + num1 * iactual, databuff + i * iactual, iactual);//回放数据
            num1++;
            *HFlen = num1 * iactual;
        }

        if (flag1 == VC_63_02 || flag1 == VC_63_03 )
        {
            memcpy(TCZdata + num63 * iactual, databuff + i * iactual, iactual);//填充帧（空帧）
            num63++;
            *TCZlen = num63 * iactual;
        }

    }

    free(databuff);

    return; //返回合并数据的长度
}
void newcombine_one(unsigned char* Inputcode1, int Inputlen1,
             unsigned char* SSdata, unsigned char* HFdata, unsigned char* TCZdata,
             long long* SSlen, long long* HFlen, long long* TCZlen,
             unsigned char* remaincode1, long long* remainlen1,
             int irecord, int iactual)
{
    *SSlen = *HFlen =  *TCZlen = 0;

    //count1 1通道 数据的个数
    //flag1帧分类标识符
    int				count1;
    unsigned int	flag1;
    int             num0 = 0,num1 = 0,num63 = 0;//对应类型数据AOS个数

    count1 = Inputlen1 / iactual;

    *remainlen1 = 0;

    //帧提取分类
    for (int i = 0; i < count1; i++)
    {
        //iactual实际帧长，我们理解这里是AOS帧实际长度即可为1024，1040这样
        //y 执行位运算
        flag1 = (Inputcode1[i * iactual + 4] << 8 | Inputcode1[i * iactual + 5]) & 0xFFFF;
        if (flag1 == VC_1_02 || flag1 == VC_1_03 )
        //if (flag1 == VC1)
        {
            memcpy(SSdata + num0 * iactual, Inputcode1 + i * iactual, iactual);
            num0++;
            *SSlen = num0 * iactual;
        }
        if (flag1 == VC_2_02 || flag1 == VC_2_03  )
        //if (flag1 == VC2)
        {
            memcpy(HFdata + num1 * iactual, Inputcode1 + i * iactual, iactual);
            num1++;
            *HFlen = num1 * iactual;
        }

        if (flag1 == VC_63_02 || flag1 == VC_63_03 )
        {
            memcpy(TCZdata + num63 * iactual, Inputcode1 + i * iactual, iactual);
            num63++;
            *TCZlen = num63 * iactual;
        }

    }

}
