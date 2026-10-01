#ifndef CRI_SJ_H
#define CRI_SJ_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CriStream CriStream;

typedef struct CriChunk {
	void* addr;
	s32 size;
} CriChunk;

typedef struct CriStreamVtable {
	u8 unknown00[0xc];
	void (*stop)(CriStream* stream);
	u8 unknown10[4];
	void (*reset)(CriStream* stream);
	void (*read)(CriStream* stream, s32 which, s32 size, CriChunk* out);
	void (*unget)(CriStream* stream, s32 which, CriChunk* chunk);
	void (*put)(CriStream* stream, s32 which, CriChunk* chunk);
	s32 (*get)(CriStream* stream, s32 arg);
} CriStreamVtable;

struct CriStream {
	CriStreamVtable* vtbl;
};

CriStream* fn_80221300(s32 start, s32 length, s32 mode);
void fn_80221824(CriChunk* source, s32 size, CriChunk* consumed, CriChunk* remaining);

#ifdef __cplusplus
}
#endif

#endif
