#ifndef CRI_STM_H
#define CRI_STM_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif
void fn_80216F18(void* hndl);
s32 fn_80216810(void* hndl, s32 flowlimit, s32 nsct);
void fn_80216EC4(void* hndl, s32 numSectors);
void fn_80217044(void* hndl);
void fn_8021713C(void* hndl);
s32 fn_802171C0(void* hndl);
void fn_802171DC(void* hndl, s32 value);
s32 fn_8021722C(void* hndl);
void fn_80217434(void* hndl);
void fn_80217584(void* hndl, const char* fname, void* dir, s32 ofst, s32 numSectors);

#ifdef __cplusplus
}
#endif
#endif
