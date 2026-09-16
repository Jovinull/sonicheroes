#include "cri/adapter.h"
#include "MSL_C/string.h"
#include "cri/sjcrs.h"

// CRI adapter glue sitting between MFCI and AXRNA: an error hook with its own
// message buffer, two forwarders onto the shared refcounted lock, and four
// adapter entrypoints that a wrapper layer one module down calls through.
//
// The unit runs from fn_80223424 at 0x80223424 to the end of fn_802234F0 at
// 0x80223500 and owns .bss 0x80428970 to 0x80428A78. It owns no .rodata and no
// .data. The disc ships no map, so the bounds are argued rather than read:
//
//   The .bss block is private to fn_80223424 and fn_8022347C: a callback,
//   its object pointer, and a message buffer. Their sizes, 4, 4 and 0x100,
//   add to 0x108 and land exactly on 0x80428A78,
//   where the next unit's first private block begins.
//
//   The lower bound is settled by the neighbour. game/cri/mfci.c ends at
//   0x80223424. Its private .bss pool ends at 0x8042896C, four bytes before
//   this unit's first object at 0x80428970.
//
//   The upper bound is the first cut where no data crosses. fn_80223500 and
//   everything above it work on lbl_8029BAB4 and lbl_80429B4C, which belong to
//   the AXRNA run and are reached from nowhere below 0x80223500.
//
//   The six functions after fn_8022347C touch no data at all, so they are
//   placed by their neighbours rather than by ownership. They group here
//   because the four final entrypoints are called only from fn_8021B37C,
//   fn_8021B39C, fn_8021B3C4 and fn_8021B3E4 -- four thin wrappers sitting
//   together in a single adapter layer, which is the shape this file serves.
//
// Nothing here is named: there is no version banner in the unit and no error
// string carries a function name, so every function keeps its dtk name.
//
// Explicit NULL initialization reproduces the callback pair before the message
// buffer in ordinary C BSS, without an artificial layout-touching function.
// These private names and the unavailable original filename remain inferred.

static CriErrFunc cri_ErrFunc = NULL;
static void* cri_ErrObj       = NULL;
static char cri_ErrMsg[256];

void fn_80223424(const char* msg)
{
	strncpy(cri_ErrMsg, msg, 255);
	if (cri_ErrFunc != NULL) {
		cri_ErrFunc(cri_ErrObj, cri_ErrMsg);
	}
}

void fn_8022347C(CriErrFunc func, void* obj)
{
	cri_ErrFunc = func;
	cri_ErrObj  = obj;
}

void fn_80223490(void)
{
	fn_80220544();
}

void fn_802234B0(void)
{
	fn_80220590();
}

void fn_802234D0(void* p, s16 v)
{
	if (p == NULL) {
		return;
	}
	*(s16*)((s8*)p + 0xA0) = v;
}

s32 fn_802234E0(void)
{
	return 0;
}

s32 fn_802234E8(void)
{
	return 0;
}

void fn_802234F0(void* p, s32 v)
{
	if (p == NULL) {
		return;
	}
	*(s32*)((s8*)p + 0x80) = v;
}
