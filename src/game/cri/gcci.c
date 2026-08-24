#include "types.h"

// CRI GCCI for GameCube: the file layer the stream controller sits on, wrapping
// the Dolphin DVD calls behind CRI's handle and error conventions.
//
// The unit runs from fn_8021E3D8 at 0x8021E3D8 to the end of fn_8021F404 at
// 0x8021F410, fifteen functions, and owns .rodata 0x8023FBC0 to 0x8023FDF8,
// .data 0x8029B7B8 to 0x8029B828 and .bss 0x8041F6B8 to 0x80420770. The disc
// ships no map, so the bounds are argued. Four lines agree:
//
//   The .rodata opens with the module's own version banner, "\nGCCI Ver.1.09
//   Build:May  9 2003 17:09:53\n", and every other string in the block is one
//   of this module's messages. CRI writes the banner into the library's main
//   source file.
//
//   Every .rodata, .data and .bss label the run touches has all of its users
//   inside the run. That was checked one label at a time, eleven of them, and
//   not one leaks: the error hook pair at 0x8041F6C4 and 0x8041F6C8 is reached
//   by eight functions here and by nothing else in the binary.
//
//   All three data sections are contiguous and abut their neighbours exactly.
//   The .rodata ends at 0x8023FDF8, which is where game/cri/lsc.c's begins.
//
//   The lower bound is the first cut where no data crosses; below it
//   fn_8021E118 and fn_8021E3D8 share nothing. The upper bound is fn_8021F410,
//   the shared error reporter that lsc.c also calls, so it belongs to neither.
//
// Nothing is named yet. The messages here carry no function names -- unlike
// MFCI and LSC, whose "(mfCiOpen)" and "(LSC_Create)" suffixes gave the naming
// away -- so every function keeps its dtk name until something anchors it.

typedef void (*GcciErrFunc)(void* obj, const char* msg, void* arg);

// The handle mirrors MFCI's, shifted by 0x0C: the same sector size, size,
// sector count, position, total and read-count run, in the same order.
typedef struct GcciObj {
	/* 0x00 */ s8 pad00[2];
	/* 0x02 */ s8 stat;
	/* 0x03 */ s8 pad03[0xD];
	/* 0x10 */ s32 sctsize;
	/* 0x14 */ s32 size;
	/* 0x18 */ s32 nsct;
	/* 0x1C */ s32 pos;
	/* 0x20 */ s32 total;
	/* 0x24 */ s32 rdsct;
} GcciObj;

static GcciErrFunc gcci_ErrFunc;
static void* gcci_ErrObj;

extern const char gcci_ErrHandl[];
extern const char gcci_ErrHandl2[];
extern const char gcci_ErrSize[];
extern const char gcci_ErrHandl3[];

static void gcci_SetNsct(GcciObj* p)
{
	s32 n;

	n       = p->sctsize + p->size;
	n       = n - 1;
	p->nsct = n / p->sctsize;
}

static void gcci_Error(const char* msg)
{
	if (gcci_ErrFunc != NULL) {
		gcci_ErrFunc(gcci_ErrObj, msg, NULL);
	}
}

s32 fn_8021E3D8(GcciObj* p)
{
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl);
		return 0;
	}
	return p->total;
}

s32 fn_8021E51C(GcciObj* p)
{
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl3);
		return 0;
	}
	return p->sctsize;
}

void fn_8021F20C(GcciErrFunc func, void* obj)
{
	gcci_ErrFunc = func;
	gcci_ErrObj  = obj;
}

s32 fn_8021E57C(GcciObj* p)
{
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl);
		return 0;
	}
	return p->stat;
}

s32 fn_8021EBA8(GcciObj* p)
{
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl);
		return 0;
	}
	return p->pos;
}

s32 fn_8021EC08(GcciObj* p, s32 off, s32 whence)
{
	s32 pos;

	if (p == NULL) {
		gcci_Error(gcci_ErrHandl);
		return 0;
	}
	if (whence == 0) {
		p->pos = off;
	} else if (whence == 2) {
		p->pos = p->nsct + off;
	} else if (whence == 1) {
		p->pos = p->pos + off;
	}
	p->pos = p->pos < p->nsct ? p->pos : p->nsct;
	pos    = p->pos;
	if (pos > 0) {
		if (pos && pos) {
		}
	} else {
		pos = 0;
	}
	p->pos = pos;
	return p->pos;
}

void fn_8021E438(GcciObj* p, s32 sctsize)
{
	s32 total;

	if (p == NULL) {
		gcci_Error(gcci_ErrHandl2);
		return;
	}
	if (p->sctsize % 32 != 0) {
		gcci_Error(gcci_ErrSize);
		return;
	}
	total      = p->pos * p->sctsize;
	p->sctsize = sctsize;
	gcci_SetNsct(p);
	p->pos   = total / p->sctsize;
	p->total = p->rdsct * sctsize;
}
