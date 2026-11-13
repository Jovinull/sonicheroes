#include "types.h"
#include "cri/sj.h"

extern "C" {
s32 ADXB_GetFormat(s32);
s32 ADXB_GetTotalNumSmpl(s32);
s32 ADXB_GetBlkSmpl(s32);
void ADXB_EntryData(s32, s8*, s32);
void ADXB_Start(s32);

typedef struct ObjADXSJD {
	u8 pad0;         /* 0x00 */
	s8 state;        /* 0x01 */
	u8 pad2;         /* 0x02 */
	s8 field3;       /* 0x03 */
	s32 adxb;        /* 0x04 */
	CriStream* sj;   /* 0x08 */
	CriStream* sj2;  /* 0x0C */
	u8 pad10[4];     /* 0x10 */
	CriChunk chunk;  /* 0x14 */
	u8 pad1C[0x18];  /* 0x1C */
	s32 f34;         /* 0x34 */
	u8 pad38[4];     /* 0x38 */
	s32 f3C;         /* 0x3C */
	s32 f40;         /* 0x40 */
	u8 pad44[4];     /* 0x44 */
	void (*cb)(s32); /* 0x48 */
	s32 cbarg;       /* 0x4C */
} ObjADXSJD;

void adxsjd_decexec_start(ObjADXSJD* o)
{
	s32 f3c       = o->f3C;
	s32 adxb      = o->adxb;
	CriStream* sj = o->sj;

	if (f3c >= 0 && o->f40 >= f3c) {
		if (o->cb != NULL) {
			o->cb(o->cbarg);
		}
	}
	if (o->field3 == 1) {
		if (sj->vtbl->get(sj, 1) == 0) {
			o->state = 3;
			return;
		}
	}
	sj->vtbl->read(sj, 1, 0x7fffffff, &o->chunk);
	if (ADXB_GetFormat(adxb) == 0 && o->chunk.size >= 2 && (u16) * (s16*)o->chunk.addr == 0x8001) {
		o->state = 3;
		sj->vtbl->unget(sj, 1, &o->chunk);
		return;
	}
	if (o->f34 >= ADXB_GetTotalNumSmpl(o->adxb)) {
		o->state = 3;
		sj->vtbl->unget(sj, 1, &o->chunk);
		return;
	}
	{
		s32 blk = ADXB_GetBlkSmpl(o->adxb);
		s32 num = o->sj2->vtbl->get(o->sj2, 0);

		if (num / 2 < blk) {
			sj->vtbl->unget(sj, 1, &o->chunk);
			return;
		}
	}
	if (ADXB_GetFormat(adxb) == 0xA) {
		sj->vtbl->unget(sj, 1, &o->chunk);
	}
	ADXB_EntryData(adxb, o->chunk.addr, o->chunk.size);
	ADXB_Start(adxb);
}
}
