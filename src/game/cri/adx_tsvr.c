/*
 * adx_tsvr.c -- ADXT handle server: ExecHndl, adxt_stat_decinfo, trap entries.
 * .text   0x80219904-0x8021A77C (7 functions)
 * .rodata 0x8023E850-0x8023E8E6 (+2 bytes alignment padding to 0x8023E8E8)
 * .bss    0x804147A8-0x804147B4 (+4 bytes alignment padding to 0x804147B8)
 *
 * TU evidence: MKD adx_tsvr.o holds exactly ExecHndl .. adxt_trap_entry_lps in
 * this order; strings E02080842/E9081001/E8101201 and the adxt_dbg_* counters
 * are only used here; ADXT_GetStat/GetNumChan are called, not inlined. The
 * per-state helpers (PS2: adxt_stat_prep/playing/decend, ADXT_ExecRd*Chk) are
 * inlined into ExecHndl. CRI's Sint32 is long; that typing is load-bearing.
 */
#include "types.h"
typedef long Sint32;
#include "MSL_C/string.h"

typedef struct SJ_OBJ SJ_OBJ;
typedef SJ_OBJ* SJ;

typedef struct SJCK {
	s8* data;
	Sint32 len;
} SJCK;

typedef struct SJ_IF {
	void* obj0;
	void* obj4;
	void* obj8;
	void (*Destroy)(SJ sj);
	void* GetUuid;
	void (*Reset)(SJ sj);
	void (*GetChunk)(SJ sj, Sint32 id, Sint32 nbyte, SJCK* ck);
	void (*UngetChunk)(SJ sj, Sint32 id, SJCK* ck);
	void (*PutChunk)(SJ sj, Sint32 id, SJCK* ck);
	Sint32 (*GetNumData)(SJ sj, Sint32 id);
} SJ_IF;

struct SJ_OBJ {
	SJ_IF* vtbl;
};

typedef struct ADXT_OBJ {
	s8 used;           /* 0x00 */
	s8 stat;           /* 0x01 */
	s8 pmode;          /* 0x02 */
	s8 maxnch;         /* 0x03 */
	void* sjd;         /* 0x04 */
	void* stm;         /* 0x08 */
	void* rna;         /* 0x0C */
	SJ sjf;            /* 0x10 */
	SJ sji;            /* 0x14 */
	SJ sjo[2];         /* 0x18 */
	s8* ibuf;          /* 0x20 */
	Sint32 ibufbsize;  /* 0x24 */
	Sint32 ibufxsize;  /* 0x28 */
	s8* obuf;          /* 0x2C */
	Sint32 obufbsize;  /* 0x30 */
	Sint32 obufdist;   /* 0x34 */
	Sint32 svrfreq;    /* 0x38 */
	s16 maxsct;        /* 0x3C */
	s16 minsct;        /* 0x3E */
	s16 outvol;        /* 0x40 */
	s16 outpan[2];     /* 0x42 */
	s16 outbalance;    /* 0x46 */
	Sint32 maxdecsmpl; /* 0x48 */
	Sint32 lpcnt;      /* 0x4C */
	Sint32 lp_skiplen; /* 0x50 */
	Sint32 trp;        /* 0x54 */
	Sint32 wpos;       /* 0x58 */
	Sint32 mofst;      /* 0x5C */
	s16 ecode;         /* 0x60 */
	s16 pad62;         /* 0x62 */
	Sint32 edecpos;    /* 0x64 */
	s16 edeccnt;       /* 0x68 */
	s16 eshrtcnt;      /* 0x6A */
	s8 lpflg;          /* 0x6C */
	s8 autorcvr;       /* 0x6D */
	s8 fltmode;        /* 0x6E */
	s8 execflag;       /* 0x6F */
	s8 pstwait_flag;   /* 0x70 */
	s8 pstready_flag;  /* 0x71 */
	s8 pause_flag;     /* 0x72 */
	s8 pad73;          /* 0x73 */
	void* amp;         /* 0x74 */
	SJ ampsji[2];      /* 0x78 */
	SJ ampsjo[2];      /* 0x80 */
	Sint32 time_ofst;  /* 0x88 */
	Sint32 lesct;      /* 0x8C */
	Sint32 trpnsmpl;   /* 0x90 */
	void* lsc;         /* 0x94 */
	s8 lnkflg;         /* 0x98 */
	s8 pad99[3];       /* 0x99 */
	u32 tvofst;        /* 0x9C */
	Sint32 svcnt;      /* 0xA0 */
	Sint32 decofst;    /* 0xA4 */
	s8 stmstart;       /* 0xA8 */
	s8 padA9[3];       /* 0xA9 */
	char* fnbuf;       /* 0xAC */
	char* fname;       /* 0xB0 */
	void* dir;         /* 0xB4 */
	Sint32 ofst;       /* 0xB8 */
	Sint32 nsct;       /* 0xBC */
} ADXT_OBJ;

typedef ADXT_OBJ* ADXT;

extern Sint32 adxt_vsync_cnt; /* adxt_vsync_cnt */

extern void ADXERR_CallErrFunc1(const char* msg);
extern void ADXERR_CallErrFunc2(const char* msg1, const char* msg2);
extern void ADXERR_ItoA2(Sint32 no1, Sint32 no2, char* buf, Sint32 len);
extern Sint32 ADXSJD_GetStat(void* sjd);
extern Sint32 ADXSJD_GetNumChan(void* sjd);
extern Sint32 ADXSJD_GetBlkSmpl(void* sjd);
extern Sint32 ADXSJD_GetSfreq(void* sjd);
extern Sint32 ADXSJD_GetNumLoop(void* sjd);
extern Sint32 ADXSJD_GetLpEndOfst(void* sjd);
extern Sint32 ADXSJD_GetLpEndPos(void* sjd);
extern Sint32 ADXSJD_GetLpStartOfst(void* sjd);
extern Sint32 ADXSJD_GetLpStartPos(void* sjd);
extern Sint32 ADXSJD_GetTotalNumSmpl(void* sjd);
extern Sint32 ADXSJD_GetOutBps(void* sjd);
extern s16 ADXSJD_GetDefOutVol(void* sjd);
extern s16 ADXSJD_GetDefPan(void* sjd, Sint32 ch);
extern Sint32 ADXSJD_GetFormat(void* sjd);
extern void* ADXSJD_GetSpsdInfo(void* sjd);
extern Sint32 ADXSJD_GetDecNumSmpl(void* sjd);
extern void ADXSJD_SetMaxDecSmpl(void* sjd, Sint32 nsmpl);
extern void ADXSJD_SetTrapNumSmpl(void* sjd, Sint32 nsmpl);
extern void ADXSJD_SetTrapDtLen(void* sjd, Sint32 len);
extern void ADXSJD_SetTrapCnt(void* sjd, Sint32 cnt);
extern void ADXSJD_SetDecPos(void* sjd, Sint32 pos);
extern void ADXSJD_EntryTrapFunc(void* sjd, void (*func)(void*), void* obj);
extern void ADXSJD_TermSupply(void* sjd);
extern void ADXSJD_Stop(void* sjd);
extern void ADXSJD_Start(void* sjd);
extern void ADXSJD_ExecHndl(void* sjd);
extern void ADXSJD_RestoreSnapshot(void* sjd);
extern void ADXSJD_TakeSnapshot(void* sjd);
extern Sint32 ADXRNA_GetNumData(void* rna);
extern Sint32 ADXRNA_GetNumRoom(void* rna);
extern void ADXRNA_SetPlaySw(void* rna, Sint32 sw);
extern void ADXRNA_SetTransSw(void* rna, Sint32 sw);
extern void ADXRNA_SetBitPerSmpl(void* rna, Sint32 bps);
extern void ADXRNA_SetSfreq(void* rna, Sint32 sfreq);
extern void ADXRNA_SetNumChan(void* rna, Sint32 nch);
extern void ADXRNA_SetTotalNumSmpl(void* rna, Sint32 nsmpl);
extern void ADXRNA_SetOutVol(void* rna, Sint32 vol);
extern void ADXRNA_SetOutPan(void* rna, Sint32 ch, Sint32 pan);
extern void ADXRNA_SetStmHdInfo(void* rna, void* info);
extern void ADXAMP_SetSfreq(void* amp, Sint32 sfreq);
extern Sint32 ADX_DecodeFooter(s8* buf, Sint32 len, s16* ftrlen);
extern Sint32 ADX_ScanInfoCode(s8* buf, Sint32 len, s16* infolen);
extern void fn_80221824(SJCK* ck, Sint32 len, SJCK* ck1, SJCK* ck2);
extern Sint32 LSC_GetStat(void* lsc);

extern Sint32 ADXSTM_GetStat(void* stm);
extern void ADXSTM_SetEos(void* stm, Sint32 eos);
extern void ADXSTM_EntryEosFunc(void* stm, void (*func)(void*), void* obj);
extern Sint32 ADXSTM_Seek(void* stm, Sint32 pos);

extern Sint32 ADXT_GetNumChan(ADXT adxt);
extern Sint32 ADXT_GetStat(ADXT adxt);
extern void ADXT_GetTranspose(ADXT adxt, Sint32* transps, Sint32* detune);
extern void ADXT_SetTranspose(ADXT adxt, Sint32 transps, Sint32 detune);
extern void ADXT_Stop(ADXT adxt);
extern void adxt_start_stm(ADXT adxt, const char* fname, void* dir, Sint32 ofst, Sint32 nsct);

void adxt_stat_decinfo(ADXT adxt);
void adxt_nlp_trap_entry(void* obj);
void adxt_set_outpan(ADXT adxt);
void adxt_eos_entry(void* obj);
void adxt_trap_entry(void* obj);
void adxt_trap_entry_lps(void* obj);

Sint32 adxt_dbg_rna_ndata = 0;
Sint32 adxt_dbg_ndt       = 0;
Sint32 adxt_dbg_nch       = 0;

static inline void adxt_stat_prep(ADXT adxt)
{
	void* rna;
	void* sjd;
	Sint32 ndata;
	Sint32 nroom;
	Sint32 nch;
	Sint32 i;
	Sint32 len;
	SJ sj;
	SJCK ck;

	rna   = adxt->rna;
	sjd   = adxt->sjd;
	ndata = ADXRNA_GetNumData(rna);
	nroom = ADXRNA_GetNumRoom(rna);
	if (ndata >= adxt->maxdecsmpl * 2 || nroom <= ADXSJD_GetBlkSmpl(sjd)
	    || ADXSJD_GetStat(adxt->sjd) == 3) {
		if (adxt->pstwait_flag == 0) {
			if (adxt->pause_flag == 0) {
				ADXRNA_SetPlaySw(rna, 1);
				adxt->tvofst = 0;
				adxt->svcnt  = adxt_vsync_cnt;
			}
			adxt->stat = 3;
		}
		adxt->pstready_flag = 1;
	}
	if (ADXSJD_GetStat(adxt->sjd) == 3) {
		nch = ADXT_GetNumChan(adxt);
		len = adxt->maxdecsmpl * nch * 2;
		for (i = 0; i < nch; i++) {
			sj = adxt->sjo[i];
			sj->vtbl->GetChunk(sj, 0, len, &ck);
			memset(ck.data, 0, ck.len);
			sj->vtbl->PutChunk(sj, 1, &ck);
		}
	}
}

static inline void adxt_stat_playing(ADXT adxt)
{
	Sint32 nch;
	Sint32 i;

	if (ADXSJD_GetStat(adxt->sjd) == 3) {
		nch          = ADXSJD_GetNumChan(adxt->sjd);
		adxt_dbg_nch = nch;
		for (i = 0; i < nch; i++) {
			if ((adxt_dbg_ndt = adxt->sjo[i]->vtbl->GetNumData(adxt->sjo[i], 1)) >= 0x40) {
				break;
			}
		}
		if (i == nch) {
			ADXRNA_SetTransSw(adxt->rna, 0);
			adxt->stat = 4;
		}
	}
}

static inline void adxt_stat_decend(ADXT adxt)
{
	adxt_dbg_rna_ndata = ADXRNA_GetNumData(adxt->rna);
	if (ADXRNA_GetNumData(adxt->rna) <= 0) {
		ADXRNA_SetPlaySw(adxt->rna, 0);
		adxt->stat = 5;
	}
}

static inline void ADXT_ExecRdCompChk(ADXT adxt)
{
	if (adxt->stm != NULL && ADXT_GetStat(adxt) != 0) {
		switch (adxt->pmode) {
			case 0:
			case 1:
				if (ADXSTM_GetStat(adxt->stm) == 3) {
					ADXSJD_TermSupply(adxt->sjd);
				}
				break;
			case 2:
				ADXSJD_TermSupply(adxt->sjd);
				break;
			case 3:
				break;
		}
	}
}

static inline void ADXT_ExecRdErrChk(ADXT adxt)
{
	if (adxt->stm != NULL && ADXSTM_GetStat(adxt->stm) == 4) {
		adxt->ecode = -1;
		adxt->stat  = 6;
	}
	if (adxt->lsc != NULL && LSC_GetStat(adxt->lsc) == 3) {
		adxt->ecode = -1;
		adxt->stat  = 6;
	}
}

void ADXT_ExecHndl(ADXT adxt)
{
	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080842 ADXT_ExecHndl: parameter error");
		return;
	}
	if (adxt->stat == 3) {
		adxt_stat_playing(adxt);
	} else if (adxt->stat == 1) {
		adxt_stat_decinfo(adxt);
	} else if (adxt->stat == 2) {
		adxt_stat_prep(adxt);
	} else if (adxt->stat == 4) {
		adxt_stat_decend(adxt);
	}
	ADXT_ExecRdCompChk(adxt);
	ADXT_ExecRdErrChk(adxt);
}

void adxt_stat_decinfo(ADXT adxt)
{
	char buf[32];
	Sint32 transps;
	Sint32 detune;
	void* sjd;
	Sint32 sfreq;
	Sint32 nloop;
	Sint32 blksmpl;
	Sint32 lpeofst;
	Sint32 lesct;
	Sint32 nch;
	Sint32 nsmpl;
	Sint32 bps;
	void* info;

	sjd     = adxt->sjd;
	transps = 0;
	detune  = 0;
	if ((adxt->pmode == 0 || adxt->pmode == 1) && adxt->stmstart == 1) {
		if (ADXSTM_GetStat(adxt->stm) == 2) {
			return;
		}
		if (adxt->sjf != NULL) {
			adxt->sjf->vtbl->Reset(adxt->sjf);
		}
		adxt_start_stm(adxt, adxt->fname, adxt->dir, adxt->ofst, adxt->nsct);
		adxt->stmstart = 0;
	}
	if (ADXSJD_GetStat(sjd) != 2) {
		return;
	}
	nch = ADXSJD_GetNumChan(sjd);
	if (nch > adxt->maxnch) {
		ADXERR_ItoA2(nch, adxt->maxnch, buf, 16);
		ADXERR_CallErrFunc2("E9081001 adxt_stat_decinfo: can't play this number of channels", buf);
		ADXT_Stop(adxt);
		return;
	}
	sfreq = ADXSJD_GetSfreq(sjd);
	nloop = ADXSJD_GetNumLoop(sjd);
	if (nloop > 0) {
		adxt->maxdecsmpl = (sfreq / adxt->svrfreq) * 3;
	} else {
		adxt->maxdecsmpl = ((sfreq / adxt->svrfreq) * 3) / 2;
	}
	blksmpl          = ADXSJD_GetBlkSmpl(sjd) * 2;
	adxt->maxdecsmpl = blksmpl * ((adxt->maxdecsmpl + blksmpl) / blksmpl);
	ADXSJD_SetMaxDecSmpl(sjd, adxt->maxdecsmpl);
	if (nloop > 0) {
		if (adxt->pmode == 2) {
			adxt->lp_skiplen = 0;
		} else {
			lpeofst          = ADXSJD_GetLpEndOfst(sjd);
			adxt->lp_skiplen = 0x800 - lpeofst % 0x800;
			lesct            = (lpeofst + 0x7FF) / 0x800;
			adxt->lp_skiplen %= 0x800;
			adxt->lesct = lesct;
			ADXSTM_SetEos(adxt->stm, lesct);
			ADXSTM_EntryEosFunc(adxt->stm, (void (*)(void*))adxt_eos_entry, adxt);
		}
		ADXSJD_GetLpEndPos(sjd);
		adxt->trpnsmpl = ADXSJD_GetLpStartPos(sjd);
		ADXSJD_SetTrapNumSmpl(sjd, adxt->trpnsmpl);
		ADXSJD_SetTrapDtLen(sjd, 0);
		ADXSJD_SetTrapCnt(sjd, 0);
		ADXSJD_EntryTrapFunc(sjd, (void (*)(void*))adxt_trap_entry_lps, adxt);
	} else {
		if (adxt->stm != NULL) {
			ADXSTM_SetEos(adxt->stm, 0x7FFFFFFF);
		}
		ADXSJD_SetTrapNumSmpl(sjd, ADXSJD_GetTotalNumSmpl(sjd));
		ADXSJD_SetTrapDtLen(sjd, 0);
		ADXSJD_SetTrapCnt(sjd, 0);
		ADXSJD_EntryTrapFunc(sjd, (void (*)(void*))adxt_nlp_trap_entry, adxt);
	}
	sfreq = ADXSJD_GetSfreq(sjd);
	nch   = ADXSJD_GetNumChan(sjd);
	nsmpl = ADXSJD_GetTotalNumSmpl(sjd);
	bps   = ADXSJD_GetOutBps(sjd);
	ADXRNA_SetBitPerSmpl(adxt->rna, bps);
	ADXRNA_SetSfreq(adxt->rna, sfreq);
	ADXRNA_SetNumChan(adxt->rna, nch);
	ADXRNA_SetTotalNumSmpl(adxt->rna, nsmpl);
	ADXRNA_SetOutVol(adxt->rna, adxt->outvol + ADXSJD_GetDefOutVol(adxt->sjd));
	ADXT_GetTranspose(adxt, &transps, &detune);
	if (transps != 0 || detune != 0) {
		ADXT_SetTranspose(adxt, transps, detune);
	}
	adxt_set_outpan(adxt);
	if (adxt->amp != NULL) {
		ADXAMP_SetSfreq(adxt->amp, sfreq);
	}
	if (ADXSJD_GetFormat(sjd) == 2) {
		info = ADXSJD_GetSpsdInfo(sjd);
		ADXRNA_SetStmHdInfo(adxt->rna, info);
	}
	ADXRNA_SetTransSw(adxt->rna, 1);
	adxt->stat = 2;
}

void adxt_nlp_trap_entry(void* obj)
{
	ADXT adxt = (ADXT)obj;
	void* sjd = adxt->sjd;
	SJ sj     = adxt->sji;
	SJCK ck1;
	SJCK ck1r;
	SJCK ck2;
	SJCK ck2r;
	s16 len1;
	s16 len2;
	Sint32 st1;
	Sint32 st2;
	Sint32 skip;
	Sint32 skip2;

	if (adxt->lnkflg == 0) {
		return;
	}
	len2 = 0;
	sj->vtbl->GetChunk(sj, 1, 0x7FFFFFFF, &ck1);
	sj->vtbl->GetChunk(sj, 1, 0x7FFFFFFF, &ck2);
	if (ADX_DecodeFooter(ck1.data, ck1.len, &len1) != 0) {
		adxt->lnkflg = 0;
		sj->vtbl->UngetChunk(sj, 1, &ck2);
		sj->vtbl->UngetChunk(sj, 1, &ck1);
		return;
	}
	skip = len1;
	st1  = ADX_ScanInfoCode(ck1.data + len1, ck1.len - len1, &len1);
	if (st1 == 0) {
		st2 = -1;
	} else {
		st2 = ADX_ScanInfoCode(ck2.data, ck2.len, &len2);
	}
	skip += len1;
	skip2 = (s16)len2;
	if (st1 != 0 && st2 != 0) {
		sj->vtbl->UngetChunk(sj, 1, &ck2);
		sj->vtbl->UngetChunk(sj, 1, &ck1);
		adxt->lnkflg = 0;
		return;
	}
	if (st1 == 0) {
		sj->vtbl->UngetChunk(sj, 1, &ck2);
		fn_80221824(&ck1, skip, &ck1, &ck1r);
		sj->vtbl->PutChunk(sj, 0, &ck1);
		sj->vtbl->UngetChunk(sj, 1, &ck1r);
	} else {
		sj->vtbl->PutChunk(sj, 0, &ck1);
		fn_80221824(&ck2, skip2, &ck2, &ck2r);
		sj->vtbl->PutChunk(sj, 0, &ck2);
		sj->vtbl->UngetChunk(sj, 1, &ck2r);
	}
	adxt->decofst += ADXSJD_GetDecNumSmpl(sjd);
	ADXSJD_Stop(sjd);
	ADXSJD_Start(sjd);
	ADXSJD_ExecHndl(sjd);
	if (ADXSJD_GetStat(sjd) != 2) {
		adxt->lnkflg = 0;
		return;
	}
	ADXSJD_SetMaxDecSmpl(sjd, adxt->maxdecsmpl);
	ADXSJD_SetTrapNumSmpl(sjd, ADXSJD_GetTotalNumSmpl(sjd));
	ADXSJD_SetTrapDtLen(sjd, 0);
	ADXSJD_SetTrapCnt(sjd, 0);
}

void adxt_set_outpan(ADXT adxt)
{
	Sint32 defpan[2];
	Sint32 nch;
	Sint32 i;
	Sint32 pan;

	nch = ADXSJD_GetNumChan(adxt->sjd);
	for (i = 0; i < 2; i++) {
		defpan[i] = ADXSJD_GetDefPan(adxt->sjd, i);
	}
	if (nch == 1) {
		pan = adxt->outpan[0];
		if (pan == -128 && defpan[0] == -128) {
			ADXRNA_SetOutPan(adxt->rna, 0, 0);
		} else if (pan != -128 && defpan[0] == -128) {
			ADXRNA_SetOutPan(adxt->rna, 0, pan);
		} else if (pan == -128 && defpan[0] != -128) {
			ADXRNA_SetOutPan(adxt->rna, 0, defpan[0]);
		} else {
			ADXRNA_SetOutPan(adxt->rna, 0, pan + defpan[0]);
		}
		return;
	}
	pan = adxt->outpan[0];
	if (pan == -128 && defpan[0] == -128) {
		ADXRNA_SetOutPan(adxt->rna, 0, -15);
	} else if (pan != -128 && defpan[0] == -128) {
		ADXRNA_SetOutPan(adxt->rna, 0, pan);
	} else if (pan == -128 && defpan[0] != -128) {
		ADXRNA_SetOutPan(adxt->rna, 0, defpan[0]);
	} else {
		ADXRNA_SetOutPan(adxt->rna, 0, pan + defpan[0]);
	}
	pan = adxt->outpan[1];
	if (pan == -128 && defpan[1] == -128) {
		ADXRNA_SetOutPan(adxt->rna, 1, 15);
	} else if (pan != -128 && defpan[1] == -128) {
		ADXRNA_SetOutPan(adxt->rna, 1, pan);
	} else if (pan == -128 && defpan[1] != -128) {
		ADXRNA_SetOutPan(adxt->rna, 1, defpan[1]);
	} else {
		ADXRNA_SetOutPan(adxt->rna, 1, pan + defpan[1]);
	}
}

void adxt_eos_entry(void* obj)
{
	ADXT adxt = (ADXT)obj;
	void* stm = adxt->stm;
	void* sjd = adxt->sjd;
	Sint32 lpsofst;

	if (stm == NULL || sjd == NULL) {
		return;
	}
	lpsofst = ADXSJD_GetLpStartOfst(sjd);
	if (adxt->lpflg == 0) {
		ADXSJD_SetTrapNumSmpl(adxt->sjd, -1);
		ADXSTM_SetEos(adxt->stm, 0x7FFFFFFF);
	} else {
		ADXSTM_Seek(stm, lpsofst / 0x800);
	}
}

void adxt_trap_entry(void* obj)
{
	ADXT adxt = (ADXT)obj;
	void* sjd = adxt->sjd;
	SJ sj     = adxt->sji;
	SJCK ck;
	Sint32 lpspos;
	Sint32 lpsofst;
	Sint32 lpepos;

	lpspos  = ADXSJD_GetLpStartPos(sjd);
	lpsofst = ADXSJD_GetLpStartOfst(sjd);
	lpepos  = ADXSJD_GetLpEndPos(sjd);
	if (adxt->stm == NULL && adxt->lpflg == 0) {
		ADXSJD_SetTrapNumSmpl(adxt->sjd, -1);
		return;
	}
	sj->vtbl->GetChunk(sj, 1, adxt->lp_skiplen, &ck);
	if (ck.len < adxt->lp_skiplen) {
		ADXERR_CallErrFunc1("E8101201 adxt_trap_entry: not enough data");
	}
	sj->vtbl->PutChunk(sj, 0, &ck);
	ADXSJD_SetTrapCnt(sjd, 0);
	adxt->trpnsmpl = lpepos - lpspos;
	ADXSJD_SetTrapNumSmpl(sjd, lpepos - lpspos);
	ADXSJD_SetTrapDtLen(sjd, lpsofst);
	ADXSJD_SetDecPos(sjd, lpspos);
	if (adxt->pmode == 2) {
		sj->vtbl->Reset(sj);
		sj->vtbl->GetChunk(sj, 1, lpsofst, &ck);
		sj->vtbl->PutChunk(sj, 0, &ck);
	}
	ADXSJD_RestoreSnapshot(sjd);
	adxt->lpcnt++;
}

void adxt_trap_entry_lps(void* obj)
{
	ADXT adxt = (ADXT)obj;
	void* sjd = adxt->sjd;
	Sint32 lpspos;
	Sint32 lpsofst;
	Sint32 lpepos;

	lpspos  = ADXSJD_GetLpStartPos(sjd);
	lpsofst = ADXSJD_GetLpStartOfst(sjd);
	lpepos  = ADXSJD_GetLpEndPos(sjd);
	ADXSJD_TakeSnapshot(sjd);
	ADXSJD_SetTrapCnt(sjd, 0);
	adxt->trpnsmpl = lpepos - lpspos;
	ADXSJD_SetTrapNumSmpl(sjd, lpepos - lpspos);
	ADXSJD_SetTrapDtLen(sjd, lpsofst);
	ADXSJD_SetDecPos(sjd, lpspos);
	ADXSJD_EntryTrapFunc(sjd, (void (*)(void*))adxt_trap_entry, adxt);
}
