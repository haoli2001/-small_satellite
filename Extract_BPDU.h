#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __EXTRACTPDU_H__
#define __EXTRACTPDU_H__

int Extract_BPDU(unsigned char* Inputcode, int Inputlen, unsigned char* pBPDU, int irecord, char *pathLog, int AOSdataFlag,unsigned int *vcnumid);
int Extract_GC(unsigned char* Inputcode, int Inputlen, unsigned char* pGC);
//uint16_t crc16ccittfalse(uint8_t *ptr,uint16_t len);


#endif

#ifdef __cplusplus
}
#endif
