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
// NOT MATCHING: fourteen of the twenty-two functions are written so far, and
// all fourteen are byte-exact. The rest are still assembly. Struct offsets
// recovered by them are recorded below; the fields they do not touch are
// padding until something reaches them.

#define LSC_STM_MAX 16

typedef struct LscSj LscSj;

typedef struct LscSjVtbl {
	/* 0x00 */ u8 pad00[0x24];
	/* 0x24 */ s32 (*get)(LscSj* sj, s32 which);
} LscSjVtbl;

struct LscSj {
	/* 0x00 */ LscSjVtbl* vtbl;
};

typedef struct LscStm {
	/* 0x00 */ s32 id;
	/* 0x04 */ const char* fname;
	/* 0x08 */ s32 sum;
	/* 0x0C */ s32 ofst;
	/* 0x10 */ s32 arg4;
	/* 0x14 */ s32 nbyte;
	/* 0x18 */ s32 stat;
	/* 0x1C */ s32 rdsct;
} LscStm;

typedef struct LscObj {
	/* 0x00 */ s8 used;
	/* 0x01 */ s8 stat;
	/* 0x02 */ s8 busy;
	/* 0x03 */ s8 lpflg;
	/* 0x04 */ s8 halt;
	/* 0x05 */ s8 pad05[3];
	/* 0x08 */ struct LscSj* sj;
	/* 0x0C */ s8 pad0C[8];
	/* 0x14 */ s32 flowlimit;
	/* 0x18 */ s32 nsct;
	/* 0x1C */ s32 tail;
	/* 0x20 */ s32 head;
	/* 0x24 */ s32 numstm;
	/* 0x28 */ void* stmhndl;
	/* 0x2C */ s32 f2C;
	/* 0x30 */ s32 f30;
	/* 0x34 */ s32 f34;
	/* 0x38 */ LscStm stm[LSC_STM_MAX];
} LscObj;

typedef void (*LscStatFunc)(void* obj, s32 stat);

extern void fn_8021F410(const char* msg, ...);
extern void fn_8021F504(void* crs);
extern void fn_8021F524(void* crs);
extern void fn_802202FC(LscObj* lsc);
s32 fn_8021FD04(LscObj* lsc, const char* fname, s32 ofst, s32 arg4, s32 nbyte);

extern const char* const volatile lsc_verptr;
extern void fn_8021F4D0(s32 a, s32 b);
void fn_8021FF7C(LscObj* lsc);
extern void fn_80216F18(void* hndl);
extern void* memset(void* p, int c, u32 n);

extern const char lsc_ErrParam[];
extern const char lsc_ErrSj[];
extern const char lsc_ErrFp[];
extern const char lsc_ErrFname[];
extern u32 strlen(const char* s);
extern s32 fn_8021722C(void* hndl);
extern s32 fn_802171C0(void* hndl);
extern void fn_80217044(void* hndl);
extern void fn_80217434(void* hndl);
extern void fn_80217584(void* hndl, const char* fname, s32 ofst, s32 arg4, s32 nbyte);
extern void fn_80216EC4(void* hndl, s32 nbyte);
extern void fn_80216810(void* hndl, s32 min, s32 nsct);
extern void fn_802171DC(void* hndl, s32 a);
extern void fn_8021713C(void* hndl);
extern const char lsc_ErrMin[];
extern const char lsc_ErrNo[];
extern const char lsc_ErrId[];

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

static LscObj lsc_ObjTbl[LSC_OBJ_MAX];

static struct {
	LscStatFunc func;
	void* obj;
	s32 stat;
	s32 pad;
} lsc_StatEntry;

static s32 lsc_RefCnt;

void LSC_SetLpFlg(LscObj* lsc, s8 flag)
{
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return;
	}
	lsc->lpflg = flag;
}

// Kept out of line: the server calls it rather than inlining it, and at this
// size the compiler would inline it by default.
#pragma dont_inline on
void LSC_CallStatFunc(void)
{
	if (lsc_StatEntry.func != NULL) {
		lsc_StatEntry.func(lsc_StatEntry.obj, lsc_StatEntry.stat);
	}
}
#pragma dont_inline off

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

void LSC_ResetEntry(LscObj* lsc)
{
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return;
	}
	if (lsc->stat == 0) {
		lsc->tail   = 0;
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

// Refcounted init and finish. Both keep their dtk names: the PS2 run has an
// LSC_Init and an LSC_Finish in the right place, but the anchors the rest of
// the naming rests on do not reach this far, so the mapping here would be a
// guess rather than a reading.
void fn_802201E0(void)
{
	void* crs[2];
	s32 i;

	fn_8021F524(crs);
	if (--lsc_RefCnt == 0) {
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
	void* crs[2];

	(void)lsc_verptr;
	fn_8021F524(crs);
	if (lsc_RefCnt == 0) {
		memset(lsc_ObjTbl, 0, sizeof(lsc_ObjTbl));
		fn_8021F4D0(0, 0);
	}
	lsc_RefCnt++;
	fn_8021F504(crs);
}

// Stops the entry and wipes it. The null check appears twice because the outer
// guard and the module's error macro are both in the source; the macro's copy
// is unreachable and the compiler still emits it, the same shape the MFCI close
// has.
void fn_8021FF7C(LscObj* lsc)
{
	if (lsc == NULL) {
		return;
	}
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
	} else if (lsc->stat != 0) {
		lsc->stat = 0;
		if (lsc->stmhndl != NULL && lsc->busy == 1) {
			fn_80216F18(lsc->stmhndl);
			lsc->busy = 0;
		}
		lsc->f2C = 0;
		if (lsc == NULL) {
			fn_8021F410(lsc_ErrParam);
		} else if (lsc->stat == 0) {
			lsc->tail   = 0;
			lsc->head   = 0;
			lsc->numstm = 0;
		}
		lsc->f34 = 0;
	}
	lsc->used = 0;
	memset(lsc, 0, sizeof(LscObj));
}

// The same body fn_8021FF7C carries inline, as a function of its own.
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
	if (lsc->stmhndl != NULL && lsc->busy == 1) {
		fn_80216F18(lsc->stmhndl);
		lsc->busy = 0;
	}
	lsc->f2C = 0;
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
	} else if (lsc->stat == 0) {
		lsc->tail   = 0;
		lsc->head   = 0;
		lsc->numstm = 0;
	}
	lsc->f34 = 0;
}

// Restarts the entry: stops whatever is running, then sets the state from
// whether any streams are entered. The stop is fn_8021FAE4, which the compiler
// inlines here.
void fn_8021FBA0(LscObj* lsc)
{
	void* crs[2];

	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return;
	}
	fn_8021F524(crs);
	if (lsc->stat != 0) {
		fn_8021FAE4(lsc);
	}
	if (lsc->numstm > 0) {
		lsc->stat = 2;
	} else {
		lsc->stat = 1;
	}
	fn_8021F504(crs);
}

// LSC_Create: takes the first unused entry, asks the stream joiner for the two
// halves of its sector count, and derives the flow limit as eight tenths of it.
// The compiler unrolls the sixteen-slot clear and leaves the loop's init and
// entry test behind, which is why the compare below has no branch.
LscObj* LSC_Create(LscSj* sj)
{
	void* crs[2];
	LscObj* lsc;
	s32 i;
	s32 n;

	if (sj == NULL) {
		fn_8021F410(lsc_ErrSj);
		return NULL;
	}
	fn_8021F524(crs);
	lsc = NULL;
	for (i = 0; i < LSC_OBJ_MAX; i++) {
		if (lsc_ObjTbl[i].used == 0) {
			lsc = &lsc_ObjTbl[i];
			break;
		}
	}
	if (lsc == NULL) {
		fn_8021F410(lsc_ErrMin);
	} else {
		lsc->sj        = sj;
		lsc->stat      = 0;
		n              = sj->vtbl->get(sj, 1);
		lsc->nsct      = sj->vtbl->get(sj, 0) + n;
		lsc->flowlimit = lsc->nsct * 8 / 10;
		for (i = 0; i < LSC_STM_MAX; i++) {
			lsc->stm[i].stat = 0;
		}
		lsc->used = 1;
	}
	fn_8021F504(crs);
	return lsc;
}

// lsc_ExecHndl: one pass of the server over a single handle. Three stages run
// in sequence on the record at the head of the ring -- poll a read in flight,
// retire one that finished, then start the next -- so a record can move two
// states in a single pass.
void fn_802202FC(LscObj* lsc)
{
	LscStm* stm;
	s32 ret;
	const char* fname;
	s32 ofst;
	s32 arg4;
	s32 nbyte;

	if (lsc->halt == 1) {
		return;
	}
	if (lsc->stat != 2) {
		return;
	}
	if (lsc->numstm <= 0) {
		return;
	}

	if (lsc->stm[lsc->head].stat == 1) {
		if (lsc->stmhndl == NULL) {
			fn_8021F410(lsc_ErrFp);
		} else {
			stm = &lsc->stm[lsc->head];
			ret = fn_8021722C(lsc->stmhndl);
			if (ret == 4) {
				lsc->stat = 3;
			} else if (ret == 2) {
				stm->rdsct = fn_802171C0(lsc->stmhndl);
			} else if (ret == 3) {
				stm->rdsct = lsc->f2C;
				stm->stat  = 2;
			}
		}
	}

	if (lsc->stm[lsc->head].stat == 2) {
		nbyte = 0;
		arg4  = 0;
		ofst  = 0;
		fname = NULL;
		if (lsc->stmhndl != NULL) {
			if (lsc->lpflg == 1) {
				stm   = &lsc->stm[lsc->head];
				fname = stm->fname;
				ofst  = stm->ofst;
				arg4  = stm->arg4;
				nbyte = stm->nbyte;
			}
			lsc->numstm--;
			lsc->head = (lsc->head + 1) % LSC_STM_MAX;
			if (lsc->numstm <= 0) {
				LSC_CallStatFunc();
				lsc->stat = 1;
			}
			if (lsc->lpflg == 1) {
				fn_8021FD04(lsc, fname, ofst, arg4, nbyte);
			}
		}
	}

	if (lsc->stm[lsc->head].stat == 0) {
		stm = &lsc->stm[lsc->head];
		if (lsc->numstm > 0) {
			fn_80217044(lsc->stmhndl);
			fn_80217434(lsc->stmhndl);
			fn_80217584(lsc->stmhndl, stm->fname, stm->ofst, stm->arg4, stm->nbyte);
			fn_80216EC4(lsc->stmhndl, stm->nbyte);
			lsc->f2C   = stm->nbyte;
			stm->rdsct = 0;
			lsc->busy  = 0;
			if (lsc->busy == 0) {
				fn_80216810(lsc->stmhndl, lsc->flowlimit, lsc->nsct);
				fn_802171DC(lsc->stmhndl, 0);
				fn_8021713C(lsc->stmhndl);
				lsc->busy = 1;
			}
			stm->stat = 1;
		}
	}
}

// LSC_EntryFileRange: queues one file range on the tail of the ring. The id it
// hands back is the previous entry's plus one, wrapping at INT_MAX, and the
// name is summed a word at a time -- the compiler unrolls that loop eight deep.
s32 fn_8021FD04(LscObj* lsc, const char* fname, s32 ofst, s32 arg4, s32 nbyte)
{
	LscStm* stm;
	s32 id;
	u32 n;
	u32 i;

	if (lsc == NULL) {
		fn_8021F410(lsc_ErrParam);
		return -1;
	}
	if (lsc->numstm >= LSC_STM_MAX) {
		return -1;
	}
	if (fname == NULL) {
		fn_8021F410(lsc_ErrFname);
		return -1;
	}

	stm = &lsc->stm[lsc->tail];
	id  = lsc->stm[(lsc->tail + LSC_STM_MAX - 1) % LSC_STM_MAX].id;
	id  = id == 0x7FFFFFFF ? 0 : id + 1;

	stm->id    = id;
	stm->fname = fname;
	stm->sum   = 0;
	n          = strlen(fname) / 4;
	for (i = 0; i < n; i++) {
		stm->sum += ((s32*)fname)[i];
	}
	stm->arg4  = arg4;
	stm->nbyte = nbyte;
	stm->ofst  = ofst;
	stm->stat  = 0;
	stm->rdsct = 0;
	lsc->numstm++;
	lsc->tail = (lsc->tail + 1) % LSC_STM_MAX;
	if (lsc->stat == 1) {
		lsc->stat = 2;
	}
	return id;
}
