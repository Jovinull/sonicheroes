#include "types.h"

// CRI MFCI for GameCube: the file-entry layer that turns a "AAAAAAAA.SSSSSSS"
// name into an address/size pair and hands out read handles over it.
//
// The unit runs from fn_80222A14 at 0x80222A14 to the end of fn_80223410 at
// 0x80223424, and owns .rodata 0x80240168 to 0x80240400, .data 0x8029BA48 to
// 0x8029BAB0 and .bss 0x80427F78 to 0x80428970. The disc ships no map, so the
// bounds are argued rather than read. Five independent lines agree:
//
//   The .rodata block opens with the module's own version banner,
//   "\nMFCI/GC Ver.1.05 Build:May  9 2003 17:10:33\n", and runs to 0x80240400,
//   where AXRNA's banner starts. CRI puts that banner in the module's main
//   source file, and every string in the block names something declared here:
//   mfCiOpen, mfCiOpenEntry, mfCiReqRd and mfci_get_adr_size.
//
//   The .bss is private to the run. lbl_80427F78 and the block at lbl_80427F7C
//   are touched by exactly the twelve functions from fn_80222A14 to
//   fn_802233F0, and by nothing before or after.
//
//   Every .rodata label inside 0x80240168..0x80240400 is reached from this run
//   and from nowhere else, including lbl_80240198, whose only reader is
//   fn_80223410.
//
//   The .data at 0x8029BA48 is this module's interface table. Its thirteen
//   non-null entries are exactly the functions of the run, in reverse source
//   order, and fn_80223410 is the accessor that hands the table back.
//
//   The neighbours settle both ends. Nothing below 0x80222A14 touches any of
//   the block; fn_80223424 and everything after it work on lbl_80428970, a
//   disjoint private block that starts exactly where this .bss ends. The
//   lock/unlock pair the file calls, fn_802229AC and fn_8022291C, sits just
//   below the run but belongs elsewhere: fourteen functions spread from
//   0x802127B0 to 0x8021B214 call it too, so it is shared CRI plumbing rather
//   than a static of this file.
//
// Names come from the error strings, which CRI writes with the reporting
// function in parentheses. Everything not named there keeps its dtk name.
//
// The names come from two places. The error strings name the reporting function
// in parentheses, and the PS2 build of the same CRI library ships a symbol
// table: its mfci_vtbl is entry for entry the table below, which fixes every
// slot. That mapping reads, from the top of the run down: mfCiGetNumTr,
// mfCiSetSctLen, mfCiGetSctLen, mfCiGetStat, mfCiStopTr, mfCiReqRd, mfCiTell,
// mfCiSeek, mfCiClose, mfCiOpen, mfCiGetFileSize, mfCiEntryErrFunc,
// mfCiExecServer and mfCiGetInterface. The statics it also names are
// mfci_alloc, mfci_reset_hn, mfci_get_adr_size and mfci_call_errfn.
//
// NOT MATCHING: eleven of the fourteen functions are byte-exact. What is left
// is fn_80222C40 (mfCiReqRd), fn_80222F28 (mfCiSeek) and fn_80223404
// (mfCiExecServer).
//
//   fn_80222C40 differs only in register allocation: the target ranks the
//   handle above the buffer (r29/r28), this build ranks the buffer above the
//   handle, and the two callee-saved registers the string and .bss bases free
//   up afterwards follow that swap. Every instruction, every relocation and the
//   function size already agree; 48 bytes differ and all of them are register
//   fields. Ruled out: local declaration order, local types (`u32` vs a pointer
//   for the address, signedness of the clamp), aliasing the buffer through a
//   local `s8*`, extracting the min, the request setup or the memset tail into
//   a static helper, and reshaping mfci_get_adr_size, which is inlined here.
//   The mfCiOpenEntry lever described below is binary and already saturated:
//   its two states give handle-above-buffer with the .rodata base sunk too far,
//   or the base order right with the handle and buffer swapped. Neither is the
//   target, so the remaining nudge has to come from somewhere else again.
//
//   fn_80222F28 is one instruction short. The target lowers the final clamp
//   branchily -- `ble` into the block, `b` past the `li` into the shared store,
//   so both arms converge on one `stw` with the value in r0. That the compiler
//   is willing to branch for a select is not in doubt: the preceding clamp
//   against nsct is emitted exactly that way. It is the zero that is the
//   problem. Every `?:` spelling whose false arm reaches zero -- literal,
//   returned from a static helper, `off - off`, `whence & 0`, a local assigned
//   0 -- constant-propagates before the idiom recogniser runs, and the clamp
//   comes out as branchless `neg/andc/srawi/and`. Every plain `if`/`else`
//   spelling has an empty then-arm, which the compiler answers by inverting
//   the test and dropping the `b`.
//
//   The closest miss is worth keeping. Route both arms through a same-TU
//   static setter -- `if (hn->pos > 0) { mfci_SetPos(hn, hn->pos); } else {
//   mfci_SetPos(hn, 0); }` -- and the branch layout comes out exactly right,
//   `ble` into the block and `b` skipping the `li`. What is left over is the
//   then-arm's own redundant `stw`, which this compiler does not tail-merge
//   with the else-arm's, so the function lands at 248 against the target's 244.
//
//   fn_80223404 is three instructions in the target -- `li r0, 0`,
//   `cmpwi r0, 0x28`, `blr` -- the dead remains of a loop the optimiser
//   deleted after emitting its guard. The PS2 build shows the body: a walk over
//   the object table calling mfCiExecHndl, which is empty there (eight bytes,
//   `jr ra`), guarded at the call site by the same stat test. Reproducing that
//   split exactly -- empty callee, test in the caller -- lets this compiler
//   delete the loop outright and emit a bare `blr`. Moving the test into the
//   callee instead keeps the loop, as a `mtctr`/`bdnz` spin; that is what is
//   written below, because it is the closest of the three shapes this compiler
//   will produce. The third is `volatile`, which yields a full stack frame.
//   They are attractors, not a spectrum: index and pointer walks, `while`,
//   `do`, `goto`, a `break`, an empty inner loop, `-inline deferred` and empty
//   callees nested two and three deep all land on one of them. The target sits
//   between the first two -- the loop was deleted late enough that its guard
//   had already been emitted, and its trip count never became a `ctr` loop,
//   which here happens only while the body still holds a call.
//
// The register allocation of mfCiOpen and mfCiReqRd turned out to be steered
// from outside those functions. Whether mfCiOpenEntry touches a third .bss
// object decides, for the whole unit, how the section bases rank against the
// parameters: without it the .rodata base sinks below them, with it the base
// order is right. That is why mfCiOpenEntry below hands mfci_WorkStr to
// mfCiOpen -- the reference has to be to mfci_WorkStr and not mfci_ObjTbl,
// because .bss is laid out in order of first reference and touching the table
// there would move it in front of the work buffer.
//
// .rodata and .bss both match the original layout byte for byte. The .bss order
// is load-bearing and not obvious: MWCC lays those statics out in order of
// first reference, not order of declaration, so mfci_WorkStr only lands at
// offset 8 because nothing touches mfci_ObjTbl before mfci_get_adr_size runs.
// Both sections read four bytes longer in the target object than here; that is
// the padding dtk's split carries to the next unit's boundary, not data of
// ours -- 0x80240168 + 664 is exactly where AXRNA's banner starts.
//
// The .rodata still carries the three "(mfCiOpenEntry)" messages although no
// surviving function reads them. mfCiOpenEntry is reconstructed below as the
// static it must have been, and its position at the top of the file is what
// puts those three strings at the head of the pool. The reconstruction stays a
// hypothesis, and an incomplete one: this compiler keeps the body, so the
// object holds more functions than the target's fourteen.

typedef void (*MfciErrFunc)(void* obj, const char* msg, void* arg);
typedef void (*MfciFunc)(void);

typedef struct MfciObj {
	/* 0x00 */ s8 stat;
	/* 0x01 */ s8 busy;
	/* 0x02 */ s8 pad[2];
	/* 0x04 */ s32 sctsize;
	/* 0x08 */ s32 size;
	/* 0x0C */ s32 nsct;
	/* 0x10 */ s32 pos;
	/* 0x14 */ s32 total;
	/* 0x18 */ s32 rdsct;
	/* 0x1C */ char fname[20];
	/* 0x30 */ s32 ofst;
	/* 0x34 */ s32 nbyte;
} MfciObj;

#define MFCI_OBJ_MAX  40
#define MFCI_SCT_SIZE 2048

extern void fn_802229AC(void);
extern void fn_8022291C(void);

extern u32 strlen(const char* s);
extern char* strcpy(char* dst, const char* src);
extern void* memset(void* p, int c, u32 n);
extern void* memcpy(void* d, const void* s, u32 n);
extern u32 strtoul(const char* s, char** end, int base);
extern int sprintf(char* buf, const char* fmt, ...);

s32 fn_80222A14(MfciObj* hn);
void fn_80222A74(MfciObj* hn, s32 sctsize);
s32 fn_80222B0C(MfciObj* hn);
s32 fn_80222B6C(MfciObj* hn);
void fn_80222BD0(MfciObj* hn);
s32 fn_80222C40(MfciObj* hn, s32 nsct, void* buf);
s32 fn_80222EC8(MfciObj* hn);
s32 fn_80222F28(MfciObj* hn, s32 off, s32 whence);
void fn_8022301C(MfciObj* hn);
MfciObj* fn_802230B4(const char* fname, s32 mode, s32 rw);
u32 fn_802232E4(const char* fname);
void fn_802233F0(MfciErrFunc func, void* obj);
void fn_80223404(void);
void* fn_80223410(void);

const char mfci_ver[]                         = "\nMFCI/GC Ver.1.05 Build:May  9 2003 17:10:33\n";
static const char* const volatile mfci_verptr = mfci_ver;

static MfciErrFunc mfci_ErrFunc;
static void* mfci_ErrObj;
static char mfci_WorkStr[300];
static MfciObj mfci_ObjTbl[MFCI_OBJ_MAX];

MfciFunc mfci_IfTbl[26] = {
	(MfciFunc)fn_80223404,
	(MfciFunc)fn_802233F0,
	(MfciFunc)fn_802232E4,
	NULL,
	(MfciFunc)fn_802230B4,
	(MfciFunc)fn_8022301C,
	(MfciFunc)fn_80222F28,
	(MfciFunc)fn_80222EC8,
	(MfciFunc)fn_80222C40,
	NULL,
	(MfciFunc)fn_80222BD0,
	(MfciFunc)fn_80222B6C,
	(MfciFunc)fn_80222B0C,
	(MfciFunc)fn_80222A74,
	(MfciFunc)fn_80222A14,
};

static void mfci_ErrorN(const char* msg)
{
	if (mfci_ErrFunc != NULL) {
		mfci_ErrFunc(mfci_ErrObj, msg, NULL);
	}
}

static void mfci_Error(const char* msg, void* arg)
{
	if (mfci_ErrFunc != NULL) {
		mfci_ErrFunc(mfci_ErrObj, msg, arg);
	}
}

// Never called here. The three messages it reports are the head of this file's
// string pool, so it has to sit at the top of the source even though nothing
// in the run reaches it; the linker drops the body and keeps the pool. The body
// is a hypothesis: validate, then hand the work buffer to mfCiOpen.
static MfciObj* mfCiOpenEntry(s32 no, s32 rw)
{
	MfciObj* hn;

	if (no < 0 || no >= MFCI_OBJ_MAX) {
		mfci_ErrorN("E1041001:invalid entry number.(mfCiOpenEntry)");
		return NULL;
	}
	if (rw != 0) {
		mfci_ErrorN("E1041002:rw is illigal.(mfCiOpenEntry)");
		return NULL;
	}
	hn = fn_802230B4(mfci_WorkStr, 0, rw);
	if (hn == NULL) {
		mfci_ErrorN("E1041002:not enough handle resource.(mfCiOpenEntry)");
		return NULL;
	}
	return hn;
}

static u32 mfci_get_adr_size(const char* fname, u32* size)
{
	char* p;
	u32 v;

	if (strlen(fname) != 17) {
		sprintf(
		    mfci_WorkStr, "E01100308:length of '%s' is not 17 bytes.(mfci_get_adr_size)", fname);
		mfci_ErrorN(mfci_WorkStr);
	}
	if (fname[8] != '.') {
		sprintf(mfci_WorkStr, "E01100309:illegal file name format '%s'(mfci_get_adr_size)", fname);
		mfci_ErrorN(mfci_WorkStr);
	}
	p = (char*)fname;
	v = strtoul(p, &p, 16);
	if (*p != '\0') {
		p++;
	}
	if (size != NULL) {
		*size = strtoul(p, &p, 16);
	}
	return v;
}

static MfciObj* mfci_alloc(void)
{
	MfciObj* hn;
	s32 i;

	hn = NULL;
	for (i = 0; i < MFCI_OBJ_MAX; i++) {
		if (mfci_ObjTbl[i].stat == 0) {
			hn = &mfci_ObjTbl[i];
			break;
		}
	}
	return hn;
}

static void mfci_SetNsct(MfciObj* hn)
{
	s32 n;

	n        = hn->sctsize + hn->size;
	n        = n - 1;
	hn->nsct = n / hn->sctsize;
}

s32 fn_80222A14(MfciObj* hn)
{
	if (hn == NULL) {
		mfci_ErrorN("E0092912:handl is null.");
		return 0;
	}
	return hn->total;
}

void fn_80222A74(MfciObj* hn, s32 sctsize)
{
	s32 total;

	if (hn == NULL) {
		mfci_ErrorN("E0040302:handl is null.");
		return;
	}
	total       = hn->pos * hn->sctsize;
	hn->sctsize = sctsize;
	mfci_SetNsct(hn);
	hn->pos   = total / hn->sctsize;
	hn->total = hn->rdsct * sctsize;
}

s32 fn_80222B0C(MfciObj* hn)
{
	if (hn == NULL) {
		mfci_ErrorN("E0040301:handl is null.");
		return 0;
	}
	return hn->sctsize;
}

s32 fn_80222B6C(MfciObj* hn)
{
	if (hn == NULL) {
		mfci_ErrorN("E0092912:handl is null.");
		return 0;
	}
	return hn->busy;
}

void fn_80222BD0(MfciObj* hn)
{
	if (hn == NULL) {
		mfci_ErrorN("E0092912:handl is null.");
		return;
	}
	fn_802229AC();
	hn->busy = 0;
	fn_8022291C();
}

s32 fn_80222C40(MfciObj* hn, s32 nsct, void* buf)
{
	s32 rest;
	u32 adr;
	u32 size;
	s32 n;

	if (hn == NULL) {
		mfci_ErrorN("E01100307:handl is null.");
		return 0;
	}
	if (nsct < 0) {
		mfci_Error("E01100308:nsct < 0.(mfCiReqRd)", hn);
		return 0;
	}
	if (buf == NULL) {
		mfci_Error("E01100309:buf is null.(mfCiReqRd)", hn);
		return 0;
	}
	if (nsct == 0) {
		hn->busy = 1;
		return 0;
	}

	fn_802229AC();
	hn->total = 0;
	rest      = hn->nsct - hn->pos;
	hn->rdsct = nsct < rest ? nsct : rest;
	{
		s32 ofst  = hn->pos * hn->sctsize;
		s32 nbyte = hn->rdsct * hn->sctsize;
		if (nbyte == 0) {
			hn->busy = 1;
			fn_8022291C();
			return 0;
		}
		hn->ofst  = ofst;
		hn->nbyte = nbyte;
	}
	hn->busy = 2;
	adr      = mfci_get_adr_size(hn->fname, &size);
	n        = hn->nbyte;
	if (n > (s32)(size - hn->ofst)) {
		n = (s32)(size - hn->ofst);
	}
	memcpy(buf, (void*)(adr + hn->ofst), hn->nbyte);
	memset((s8*)buf + n, 0, hn->nbyte - n);
	hn->total = hn->rdsct * hn->sctsize;
	hn->pos   = hn->pos + hn->rdsct;
	hn->busy  = 1;
	fn_8022291C();
	return hn->rdsct;
}

s32 fn_80222EC8(MfciObj* hn)
{
	if (hn == NULL) {
		mfci_ErrorN("E01100306:handl is null.");
		return 0;
	}
	return hn->pos;
}

s32 fn_80222F28(MfciObj* hn, s32 off, s32 whence)
{
	if (hn == NULL) {
		mfci_ErrorN("E01100305:handl is null.");
		return 0;
	}
	fn_802229AC();
	if (whence == 0) {
		hn->pos = off;
	} else if (whence == 2) {
		hn->pos = hn->nsct + off;
	} else if (whence == 1) {
		hn->pos = hn->pos + off;
	}
	hn->pos = hn->pos < hn->nsct ? hn->pos : hn->nsct;
	if (hn->pos > 0) {
	} else {
		hn->pos = 0;
	}
	fn_8022291C();
	return hn->pos;
}

void fn_8022301C(MfciObj* hn)
{
	if (hn == NULL) {
		return;
	}
	if (hn == NULL) {
		mfci_ErrorN("E0092912:handl is null.");
	} else {
		fn_802229AC();
		hn->busy = 0;
		fn_8022291C();
	}
	if (hn->stat == 1) {
		hn->stat = 0;
		memset(hn, 0, sizeof(MfciObj));
	}
}

MfciObj* fn_802230B4(const char* fname, s32 mode, s32 rw)
{
	MfciObj* hn;
	u32 size;

	if (fname == NULL) {
		mfci_ErrorN("E01100301:fname is null.(mfCiOpen)");
		return NULL;
	}
	if (rw != 0) {
		mfci_ErrorN("E01100302:rw is illigal.(mfCiOpen)");
		return NULL;
	}
	hn = mfci_alloc();
	if (hn == NULL) {
		mfci_ErrorN("E01100303:not enough handle resource.(mfCiOpen)");
		return NULL;
	}
	strcpy(hn->fname, fname);
	hn->sctsize = MFCI_SCT_SIZE;
	mfci_get_adr_size(hn->fname, &size);
	hn->size = size;
	mfci_SetNsct(hn);
	hn->pos   = 0;
	hn->rdsct = 0;
	hn->total = 0;
	hn->busy  = 0;
	hn->stat  = 1;
	return hn;
}

u32 fn_802232E4(const char* fname)
{
	u32 size;

	mfci_get_adr_size(fname, &size);
	return size;
}

void fn_802233F0(MfciErrFunc func, void* obj)
{
	mfci_ErrFunc = func;
	mfci_ErrObj  = obj;
}

// Empty on the PS2 build too (eight bytes, `jr ra`), where the caller guards
// the call with the same stat test. Folding the test into the callee is the
// one shape that keeps the loop alive here; see the header.
static void mfCiExecHndl(MfciObj* hn)
{
	if (hn->stat == 0) {
		return;
	}
}

void fn_80223404(void)
{
	s32 i;

	for (i = 0; i < MFCI_OBJ_MAX; i++) {
		mfCiExecHndl(&mfci_ObjTbl[i]);
	}
}

void* fn_80223410(void)
{
	(void)mfci_verptr;
	return mfci_IfTbl;
}
