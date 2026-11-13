// Reads up to 0x1000 bytes from the input stream joint, decodes the stream header with
// ADXB_DecodeHeader, keeps up to 0x40 bytes of an SPSD header (format 2), and hands the rest back
// to the joint. State becomes 2 on success and 4 on a header error.

#include "types.h"
#include "cri/sj.h"

extern "C" {

s32 ADXB_DecodeHeader(s32 adxb, u16* data, s32 size);
s32 ADXB_GetFormat(s32 adxb);
void ADXERR_CallErrFunc2(const char* msg1, const char* msg2);
void* memcpy(void* dst, const void* src, u32 size);
extern char lbl_8023D680[];
extern char lbl_8023D6A0[];

typedef struct ObjADXSJD {
	u8 pad0;        /* 0x00 */
	s8 state;       /* 0x01 */
	u8 pad2;        /* 0x02 */
	s8 field3;      /* 0x03 */
	s32 adxb;       /* 0x04 */
	CriStream* sj;  /* 0x08 */
	u8 pad0C[0x4C]; /* 0x0C */
	u8 spsd[0x40];  /* 0x58 */
	s32 len;        /* 0x98 */
} ObjADXSJD;

void adxsjd_decode_prep(ObjADXSJD* o)
{
	CriChunk chunk; /* 0x10(r1) */
	CriChunk rest;  /* 0x08(r1) */
	s32 adxb;
	CriStream* sj;
	s32 len;
	s32 fmt;
	CriChunk* c;
	s32 size;

	adxb = o->adxb;
	sj   = o->sj;
	sj->vtbl->read(sj, 1, 0x1000, &chunk);
	if (chunk.size < 0x10) {
		sj->vtbl->unget(sj, 1, &chunk);
		return;
	}
	len = ADXB_DecodeHeader(adxb, (u16*)chunk.addr, chunk.size);
	if (len == 0 || len > chunk.size) {
		sj->vtbl->unget(sj, 1, &chunk);
		return;
	}
	if (len < 0) {
		sj->vtbl->unget(sj, 1, &chunk);
		ADXERR_CallErrFunc2(lbl_8023D680, lbl_8023D6A0);
		o->state = 4;
		return;
	}
	o->len = len;
	if (ADXB_GetFormat(adxb) == 4) {
		o->field3 = 1;
	}
	if (ADXB_GetFormat(adxb) == 2) {
		c = &chunk;
		if (chunk.size < 0x40) {
			size = c->size;
		} else {
			size = 0x40;
		}
		memcpy(o->spsd, chunk.addr, size);
	}
	fmt = ADXB_GetFormat(adxb);
	if (fmt == 10 || fmt == 11 || fmt == 20 || fmt == 15) {
		sj->vtbl->unget(sj, 1, &chunk);
	} else {
		fn_80221824(&chunk, len, &chunk, &rest);
		sj->vtbl->put(sj, 0, &chunk);
		sj->vtbl->unget(sj, 1, &rest);
	}
	o->state = 2;
}
}
