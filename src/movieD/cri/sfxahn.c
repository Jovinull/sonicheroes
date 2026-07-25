#include "types.h"

// CRI SFX for GameCube: the alpha handle table.
//
// The translation unit runs from fn_17_E89C at 0xE89C to the end of
// fn_17_EA80 at 0xEAC0, and owns .bss 0x588 to 0x630. It has no .rodata. The
// module ships no map, so the bounds are argued rather than read:
//
//   The block at lbl_17_bss_588 is touched by exactly five functions, all
//   inside this run, and nothing else in the module reaches it. It is the
//   only data the run refers to, so 0xEAC0 is the first cut where nothing
//   leaks forward or back. Its size settles the .bss bound on its own: dtk
//   reads it as 0xA8, which is the two counters plus eight entries of 0x14,
//   and lbl_17_bss_630 after it belongs to the run that starts at 0xEAC0.
//
//   The unit before is sfx.c, which ends at 0xE89C. The first three functions
//   here address fields 0x4, 0x8, 0xC and 0x10 of the object sfxcnv.c reaches
//   through handle->alpha, and sfx.c creates one of these for every handle it
//   opens, which is what the error it raises on failure calls SfxAHn.
//
// The file is named after that type rather than from evidence: SfxAHn is
// spelled in the binary, the source file name is not.
//
// fn_17_E964 and fn_17_E988 are written once and inlined into fn_17_E9C0 by
// -inline auto, so the original emits a standalone body for each and a second
// copy inside fn_17_E9C0. fn_17_EA40 and fn_17_EA80 really are the same
// function twice.

typedef struct SfxAHn {
	s32 used; // 0x00
	s32 unk4; // 0x04
	s32 unk8; // 0x08
	s32 unkC; // 0x0C
	s32 unk10; // 0x10
} SfxAHn;

typedef struct SfxAGlobals {
	s32 numHn; // 0x00
	s32 maxHn; // 0x04
	SfxAHn hn[8]; // 0x08
} SfxAGlobals;

extern void* memset(void* dst, int fill, u32 len);

extern void fn_17_5CC3C(void*);
extern void fn_17_5D4D0(s32, s32, s32, void*);

static SfxAGlobals lbl_17_bss_588;

void fn_17_E89C(SfxAHn* hn, s32* arg1, s32* arg2, s32* arg3)
{
	*arg3 = hn->unk8;
	*arg1 = hn->unkC;
	*arg2 = hn->unk10;
}

void fn_17_E8B8(SfxAHn* hn, s32 arg1, s32 arg2, s32 arg3)
{
	hn->unk8 = arg3;
	hn->unkC = arg1;
	hn->unk10 = arg2;
	hn->unk4 = 1;
}

s32 fn_17_E8D0(SfxAHn* hn)
{
	return hn->unk4;
}

void fn_17_E8D8(SfxAHn* hn, s32 arg1, void* arg2)
{
	fn_17_5CC3C(arg2);
}

void fn_17_E8FC(SfxAHn* hn, s32 arg1, void* arg2)
{
	fn_17_5D4D0(hn->unk8, hn->unkC, hn->unk10, arg2);
	hn->unk4 = 0;
}

void fn_17_E940(SfxAHn* hn)
{
	if (hn != NULL) {
		hn->used = 0;
		lbl_17_bss_588.numHn--;
	}
}

void fn_17_E964(SfxAHn* hn)
{
	hn->unk8 = 0;
	hn->unkC = 0x1F;
	hn->unk10 = 0x64;
	hn->unk4 = 1;
}

SfxAHn* fn_17_E988(void)
{
	SfxAHn* hn = lbl_17_bss_588.hn;
	s32 i;

	for (i = lbl_17_bss_588.maxHn; i > 0; i--) {
		if (hn->used == 0) {
			return hn;
		}
		hn++;
	}
	return NULL;
}

SfxAHn* fn_17_E9C0(void)
{
	SfxAHn* hn = fn_17_E988();

	if (hn == NULL) {
		return hn;
	}
	fn_17_E964(hn);
	lbl_17_bss_588.numHn++;
	hn->used = 1;
	return hn;
}

void fn_17_EA3C(void)
{
}

void fn_17_EA40(void)
{
	memset(&lbl_17_bss_588, 0, sizeof(lbl_17_bss_588));
	lbl_17_bss_588.maxHn = 8;
}

void fn_17_EA80(void)
{
	memset(&lbl_17_bss_588, 0, sizeof(lbl_17_bss_588));
	lbl_17_bss_588.maxHn = 8;
}
