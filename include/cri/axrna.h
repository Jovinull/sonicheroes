#ifndef CRI_AXRNA_H
#define CRI_AXRNA_H

#include "cri/sj.h"
#include "dolphin/ax.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AxRna AxRna;

void fn_80223500(AxRna* handle, s32 channel, s32 pan);
void fn_802235B4(AxRna* handle, s32 volume);
void fn_80223660(AxRna* handle, s32 rate);
void fn_802237B4(void* handle, s8 state);
void fn_802237C4(void);
void fn_80223820(AxRna* handle);
void fn_80223B58(u32 request);
void fn_80223C24(u32 request);
void fn_80223D00(AxRna* handle);
s32 fn_80223E78(AxRna* handle);
s32 fn_80223ED0(AxRna* handle);
void fn_80223F2C(AxRna* handle, s32 enabled);
void fn_802240CC(AxRna* handle, s32 enabled);
void fn_802242CC(AxRna* handle);
AxRna* fn_8022439C(CriStream** streams, s32 channelCount);
void fn_80224A88(AxVoice* voice);
void fn_80224B1C(void);
void fn_80224C3C(void);
void fn_80224CB0(void* function, void* object);

#ifdef __cplusplus
}
#endif

#endif
