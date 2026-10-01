#ifndef CRI_SFXAHN_H
#define CRI_SFXAHN_H

#include "types.h"

/* Opaque alpha handle; the SfxAHn name is corroborated by a native error string. */
typedef struct SfxAHn SfxAHn;

#ifdef __cplusplus
extern "C" {
#endif

void fn_17_E89C(SfxAHn* handle, s32* arg1, s32* arg2, s32* arg3);
void fn_17_E8B8(SfxAHn* handle, s32 arg1, s32 arg2, s32 arg3);
s32 fn_17_E8D0(SfxAHn* handle);
/* The first two arguments of E8D8 and the second of E8FC are unused natively;
 * their historical types are not established by these bodies. */
void fn_17_E8D8(SfxAHn* handle, s32 arg1, void* buffer);
void fn_17_E8FC(SfxAHn* handle, s32 arg1, void* buffer);
void fn_17_E940(SfxAHn* handle);
void fn_17_E964(SfxAHn* handle);
SfxAHn* fn_17_E988(void);
SfxAHn* fn_17_E9C0(void);
void fn_17_EA3C(void);
void fn_17_EA40(void);
void fn_17_EA80(void);

#ifdef __cplusplus
}
#endif

#endif
