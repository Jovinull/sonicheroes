#include "types.h"

// CRI SFX for GameCube: module init/teardown and the handle table.
//
// The translation unit runs from fn_17_E2F4 at 0xE2F4 to the end of
// fn_17_E810 at 0xE89C, owns .rodata 0x800 to 0x8A0 and .bss 0xD0 to 0x588.
// The module ships no map, so the bounds are argued rather than read. Three
// independent lines agree:
//
//   The .rodata block opens with the module's own version banner,
//   "\nCRI SFX/GC Ver.1.24 Build:May  9 2003 15:19:50\n", followed by the
//   three errors this file can raise. CRI puts that banner in the module's
//   main source file, and every string in the block names something declared
//   here: sfx_InitHn, and the Z and A handles it creates.
//
//   The data is private to the run. lbl_17_bss_D4 is touched by exactly
//   fn_17_E2FC and fn_17_E30C, the block at lbl_17_bss_D8 by exactly the
//   eight functions from fn_17_E318 to fn_17_E7B8, lbl_17_bss_D0 by exactly
//   fn_17_E76C and fn_17_E810, and lbl_17_rodata_800 by exactly fn_17_E4E4,
//   fn_17_E804 and fn_17_E810. 0xE89C is the first cut where nothing leaks
//   forward or back.
//
//   The neighbours settle both ends. The unit before is sfxcnv.c, which ends
//   at 0xE2F4. After 0xE89C the functions work on a different object:
//   fn_17_E89C, fn_17_E8B8 and fn_17_E8D0 all address fields 0x4, 0x8, 0xC
//   and 0x10 of a struct sfxcnv.c reaches through handle->alpha, and the run
//   from 0xE8FC shares lbl_17_bss_588, a disjoint private block that starts
//   exactly where this file's .bss ends.
//
// Only sfx_InitHn is named from evidence; the rest keep their dtk names
// because nothing in the module spells them.
//
// fn_17_E338 and fn_17_E3FC are written once and inlined into fn_17_E4E4 by
// -inline auto, which is why the original emits a standalone body for each
// and a second copy inside fn_17_E4E4.
//
// It is built with -lang=c++ for the .bss ordering noted below, and with
// -bool off alongside it. Without that, a comparison has type bool and the
// compiler truncates the result to a byte, so fn_17_E3E4 and the copy of it
// inlined into fn_17_E4E4 each gain a clrlwi the original does not have.

typedef struct SfxHn {
	s32 used;       // 0x00
	s32 unk4;       // 0x04
	s32 unk8;       // 0x08
	s32 unkC;       // 0x0C
	u8 unk10[0x10]; // 0x10
	void* zhn;      // 0x20
	s32 unk24;      // 0x24
	s32 unk28;      // 0x28
	void* ahn;      // 0x2C
	u8 unk30[0x4];  // 0x30
	s32 unk34;      // 0x34
	u32 work;       // 0x38
	u32 buf1;       // 0x3C
	u32 buf2;       // 0x40
	u32 buf3;       // 0x44
	u8 unk48[0x8];  // 0x48
	void* workptr;  // 0x50
	s32 worksize;   // 0x54
	u8 unk58[0x8];  // 0x58
	s32 unk60;      // 0x60
	u8 unk64[0x2C]; // 0x64
} SfxHn;

typedef struct SfxGlobals {
	s32 numHn;                           // 0x00
	s32 maxHn;                           // 0x04
	void (*errFunc)(void*, const char*); // 0x08
	void* errObj;                        // 0x0C
	s32 errCount;                        // 0x10
	s32 unk14;                           // 0x14
	SfxHn hn[8];                         // 0x18
	u8 unk498[0x10];                     // 0x498
} SfxGlobals;

// The whole .rodata block is one pooled string object: the banner at 0x00 and
// the three errors at 0x34, 0x60 and 0x80, addressed off a single base.
extern "C" const char sfx_version[] = "\nCRI SFX/GC Ver.1.24 Build:May  9 2003 15:19:50\n";
#define SFX_ERR_WORKSIZE "E201194: sfx_InitHn: work size is short."
#define SFX_ERR_ZHN      "E201281: SfxZHn: can't create."
#define SFX_ERR_AHN      "E202011: SfxAHn: can't create."

extern "C" void* memset(void* dst, int fill, u32 len);

extern "C" void fn_17_10980(void*);
extern "C" void* fn_17_109F0();
extern "C" void fn_17_10A60(void);
extern "C" void fn_17_10AAC(void);
extern "C" void fn_17_10B6C(void);
extern "C" void fn_17_10B8C(void);
extern "C" void fn_17_5ED04(void);
extern "C" void fn_17_E940(void*);
extern "C" void* fn_17_E9C0(void*);
extern "C" void fn_17_EA3C(void);
extern "C" void fn_17_EA80(void);

// The order below is the order the original lays them out in, and it only
// survives because the file is compiled as C++. In C this compiler emits .bss
// in order of first reference, which puts lbl_17_bss_D4 first because
// fn_17_E2FC reaches it before anything touches the table; in C++ it emits
// declaration order.
//
// The banner pointer is its own object rather than the last field of the
// table. The two are adjacent and the table's memset stops just short of it,
// so either reading fits the addresses, but only this one produces the code:
// fn_17_E810 reaches the pointer off the block base while the table's own
// address is already live in another register, which a member of the table
// would never do.
static s32 lbl_17_bss_D0;          // 0xD0
static s32 lbl_17_bss_D4;          // 0xD4
static SfxGlobals lbl_17_bss_D8;   // 0xD8
static const char* lbl_17_bss_580; // 0x580
static s32 lbl_17_bss_584;         // 0x584

extern "C" s32 fn_17_E2F4(void)
{
	return 0x11;
}

extern "C" s32 fn_17_E2FC(void)
{
	return lbl_17_bss_D4;
}

extern "C" void fn_17_E30C(s32 arg0)
{
	lbl_17_bss_D4 = arg0;
}

extern "C" s32 fn_17_E318(void)
{
	return lbl_17_bss_D8.unk14;
}

extern "C" void fn_17_E328(s32 arg0)
{
	lbl_17_bss_D8.unk14 = arg0;
}

extern "C" void fn_17_E338(void* arg0, void* arg1, const char* msg)
{
	void (*errFunc)(void*, const char*) = lbl_17_bss_D8.errFunc;
	void* errObj                        = lbl_17_bss_D8.errObj;

	lbl_17_bss_D8.errCount++;
	if (errFunc != NULL) {
		errFunc(errObj, msg);
	}
}

extern "C" void fn_17_E384(SfxHn* hn)
{
	if (hn != NULL) {
		void* zhn = hn->zhn;
		void* ahn = hn->ahn;

		hn->used = 0;
		fn_17_10980(zhn);
		fn_17_E940(ahn);
		lbl_17_bss_D8.numHn--;
	}
}

extern "C" s32 fn_17_E3E4(s32 worksize)
{
	return worksize >= 0x301F;
}

extern "C" void fn_17_E3FC(SfxHn* hn, void* work, s32 worksize)
{
	memset(hn, 0, sizeof(SfxHn));
	hn->unk4     = 0;
	hn->unk8     = 0;
	hn->unkC     = 0;
	hn->unk24    = 1;
	hn->unk28    = 0;
	hn->unk34    = 0;
	hn->work     = ((u32)work + 0x1F) & ~0x1F;
	hn->buf1     = hn->work + 0x400;
	hn->buf2     = hn->buf1 + 0x400;
	hn->buf3     = hn->buf2 + 0x400;
	hn->workptr  = work;
	hn->worksize = worksize;
	hn->unk60    = -1;
	hn->used     = 1;
}

extern "C" SfxHn* fn_17_E4AC(void)
{
	SfxHn* hn = lbl_17_bss_D8.hn;
	s32 i;

	for (i = lbl_17_bss_D8.maxHn; i > 0; i--) {
		if (hn->used == 0) {
			return hn;
		}
		hn++;
	}
	return NULL;
}

#pragma opt_propagation off
extern "C" SfxHn* fn_17_E4E4(void* work, s32 worksize)
{
	SfxHn* hn = fn_17_E4AC();
	void* zhn;
	void* ahn;
	s32 valid;

	if (hn == NULL) {
		return hn;
	}
	valid = fn_17_E3E4(worksize);
	if (valid != 1) {
		fn_17_E338(NULL, NULL, SFX_ERR_WORKSIZE);
		return NULL;
	}

	fn_17_E3FC(hn, work, worksize);

	zhn = fn_17_109F0();
	if (zhn == NULL) {
		fn_17_E338(NULL, NULL, SFX_ERR_ZHN);
		fn_17_E384(hn);
		return NULL;
	}

	hn->zhn = zhn;
	ahn     = fn_17_E9C0(zhn);
	if (ahn == NULL) {
		fn_17_E338(NULL, NULL, SFX_ERR_AHN);
		fn_17_E384(hn);
		return NULL;
	}

	hn->ahn = ahn;
	lbl_17_bss_D8.numHn++;
	return hn;
}
#pragma opt_propagation on

extern "C" void fn_17_E758(void (*errFunc)(void*, const char*), void* errObj)
{
	lbl_17_bss_D8.errFunc = errFunc;
	lbl_17_bss_D8.errObj  = errObj;
}

extern "C" void fn_17_E76C(void)
{
	if (lbl_17_bss_D0 > 0) {
		fn_17_10A60();
		fn_17_EA3C();
		fn_17_10B6C();
		lbl_17_bss_D0--;
	}
}

extern "C" void fn_17_E7B8(void)
{
	memset(&lbl_17_bss_D8, 0, sizeof(lbl_17_bss_D8));
	lbl_17_bss_D8.maxHn = 8;
	lbl_17_bss_D8.unk14 = 1;
	fn_17_5ED04();
}

extern "C" const char* fn_17_E804(void)
{
	return sfx_version;
}

extern "C" void fn_17_E810(void)
{
	if (lbl_17_bss_D0 < 1) {
		lbl_17_bss_580 = sfx_version;
		memset(&lbl_17_bss_D8, 0, sizeof(lbl_17_bss_D8));
		lbl_17_bss_D8.maxHn = 8;
		lbl_17_bss_D8.unk14 = 1;
		fn_17_5ED04();
		fn_17_10B8C();
		fn_17_10AAC();
		fn_17_EA80();
		lbl_17_bss_D4 = 0;
		lbl_17_bss_D0++;
	}
}
