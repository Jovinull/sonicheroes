// Static initializer of the live save data lbl_803E774C (HYPOTHESIS; the save block of
// nMemoryCardUtil, 0x708 bytes plus a word; its destructor is fn_80116DF8): clears the save and
// its block at 0x18, sets a few fields, fills the thirteen name pairs at 0x553 with the default
// two-letter names lbl_80288DF0 (each copy NUL-terminated through the inline helper) and
// registers it so its destructor runs at shutdown (chain node lbl_803E7740). The hand-written
// .ctors entry follows game/fn_80052150.cpp.
#include "types.h"
#include "MSL_C/string.h"

struct Names801186B0 {
	u8 first[3];  // +0
	u8 second[3]; // +3
};

struct Block801186B0 {
	u8 pad0[0x4];
	u8 f1C; // 0x1C
	u8 f1D; // 0x1D
	u8 pad6[0x20 - 0x6];
	s32 f38; // 0x38
};

struct Save801186B0 {
	u8 pad0[0x18];
	Block801186B0 block18; // 0x18
	s32 f3C;               // 0x3C
	s32 f40;               // 0x40
	s32 f44;               // 0x44
	s32 f48;               // 0x48
	u8 pad4C[0x553 - 0x4C];
	Names801186B0 names[13]; // 0x553
	u8 pad5A1[0x6F2 - 0x5A1];
	u8 f6F2; // 0x6F2
	u8 f6F3; // 0x6F3
	u8 pad6F4[0x708 - 0x6F4];
	s32 f708; // 0x708
};

extern "C" {
void __register_global_object(void* object, void* destructor, void* node);
void* fn_80116DF8(void* p, s16 flags);

extern Save801186B0 lbl_803E774C;
extern u8 lbl_803E7740[12];
extern u8 lbl_80288DF0[13][2];

static inline void SetName801186B0(void* dst, const u8* src)
{
	u8* name = (u8*)dst;
	name[0]  = src[0];
	name[1]  = src[1];
	name[2]  = 0;
}

void fn_801186B0(void)
{
	memset(&lbl_803E774C, 0, 0x708);
	memset(&lbl_803E774C.block18, 0, sizeof(lbl_803E774C.block18));
	lbl_803E774C.block18.f1C = 1;
	lbl_803E774C.block18.f1D = 1;
	lbl_803E774C.block18.f38 = 0;
	for (s32 i = 0; i < 13; i++) {
		SetName801186B0(lbl_803E774C.names[i].first, lbl_80288DF0[i]);
		SetName801186B0(lbl_803E774C.names[i].second, lbl_80288DF0[i]);
	}
	lbl_803E774C.f3C  = 3;
	lbl_803E774C.f40  = 3;
	lbl_803E774C.f44  = 3;
	lbl_803E774C.f48  = 3;
	lbl_803E774C.f6F2 = 1;
	lbl_803E774C.f6F3 = 1;
	lbl_803E774C.f708 = -1;
	__register_global_object(&lbl_803E774C, (void*)fn_80116DF8, lbl_803E7740);
}
}

__declspec(section ".ctors") void (*const fn801186B0CtorEntry)(void) = fn_801186B0;
