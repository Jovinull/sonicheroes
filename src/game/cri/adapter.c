#include "types.h"

// CRI adapter glue sitting between MFCI and AXRNA: an error hook with its own
// message buffer, two forwarders onto the shared refcounted lock, and four
// setters that a wrapper layer one module down calls through.
//
// The unit runs from fn_80223424 at 0x80223424 to the end of fn_802234F0 at
// 0x80223500 and owns .bss 0x80428970 to 0x80428A78. It owns no .rodata and no
// .data. The disc ships no map, so the bounds are argued rather than read:
//
//   The .bss block is private. lbl_80428970 and lbl_80428974 are touched by
//   exactly fn_80223424 and fn_8022347C, and by nothing else in the binary.
//   Their sizes, 4 and 0x104, add to 0x108 and land exactly on 0x80428A78,
//   where the next unit's first private block begins.
//
//   The lower bound is settled by the neighbour. game/cri/mfci.c ends at
//   0x80223424, and its own .bss ends at 0x80428970, exactly where this one
//   starts.
//
//   The upper bound is the first cut where no data crosses. fn_80223500 and
//   everything above it work on lbl_8029BAB4 and lbl_80429B4C, which belong to
//   the AXRNA run and are reached from nowhere below 0x80223500.
//
//   The six functions after fn_8022347C touch no data at all, so they are
//   placed by their neighbours rather than by ownership. They group here
//   because the four setters are called only from fn_8021B37C, fn_8021B39C,
//   fn_8021B3C4 and fn_8021B3E4 -- four thin wrappers, one per setter, sitting
//   together in a single adapter layer, which is the shape this file serves.
//
// Nothing here is named: there is no version banner in the unit and no error
// string carries a function name, so every function keeps its dtk name.
//
// One reconstruction is a hypothesis rather than a reading. MWCC lays .bss out
// in order of first reference, not of declaration, and the only reference order
// that puts the buffer at offset 8 is one where the hook pair is touched first.
// No surviving function does that -- fn_80223424 reaches the buffer before
// either -- so the original must have had something above it that did.
// cri_GetErrFunc below stands in for it. The linker drops it, all eight target
// functions are byte-exact, and the artifact hashes are unchanged; what is
// unproven is the shape of the function that produced the layout, not the
// layout itself.

typedef void (*CriErrFunc)(void* obj, const char* msg);

extern char* strncpy(char* dst, const char* src, u32 n);
extern void fn_80220544(void);
extern void fn_80220590(void);

static CriErrFunc cri_ErrFunc;
static void* cri_ErrObj;
static char cri_ErrMsg[256];

// Never called. Reconstructed because the original must have touched the hook
// pair before the buffer: MWCC lays .bss out in order of first reference, and
// that is the only order that puts the buffer at offset 8.
static CriErrFunc cri_GetErrFunc(void)
{
	if (cri_ErrObj != NULL) {
		return cri_ErrFunc;
	}
	return NULL;
}

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
