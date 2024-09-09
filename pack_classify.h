#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __PACKCLASSIFY__
#define __PACKCLASSIFY__

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

int pack_classify(unsigned char* pInputCode, int InputLen, unsigned char* p0187, int* i0187, unsigned char* p01A2, int* i01A2,
                  unsigned char* p02B1, int* i02B1, unsigned char* p02C1, int* i02C1, unsigned char* p0218, int* i0218,
                  unsigned char* p032E, int* i032E, unsigned char* p033D, int* i033D, unsigned char* p034D, int* i034D,
                  unsigned char* p045E, int* i045E);


int vc1pack_classify(unsigned char* pInputCode, int InputLen, unsigned char* pXWGC, int* iXWGC);

#endif


#ifdef __cplusplus
}
#endif
