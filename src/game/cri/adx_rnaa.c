// CRI ADXRNA wrappers over AXRNA (adx_rnaa).
//
// .text 0x8021B37C..0x8021B5E8, nineteen one-call wrappers, no data.
// Boundary: identical function list and order in MKD adx_rnaa.o; each wraps
// one AXRNA entry of game/cri/axrna.c. adx_dcd5 (ADXB family) follows.

#include "types.h"

typedef struct AXRNA_OBJ AXRNA_OBJ;
typedef void (*AxrnaErrFn)(void* obj, const char* msg);

extern void fn_802234D0(AXRNA_OBJ* rna, s32 flag);        /* AXRNA_SetAdjsfreqFlg */
extern void fn_802234E8(AXRNA_OBJ* rna, void* hdinfo);    /* AXRNA_SetStmHdInfo */
extern s32 fn_802234E0(AXRNA_OBJ* rna, s32 nsmpl);        /* AXRNA_DiscardData */
extern void fn_802234F0(AXRNA_OBJ* rna, s32 bps);         /* AXRNA_SetBitPerSmpl */
extern void fn_80223500(AXRNA_OBJ* rna, s32 ch, s32 pan); /* AXRNA_SetOutPan */
extern void fn_802235B4(AXRNA_OBJ* rna, s32 vol);         /* AXRNA_SetOutVol */
extern void fn_80223660(AXRNA_OBJ* rna, s32 sfreq);       /* AXRNA_SetSfreq */
extern void fn_802237B4(AXRNA_OBJ* rna, s32 nch);         /* AXRNA_SetNumChan */
extern void fn_802237C4(void);                            /* AXRNA_ExecServer */
extern s32 fn_80223E78(AXRNA_OBJ* rna);                   /* AXRNA_GetNumRoom */
extern s32 fn_80223ED0(AXRNA_OBJ* rna);                   /* AXRNA_GetNumData */
extern void fn_80223F2C(AXRNA_OBJ* rna, s32 sw);          /* AXRNA_SetPlaySw */
extern void fn_802240CC(AXRNA_OBJ* rna, s32 sw);          /* AXRNA_SetTransSw */
extern void fn_802242CC(AXRNA_OBJ* rna);                  /* AXRNA_Destroy */
extern AXRNA_OBJ* fn_8022439C(void** sjo, s32 maxnch);    /* AXRNA_Create */
extern void fn_80224CB0(AxrnaErrFn func, void* obj);      /* AXRNA_EntryErrFunc */
extern void fn_80224B1C(void);                            /* AXRNA_Finish */
extern void fn_80224C3C(void);                            /* AXRNA_Init */

void ADXRNA_Init(void)
{
	fn_80224C3C();
}

void ADXRNA_Finish(void)
{
	fn_80224B1C();
}

void ADXRNA_EntryErrFunc(AxrnaErrFn func, void* obj)
{
	fn_80224CB0(func, obj);
}

AXRNA_OBJ* ADXRNA_Create(void** sjo, s32 maxnch, void* work)
{
	return fn_8022439C(sjo, maxnch);
}

void ADXRNA_Destroy(AXRNA_OBJ* rna)
{
	fn_80223F2C(rna, 0);
	fn_802240CC(rna, 0);
	fn_802242CC(rna);
}

void ADXRNA_SetTransSw(AXRNA_OBJ* rna, s32 sw)
{
	fn_802240CC(rna, sw);
}

void ADXRNA_SetPlaySw(AXRNA_OBJ* rna, s32 sw)
{
	fn_80223F2C(rna, sw);
}

s32 ADXRNA_GetNumData(AXRNA_OBJ* rna)
{
	return fn_80223ED0(rna);
}

s32 ADXRNA_GetNumRoom(AXRNA_OBJ* rna)
{
	return fn_80223E78(rna);
}

void ADXRNA_ExecServer(void)
{
	fn_802237C4();
}

void ADXRNA_SetNumChan(AXRNA_OBJ* rna, s32 nch)
{
	fn_802237B4(rna, nch);
}

void ADXRNA_SetSfreq(AXRNA_OBJ* rna, s32 sfreq)
{
	fn_80223660(rna, sfreq);
}

void ADXRNA_SetOutVol(AXRNA_OBJ* rna, s32 vol)
{
	fn_802235B4(rna, vol);
}

void ADXRNA_SetOutPan(AXRNA_OBJ* rna, s32 ch, s32 pan)
{
	fn_80223500(rna, ch, pan);
}

void ADXRNA_SetBitPerSmpl(AXRNA_OBJ* rna, s32 bps)
{
	fn_802234F0(rna, bps);
}

s32 ADXRNA_DiscardData(AXRNA_OBJ* rna, s32 nsmpl)
{
	return fn_802234E0(rna, nsmpl);
}

void ADXRNA_SetTotalNumSmpl(AXRNA_OBJ* rna, s32 nsmpl) { }

s32 ADXRNA_SetStmHdInfo(AXRNA_OBJ* rna, void* hdinfo)
{
	fn_802234E8(rna, hdinfo);
	return 0;
}

void ADXRNA_SetAdjsfreqFlg(AXRNA_OBJ* rna, s32 flag)
{
	fn_802234D0(rna, flag);
}
