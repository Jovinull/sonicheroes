#ifndef CRI_SJMEM_H
#define CRI_SJMEM_H

#include "cri/sj.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SjmemObj SjmemObj;

s32 fn_802205DC(SjmemObj* stream, s32 id, s32 size, s32* readSize);
void fn_80220694(SjmemObj* stream, s32 id, CriChunk* chunk);
void fn_802207C4(SjmemObj* stream, s32 id, CriChunk* chunk);
void fn_80220858(SjmemObj* stream, s32 id, s32 size, CriChunk* chunk);
s32 fn_80220940(SjmemObj* stream, s32 id);
void fn_8022099C(SjmemObj* stream);
void fn_802209B0(SjmemObj* stream, SjErrorFunc callback, void* object);
const void* fn_802209BC(SjmemObj* stream);
void fn_802209C4(SjmemObj* stream);
CriStream* fn_80220A04(void* buffer, s32 size);
void fn_80220B2C(void);
void fn_80220B74(void);
void fn_80220BC8(void* object, s32 error);

#ifdef __cplusplus
}
#endif

#endif
