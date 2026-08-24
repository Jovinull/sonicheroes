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

typedef struct GcciObj {
	/* 0x00 */ s8 pad00[2];
	/* 0x02 */ s8 unk02;
	/* 0x03 */ s8 pad03[0xD];
	/* 0x10 */ s32 unk10;
	/* 0x14 */ s32 pad14;
	/* 0x18 */ s32 unk18;
	/* 0x1C */ s32 unk1C;
	/* 0x20 */ s32 unk20;
} GcciObj;

static GcciErrFunc gcci_ErrFunc;
static void* gcci_ErrObj;

extern const char gcci_ErrHandl[];
extern const char gcci_ErrHandl2[];
extern const char gcci_ErrSize[];
extern const char gcci_ErrHandl3[];

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
	return p->unk20;
}

s32 fn_8021E51C(GcciObj* p)
{
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl3);
		return 0;
	}
	return p->unk10;
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
	return p->unk02;
}

s32 fn_8021EBA8(GcciObj* p)
{
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl);
		return 0;
	}
	return p->unk1C;
}

s32 fn_8021EC08(GcciObj* p, s32 off, s32 whence)
{
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl);
		return 0;
	}
	if (whence == 0) {
		p->unk1C = off;
	} else if (whence == 2) {
		p->unk1C = p->unk18 + off;
	} else if (whence == 1) {
		p->unk1C = p->unk1C + off;
	}
	p->unk1C = p->unk1C < p->unk18 ? p->unk1C : p->unk18;
	if (p->unk1C > 0) {
	} else {
		p->unk1C = 0;
	}
	return p->unk1C;
}
