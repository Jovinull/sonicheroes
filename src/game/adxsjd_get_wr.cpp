#include "types.h"

extern "C" {

typedef struct CriChunk {
	s8* addr;
	s32 size;
} CriChunk;

typedef struct SjObj SjObj;

typedef struct SjVtbl {
	u8 pad[0x18];
	void (*getChunk)(SjObj* sj, s32 id, s32 size, CriChunk* chunk);
} SjVtbl;

struct SjObj {
	SjVtbl* vtbl;
};

typedef struct SjdObj {
	u8 pad0[4];
	s32 decoder;       /* 0x04 */
	SjObj* in;         /* 0x08 */
	SjObj* out[2];     /* 0x0C */
	CriChunk inck;     /* 0x14 */
	CriChunk outck[2]; /* 0x1C */
	s32 f2c;           /* 0x2C */
	s32 f30;           /* 0x30 */
	s32 f34;           /* 0x34 */
	s32 maxdecsmpl;    /* 0x38 */
	s32 trapNumSmpl;   /* 0x3C */
	s32 trapCnt;       /* 0x40 */
	s32 f44;           /* 0x44 */
} SjdObj;

s32 ADXB_GetNumChan(s32);
s8* fn_80220C18(void*);
int ADXB_GetPcmBuf(s32);

int adxsjd_get_wr(void* sjdp, s32* pos, s32* size, s32* remain)
{
	SjdObj* o = (SjdObj*)sjdp;
	SjObj* sj;
	s32 i;
	s32 n;

	sj = o->out[0];
	for (i = 0; i < ADXB_GetNumChan(o->decoder); i++) {
		o->out[i]->vtbl->getChunk(o->out[i], 0, 0x4000, &o->outck[i]);
	}
	*pos  = (o->outck[0].addr - fn_80220C18(sj)) / 2;
	n     = o->outck[0].size / 2;
	*size = n < o->maxdecsmpl ? n : o->maxdecsmpl;
	if (o->trapNumSmpl >= 0) {
		*remain = o->trapNumSmpl - o->trapCnt;
	} else {
		*remain = 0x1FFFFFFF;
	}
	return ADXB_GetPcmBuf(o->decoder);
}
}
