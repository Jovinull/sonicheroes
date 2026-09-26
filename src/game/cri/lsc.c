#include "cri/lsc.h"
#include "cri/stm.h"
#include "MSL_C/string.h"

// Public LSC API: nineteen surviving functions; source boundary inferred from
// independent status state, error strings and cross-unit calls.

const char lsc_ErrParam[]            = "E0003: Illigal parameter lsc=NULL\n";
const char lsc_ErrMin[]              = "E0010: Illigal parameter min=%d\n";
const char lsc_ErrId[]               = "E0012: Can not find stream ID =%d\n";
const char lsc_ErrNo[]               = "E0009: Illigal parameter no=%d\n";
const char lsc_ErrFname[]            = "E0011: Illigal parameter fname=%s\n";
const char lsc_ErrCreateParam[]      = "E0001: Illigal parameter=sj (LSC_Create)\n";
const char lsc_ErrCreateNoInstance[] = "E0002: Not enough instance (LSC_Create)\n";

static LscStatFunc lsc_StatFunc = NULL;
static void* lsc_StatObj        = NULL;
static s32 lsc_StatValue        = 0;

void LSC_SetLpFlg(LscObj* lsc, s8 flag)
{
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return;
	}
	lsc->lpflg = flag;
}

void LSC_CallStatFunc(void)
{
	if (lsc_StatFunc != NULL) {
		lsc_StatFunc(lsc_StatObj, lsc_StatValue);
	}
}

s32 LSC_GetFlowLimit(LscObj* lsc)
{
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return -1;
	}
	return lsc->flowlimit;
}

void LSC_SetFlowLimit(LscObj* lsc, s32 min)
{
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return;
	}
	if (min < 0 || min > lsc->nsct) {
		fn_8021F410(lsc_ErrMin, min);
		return;
	}
	lsc->flowlimit = min;
}

s32 LSC_GetStmRdSct(LscObj* lsc, s32 id)
{
	s32 i;

	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return 0;
	}
	for (i = 0; i < LSC_STM_MAX; i++) {
		if (lsc->stm[i].id == id) {
			break;
		}
	}
	if (i == LSC_STM_MAX) {
		fn_8021F410(lsc_ErrId, id);
		return 0;
	}
	return lsc->stm[i].rdsct;
}

s32 LSC_GetStmStat(LscObj* lsc, s32 id)
{
	s32 i;

	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return -1;
	}
	for (i = 0; i < LSC_STM_MAX; i++) {
		if (lsc->stm[i].id == id) {
			break;
		}
	}
	if (i == LSC_STM_MAX) {
		fn_8021F410(lsc_ErrId, id);
		return -1;
	}
	return lsc->stm[i].stat;
}

const char* LSC_GetStmFname(LscObj* lsc, s32 id)
{
	s32 i;

	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return NULL;
	}
	for (i = 0; i < LSC_STM_MAX; i++) {
		if (lsc->stm[i].id == id) {
			break;
		}
	}
	if (i == LSC_STM_MAX) {
		fn_8021F410(lsc_ErrId, id);
		return NULL;
	}
	return lsc->stm[i].fname;
}

s32 LSC_GetStmId(LscObj* lsc, s32 no)
{
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return -1;
	}
	if (no < 0 || no >= lsc->numstm) {
		fn_8021F410(lsc_ErrNo, no);
		return -1;
	}
	return lsc->stm[(lsc->head + no) % LSC_STM_MAX].id;
}

s32 LSC_GetNumStm(LscObj* lsc)
{
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return -1;
	}
	return lsc->numstm;
}

s32 LSC_GetStat(LscObj* lsc)
{
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return -1;
	}
	return lsc->stat;
}

void LSC_ExecServer(void)
{
	s8 crs[0x10];
	s32 i;

	fn_8021F524(crs);
	for (i = 0; i < LSC_OBJ_MAX; i++) {
		if (lsc_ObjTbl[i].used == 1) {
			fn_802202FC(&lsc_ObjTbl[i]);
		}
	}
	fn_8021F504(crs);
}

static inline void lsc_ResetEntry(LscObj* lsc)
{
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return;
	}
	if (lsc->stat == 0) {
		lsc->rdsct  = 0;
		lsc->head   = 0;
		lsc->numstm = 0;
	}
}

static inline void lsc_Stop(LscObj* lsc)
{
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return;
	}
	if (lsc->stat == 0) {
		return;
	}
	lsc->stat = 0;
	if (lsc->stmhndl != NULL && lsc->streamStarted == 1) {
		ADXSTM_Stop(lsc->stmhndl);
		lsc->streamStarted = 0;
	}
	lsc->requestedSectors = 0;
	lsc_ResetEntry(lsc);
	lsc->unk34 = 0;
}

void fn_8021FAE4(LscObj* lsc)
{
	lsc_Stop(lsc);
}

void fn_8021FBA0(LscObj* lsc)
{
	s8 crs[8];
	s8 stat;

	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return;
	}
	fn_8021F524(crs);
	stat = lsc->stat;
	if (stat != 0) {
		lsc_Stop(lsc);
	}
	if (lsc->numstm > 0) {
		lsc->stat = 2;
	} else {
		lsc->stat = 1;
	}
	fn_8021F504(crs);
}

void LSC_ResetEntry(LscObj* lsc)
{
	lsc_ResetEntry(lsc);
}

static inline LscStm* lsc_GetWriteEntry(LscObj* lsc, s32* previousIndex)
{
	*previousIndex = (lsc->rdsct + LSC_STM_MAX - 1) % LSC_STM_MAX;
	return &lsc->stm[lsc->rdsct];
}

s32 LSC_EntryFileRange(LscObj* lsc, const char* fname, void* dir, s32 ofst, s32 numSectors)
{
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return -1;
	}
	if (lsc->numstm >= LSC_STM_MAX) {
		return -1;
	}
	if (fname == NULL) {
		fn_8021F410(lsc_ErrFname, fname);
		return -1;
	}
	{
		s32 id;
		LscStm* stm;
		s32 i;
		u32 fnameLength;
		s32 prevStmIndex;
		const u32* words;

		words       = (const u32*)fname;
		stm         = lsc_GetWriteEntry(lsc, &prevStmIndex);
		id          = lsc->stm[prevStmIndex].id == 0x7FFFFFFF ? 0 : lsc->stm[prevStmIndex].id + 1;
		stm->id     = id;
		stm->fname  = fname;
		fnameLength = strlen(fname) / sizeof(u32);
		stm->filenameChecksum = 0;
		for (i = 0; i < fnameLength; i++) {
			u32 word = words[i];
			stm->filenameChecksum += word;
		}
		stm->ofst       = ofst;
		stm->numSectors = numSectors;
		stm->dir        = dir;
		stm->stat       = 0;
		stm->rdsct      = 0;
		lsc->numstm     = lsc->numstm + 1;
		lsc->rdsct      = (lsc->rdsct + 1) % LSC_STM_MAX;
		if (lsc->stat == 1) {
			lsc->stat = 2;
		}
		return id;
	}
}

void LSC_EntryFname(LscObj* lsc, const char* fname)
{
	LSC_EntryFileRange(lsc, fname, 0, 0, 0x100000 - 1);
}

void LSC_SetStmHndl(LscObj* lsc, void* hndl)
{
	lsc->stmhndl = hndl;
}

void fn_8021FF7C(LscObj* lsc)
{
	if (lsc == NULL) {
		return;
	}
	lsc_Stop(lsc);
	lsc->used = 0;
	memset(lsc, 0, sizeof(*lsc));
}

static inline LscObj* lsc_Alloc(void)
{
	LscObj* lsc = NULL;
	LscObj* obj = lsc_ObjTbl;
	s32 i;

	for (i = 0; i < LSC_OBJ_MAX; obj++, i++) {
		if (obj->used == 0) {
			lsc = &lsc_ObjTbl[i];
			break;
		}
	}
	return lsc;
}

LscObj* LSC_Create(CriStream* sj)
{
	LscObj* lsc;
	s8 crs[8];
	signed long i;

	if (sj == NULL) {
		fn_8021F410(lsc_ErrCreateParam);
		return NULL;
	}
	fn_8021F524(crs);
	lsc = lsc_Alloc();
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrCreateNoInstance);
	} else {
		lsc->sj        = sj;
		lsc->stat      = 0;
		lsc->nsct      = sj->vtbl->get(sj, 0) + sj->vtbl->get(sj, 1);
		lsc->flowlimit = (lsc->nsct * 8) / 10;
		for (i = 0; i < LSC_STM_MAX; i++) {
			lsc->stm[i].stat = 0;
		}
		lsc->used = 1;
	}
	fn_8021F504(crs);
	return lsc;
}
