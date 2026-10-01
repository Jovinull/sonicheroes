#include "cri/lsc.h"
#include "cri/stm.h"

// Per-handle LSC server and three inlined state handlers. Its boundary is
// inferred from private string ownership, call/global separation and the
// correlated PS2 helper group, not a surviving source-file marker.

static const char lsc_ErrHandle[] = "E0007: lsc->fp=NULL\n";

static inline void lsc_StatRead(LscObj* lsc)
{
	LscStm* stm;
	s32 stat;

	if (lsc->stmhndl == NULL) {
		fn_8021F410(lsc_ErrHandle);
		return;
	}
	stm  = &lsc->stm[lsc->head];
	stat = fn_8021722C(lsc->stmhndl);
	if (stat == 4) {
		lsc->stat = 3;
	} else if (stat == 2) {
		stm->rdsct = fn_802171C0(lsc->stmhndl);
	} else if (stat == 3) {
		stm->rdsct = lsc->requestedSectors;
		stm->stat  = 2;
	}
}

static inline void lsc_StatEnd(LscObj* lsc)
{
	const char* fname = NULL;
	void* dir         = NULL;
	s32 ofst          = 0;
	s32 numSectors    = 0;
	LscStm* stm;

	if (lsc->stmhndl == NULL) {
		return;
	}
	if (lsc->lpflg == 1) {
		stm        = &lsc->stm[lsc->head];
		fname      = stm->fname;
		dir        = stm->dir;
		ofst       = stm->ofst;
		numSectors = stm->numSectors;
	}
	lsc->numstm--;
	lsc->head = (lsc->head + 1) % LSC_STM_MAX;
	if (lsc->numstm <= 0) {
		LSC_CallStatFunc();
		lsc->stat = 1;
	}
	if (lsc->lpflg == 1) {
		LSC_EntryFileRange(lsc, fname, dir, ofst, numSectors);
	}
}

static inline void lsc_StartStream(LscObj* lsc)
{
	if (lsc->streamStarted == 0) {
		fn_80216810(lsc->stmhndl, lsc->flowlimit, lsc->nsct);
		fn_802171DC(lsc->stmhndl, 0);
		fn_8021713C(lsc->stmhndl);
		lsc->streamStarted = 1;
	}
}

static inline void lsc_StatWait(LscObj* lsc)
{
	LscStm* stm = &lsc->stm[lsc->head];

	if (lsc->numstm <= 0) {
		return;
	}
	fn_80217044(lsc->stmhndl);
	fn_80217434(lsc->stmhndl);
	fn_80217584(lsc->stmhndl, stm->fname, stm->dir, stm->ofst, stm->numSectors);
	fn_80216EC4(lsc->stmhndl, stm->numSectors);
	lsc->requestedSectors = stm->numSectors;
	stm->rdsct            = 0;
	lsc->streamStarted    = 0;
	lsc_StartStream(lsc);
	stm->stat = 1;
}

void fn_802202FC(LscObj* lsc)
{
	if (lsc->unk4 == 1) {
		return;
	}
	if (lsc->stat != 2) {
		return;
	}
	if (lsc->numstm <= 0) {
		return;
	}
	if (lsc->stm[lsc->head].stat == 1) {
		lsc_StatRead(lsc);
	}
	if (lsc->stm[lsc->head].stat == 2) {
		lsc_StatEnd(lsc);
	}
	if (lsc->stm[lsc->head].stat != 0) {
		return;
	}
	lsc_StatWait(lsc);
}
