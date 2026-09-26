// adx_lsc: ADXT seamless-loop (LSC) entry points.
// .text 0x8021389C-0x80213A5C (5 functions), .rodata 0x8023DFE0-0x8023E0DE.
// Boundary: PS2 symbols group these under adx_lsc (with ADXT_EntryAfs,
// ADXT_StartFnameLp, ADXT_ReleaseSeamless that GC strips); all six strings are
// ADXT_* parameter errors of this file and sit between adx_errs' " " and
// adx_sje's "(c)CRI". Not present in MKD.
// ADXT_StartFnameLp is stripped from the DOL (pass -s ADXT_StartFnameLp); its
// inlined calls are what order the pool EntryFname, StartSeamless,
// SetSeamlessLp after GetNumFiles.

#include "types.h"

typedef struct SjObj SjObj;
typedef struct SjIf {
	void* qi;
	void* addref;
	void* release;
	void* destroy;
	void* getuuid;
	void (*Reset)(SjObj* sj);
} SjIf;
struct SjObj {
	SjIf* vtbl;
};

typedef struct LscObj LscObj;

typedef struct AdxtObj {
	s8 used;
	s8 stat;
	s8 pstat;
	u8 pad03[0x10 - 0x03];
	SjObj* sjf;
	SjObj* sji;
	u8 pad18[0x3E - 0x18];
	s16 maxsct;
	u8 pad40[0x94 - 0x40];
	LscObj* lsc;
	s8 lpflg;
} AdxtObj;

extern void ADXERR_CallErrFunc1(const char* msg);
extern void ADXERR_CallErrFunc2(const char* msg1, const char* msg2);
extern void ADXCRS_Lock(void);
extern void ADXCRS_Unlock(void);
extern void ADXT_StopWithoutLsc(AdxtObj* adxt);
extern void adxt_start_sj(AdxtObj* adxt, SjObj* sj);
extern void LSC_ResetEntry(LscObj* lsc);
extern s32 LSC_GetNumStm(LscObj* lsc);
extern void LSC_SetLpFlg(LscObj* lsc, s32 flg);
extern void LSC_SetFlowLimit(LscObj* lsc, s32 min);
extern void fn_8021FBA0(LscObj* lsc); /* LSC_Start */
extern s32 LSC_EntryFname(LscObj* lsc, const char* fname);

void ADXT_EntryFname(AdxtObj* adxt, const char* fname)
{
	LscObj* lsc = adxt->lsc;

	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080848 ADXT_EntryFname: parameter error");
		return;
	}
	if (LSC_EntryFname(lsc, fname) < 0) {
		ADXERR_CallErrFunc2("E0010601:Can't entry file ", fname);
	}
}

void ADXT_StartSeamless(AdxtObj* adxt)
{
	LscObj* lsc = adxt->lsc;

	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080850 ADXT_StartSeamless: parameter error");
		return;
	}
	ADXT_StopWithoutLsc(adxt);
	ADXCRS_Lock();
	adxt_start_sj(adxt, adxt->sjf);
	adxt->sji->vtbl->Reset(adxt->sji);
	adxt->pstat = 4;
	LSC_SetFlowLimit(lsc, adxt->maxsct << 11);
	fn_8021FBA0(lsc);
	adxt->lpflg = 1;
	ADXCRS_Unlock();
}

void ADXT_SetSeamlessLp(AdxtObj* adxt, s32 flg)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080851 ADXT_SetSeamlessLp: parameter error");
		return;
	}
	LSC_SetLpFlg(adxt->lsc, flg);
}

/* Stripped from the DOL; its inlined copies of the three calls below place
 * their strings ahead of theirs in the pool. */
void ADXT_StartFnameLp(AdxtObj* adxt, const char* fname)
{
	ADXT_EntryFname(adxt, fname);
	ADXT_StartSeamless(adxt);
	ADXT_SetSeamlessLp(adxt, 1);
}

s32 ADXT_GetNumFiles(AdxtObj* adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080854 ADXT_GetNumFiles: parameter error");
		return -1;
	}
	return LSC_GetNumStm(adxt->lsc);
}

void ADXT_ResetEntry(AdxtObj* adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080849 ADXT_ResetEntry: parameter error");
		return;
	}
	if (adxt->stat == 0) {
		LSC_ResetEntry(adxt->lsc);
	}
}
