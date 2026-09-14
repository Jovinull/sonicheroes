#ifndef CRI_SJRBF_H
#define CRI_SJRBF_H

#include "cri/sj.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SjObj SjObj;
typedef void (*SjErrorFunc)(void* object, s32 error);

s32 fn_80220BF0(SjObj* stream, s32 id, s32 index);
s32 fn_80220C08(SjObj* stream);
s32 fn_80220C10(SjObj* stream);
s8* fn_80220C18(SjObj* stream);
s32 fn_80220C20(SjObj* stream, s32 id, s32 size, s32* readSize);
void fn_80220D2C(SjObj* stream, s32 id, CriChunk* chunk);
void fn_80220ED8(SjObj* stream, s32 id, CriChunk* chunk);
void fn_80221034(SjObj* stream, s32 id, s32 size, CriChunk* chunk);
s32 fn_802211E8(SjObj* stream, s32 id);
void fn_80221244(SjObj* stream);
void fn_8022129C(SjObj* stream, SjErrorFunc callback, void* object);
const void* fn_802212A8(SjObj* stream);
void fn_802212B0(SjObj* stream);
void fn_80221498(void);
void fn_802214E8(void);
void fn_8022154C(void* object, s32 error);

#ifdef __cplusplus
}
#endif

#endif
