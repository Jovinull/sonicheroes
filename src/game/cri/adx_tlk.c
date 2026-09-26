/*
 * adx_tlk.c -- ADXT public API (8.84): SetOutputMono .. Create.
 * .text   0x80217BD8-0x80219778 (32 functions + 18 stripped, see below)
 * .rodata 0x8023E128-0x8023E7D0 (one pool: parameter-error strings of kept and
 *         linker-stripped functions interleaved with the f64/f32 constants)
 * .data   0x8029B790-0x8029B794 (+4 bytes alignment padding to 0x8029B798)
 * .bss    0x80414768-0x804147A4 (+4 bytes alignment padding to 0x804147A8)
 * adxt_obj/adxt_vsync_cnt (0x8040EEB8..) belong to an earlier unit.
 *
 * TU evidence: MKD adx_tlk.o holds InsertSilence .. Create in this order; the
 * PS2 symbol list (reverse order) puts ADXT_SetOutputMono and ADXT_SetKeyString
 * right before InsertSilence, and the pool starts with the SetKeyString
 * string. StartFname/StartAfs follow but call ADXT_Stop instead of inlining it
 * as StartSj/Destroy do, so they are a separate unit (adx_tlk2.c).
 * Stripped functions (pass with -s; only their strings survive, bodies are
 * minimal reconstructions): ADXT_SetKeyString, GetStatPause, IsReadyPlayStart,
 * SetWaitPlayStart, GetInputSj, SetLpFlg, GetLpCnt, IsCompleted, IsIbufSafety,
 * GetIbufRemainTime, GetNumSmplObuf, GetNumSctIbuf, SetReloadSct,
 * SetReloadTime, GetOutBalance, SetOutBalance, GetFmtBps, GetHdrLen, plus
 * ADXT_GetTimeSfreq2 (PS2 name, no string; inlined twice into ADXT_GetTime).
 * The literal pool (strings interleaved with compiler f32/f64 constants)
 * cannot be reproduced with string data declarations, so the stripped
 * functions stay as minimal bodies.
 * Six unreferenced bss words (0x80414774..0x80414788) are named after the MKD
 * server counters; only their count is evidenced.
 * Build: GC/1.3.2, "-sdata 0 -sdata2 0 -str reuse,readonly -use_lmw_stmw on
 * -inline deferred". Functions are written in original (PS2) source order;
 * deferred mode emits them reversed, i.e. in DOL order.
 */
#include "types.h"
#include "MSL_C/string.h"

typedef struct SJ_OBJ SJ_OBJ;
typedef SJ_OBJ* SJ;

typedef struct SJCK {
	s8* data;
	s32 len;
} SJCK;

typedef struct SJ_IF {
	void* obj0;
	void* obj4;
	void* obj8;
	void (*Destroy)(SJ sj);
	void* GetUuid;
	void (*Reset)(SJ sj);
	void (*GetChunk)(SJ sj, s32 id, s32 nbyte, SJCK* ck);
	void (*UngetChunk)(SJ sj, s32 id, SJCK* ck);
	void (*PutChunk)(SJ sj, s32 id, SJCK* ck);
	s32 (*GetNumData)(SJ sj, s32 id);
} SJ_IF;

struct SJ_OBJ {
	SJ_IF* vtbl;
};

typedef struct ADXT_OBJ {
	s8 used;          /* 0x00 */
	s8 stat;          /* 0x01 */
	s8 pmode;         /* 0x02 */
	s8 maxnch;        /* 0x03 */
	void* sjd;        /* 0x04 */
	void* stm;        /* 0x08 */
	void* rna;        /* 0x0C */
	SJ sjf;           /* 0x10 */
	SJ sji;           /* 0x14 */
	SJ sjo[2];        /* 0x18 */
	s8* ibuf;         /* 0x20 */
	s32 ibufbsize;    /* 0x24 */
	s32 ibufxsize;    /* 0x28 */
	s8* obuf;         /* 0x2C */
	s32 obufbsize;    /* 0x30 */
	s32 obufdist;     /* 0x34 */
	s32 svrfreq;      /* 0x38 */
	s16 maxsct;       /* 0x3C */
	s16 minsct;       /* 0x3E */
	s16 outvol;       /* 0x40 */
	s16 outpan[2];    /* 0x42 */
	s16 outbalance;   /* 0x46 */
	s32 maxdecsmpl;   /* 0x48 */
	s32 lpcnt;        /* 0x4C */
	s32 lp_skiplen;   /* 0x50 */
	s32 trp;          /* 0x54 */
	s32 wpos;         /* 0x58 */
	s32 mofst;        /* 0x5C */
	s16 ecode;        /* 0x60 */
	s16 pad62;        /* 0x62 */
	s32 edecpos;      /* 0x64 */
	s16 edeccnt;      /* 0x68 */
	s16 eshrtcnt;     /* 0x6A */
	s8 lpflg;         /* 0x6C */
	s8 autorcvr;      /* 0x6D */
	s8 fltmode;       /* 0x6E */
	s8 execflag;      /* 0x6F */
	s8 pstwait_flag;  /* 0x70 */
	s8 pstready_flag; /* 0x71 */
	s8 pause_flag;    /* 0x72 */
	s8 pad73;         /* 0x73 */
	void* amp;        /* 0x74 */
	SJ ampsji[2];     /* 0x78 */
	SJ ampsjo[2];     /* 0x80 */
	s32 time_ofst;    /* 0x88 */
	s32 lesct;        /* 0x8C */
	s32 trpnsmpl;     /* 0x90 */
	void* lsc;        /* 0x94 */
	s8 lnkflg;        /* 0x98 */
	s8 pad99[3];      /* 0x99 */
	u32 tvofst;       /* 0x9C */
	s32 svcnt;        /* 0xA0 */
	s32 decofst;      /* 0xA4 */
	s8 stmstart;      /* 0xA8 */
	s8 padA9[3];      /* 0xA9 */
	char* fnbuf;      /* 0xAC */
	char* fname;      /* 0xB0 */
	void* dir;        /* 0xB4 */
	s32 ofst;         /* 0xB8 */
	s32 nsct;         /* 0xBC */
} ADXT_OBJ;

typedef ADXT_OBJ* ADXT;

extern ADXT_OBJ adxt_obj[16]; /* adxt_obj */
extern s32 adxt_vsync_cnt;    /* adxt_vsync_cnt */

extern void ADXERR_CallErrFunc1(const char* msg);
extern void ADX_SetDecodeSteAsMonoSw(s32 flag);
extern void fn_80221824(SJCK* ck, s32 len, SJCK* ck1, SJCK* ck2);
extern s32 ADX_DecodeInfo(void* hdr, s32 len, s16* hdrlen, s8* type, s8* bps, s8* blklen, s8* nch,
    s32* sfreq, s32* nsmpl, s32* lpcnt);
extern s32 ADXSJD_GetDecNumSmpl(void* sjd);
extern s32 ADXRNA_DiscardData(void* rna, s32 nsmpl);
extern void ADXSJD_ExecServer(void);
extern void ADXT_ExecHndl(ADXT adxt);
extern void ADXRNA_ExecServer(void);
extern void ADXRNA_SetPlaySw(void* rna, s32 sw);
extern void ADXRNA_SetTransSw(void* rna, s32 sw);
extern s16 ADXSJD_GetDefOutVol(void* sjd);
extern void ADXRNA_SetOutVol(void* rna, s32 vol);
extern s16 ADXSJD_GetDefPan(void* sjd, s32 ch);
extern void ADXRNA_SetOutPan(void* rna, s32 ch, s32 pan);
extern s32 ADXSJD_GetNumChan(void* sjd);
extern s32 ADXSJD_GetSfreq(void* sjd);
extern s32 ADXSJD_GetTotalNumSmpl(void* sjd);
extern s32 ADXSJD_GetOutBps(void* sjd);
extern s32 ADXRNA_GetNumData(void* rna);
extern void fn_8021FAE4(void* lsc);
extern void ADXSJD_Stop(void* sjd);
extern void ADXAMP_Stop(void* amp);
extern void ADXSJD_SetInSj(void* sjd, SJ sj);
extern void ADXSJD_Start(void* sjd);
extern void ADXAMP_Start(void* amp);
extern void ADXRNA_Destroy(void* rna);
extern void ADXSJD_Destroy(void* sjd);
extern void fn_8021FF7C(void* lsc);
extern void ADXAMP_Destroy(void* amp);
extern void* ADXSJD_Create(SJ sj, s32 maxnch, SJ* sjo);
extern void* ADXRNA_Create(SJ* sjo, s32 maxnch, void* work);
extern SJ fn_80221300(void* buf, s32 bsize, s32 xsize);
extern void* LSC_Create(SJ sj);
extern void LSC_SetStmHndl(void* lsc, void* stm);
extern void ADXCRS_Lock(void);
extern void ADXCRS_Unlock(void);

extern void ADXSTM_SetBufSize(void* stm, s32 min, s32 max);
extern void ADXSTM_SetEos(void* stm, s32 eos);
extern void ADXSTM_EntryEosFunc(void* stm, void (*func)(void*), void* obj);
extern s32 ADXSTM_Seek(void* stm, s32 pos);
extern void ADXSTM_StopNw(void* stm);
extern void ADXSTM_ReleaseFileNw(void* stm);
extern void ADXSTM_BindFileNw(void* stm, const char* fname, void* dir, s32 ofst, s32 nsct);
extern s32 ADXSTM_Start(void* stm);
extern void ADXSTM_Destroy(void* stm);
extern void* ADXSTM_Create(SJ sj, s32 prio);

s32 adxt_time_mode               = 0;
s32 adxt_tsvr_enter_cnt          = 0;
u32 adxt_time_adjust_cnt         = 0;
u32 adxt_svrcnt                  = 0;
u32 adxt_svrcnt_sjd              = 0;
u32 adxt_svrcnt_rna              = 0;
u32 adxt_svrcnt_adxf             = 0;
u32 adxt_svrcnt_adxstm           = 0;
u32 adxt_svrcnt_hndl             = 0;
void (*ahxdetachfunc)(ADXT adxt) = NULL;
f32 adxt_diff_av                 = 0.0f;
s32 adxt_time_unit               = 0;
s32 adxt_mvtmp_d                 = 0;
s32 adxt_mviop_d                 = 0;
s32 adxt_mviop_f                 = 0;
u32 adxt_time_adjust_sw          = 1;

void ADXT_SetKeyString(ADXT adxt, const char* str);
void ADXT_SetOutputMono(s32 flag);
s32 ADXT_InsertSilence(ADXT adxt, s32 nch, s32 nsmpl);
s32 ADXT_IsEndcode(u8* buf, s32 bsize, s32* endsize);
s32 ADXT_IsHeader(u8* buf, s32 bsize, s32* hdrsize);
s32 ADXT_GetDecNumSmpl(ADXT adxt);
void ADXT_SetTimeOfst(ADXT adxt, s32 ofst);
s32 ADXT_DiscardSmpl(ADXT adxt, s32 nsmpl);
void ADXT_GetTranspose(ADXT adxt, s32* transps, s32* detune);
void ADXT_SetTranspose(ADXT adxt, s32 transps, s32 detune);
s32 ADXT_GetStatPause(ADXT adxt);
void ADXT_Pause(ADXT adxt, s32 sw);
s32 ADXT_IsReadyPlayStart(ADXT adxt);
void ADXT_SetWaitPlayStart(ADXT adxt, s32 flag);
SJ ADXT_GetInputSj(ADXT adxt);
void ADXT_SetLpFlg(ADXT adxt, s32 flg);
s32 ADXT_GetLpCnt(ADXT adxt);
void ADXT_ClearErrCode(ADXT adxt);
s32 ADXT_GetErrCode(ADXT adxt);
void ADXT_ExecServer(void);
s32 ADXT_IsCompleted(ADXT adxt);
void ADXT_SetAutoRcvr(ADXT adxt, s32 rcvr);
s32 ADXT_IsIbufSafety(ADXT adxt);
f32 ADXT_GetIbufRemainTime(ADXT adxt);
s32 ADXT_GetNumSmplObuf(ADXT adxt, s32 ch);
s32 ADXT_GetNumSctIbuf(ADXT adxt);
void ADXT_SetReloadSct(ADXT adxt, s32 minsct);
void ADXT_SetReloadTime(ADXT adxt, f32 time, s32 nch, s32 sfreq);
void ADXT_SetSvrFreq(ADXT adxt, s32 freq);
s32 ADXT_GetOutVol(ADXT adxt);
void ADXT_SetOutVol(ADXT adxt, s32 vol);
s32 ADXT_GetOutBalance(ADXT adxt);
void ADXT_SetOutBalance(ADXT adxt, s32 balance);
s32 ADXT_GetOutPan(ADXT adxt, s32 ch);
void ADXT_SetOutPan(ADXT adxt, s32 ch, s32 pan);
s32 ADXT_GetFmtBps(ADXT adxt);
s32 ADXT_GetHdrLen(ADXT adxt);
s32 ADXT_GetNumChan(ADXT adxt);
s32 ADXT_GetSfreq(ADXT adxt);
s32 ADXT_GetNumSmpl(ADXT adxt);
s32 ADXT_GetTimeReal(ADXT adxt);
void ADXT_GetTime(ADXT adxt, s32* ncount, s32* tscale);
void ADXT_GetTimeSfreq2(ADXT adxt, s32* ncount, s32* tscale);
s32 ADXT_GetStat(ADXT adxt);
void ADXT_Stop(ADXT adxt);
void ADXT_StopWithoutLsc(ADXT adxt);
void ADXT_StartSj(ADXT adxt, SJ sj);
void adxt_start_stm(ADXT adxt, const char* fname, void* dir, s32 ofst, s32 nsct);
void adxt_start_sj(ADXT adxt, SJ sj);
void ADXT_Destroy(ADXT adxt);
ADXT ADXT_Create(s32 maxnch, void* work, s32 worksize);

ADXT ADXT_Create(s32 maxnch, void* work, s32 worksize)
{
	s32 i;
	ADXT adxt;
	s8* wk;
	s32 wksize;
	s32 obufsize;

	wk     = (s8*)(((u32)work + 0x3F) & ~0x3F);
	wksize = worksize - (wk - (s8*)work);
	if (maxnch < 0 || work == NULL || worksize < 0) {
		ADXERR_CallErrFunc1("E02080804 ADXT_Create: parameter error");
		return NULL;
	}
	for (i = 0; i < 16; i++) {
		if (adxt_obj[i].used == 0) {
			break;
		}
	}
	if (i == 16) {
		return NULL;
	}
	adxt = &adxt_obj[i];
	memset(adxt, 0, sizeof(ADXT_OBJ));
	adxt->maxnch    = maxnch;
	obufsize        = (maxnch * 0x3060) << 1;
	adxt->ibuf      = wk + obufsize;
	adxt->ibufbsize = ((wksize - obufsize - 0x124) / 0x800) * 0x800;
	adxt->ibufxsize = 0x24;
	adxt->fnbuf     = (char*)(adxt->ibufbsize + adxt->ibufxsize + adxt->ibuf);
	adxt->obuf      = wk;
	adxt->obufbsize = 0x2000;
	adxt->obufdist  = 0x2060;
	adxt->sji       = NULL;
	adxt->sjf       = fn_80221300(adxt->ibuf, adxt->ibufbsize, adxt->ibufxsize);
	if (adxt->sjf == NULL) {
		ADXT_Destroy(adxt);
		return NULL;
	}
	if ((adxt->stm = ADXSTM_Create(adxt->sjf, 0)) == NULL) {
		ADXT_Destroy(adxt);
		return NULL;
	}
	for (i = 0; i < maxnch; i++) {
		adxt->sjo[i] = fn_80221300(adxt->obuf + adxt->obufdist * i * 2, adxt->obufbsize * 2,
		    (adxt->obufdist - adxt->obufbsize) * 2);
		if (adxt->sjo[i] == NULL) {
			ADXT_Destroy(adxt);
			return NULL;
		}
	}
	if ((adxt->sjd = ADXSJD_Create(adxt->sjf, maxnch, adxt->sjo)) == NULL) {
		ADXT_Destroy(adxt);
		return NULL;
	}
	if ((adxt->rna = ADXRNA_Create(adxt->sjo, maxnch, wk + maxnch * 0x40C0)) == NULL) {
		ADXT_Destroy(adxt);
		return NULL;
	}
	if ((adxt->lsc = LSC_Create(adxt->sjf)) == NULL) {
		ADXT_Destroy(adxt);
		return NULL;
	}
	LSC_SetStmHndl(adxt->lsc, adxt->stm);
	adxt->svrfreq = 60;
	adxt->maxsct  = adxt->ibufbsize / 0x800;
	adxt->minsct  = 0.85f * (f32)adxt->maxsct;
	adxt->outvol  = 0;
	for (i = 0; i < maxnch; i++) {
		adxt->outpan[i] = -128;
	}
	adxt->outbalance = 0;
	adxt->lpflg      = 1;
	adxt->trp        = 0;
	adxt->wpos       = 0;
	adxt->mofst      = 0;
	adxt->ecode      = 0;
	adxt->edecpos    = 0;
	adxt->edeccnt    = 0;
	adxt->eshrtcnt   = 0;
	adxt->autorcvr   = 1;
	adxt->pause_flag = 0;
	adxt->time_ofst  = 0;
	adxt->lnkflg     = 0;
	adxt->used       = 1;
	return adxt;
}

void ADXT_Destroy(ADXT adxt)
{
	void* p;
	SJ sj;
	s32 i;

	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080805 ADXT_Destroy: parameter error");
		return;
	}
	if (ahxdetachfunc != NULL) {
		ahxdetachfunc(adxt);
	}
	if (adxt->used == 1) {
		ADXT_Stop(adxt);
	}
	if (adxt->rna != NULL) {
		p         = adxt->rna;
		adxt->rna = NULL;
		ADXRNA_Destroy(p);
	}
	if (adxt->sjd != NULL) {
		p         = adxt->sjd;
		adxt->sjd = NULL;
		ADXSJD_Destroy(p);
	}
	p = adxt->stm;
	if (p != NULL) {
		adxt->stm = NULL;
		ADXSTM_EntryEosFunc(p, NULL, NULL);
		ADXSTM_Destroy(p);
	}
	if (adxt->lsc != NULL) {
		p         = adxt->lsc;
		adxt->lsc = NULL;
		fn_8021FF7C(p);
	}
	ADXCRS_Lock();
	if (adxt->sjf != NULL) {
		sj        = adxt->sjf;
		adxt->sjf = NULL;
		sj->vtbl->Destroy(sj);
	}
	for (i = 0; i < adxt->maxnch; i++) {
		if (adxt->sjo[i] != NULL) {
			sj           = adxt->sjo[i];
			adxt->sjo[i] = NULL;
			sj->vtbl->Destroy(sj);
		}
		if (adxt->ampsji[i] != NULL) {
			sj              = adxt->ampsji[i];
			adxt->ampsji[i] = NULL;
			sj->vtbl->Destroy(sj);
		}
		if (adxt->ampsjo[i] != NULL) {
			sj              = adxt->ampsjo[i];
			adxt->ampsjo[i] = NULL;
			sj->vtbl->Destroy(sj);
		}
	}
	if (adxt->amp != NULL) {
		p         = adxt->amp;
		adxt->amp = NULL;
		ADXAMP_Destroy(p);
	}
	memset(adxt, 0, sizeof(ADXT_OBJ));
	adxt->used = 0;
	ADXCRS_Unlock();
}

void adxt_start_sj(ADXT adxt, SJ sj)
{
	s32 i;

	for (i = 0; i < adxt->maxnch; i++) {
		adxt->sjo[i]->vtbl->Reset(adxt->sjo[i]);
	}
	ADXSJD_SetInSj(adxt->sjd, sj);
	adxt->sji = sj;
	ADXSJD_Start(adxt->sjd);
	adxt->stat          = 1;
	adxt->lpcnt         = 0;
	adxt->pstready_flag = 0;
	adxt->lesct         = 0x7FFFFFFF;
	adxt->trpnsmpl      = -1;
	adxt->tvofst        = 0;
	adxt->decofst       = 0;
	adxt->svcnt         = adxt_vsync_cnt;
	if (adxt->amp != NULL) {
		ADXAMP_Start(adxt->amp);
	}
}

void adxt_start_stm(ADXT adxt, const char* fname, void* dir, s32 ofst, s32 nsct)
{
	ADXSTM_SetBufSize(adxt->stm, adxt->minsct * 0x800, adxt->maxsct * 0x800);
	ADXSTM_SetEos(adxt->stm, 25);
	ADXSTM_EntryEosFunc(adxt->stm, NULL, NULL);
	ADXSTM_Seek(adxt->stm, 0);
	ADXSTM_StopNw(adxt->stm);
	ADXSTM_ReleaseFileNw(adxt->stm);
	ADXSTM_BindFileNw(adxt->stm, fname, dir, ofst, nsct);
	ADXSTM_Start(adxt->stm);
	adxt_start_sj(adxt, adxt->sjf);
}

void ADXT_StartSj(ADXT adxt, SJ sj)
{
	if (adxt == NULL || sj == NULL) {
		ADXERR_CallErrFunc1("E02080812 ADXT_StartSj: parameter error");
		return;
	}
	ADXT_Stop(adxt);
	ADXCRS_Lock();
	adxt_start_sj(adxt, sj);
	adxt->pmode  = 3;
	adxt->lnkflg = 1;
	ADXCRS_Unlock();
}

void ADXT_StopWithoutLsc(ADXT adxt)
{
	SJ sj;

	ADXCRS_Lock();
	ADXRNA_SetTransSw(adxt->rna, 0);
	ADXRNA_SetPlaySw(adxt->rna, 0);
	ADXSJD_Stop(adxt->sjd);
	if (adxt->pmode == 2 && adxt->sji != NULL) {
		sj        = adxt->sji;
		adxt->sji = NULL;
		sj->vtbl->Destroy(sj);
	}
	if (adxt->amp != NULL) {
		ADXAMP_Stop(adxt->amp);
	}
	adxt->sji      = NULL;
	adxt->stat     = 0;
	adxt->stmstart = 0;
	ADXCRS_Unlock();
}

void ADXT_Stop(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080813 ADXT_Stop: parameter error");
		return;
	}
	if (adxt->stm != NULL) {
		ADXSTM_ReleaseFileNw(adxt->stm);
	}
	ADXCRS_Lock();
	if (adxt->pmode == 4) {
		fn_8021FAE4(adxt->lsc);
		if (adxt->sji != NULL) {
			adxt->sji->vtbl->Reset(adxt->sji);
		}
	}
	ADXT_StopWithoutLsc(adxt);
	ADXCRS_Unlock();
}

s32 ADXT_GetStat(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080814 ADXT_GetStat: parameter error");
		return -1;
	}
	return adxt->stat;
}

/* stripped (PS2 name; inlined into ADXT_GetTime) */
void ADXT_GetTimeSfreq2(ADXT adxt, s32* ncount, s32* tscale)
{
	s32 decnsmpl;

	if (adxt->stat == 3 || adxt->stat == 4) {
		*tscale  = ADXSJD_GetSfreq(adxt->sjd);
		decnsmpl = ADXSJD_GetDecNumSmpl(adxt->sjd);
		*ncount  = adxt->decofst
		    + (decnsmpl - (ADXRNA_GetNumData(adxt->rna) + ADXT_GetNumSmplObuf(adxt, 0)));
	} else if (adxt->stat == 5) {
		*ncount = ADXSJD_GetTotalNumSmpl(adxt->sjd);
		*tscale = ADXSJD_GetSfreq(adxt->sjd);
		*ncount *= 16 / ADXSJD_GetOutBps(adxt->sjd);
		*ncount += adxt->decofst;
	} else {
		*ncount = 0;
		*tscale = 1;
	}
	*ncount += adxt->time_ofst;
}

void ADXT_GetTime(ADXT adxt, s32* ncount, s32* tscale)
{
	s32 n;
	s32 s;
	s32 mode;

	if (adxt == NULL || ncount == NULL || tscale == NULL) {
		ADXERR_CallErrFunc1("E02080815 ADXT_GetTime: parameter error");
		return;
	}
	if (adxt_time_mode == 0) {
		ADXT_GetTimeSfreq2(adxt, ncount, tscale);
		return;
	}
	adxt_diff_av = 0.0f;
	if (adxt->stat == 3 || adxt->stat == 4) {
		if (adxt->pause_flag == 0) {
			*ncount = adxt->tvofst + (adxt_vsync_cnt - adxt->svcnt) * 100;
		} else {
			*ncount = adxt->tvofst;
		}
		ADXT_GetTimeSfreq2(adxt, &n, &s);
		adxt_diff_av = 1000.0f * ((f32)n / (f32)s - (f32)*ncount / (f32)adxt_time_unit);
		if (adxt_diff_av > 60.0f || adxt_diff_av < -60.0f) {
			if (adxt_time_adjust_sw == 1) {
				mode           = adxt_time_mode;
				adxt_time_mode = 0;
				ADXT_GetTime(adxt, &n, &s);
				adxt_time_mode = mode;
				adxt_time_adjust_cnt++;
			}
			adxt->tvofst = (f32)adxt_time_unit * ((f32)n / (f32)s);
			adxt->svcnt  = adxt_vsync_cnt;
		}
	} else if (adxt->stat == 5) {
		n = ADXSJD_GetTotalNumSmpl(adxt->sjd);
		s = ADXSJD_GetSfreq(adxt->sjd);
		n *= 16 / ADXSJD_GetOutBps(adxt->sjd);
		*ncount = (s32)((f32)adxt_time_unit * ((f32)n / (f32)s));
		*ncount += adxt->tvofst + 1;
	} else {
		*ncount = 0;
	}
	*ncount += adxt->time_ofst;
	*tscale = adxt_time_unit;
}

s32 ADXT_GetTimeReal(ADXT adxt)
{
	s32 ncount;
	s32 tscale;

	ADXT_GetTime(adxt, &ncount, &tscale);
	return 100.0f * ((f32)ncount / (f32)tscale);
}

s32 ADXT_GetNumSmpl(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080817 ADXT_GetNumSmpl: parameter error");
		return -1;
	}
	if (adxt->stat >= 2) {
		return ADXSJD_GetTotalNumSmpl(adxt->sjd);
	}
	return 0;
}

s32 ADXT_GetSfreq(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080819 ADXT_GetSfreq: parameter error");
		return -1;
	}
	if (adxt->stat >= 2) {
		return ADXSJD_GetSfreq(adxt->sjd);
	}
	return 0;
}

s32 ADXT_GetNumChan(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080820 ADXT_GetNumChan: parameter error");
		return -1;
	}
	if (adxt->stat >= 2) {
		return ADXSJD_GetNumChan(adxt->sjd);
	}
	return 0;
}

/* stripped */
s32 ADXT_GetHdrLen(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080822 ADXT_GetHdrLen: parameter error");
		return -1;
	}
	return 0;
}

/* stripped */
s32 ADXT_GetFmtBps(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080821 ADXT_GetFmtBps: parameter error");
		return -1;
	}
	return 0;
}

void ADXT_SetOutPan(ADXT adxt, s32 ch, s32 pan)
{
	s16 defpan;

	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080825 ADXT_SetOutPan: parameter error");
		return;
	}
	defpan = ADXSJD_GetDefPan(adxt->sjd, ch);
	if ((s16)defpan == -128) {
		defpan = 0;
	}
	adxt->outpan[ch] = pan + (s16)defpan;
	if (ch < adxt->maxnch) {
		ADXRNA_SetOutPan(adxt->rna, ch, pan);
	} else {
		ADXERR_CallErrFunc1("E8101208 ADXT_SetOutPan: parameter error");
	}
}

s32 ADXT_GetOutPan(ADXT adxt, s32 ch)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080826 ADXT_GetOutPan: parameter error");
		return 0;
	}
	return adxt->outpan[ch];
}

/* stripped */
void ADXT_SetOutBalance(ADXT adxt, s32 balance)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080870 ADXT_SetOutBalance: parameter error");
		return;
	}
	adxt->outbalance = balance;
}

/* stripped */
s32 ADXT_GetOutBalance(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080871 ADXT_GetOutBalance: parameter error");
		return 0;
	}
	return adxt->outbalance;
}

void ADXT_SetOutVol(ADXT adxt, s32 vol)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080823 ADXT_SetOutVol: parameter error");
		return;
	}
	adxt->outvol = vol;
	ADXRNA_SetOutVol(adxt->rna, adxt->outvol + ADXSJD_GetDefOutVol(adxt->sjd));
}

s32 ADXT_GetOutVol(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080824 ADXT_GetOutVol: parameter error");
		return 0;
	}
	return adxt->outvol;
}

void ADXT_SetSvrFreq(ADXT adxt, s32 freq)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080840 ADXT_SetSvrFreq: parameter error");
		return;
	}
	adxt->svrfreq = freq;
}

/* stripped */
void ADXT_SetReloadTime(ADXT adxt, f32 time, s32 nch, s32 sfreq)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080838 ADXT_SetReloadTime: parameter error");
		return;
	}
	adxt->minsct = adxt->maxsct - (s32)(time * (f32)(nch * sfreq));
}

/* stripped */
void ADXT_SetReloadSct(ADXT adxt, s32 minsct)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080839 ADXT_SetReloadSct: parameter error");
		return;
	}
	adxt->minsct = minsct;
}

/* stripped */
s32 ADXT_GetNumSctIbuf(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080834 ADXT_GetNumSctIbuf: parameter error");
		return -1;
	}
	return adxt->sjf->vtbl->GetNumData(adxt->sjf, 1) / 0x800;
}

/* stripped */
s32 ADXT_GetNumSmplObuf(ADXT adxt, s32 ch)
{
	SJ sj;

	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080837 ADXT_GetNumSmplObuf: parameter error");
		return -1;
	}
	sj = adxt->sjo[ch];
	if (sj != NULL) {
		return sj->vtbl->GetNumData(sj, 1) / 2;
	}
	return 0;
}

/* stripped */
f32 ADXT_GetIbufRemainTime(ADXT adxt)
{
	s32 nch;
	s32 sfreq;

	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080835 ADXT_GetIbufRemainTime: parameter error");
		return -1.0f;
	}
	if (ADXT_GetStat(adxt) < 2) {
		return 0.0f;
	}
	nch   = ADXT_GetNumChan(adxt);
	sfreq = ADXT_GetSfreq(adxt);
	return (f32)adxt->ibufbsize / (f32)(nch * sfreq);
}

/* stripped */
s32 ADXT_IsIbufSafety(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080836 ADXT_IsIbufSafety: parameter error");
		return 0;
	}
	return (f32)adxt->ibufbsize > 0.0f;
}

void ADXT_SetAutoRcvr(ADXT adxt, s32 rcvr)
{
	adxt->autorcvr = rcvr;
}

/* stripped */
s32 ADXT_IsCompleted(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080802 ADXT_IsCompleted: parameter error");
		return -1;
	}
	return adxt->stat == 5;
}

void ADXT_ExecServer(void)
{
	s32 i;

	ADXCRS_Lock();
	if (adxt_tsvr_enter_cnt != 0) {
		ADXCRS_Unlock();
		return;
	}
	adxt_tsvr_enter_cnt = 1;
	ADXCRS_Unlock();
	ADXCRS_Lock();
	ADXSJD_ExecServer();
	adxt_tsvr_enter_cnt = 2;
	for (i = 0; i < 16; i++) {
		if (adxt_obj[i].used == 1) {
			ADXT_ExecHndl(&adxt_obj[i]);
		}
	}
	adxt_tsvr_enter_cnt = 3;
	ADXRNA_ExecServer();
	adxt_tsvr_enter_cnt = 0;
	ADXCRS_Unlock();
}

s32 ADXT_GetErrCode(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080843 ADXT_GetErrCode: parameter error");
		return -1;
	}
	return adxt->ecode;
}

void ADXT_ClearErrCode(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080844 ADXT_ClearErrCode: parameter error");
		return;
	}
	adxt->ecode    = 0;
	adxt->edecpos  = 0;
	adxt->edeccnt  = 0;
	adxt->eshrtcnt = 0;
}

/* stripped */
s32 ADXT_GetLpCnt(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080829 ADXT_GetLpCnt: parameter error");
		return -1;
	}
	return adxt->lpcnt;
}

/* stripped */
void ADXT_SetLpFlg(ADXT adxt, s32 flg)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080828 ADXT_SetLpFlg: parameter error");
		return;
	}
	adxt->lpflg = flg;
}

/* stripped */
SJ ADXT_GetInputSj(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080833 ADXT_GetInputSj: parameter error");
		return NULL;
	}
	return adxt->sji;
}

/* stripped */
void ADXT_SetWaitPlayStart(ADXT adxt, s32 flag)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080830 ADXT_SetWaitPlayStart: parameter error");
		return;
	}
	adxt->pstwait_flag = flag;
}

/* stripped */
s32 ADXT_IsReadyPlayStart(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080831 ADXT_IsReadyPlayStart: parameter error");
		return -1;
	}
	return adxt->pstready_flag;
}

void ADXT_Pause(ADXT adxt, s32 sw)
{
	s32 stat;
	s32 ncount;
	s32 tscale;
	s32 mode;

	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080846 ADXT_Pause: parameter error");
		return;
	}
	stat = adxt->stat;
	if (sw == adxt->pause_flag) {
		return;
	}
	ADXCRS_Lock();
	adxt->pause_flag = sw;
	if (stat == 3 || stat == 4) {
		if (sw == 1) {
			ADXRNA_SetPlaySw(adxt->rna, 0);
		} else {
			ADXRNA_SetPlaySw(adxt->rna, 1);
			adxt->svcnt = adxt_vsync_cnt;
		}
		mode           = adxt_time_mode;
		adxt_time_mode = 0;
		ADXT_GetTime(adxt, &ncount, &tscale);
		adxt_time_mode = mode;
		adxt->tvofst   = (f32)adxt_time_unit * ((f32)ncount / (f32)tscale);
	}
	ADXCRS_Unlock();
}

/* stripped */
s32 ADXT_GetStatPause(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080847 ADXT_GetStatPause: parameter error");
		return 0;
	}
	return adxt->pause_flag;
}

void ADXT_SetTranspose(ADXT adxt, s32 transps, s32 detune) { }

void ADXT_GetTranspose(ADXT adxt, s32* transps, s32* detune) { }

s32 ADXT_DiscardSmpl(ADXT adxt, s32 nsmpl)
{
	s32 n;
	s32 ncount;
	s32 tscale;
	s32 mode;

	if (adxt->pause_flag == 0) {
		return 0;
	}
	n = ADXRNA_DiscardData(adxt->rna, nsmpl);
	ADXT_ExecServer();
	mode           = adxt_time_mode;
	adxt_time_mode = 0;
	ADXT_GetTime(adxt, &ncount, &tscale);
	adxt_time_mode = mode;
	adxt->tvofst   = (f32)adxt_time_unit * ((f32)ncount / (f32)tscale);
	adxt->svcnt    = adxt_vsync_cnt;
	return n;
}

void ADXT_SetTimeOfst(ADXT adxt, s32 ofst)
{
	adxt->time_ofst = ofst;
}

s32 ADXT_GetDecNumSmpl(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080818 ADXT_GetDecNumSmpl: parameter error");
		return -1;
	}
	return ADXSJD_GetDecNumSmpl(adxt->sjd);
}

s32 ADXT_IsHeader(u8* buf, s32 bsize, s32* hdrsize)
{
	s16 hdrlen;
	s8 type;
	s8 bps;
	s8 blklen;
	s8 nch;
	s32 sfreq;
	s32 nsmpl;
	s32 lpcnt;

	if (bsize < 2) {
		return 0;
	}
	if (*(u16*)buf != 0x8000) {
		return 0;
	}
	if (ADX_DecodeInfo(buf, bsize, &hdrlen, &type, &bps, &blklen, &nch, &sfreq, &nsmpl, &lpcnt)
	    < 0) {
		return 0;
	}
	*hdrsize = hdrlen;
	return 1;
}

s32 ADXT_IsEndcode(u8* buf, s32 bsize, s32* endsize)
{
	if (bsize < 2) {
		return 0;
	}
	if (*(u16*)buf != 0x8001) {
		return 0;
	}
	*endsize = bsize;
	return 1;
}

s32 ADXT_InsertSilence(ADXT adxt, s32 nch, s32 nsmpl)
{
	s32 blksize;
	s32 nbyte;
	SJ sj;
	s32 len1;
	s32 len2;
	SJCK ck;
	SJCK ck2;

	sj = adxt->sji;
	if (adxt->sji == NULL) {
		return 0;
	}
	blksize = nch * 18;
	nbyte   = (nsmpl / 32) * blksize;
	sj->vtbl->GetChunk(sj, 0, nbyte, &ck);
	len1 = blksize * (ck.len / blksize);
	memset(ck.data, 0, len1);
	fn_80221824(&ck, len1, &ck, &ck2);
	sj->vtbl->PutChunk(sj, 1, &ck);
	sj->vtbl->UngetChunk(sj, 0, &ck2);
	nbyte -= len1;
	sj->vtbl->GetChunk(sj, 0, nbyte, &ck);
	len2 = blksize * (ck.len / blksize);
	memset(ck.data, 0, len2);
	fn_80221824(&ck, len2, &ck, &ck2);
	sj->vtbl->PutChunk(sj, 1, &ck);
	sj->vtbl->UngetChunk(sj, 0, &ck2);
	return ((len1 + len2) / blksize) * 32;
}

void ADXT_SetOutputMono(s32 flag)
{
	ADX_SetDecodeSteAsMonoSw(flag);
}

/* stripped: only its parameter-error literal survives (first string of the pool) */
void ADXT_SetKeyString(ADXT adxt, const char* str)
{
	if (adxt == NULL || str == NULL) {
		ADXERR_CallErrFunc1("E02080860 ADXT_SetKeyString: parameter error");
		return;
	}
}
