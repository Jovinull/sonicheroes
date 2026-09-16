#ifndef CRI_ADAPTER_H
#define CRI_ADAPTER_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*CriErrFunc)(void* object, const char* message);

void fn_80223424(const char* message);
void fn_8022347C(CriErrFunc function, void* object);
void fn_80223490(void);
void fn_802234B0(void);
void fn_802234D0(void* object, s16 value);
s32 fn_802234E0(void);
s32 fn_802234E8(void);
void fn_802234F0(void* object, s32 value);

#ifdef __cplusplus
}
#endif

#endif
