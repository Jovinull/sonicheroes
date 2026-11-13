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
	s8 used;               /* 0x00 */
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

extern ObjADXSJD adxsjd_obj[16];

static inline void adxsjd_exechndl(ObjADXSJD* sjd)
{
	s16 fmt;
	s32 limit;
	CriStream* sj;
	s32 n;
	s32 adxb2;
	s32 dtlen;
	s32 total;
	CriChunk consumed;
	CriChunk rest;
	s32 adxb;
	s32 ax2;
	s32 j;
	s8 stat;

	stat = sjd->stat;
	if (stat == 2) {
		adxb = sjd->adxb;
		if (ADXB_GetStat(adxb) == 0) {
			adxsjd_decexec_start(sjd);
		}
		ADXB_ExecHndl(adxb);
		if (ADXB_GetStat(adxb) == 3) {
			adxb2 = sjd->adxb;
			sj    = sjd->sj;
			total = ADXB_GetTotalNumSmpl(adxb2);
			dtlen = ADXB_GetDecDtLen(adxb2);
			n     = ADXB_GetDecNumSmpl(adxb2);
			limit = (n < total - sjd->f34) ? n : total - sjd->f34;
			fn_80221824(&sjd->chunk, dtlen, &consumed, &rest);
			sj->vtbl->put(sj, 0, &consumed);
			sj->vtbl->unget(sj, 1, &rest);
			for (j = 0; j < ADXB_GetNumChan(sjd->adxb); j++) {
				fn_80221824(&sjd->ck[j], limit * 2, &consumed, &rest);
				if (sjd->outfunc != 0) {
					sjd->outfunc(sjd->outarg, j, consumed.addr, consumed.size);
				}
				sjd->sjo[j]->vtbl->put(sjd->sjo[j], 1, &consumed);
				sjd->sjo[j]->vtbl->unget(sjd->sjo[j], 0, &rest);
			}
			sjd->f2c += limit;
			sjd->f30 += dtlen;
			sjd->f34 += limit;
			sjd->f40 += limit;
			sjd->f44 += dtlen;
			ADXB_Reset(adxb2);
		}
		fmt = *(s16*)((u8*)adxb + 0x98);
		if (fmt != 10 && fmt != 20 && fmt != 11 && fmt != 15)
			return;
		ax2   = sjd->adxb;
		total = ADXB_GetTotalNumSmpl(ax2);
		dtlen = ADXB_GetDecDtLen(ax2);
		n     = ADXB_GetDecNumSmpl(ax2);
		limit = total - sjd->f34;
		if (n < limit) {
			limit = n;
		}
		sjd->f2c += limit;
		sjd->f30 += dtlen;
		sjd->f34 += limit;
	} else if (stat == 1) {
		adxsjd_decode_prep(sjd);
	}
}

void ADXSJD_ExecServer(void)
{
	s32 i;

	for (i = 0; i < 16; i++) {
		ObjADXSJD* sjd = &adxsjd_obj[i];

		if (sjd->used == 1) {
			adxsjd_exechndl(sjd);
		}
	}
}
}
