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
// NOT MATCHING: seven of the twenty-two functions are written so far, and all
// seven are byte-exact. The rest are still assembly. Struct offsets recovered
// by them are recorded in LscObj below; the fields they do not touch are
// padding until something reaches them.

typedef struct LscObj {
	/* 0x00 */ s8 pad0;
	/* 0x01 */ s8 stat;
	/* 0x02 */ s8 pad2;
	/* 0x03 */ s8 lpflg;
	/* 0x04 */ s8 pad4[0x10];
	/* 0x14 */ s32 flowlimit;
	/* 0x18 */ s32 nsct;
	/* 0x1C */ s8 pad1C[8];
	/* 0x24 */ s32 numstm;
	/* 0x28 */ void* stmhndl;
} LscObj;

typedef void (*LscStatFunc)(void* obj, s32 stat);

extern void fn_8021F410(const char* msg, ...);

extern const char lsc_ErrParam[];
extern const char lsc_ErrMin[];

void LSC_SetLpFlg(LscObj* lsc, s8 flag);
void LSC_CallStatFunc(void);
s32 LSC_GetFlowLimit(LscObj* lsc);
void LSC_SetFlowLimit(LscObj* lsc, s32 min);
s32 LSC_GetNumStm(LscObj* lsc);
s32 LSC_GetStat(LscObj* lsc);
void LSC_SetStmHndl(LscObj* lsc, void* hndl);

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

void LSC_CallStatFunc(void)
{
	if (lsc_StatEntry.func != NULL) {
		lsc_StatEntry.func(lsc_StatEntry.obj, lsc_StatEntry.stat);
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
