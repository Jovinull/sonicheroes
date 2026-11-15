// Translucent draw of an effect object (HYPOTHESIS: its TDisp; the class name is UNKNOWN): saves
// render states 0xA, 0xB, 0x14 and 0xE (fn_80194294), sets them to 5, 2, 1 and 0 (fn_80194234;
// HYPOTHESIS: source/destination blend, cull mode and z-write), gives the material lbl_8042C520 the
// object's alpha (+0x29), renders the clump (+0x34, fn_8014FF2C) and restores the states. The
// sibling effects fn_800F638C, fn_800F668C, fn_800F9A8C and fn_800F9DC8 differ only in the
// material.
#include "types.h"

struct RGBA800F9DC8 {
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
};

struct Material800F9DC8 {
	u8 pad0[4];
	RGBA800F9DC8 color; // 0x4
};

struct Effect800F9DC8 {
	u8 pad0[0x29];
	u8 alpha; // 0x29
	u8 pad2A[0x34 - 0x2A];
	void* clump; // 0x34
};

extern "C" {
extern Material800F9DC8* lbl_8042C520;
void fn_80194294(s32 state, void* value);
void fn_80194234(s32 state, s32 value);
void fn_8014FF2C(void* clump);
}

// Renders the clump with the material at the effect's alpha.
static inline void RenderWithAlpha(Effect800F9DC8* effect, void* clump)
{
	if (lbl_8042C520 != NULL) {
		RGBA800F9DC8 color;

		color.red           = lbl_8042C520->color.red;
		color.green         = lbl_8042C520->color.green;
		color.blue          = lbl_8042C520->color.blue;
		color.alpha         = effect->alpha;
		lbl_8042C520->color = color;
	}
	fn_8014FF2C(clump);
}

extern "C" void fn_800F9DC8(Effect800F9DC8* effect)
{
	s32 blendSource;
	s32 blendDest;
	s32 cullMode;
	s32 zWrite;

	fn_80194294(0xA, &blendSource);
	fn_80194294(0xB, &blendDest);
	fn_80194294(0x14, &cullMode);
	fn_80194294(0xE, &zWrite);
	fn_80194234(0xA, 5);
	fn_80194234(0xB, 2);
	fn_80194234(0x14, 1);
	fn_80194234(0xE, 0);
	RenderWithAlpha(effect, effect->clump);
	fn_80194234(0xE, zWrite);
	fn_80194234(0x14, cullMode);
	fn_80194234(0xA, blendSource);
	fn_80194234(0xB, blendDest);
}
