#ifndef CRI_STM_H
#define CRI_STM_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif
void ADXSTM_Stop(void* hndl);
s32 ADXSTM_SetBufSize(void* hndl, s32 flowlimit, s32 nsct);
void ADXSTM_SetEos(void* hndl, s32 numSectors);
void ADXSTM_StopNw(void* hndl);
void ADXSTM_Start(void* hndl);
s32 ADXSTM_Tell(void* hndl);
void ADXSTM_Seek(void* hndl, s32 value);
s32 ADXSTM_GetStat(void* hndl);
void ADXSTM_ReleaseFileNw(void* hndl);
void ADXSTM_BindFileNw(void* hndl, const char* fname, void* dir, s32 ofst, s32 numSectors);

#ifdef __cplusplus
}
#endif
#endif
