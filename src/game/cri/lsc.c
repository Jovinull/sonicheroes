#include "types.h"

// CRI LSC for GameCube: the stream-list controller that sits above the file
// layer and hands out numbered streams.
//
// The unit runs from fn_8021F544 at 0x8021F544 to the end of fn_802202FC at
// 0x80220544 -- exactly 0x1000 bytes, twenty-two functions -- and owns .rodata
// 0x8023FDF8 to 0x8023FF50 and .bss 0x80420878 to 0x80422C10. As with the other
// CRI units the disc ships no map, so the bounds are argued. Four lines agree:
//
//   The .rodata block carries the module's own version banner,
//   "\nLSC/GC Ver.2.11 Build:May  9 2003 17:09:53\n", followed by the pointer
//   that reads it, and every other string in the block is one of this module's
//   error messages. Two of them name the function that reports them,
//   "E0001: Illigal parameter=sj (LSC_Create)" and "E0002: Not enough instance
//   (LSC_Create)". CRI writes the banner into the module's main source file.
//
//   Every .rodata and .bss label the run touches has all of its users inside
//   the run, and nothing outside reaches any of them.
//
//   The .bss is contiguous and ends exactly where the neighbour begins:
//   0x80420878 is sixteen bytes, 0x80420888 four, 0x8042088C nine thousand and
//   ninety-two, which lands on 0x80422C10 -- the first object the next unit
//   uses.
//
//   The neighbours settle both ends. The function below 0x8021F544 reaches
//   lbl_80420770, shared with a function further down still; the one above
//   0x80220544 reaches lbl_80422C10 and lbl_80422C14, which nothing here
//   touches.
//
// Names come from the PS2 build of the same library, whose symbol table has
// thirty-four LSC entries in one contiguous run. Twelve of them do not survive
// as separate functions here, so the mapping is by position within the run,
// anchored at three points that cannot be anything else: LSC_SetStmHndl is
// eight bytes on both machines and is the only function of that length,
// LSC_Create is the only one that reports the two "(LSC_Create)" messages, and
// the three consecutive 0x94-byte PS2 getters that share the "Can not find
// stream ID" message land on the three consecutive 256-byte functions here.
// Everything named below rests on that alignment; everything not yet written
// keeps its dtk name.
//
// The error reporter, fn_8021F410, sits just below the run and is shared CRI
// plumbing rather than a static of this file -- the functions above 0x8021F544
// call it too. It is variadic, which is why every call site sets cr1eq.
//
// Two call relationships pin the naming beyond the three anchors above.
// fn_8021FF44 does nothing but tail-call fn_8021FD04 with a zero offset and a
// length of 0x100000 - 1, which is LSC_EntryFname delegating to
// LSC_EntryFileRange. fn_8021FA78 walks sixteen handles and calls fn_802202FC
// on each one that is in use, which is LSC_ExecServer driving lsc_ExecHndl.
//
// The handle layout fell out of LSC_GetStmId: it indexes 0x38 + n * 0x20 with n
// taken modulo sixteen, and 0x38 + 16 * 0x20 is 0x238, which is exactly the
// stride LSC_ExecServer walks. So LscObj ends in a sixteen-entry ring of
// thirty-two byte stream records, and the object table is sixteen of those.
// The three search-by-id getters give the record's fields and their own return
// types confirm which is which: the one that returns zero on failure yields a
// count, the one that returns -1 yields a status, the one that returns null
// yields a name.
//
// NOT MATCHING: all twenty-two functions are written, and twenty-one are
// byte-exact. The remaining function is still being matched. Struct offsets
// recovered by them are recorded below; the fields they do not touch are
// padding until something reaches them.

#define LSC_STM_MAX 16

typedef struct LscSj LscSj;

typedef struct LscStm {
	/* 0x00 */ s32 id;
	/* 0x04 */ const char* fname;
	/* 0x08 */ s32 unk08;
	/* 0x0C */ void* dir;
	/* 0x10 */ s32 ofst;
	/* 0x14 */ s32 nbyte;
	/* 0x18 */ s32 stat;
	/* 0x1C */ s32 rdsct;
} LscStm;

typedef struct LscObj {
	/* 0x00 */ s8 used;
	/* 0x01 */ s8 stat;
	/* 0x02 */ s8 pad2;
	/* 0x03 */ s8 lpflg;
	/* 0x04 */ s8 unk4;
	/* 0x08 */ LscSj* sj;
	/* 0x0C */ s32 unkC;
	/* 0x10 */ s32 unk10;
	/* 0x14 */ s32 flowlimit;
	/* 0x18 */ s32 nsct;
	/* 0x1C */ s32 rdsct;
	/* 0x20 */ s32 head;
	/* 0x24 */ s32 numstm;
	/* 0x28 */ void* stmhndl;
	/* 0x2C */ void* unk2C;
	/* 0x30 */ s8 pad30[4];
	/* 0x34 */ s32 unk34;
	/* 0x38 */ LscStm stm[LSC_STM_MAX];
} LscObj;

typedef void (*LscStatFunc)(void* obj, s32 stat);

typedef struct LscSjVtable {
	s8 pad00[0x24];
	s32 (*getNumSct)(LscSj* sj, s32 selector);
} LscSjVtable;

struct LscSj {
	LscSjVtable* vtable;
};

extern void fn_8021F410(const char* msg, ...);
extern void fn_8021F504(void* crs);
extern void fn_8021F524(void* crs);
extern void fn_8021F4D0(s32, s32);
extern void fn_80216F18(void* hndl);
extern void fn_80216810(void* hndl, s32 flowlimit, s32 nsct);
extern void fn_80216EC4(void* hndl, s32 nbyte);
extern void fn_80217044(void* hndl);
extern void fn_8021713C(void* hndl);
extern s32 fn_802171C0(void* hndl);
extern void fn_802171DC(void* hndl, s32 value);
extern s32 fn_8021722C(void* hndl);
extern void fn_80217434(void* hndl);
extern void fn_80217584(void* hndl, const char* fname, void* dir, s32 ofst, s32 nbyte);
extern void fn_802202FC(LscObj* lsc);
extern void fn_8021FF7C(LscObj* lsc);
extern s32 fn_8021FD04(LscObj* lsc, const char* fname, void* dir, s32 ofst, s32 nbyte);
extern void* memset(void* dst, s32 value, u32 size);
extern u32 strlen(const char* str);
extern volatile u32 lbl_8023FF30[];

extern const char lsc_ErrParam[];
extern const char lsc_ErrMin[];
extern const char lsc_ErrNo[];
extern const char lsc_ErrId[];
extern const char lsc_ErrFname[];
extern const char lsc_ErrCreateParam[];
extern const char lsc_ErrCreateNoInstance[];
extern const char lsc_ErrHandle[];

void LSC_SetLpFlg(LscObj* lsc, s8 flag);
void LSC_CallStatFunc(void);
s32 LSC_GetFlowLimit(LscObj* lsc);
void LSC_SetFlowLimit(LscObj* lsc, s32 min);
s32 LSC_GetNumStm(LscObj* lsc);
s32 LSC_GetStat(LscObj* lsc);
void LSC_SetStmHndl(LscObj* lsc, void* hndl);
void LSC_ResetEntry(LscObj* lsc);
void LSC_ExecServer(void);
void LSC_EntryFname(LscObj* lsc, const char* fname);
s32 LSC_GetStmId(LscObj* lsc, s32 no);
s32 LSC_GetStmRdSct(LscObj* lsc, s32 id);
s32 LSC_GetStmStat(LscObj* lsc, s32 id);
const char* LSC_GetStmFname(LscObj* lsc, s32 id);

#define LSC_OBJ_MAX 16

static u32 lsc_ObjTblPad;
static LscObj lsc_ObjTbl[LSC_OBJ_MAX];
static s32 lsc_InitCount;

static struct {
	LscStatFunc func;
	void* obj;
	s32 stat;
	s32 pad;
} lsc_StatEntry;

void LSC_SetLpFlg(LscObj* lsc, s8 flag)
{
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return;
	}
	lsc->lpflg = flag;
}

#pragma dont_inline on
void LSC_CallStatFunc(void)
{
	if (lsc_StatEntry.func != NULL) {
		lsc_StatEntry.func(lsc_StatEntry.obj, lsc_StatEntry.stat);
	}
}
#pragma dont_inline reset

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

void LSC_SetStmHndl(LscObj* lsc, void* hndl)
{
	lsc->stmhndl = hndl;
}

#pragma dont_inline on
void fn_8021FF7C(LscObj* lsc)
{
	if (lsc == NULL) {
		return;
	}
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
	} else if (lsc->stat != 0) {
		lsc->stat = 0;
		if (lsc->stmhndl != NULL && lsc->pad2 == 1) {
			fn_80216F18(lsc->stmhndl);
			lsc->pad2 = 0;
		}
		lsc->unk2C = NULL;
		if (lsc == NULL) {
			fn_8021F410(lsc_ErrParam);
		} else if (lsc->stat == 0) {
			lsc->rdsct  = 0;
			lsc->head   = 0;
			lsc->numstm = 0;
		}
		lsc->unk34 = 0;
	}
	lsc->used = 0;
	memset(lsc, 0, sizeof(*lsc));
}
#pragma dont_inline reset

void LSC_ResetEntry(LscObj* lsc)
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

void fn_8021FAE4(LscObj* lsc)
{
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return;
	}
	if (lsc->stat == 0) {
		return;
	}
	lsc->stat = 0;
	if (lsc->stmhndl != NULL && lsc->pad2 == 1) {
		fn_80216F18(lsc->stmhndl);
		lsc->pad2 = 0;
	}
	lsc->unk2C = NULL;
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
	} else if (lsc->stat == 0) {
		lsc->rdsct  = 0;
		lsc->head   = 0;
		lsc->numstm = 0;
	}
	lsc->unk34 = 0;
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
		if (lsc == NULL) {
			fn_8021F410(lsc_ErrParam);
		} else if (stat != 0) {
			lsc->stat = 0;
			if (lsc->stmhndl != NULL && lsc->pad2 == 1) {
				fn_80216F18(lsc->stmhndl);
				lsc->pad2 = 0;
			}
			lsc->unk2C = NULL;
			if (lsc == NULL) {
				fn_8021F410(lsc_ErrParam);
			} else if (lsc->stat == 0) {
				lsc->rdsct  = 0;
				lsc->head   = 0;
				lsc->numstm = 0;
			}
			lsc->unk34 = 0;
		}
	}
	if (lsc->numstm > 0) {
		lsc->stat = 2;
	} else {
		lsc->stat = 1;
	}
	fn_8021F504(crs);
}

static LscObj* lsc_Alloc(void)
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

#pragma opt_propagation off
LscObj* fn_80220054(LscSj* sj)
{
	LscObj* lsc;
	s8 crs[8];
	s32 i;

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
		lsc->nsct      = sj->vtable->getNumSct(sj, 0) + sj->vtable->getNumSct(sj, 1);
		lsc->flowlimit = (lsc->nsct * 8) / 10;
		i              = 0;
		if (i < LSC_STM_MAX) {
			lsc->stm[0].stat  = 0;
			lsc->stm[1].stat  = 0;
			lsc->stm[2].stat  = 0;
			lsc->stm[3].stat  = 0;
			lsc->stm[4].stat  = 0;
			lsc->stm[5].stat  = 0;
			lsc->stm[6].stat  = 0;
			lsc->stm[7].stat  = 0;
			lsc->stm[8].stat  = 0;
			lsc->stm[9].stat  = 0;
			lsc->stm[10].stat = 0;
			lsc->stm[11].stat = 0;
			lsc->stm[12].stat = 0;
			lsc->stm[13].stat = 0;
			lsc->stm[14].stat = 0;
			lsc->stm[15].stat = 0;
		}
		lsc->used = 1;
	}
	fn_8021F504(crs);
	return lsc;
}
#pragma opt_propagation reset

#pragma dont_inline on
s32 fn_8021FD04(LscObj* lsc, const char* fname, void* dir, s32 ofst, s32 nbyte)
{
	LscStm* stm;
	s32 id;
	u32 fnameLength;
	s32 i;
	s32 prevStmIndex;

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
	stm          = &lsc->stm[lsc->rdsct];
	prevStmIndex = (lsc->rdsct + LSC_STM_MAX - 1) % LSC_STM_MAX;
	id           = lsc->stm[prevStmIndex].id == 0x7FFFFFFF ? 0 : lsc->stm[prevStmIndex].id + 1;
	stm->id      = id;
	stm->fname   = fname;
	fnameLength  = strlen(fname) / sizeof(u32);
	stm->unk08   = 0;
	for (i = 0; i < fnameLength; i++) {
		stm->unk08 += ((const u32*)fname)[i];
	}
	stm->ofst   = ofst;
	stm->nbyte  = nbyte;
	stm->dir    = dir;
	stm->stat   = 0;
	stm->rdsct  = 0;
	lsc->numstm = lsc->numstm + 1;
	lsc->rdsct  = (lsc->rdsct + 1) % LSC_STM_MAX;
	if (lsc->stat == 1) {
		lsc->stat = 2;
	}
	return id;
}
#pragma dont_inline reset

void LSC_EntryFname(LscObj* lsc, const char* fname)
{
	fn_8021FD04(lsc, fname, 0, 0, 0x100000 - 1);
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

void fn_802201E0(void)
{
	s8 crs[8];
	s32 i;

	fn_8021F524(crs);
	if (--lsc_InitCount == 0) {
		for (i = 0; i < LSC_OBJ_MAX; i++) {
			if (lsc_ObjTbl[i].used == 1) {
				fn_8021FF7C(&lsc_ObjTbl[i]);
			}
		}
		memset(lsc_ObjTbl, 0, sizeof(lsc_ObjTbl));
		fn_8021F4D0(0, 0);
	}
	fn_8021F504(crs);
}

void fn_80220284(void)
{
	s8 crs[8];

	lbl_8023FF30[0];
	fn_8021F524(crs);
	if (lsc_InitCount == 0) {
		memset(lsc_ObjTbl, 0, sizeof(lsc_ObjTbl));
		fn_8021F4D0(0, 0);
	}
	lsc_InitCount++;
	fn_8021F504(crs);
}

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
		stm->rdsct = (s32)lsc->unk2C;
		stm->stat  = 2;
	}
}

static inline void lsc_StatEnd(LscObj* lsc)
{
	const char* fname = NULL;
	void* dir         = NULL;
	s32 ofst          = 0;
	s32 nbyte         = 0;
	LscStm* stm;

	if (lsc->stmhndl == NULL) {
		return;
	}
	if (lsc->lpflg == 1) {
		stm   = &lsc->stm[lsc->head];
		fname = stm->fname;
		dir   = stm->dir;
		ofst  = stm->ofst;
		nbyte = stm->nbyte;
	}
	lsc->numstm--;
	lsc->head = (lsc->head + 1) % LSC_STM_MAX;
	if (lsc->numstm <= 0) {
		LSC_CallStatFunc();
		lsc->stat = 1;
	}
	if (lsc->lpflg == 1) {
		fn_8021FD04(lsc, fname, dir, ofst, nbyte);
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
	fn_80217584(lsc->stmhndl, stm->fname, stm->dir, stm->ofst, stm->nbyte);
	fn_80216EC4(lsc->stmhndl, stm->nbyte);
	lsc->unk2C = (void*)stm->nbyte;
	stm->rdsct = 0;
	lsc->pad2  = 0;
	if (lsc->pad2 == 0) {
		fn_80216810(lsc->stmhndl, lsc->flowlimit, lsc->nsct);
		fn_802171DC(lsc->stmhndl, 0);
		fn_8021713C(lsc->stmhndl);
		lsc->pad2 = 1;
	}
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
