// Runs one decode step of an ADXSJD handle: starts decoding when idle, and when a block is
// finished hands the consumed input back to the joint and the decoded samples to each channel's
// output joint (and the optional output callback).

#include "types.h"
#include "cri/sj.h"

struct ObjADXSJD;

extern "C" {

s32 ADXB_GetStat(s32 adxb);
void ADXB_ExecHndl(s32 adxb);
s32 ADXB_GetTotalNumSmpl(s32 adxb);
s32 ADXB_GetDecDtLen(s32 adxb);
s32 ADXB_GetDecNumSmpl(s32 adxb);
s32 ADXB_GetNumChan(s32 adxb);
void ADXB_Reset(s32 adxb);
void adxsjd_decexec_start(ObjADXSJD* o);
void adxsjd_decode_prep(ObjADXSJD* o);

typedef void (*AdxsjdOutFunc)(void* arg, s32 ch, void* addr, s32 size);

typedef struct ObjADXSJD {
	u8 used;               /* 0x00 */
	s8 stat;               /* 0x01 */
	u8 pad2[2];            /* 0x02 */
	s32 adxb;              /* 0x04 */
	CriStream* sj;         /* 0x08 */
	CriStream* sjo[2];     /* 0x0C */
	CriChunk chunk;        /* 0x14 */
	CriChunk ck[2];        /* 0x1C */
	s32 f2c;               /* 0x2C */
	s32 f30;               /* 0x30 */
	s32 f34;               /* 0x34 */
	s32 f38;               /* 0x38 */
	s32 f3c;               /* 0x3C */
	s32 f40;               /* 0x40 */
	s32 f44;               /* 0x44 */
	s32 f48;               /* 0x48 */
	s32 f4c;               /* 0x4C */
	AdxsjdOutFunc outfunc; /* 0x50 */
	void* outarg;          /* 0x54 */
	u8 pad58[0x40];        /* 0x58 */
	s32 f98;               /* 0x98 */
} ObjADXSJD;

static inline s32 sjd_dtlen(s32 a)
{
	return ADXB_GetDecDtLen(a);
}
static inline s32 sjd_adxb(ObjADXSJD* p)
{
	return p->adxb;
}
void ADXSJD_ExecHndl(ObjADXSJD* o)
{
	s32 stat;
	s32 adxb;
	s32 dtlen;
	s32 adxb2;
	CriStream* sj;
	s32 ax2;
	s32 total;
	s32 n;
	s32 limit;
	CriChunk rest;
	CriChunk consumed;
	s32 j;
	ObjADXSJD* ckcur;
	ObjADXSJD* sjocur;
	s32 nb;
	s16 fmt;

	stat = o->stat;
	if (stat == 2) {
		adxb = sjd_adxb(o);
		if (ADXB_GetStat(adxb) == 0) {
			adxsjd_decexec_start(o);
		}
		ADXB_ExecHndl(adxb);
		if (ADXB_GetStat(adxb) == 3) {
			adxb2 = o->adxb;
			sj    = o->sj;
			total = ADXB_GetTotalNumSmpl(adxb2);
			dtlen = sjd_dtlen(adxb2);
			n     = ADXB_GetDecNumSmpl(adxb2);
			limit = total - o->f34;
			if (n < limit) {
				limit = n;
			}
			fn_80221824(&o->chunk, dtlen, &consumed, &rest);
			sj->vtbl->put(sj, 0, &consumed);
			sj->vtbl->unget(sj, 1, &rest);
			nb     = limit * 2;
			ckcur  = o;
			sjocur = o;
			for (j = 0; j < ADXB_GetNumChan(o->adxb); j++) {
				fn_80221824((CriChunk*)((u8*)ckcur + 0x1C), nb, &consumed, &rest);
				if (o->outfunc != 0) {
					o->outfunc(o->outarg, j, consumed.addr, consumed.size);
				}
				((CriStream**)((u8*)sjocur + 0xC))[0]->vtbl->put(
				    ((CriStream**)((u8*)sjocur + 0xC))[0], 1, &consumed);
				((CriStream**)((u8*)sjocur + 0xC))[0]->vtbl->unget(
				    ((CriStream**)((u8*)sjocur + 0xC))[0], 0, &rest);
				ckcur  = (ObjADXSJD*)((u8*)ckcur + 8);
				sjocur = (ObjADXSJD*)((u8*)sjocur + 4);
			}
			o->f2c += limit;
			o->f30 += dtlen;
			o->f34 += limit;
			o->f40 += limit;
			o->f44 += dtlen;
			ADXB_Reset(adxb2);
		}
		fmt = *(s16*)((u8*)adxb + 0x98);
		if (fmt == 10)
			goto doit;
		if (fmt == 20)
			goto doit;
		if (fmt == 11)
			goto doit;
		if (fmt == 15)
			goto doit;
		goto donothing;
	doit:
		ax2   = o->adxb;
		total = ADXB_GetTotalNumSmpl(ax2);
		dtlen = ADXB_GetDecDtLen(ax2);
		n     = ADXB_GetDecNumSmpl(ax2);
		limit = total - o->f34;
		if (n < limit) {
			limit = n;
		}
		o->f2c += limit;
		o->f30 += dtlen;
		o->f34 += limit;
	donothing:;
	} else if (stat == 1) {
		adxsjd_decode_prep(o);
	}
}
}
