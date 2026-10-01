// CRI ADX stream controller (ADXSTM): reads a file through CVFS into a CRI
// stream joint, 40 handles of 0x5C shared between real-time and normal slots.
//
// Unit: .text 0x80216758-0x80217BD8 (27 functions, ADXSTM_GetReadFlg ..
// ADXSTM_Init), .rodata 0x8023E0F8-0x8023E121, .data 0x8029B780-0x8029B78C,
// .bss 0x804138F8-0x80414768.
//
// Boundary evidence:
//   The .rodata holds only "E02110501 adxstmf_stat_exec: can't open ", the
//   ADXSTMF_ExecHndl open-failure message. MKD's adx_stmc.o follows adx_sje.o,
//   and the PS2 ADXSTM symbol list gives the source order; the GC text here is
//   exactly its reverse with unused functions removed, running from
//   ADXSTM_GetReadFlg down to ADXSTM_Init. The next function, 0x80217BD8,
//   opens the following ADXT unit (adx_tlk in MKD's object order).
//   Data ownership: rtim_num/nrml_ofst/nrml_num (.data) and rtim_ofst (.bss) are
//   used only by ADXSTM_Create; the exec-server flag and adxstmf_obj by the
//   server, Stop/ReleaseFile/BindFile/Destroy/Create/Init; the retry count and
//   the SJ error counter only by adxstmf_stat_exec.
//
// Build: C, GC/1.3.2, extra flags -sdata 0 -sdata2 0 -str reuse,readonly
// -use_lmw_stmw on -inline deferred (functions emitted in reverse source
// order). ADXSTM_ExecServer, ADXSTM_Seek and the Stop/Release/Bind helpers are
// inlined into their callers.

#include "types.h"
#include "MSL_C/string.h"
#include "cri/sj.h"

typedef struct ADXSTM {
	s8 used;                /* 0x00 */
	s8 stat;                /* 0x01 */
	s8 rdflg;               /* 0x02 */
	s8 rtry;                /* 0x03 */
	CriStream* sj;          /* 0x04 */
	void* cvfs;             /* 0x08 */
	s32 ofst;               /* 0x0C */
	s32 fsize;              /* 0x10 */
	s32 maxsize;            /* 0x14 */
	s32 minsize;            /* 0x18 */
	s32 rqsct;              /* 0x1C */
	CriChunk rqck;          /* 0x20 */
	s32 maxrqsct;           /* 0x28 */
	s32 eos;                /* 0x2C */
	s32 trnbyte;            /* 0x30 */
	void (*eosfunc)(void*); /* 0x34 */
	void* eosobj;           /* 0x38 */
	s32 sjbufsize;          /* 0x3C */
	s8 pause;               /* 0x40 */
	s8 bindreq;             /* 0x41 */
	s8 relreq;              /* 0x42 */
	s8 startreq;            /* 0x43 */
	s8 stopreq;             /* 0x44 */
	s8 opened;              /* 0x45 */
	s8 pad46[2];            /* 0x46 */
	s32 unk48;              /* 0x48 */
	const char* fname;      /* 0x4C */
	void* dir;              /* 0x50 */
	s32 pos;                /* 0x54 */
	s32 maxsct;             /* 0x58 */
} ADXSTM;

extern void cvFsStopTr(void* cvfs);
extern s32 fn_802218A8(s32* flag);
extern void fn_802229AC(void);
extern void fn_8022291C(void);
extern void ADXCRS_Lock(void);
extern void ADXCRS_Unlock(void);
void ADXSTMF_ExecHndl(ADXSTM* stm);
void ADXSTM_ExecServer(void);
extern s32 cvFsGetStat(void* cvfs);
extern s32 cvFsReqRd(void* cvfs, s32 nsct, void* buf);
extern s32 cvFsSeek(void* cvfs, s32 ofst, s32 whence);
extern s32 cvFsTell(void* cvfs);
extern void cvFsClose(void* cvfs);
extern void* cvFsOpen(const char* fname, void* dir, s32 mode);
extern void ADXERR_CallErrFunc2(const char* msg1, const char* msg2);

s32 adxstmf_rtim_ofst            = 0;
s32 adxstmf_rtim_num             = 16;
s32 adxstmf_nrml_ofst            = 16;
s32 adxstmf_nrml_num             = 24;
s32 adxstmf_execsvr_flg          = 0;
s32 adxstmf_num_rtry             = 0;
s32 adxstm_sj_internal_error_cnt = 0;
ADXSTM adxstmf_obj[40];

static inline void adxstm_StopNw(ADXSTM* stm)
{
	fn_802229AC();
	if (stm->stat == 2 && stm->rdflg == 1) {
		stm->stopreq = 1;
		if (stm->startreq == 1) {
			stm->startreq = 0;
		}
	} else {
		stm->stat = 1;
	}
	fn_8022291C();
}
static inline void adxstm_Stop(ADXSTM* stm)
{
	if (stm->cvfs != NULL && stm->relreq == 0) {
		cvFsStopTr(stm->cvfs);
	}
	fn_802229AC();
	stm->stat      = 1;
	stm->rdflg     = 0;
	stm->rqck.addr = NULL;
	fn_8022291C();
	adxstm_StopNw(stm);
	do {
		ADXSTM_ExecServer();
	} while (stm->stat != 1 || stm->rqck.addr != NULL);
}
static inline void adxstm_ReleaseFileNw(ADXSTM* stm)
{
	adxstm_StopNw(stm);
	fn_802229AC();
	if (stm->opened == 1) {
		stm->relreq = 1;
	}
	stm->bindreq = 0;
	fn_8022291C();
}
static inline void adxstm_ReleaseFile(ADXSTM* stm)
{
	adxstm_Stop(stm);
	adxstm_ReleaseFileNw(stm);
	for (;;) {
		if (stm->opened == 0) {
			break;
		}
		ADXSTM_ExecServer();
	}
}
static inline void adxstm_BindFileNw(ADXSTM* stm, const char* fname, void* dir, s32 ofst, s32 nsct)
{
	fn_802229AC();
	stm->ofst    = ofst;
	stm->fsize   = nsct * 0x800;
	stm->fname   = fname;
	stm->dir     = dir;
	stm->bindreq = 1;
	fn_8022291C();
}
static inline ADXSTM* adxstmf_Create(CriStream* sj, s32 ofst, s32 num)
{
	ADXSTM* stm = NULL;
	s32 i;

	for (i = 0; i < num; i++) {
		stm = (ADXSTM*)((u8*)adxstmf_obj + ofst * sizeof(ADXSTM));
		if (stm->used == 0) {
			break;
		}
		ofst++;
	}
	if (i == num) {
		return NULL;
	}
	ADXCRS_Lock();
	stm->stat     = 1;
	stm->rdflg    = 0;
	stm->sj       = sj;
	stm->cvfs     = NULL;
	stm->ofst     = 0;
	stm->fsize    = 0;
	stm->maxrqsct = 0x200;
	stm->pos      = 0;
	stm->maxsct   = 0xFFFFF;
	stm->eos      = stm->fsize / 0x800;
	if (stm->fsize % 0x800 > 0) {
		stm->eos++;
	}
	if (stm->sj != NULL) {
		stm->sjbufsize = sj->vtbl->get(sj, 0) + sj->vtbl->get(sj, 1);
		stm->minsize = stm->maxsize = stm->sjbufsize;
	}
	stm->pause = 0;
	stm->used  = 1;
	ADXCRS_Unlock();
	return stm;
}

s32 ADXSTM_Init(void)
{
	memset(adxstmf_obj, 0, sizeof(adxstmf_obj));
	return 1;
}

void ADXSTM_Finish(void) { }

ADXSTM* ADXSTM_Create(CriStream* sj, s32 prio)
{
	if (prio < 0x100) {
		return adxstmf_Create(sj, adxstmf_rtim_ofst, adxstmf_rtim_num);
	}
	return adxstmf_Create(sj, adxstmf_nrml_ofst, adxstmf_nrml_num);
}

void ADXSTM_Destroy(ADXSTM* stm)
{
	if (stm != NULL) {
		adxstm_Stop(stm);
		adxstm_ReleaseFile(stm);
		stm->used = 0;
		memset(stm, 0, sizeof(ADXSTM));
	}
}

void ADXSTM_BindFileNw(ADXSTM* stm, const char* fname, void* dir, s32 ofst, s32 nsct)
{
	adxstm_BindFileNw(stm, fname, dir, ofst, nsct);
}

void ADXSTM_BindFile(ADXSTM* stm, const char* fname, void* dir, s32 ofst, s32 nsct)
{
	adxstm_BindFileNw(stm, fname, dir, ofst, nsct);
	do {
		ADXSTM_ExecServer();
	} while (stm->bindreq != 0);
}

void ADXSTM_ReleaseFileNw(ADXSTM* stm)
{
	adxstm_ReleaseFileNw(stm);
}

void ADXSTM_ReleaseFile(ADXSTM* stm)
{
	adxstm_ReleaseFile(stm);
}

s32 ADXSTM_GetStat(ADXSTM* stm)
{
	return stm->stat;
}

s32 ADXSTM_Seek(ADXSTM* stm, s32 pos)
{
	stm->pos = pos;
	if (stm->pos * 0x800 > stm->fsize) {
		stm->pos = stm->fsize / 0x800 + (stm->fsize % 0x800 > 0);
	}
	return stm->pos;
}

s32 ADXSTM_Tell(ADXSTM* stm)
{
	if (stm->cvfs != NULL) {
		return stm->pos;
	}
	return 0;
}

s32 ADXSTM_Start(ADXSTM* stm)
{
	ADXCRS_Lock();
	stm->trnbyte = 0;
	stm->rtry    = 0;
	if (stm->fsize == 0) {
		stm->stat = 3;
	} else {
		stm->stat = 2;
	}
	stm->rdflg     = 0;
	stm->rqck.addr = NULL;
	stm->rqck.size = 0;
	stm->startreq  = 1;
	stm->maxsct    = 0xFFFFF;
	ADXCRS_Unlock();
	return 1;
}

s32 ADXSTM_Start2(ADXSTM* stm, s32 maxsct)
{
	ADXCRS_Lock();
	stm->trnbyte = 0;
	stm->rtry    = 0;
	if (stm->fsize == 0) {
		stm->stat = 3;
	} else {
		stm->stat = 2;
	}
	stm->rdflg     = 0;
	stm->rqck.addr = NULL;
	stm->rqck.size = 0;
	stm->startreq  = 1;
	stm->maxsct    = maxsct;
	ADXCRS_Unlock();
	return 1;
}

void ADXSTM_StopNw(ADXSTM* stm)
{
	adxstm_StopNw(stm);
}

void ADXSTM_Stop(ADXSTM* stm)
{
	adxstm_Stop(stm);
}

void ADXSTM_EntryEosFunc(ADXSTM* stm, void (*func)(void*), void* obj)
{
	stm->eosfunc = func;
	stm->eosobj  = obj;
}

void ADXSTM_SetEos(ADXSTM* stm, s32 eos)
{
	if (eos >= 0) {
		stm->eos = eos;
		return;
	}
	stm->eos = stm->fsize / 0x800 + ((stm->fsize % 0x800 > 0) ? 1 : 0);
}

static inline void adxstm_sj_internal_error(void)
{
	adxstm_sj_internal_error_cnt++;
}

void adxstmf_stat_exec(ADXSTM* stm)
{
	CriStream* sj;
	s32 stat;
	s32 nbyte;
	s32 nsct;
	s32 rdsct;
	CriChunk ck1;
	CriChunk ck2;
	CriChunk ck;

	sj   = stm->sj;
	stat = cvFsGetStat(stm->cvfs);
	fn_802229AC();
	if (stm->rdflg == 1) {
		if (stat == 1) {
			stm->rdflg = 0;
			fn_8022291C();
			nbyte = stm->rqsct * 0x800;
			fn_80221824(&stm->rqck, nbyte, &ck1, &ck2);
			sj->vtbl->put(sj, 1, &ck1);
			sj->vtbl->unget(sj, 0, &ck2);
			stm->pos += stm->rqsct;
			stm->trnbyte += nbyte;
			stm->rqck.addr = NULL;
			stm->rqck.size = 0;
			nsct           = stm->fsize / 0x800 + (stm->fsize % 0x800 > 0);
			if (stm->pos == stm->eos && stm->eosfunc != NULL) {
				stm->eosfunc(stm->eosobj);
			}
			if (stm->pos >= nsct) {
				stm->stat = 3;
			} else if ((u32)stm->trnbyte / 0x800 >= (u32)stm->maxsct
			    && (u32)stm->maxsct < 0xFFFFF) {
				stm->stat = 3;
			}
			stm->rtry = 0;
		} else if (stat == 3) {
			stm->rdflg = 0;
			fn_8022291C();
			sj->vtbl->unget(sj, 0, &stm->rqck);
			stm->rqck.addr = NULL;
			stm->rqck.size = 0;
			if (adxstmf_num_rtry >= 0) {
				if (stm->rtry >= adxstmf_num_rtry) {
					stm->stat = 4;
				} else {
					stm->rtry++;
				}
			}
		} else {
			fn_8022291C();
		}
		return;
	}
	stm->rdflg     = 1;
	stm->rqck.addr = NULL;
	stm->rqck.size = 0;
	fn_8022291C();
	if (stm->pause == 1 || stm->stopreq == 1) {
		stm->rdflg = 0;
		return;
	}
	if (stm->fsize == 0) {
		stm->rdflg = 0;
		stm->rqsct = 0;
		stm->stat  = 3;
		return;
	}
	if (sj == NULL || sj->vtbl == NULL) {
		stm->rdflg = 0;
		adxstm_sj_internal_error();
		return;
	}
	if (stm->sjbufsize - sj->vtbl->get(sj, 0) >= stm->minsize) {
		stm->rdflg = 0;
		return;
	}
	sj->vtbl->read(sj, 0, stm->maxsize, &ck);
	nsct = ck.size / 0x800;
	nsct = nsct < stm->eos - stm->pos ? nsct : stm->eos - stm->pos;
	nsct = nsct < stm->fsize / 0x800 - stm->pos ? nsct : stm->fsize / 0x800 - stm->pos;
	if (nsct < stm->maxrqsct) {
		rdsct = nsct;
	} else {
		rdsct = stm->maxrqsct;
	}
	cvFsSeek(stm->cvfs, stm->ofst + stm->pos, 0);
	stm->rqsct     = cvFsReqRd(stm->cvfs, rdsct, ck.addr);
	stm->rqck.addr = ck.addr;
	stm->rqck.size = ck.size;
	if (stm->rqsct <= 0) {
		sj->vtbl->unget(sj, 0, &stm->rqck);
		stm->rqck.addr = NULL;
		stm->rqck.size = 0;
		stm->rdflg     = 0;
		if (cvFsGetStat(stm->cvfs) == 3 && adxstmf_num_rtry >= 0) {
			if (stm->rtry >= adxstmf_num_rtry) {
				stm->stat = 4;
			} else {
				stm->rtry++;
			}
		}
	}
}

void ADXSTMF_ExecHndl(ADXSTM* stm)
{
	void* cvfs;
	s32 nsct;
	s32 fsize;

	if (stm->rdflg == 0) {
		if (stm->stopreq == 1) {
			stm->stopreq = 0;
			if (stm->startreq == 0) {
				stm->stat = 1;
			}
		}
		if (stm->relreq == 1) {
			cvfs = stm->cvfs;
			if (cvfs != NULL) {
				stm->cvfs = NULL;
				cvFsClose(cvfs);
			}
			stm->relreq = 0;
			stm->opened = 0;
		}
		fn_802229AC();
		if (stm->bindreq == 1) {
			stm->opened = 1;
			fn_8022291C();
			if (stm->cvfs == NULL) {
				cvfs      = cvFsOpen(stm->fname, stm->dir, 0);
				stm->cvfs = cvfs;
				if (cvfs == NULL) {
					ADXERR_CallErrFunc2("E02110501 adxstmf_stat_exec: can't open ", stm->fname);
					stm->stat    = 4;
					stm->opened  = 0;
					stm->bindreq = 0;
					return;
				}
				cvFsSeek(stm->cvfs, 0, 2);
				nsct  = cvFsTell(stm->cvfs);
				fsize = nsct * 0x800;
				cvFsSeek(stm->cvfs, 0, 0);
				if (stm->fsize == 0xFFFFF * 0x800) {
					stm->fsize = fsize;
				} else {
					if (stm->ofst > nsct) {
						stm->ofst = nsct;
					}
					if (stm->fsize / 0x800 + stm->ofst > nsct) {
						stm->fsize = (nsct - stm->ofst) * 0x800;
					}
				}
				ADXSTM_Seek(stm, 0);
				stm->bindreq = 0;
			}
		} else {
			fn_8022291C();
		}
		if (stm->startreq == 1) {
			stm->startreq = 0;
		}
	}
	if (stm->stat == 2 && stm->opened == 1) {
		adxstmf_stat_exec(stm);
	}
}

void ADXSTM_ExecServer(void)
{
	s32 i;

	if (fn_802218A8(&adxstmf_execsvr_flg) != 0) {
		for (i = 0; i < 40; i++) {
			if (adxstmf_obj[i].used == 1) {
				ADXSTMF_ExecHndl(&adxstmf_obj[i]);
			}
		}
		adxstmf_execsvr_flg = 0;
	}
}

s32 ADXSTM_GetBufSize(ADXSTM* stm, s32* minsize, s32* maxsize)
{
	*minsize = stm->minsize;
	*maxsize = stm->maxsize;
	return 1;
}

s32 ADXSTM_SetBufSize(ADXSTM* stm, s32 minsize, s32 maxsize)
{
	stm->minsize = minsize;
	stm->maxsize = maxsize;
	return 1;
}

s32 ADXSTM_SetReqRdSize(ADXSTM* stm, s32 nsct)
{
	stm->maxrqsct = nsct;
	return 1;
}

s32 ADXSTM_GetFileLen(ADXSTM* stm)
{
	return stm->fsize;
}

void ADXSTM_SetPause(ADXSTM* stm, s32 sw)
{
	stm->pause = sw;
}

void ADXSTM_SetSj(ADXSTM* stm, CriStream* sj)
{
	stm->sj = sj;
	ADXCRS_Lock();
	stm->sjbufsize = sj->vtbl->get(sj, 0) + sj->vtbl->get(sj, 1);
	ADXCRS_Unlock();
	stm->minsize = stm->maxsize = stm->sjbufsize;
}

s32 ADXSTM_GetReadFlg(ADXSTM* stm)
{
	return stm->rdflg;
}
