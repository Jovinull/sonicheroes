/*
 * adx_xpnd.c -- ADXPD expander (PL2/stereo decode handles).
 * .text 0x8021A77C-0x8021ABC0 (16 functions)
 * .bss  0x804147B8-0x80414B7C (+4 bytes alignment padding to 0x80414B80)
 *
 * TU evidence: MKD adx_xpnd.o holds ADXPD_ExecHndl .. ADXPD_Init in this order
 * (this older build has no ADXPD_EntryPl2); adxpd_internal_error/adxpd_obj are
 * only used here; adx_mgc.c begins at 0x8021ABC0.
 * Build: GC/1.3.2, "-sdata 0 -sdata2 0 -str reuse,readonly -use_lmw_stmw on
 * -inline deferred". Functions are written in original (PS2) source order;
 * deferred mode emits them reversed, i.e. in DOL order.
 */
#include "types.h"
#include "MSL_C/string.h"

typedef struct ADXPD_OBJ {
	s32 used;      /* 0x00 */
	s32 id;        /* 0x04 */
	s32 mode;      /* 0x08 */
	s32 stat;      /* 0x0C */
	s32 ndecblk;   /* 0x10 */
	s32 nch;       /* 0x14 */
	s8* ibuf;      /* 0x18 */
	s32 nblk;      /* 0x1C */
	s16* obufl;    /* 0x20 */
	s16* obufr;    /* 0x24 */
	s16 dly[2][2]; /* 0x28 */
	s16 k0;        /* 0x30 */
	s16 k1;        /* 0x32 */
	s16 x;         /* 0x34 */
	s16 a;         /* 0x36 */
	s16 m;         /* 0x38 */
	s16 pad3A;     /* 0x3A */
} ADXPD_OBJ;

typedef ADXPD_OBJ* ADXPD;

extern s32 ADX_DecodeMono4(
    s8* ibuf, s32 nblk, s16* obuf, s16* dly, s16 k0, s16 k1, s16* x, s16 a, s16 m);
extern s32 ADX_DecodeSte4(s8* ibuf, s32 nblk, s16* obufl, s16* dlyl, s16* obufr, s16* dlyr, s16 k0,
    s16 k1, s16* x, s16 a, s16 m);
extern void ADX_GetCoefficient(s32 cof, s32 sfreq, s16* k0, s16* k1);

ADXPD_OBJ adxpd_obj[16]; /* uninitialised bss is laid out in reverse declaration order */
s32 adxpd_internal_error;

void ADXPD_ExecHndl(ADXPD xpd);
s32 ADXPD_GetNumBlk(ADXPD xpd);
void ADXPD_Reset(ADXPD xpd);
void ADXPD_Stop(ADXPD xpd);
void ADXPD_Start(ADXPD xpd);
s32 ADXPD_EntrySte(ADXPD xpd, s8* ibuf, s32 nblk, s16* obufl, s16* obufr);
s32 ADXPD_EntryMono(ADXPD xpd, s8* ibuf, s32 nblk, s16* obuf);
s32 ADXPD_GetStat(ADXPD xpd);
void ADXPD_Destroy(ADXPD xpd);
void ADXPD_GetExtPrm(ADXPD xpd, s16* x, s16* a, s16* m);
void ADXPD_SetExtPrm(ADXPD xpd, s16 x, s16 a, s16 m);
void ADXPD_GetDly(ADXPD xpd, s16* dlyl, s16* dlyr);
void ADXPD_SetDly(ADXPD xpd, s16* dlyl, s16* dlyr);
void ADXPD_SetCoef(ADXPD xpd, s32 sfreq, s32 cof);
ADXPD ADXPD_Create(void);
void ADXPD_Init(void);

void ADXPD_Init(void)
{
	memset(adxpd_obj, 0, sizeof(adxpd_obj));
}

ADXPD ADXPD_Create(void)
{
	s32 i;
	ADXPD xpd;

	for (i = 0; i < 16; i++) {
		if (adxpd_obj[i].used == 0) {
			break;
		}
	}
	if (i == 16) {
		return NULL;
	}
	xpd = &adxpd_obj[i];
	memset(xpd, 0, sizeof(ADXPD_OBJ));
	xpd->used = 1;
	xpd->id   = i;
	xpd->mode = 0;
	xpd->stat = 0;
	ADX_GetCoefficient(500, 44100, &xpd->k0, &xpd->k1);
	memset(xpd->dly, 0, sizeof(xpd->dly));
	return xpd;
}

void ADXPD_SetCoef(ADXPD xpd, s32 sfreq, s32 cof)
{
	ADX_GetCoefficient(cof, sfreq, &xpd->k0, &xpd->k1);
}

void ADXPD_SetDly(ADXPD xpd, s16* dlyl, s16* dlyr)
{
	xpd->dly[0][0] = dlyl[0];
	xpd->dly[0][1] = dlyr[0];
	xpd->dly[1][0] = dlyl[1];
	xpd->dly[1][1] = dlyr[1];
}

void ADXPD_GetDly(ADXPD xpd, s16* dlyl, s16* dlyr)
{
	dlyl[0] = xpd->dly[0][0];
	dlyr[0] = xpd->dly[0][1];
	dlyl[1] = xpd->dly[1][0];
	dlyr[1] = xpd->dly[1][1];
}

void ADXPD_SetExtPrm(ADXPD xpd, s16 x, s16 a, s16 m)
{
	xpd->x = x;
	xpd->a = a;
	xpd->m = m;
}

void ADXPD_GetExtPrm(ADXPD xpd, s16* x, s16* a, s16* m)
{
	*x = xpd->x;
	*a = xpd->a;
	*m = xpd->m;
}

void ADXPD_Destroy(ADXPD xpd)
{
	if (xpd != NULL) {
		xpd->used = 0;
		memset(xpd, 0, sizeof(ADXPD_OBJ));
	}
}

s32 ADXPD_GetStat(ADXPD xpd)
{
	return xpd->stat;
}

s32 ADXPD_EntryMono(ADXPD xpd, s8* ibuf, s32 nblk, s16* obuf)
{
	if (xpd->stat == 0) {
		xpd->nch   = 1;
		xpd->ibuf  = ibuf;
		xpd->nblk  = nblk;
		xpd->obufl = obuf;
		xpd->obufr = NULL;
		return 1;
	}
	return 0;
}

s32 ADXPD_EntrySte(ADXPD xpd, s8* ibuf, s32 nblk, s16* obufl, s16* obufr)
{
	if (xpd->stat == 0) {
		xpd->nch   = 2;
		xpd->ibuf  = ibuf;
		xpd->nblk  = nblk;
		xpd->obufl = obufl;
		xpd->obufr = obufr;
		return 1;
	}
	return 0;
}

void ADXPD_Start(ADXPD xpd)
{
	if (xpd->stat == 0) {
		xpd->ndecblk = 0;
		xpd->stat    = 1;
	}
}

void ADXPD_Stop(ADXPD xpd)
{
	xpd->stat = 0;
	memset(xpd->dly, 0, sizeof(xpd->dly));
}

void ADXPD_Reset(ADXPD xpd)
{
	if (xpd->stat == 3) {
		xpd->stat = 0;
	}
}

s32 ADXPD_GetNumBlk(ADXPD xpd)
{
	return xpd->ndecblk;
}

void ADXPD_ExecHndl(ADXPD xpd)
{
	if (xpd->stat == 1) {
		xpd->stat = 2;
	}
	if (xpd->stat == 2) {
		if (xpd->nch == 1) {
			xpd->ndecblk = ADX_DecodeMono4(xpd->ibuf, xpd->nblk, xpd->obufl, xpd->dly[0], xpd->k0,
			    xpd->k1, &xpd->x, xpd->a, xpd->m);
		} else {
			xpd->ndecblk = ADX_DecodeSte4(xpd->ibuf, xpd->nblk, xpd->obufl, xpd->dly[0], xpd->obufr,
			    xpd->dly[1], xpd->k0, xpd->k1, &xpd->x, xpd->a, xpd->m);
			if (xpd->ndecblk % 2 == 1) {
				adxpd_internal_error = 1;
			}
		}
		xpd->stat = 3;
	}
}
