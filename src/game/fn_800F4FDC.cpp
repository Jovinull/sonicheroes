// Translucent draw of an effect object (HYPOTHESIS: its TDisp; see fn_800F638C): saves render
// states 0xA, 0xB, 0x14 and 0xE, sets them to 5, 2, 1 and 0, makes the material lbl_8042C4DC
// white with the object's alpha (+0x28), refreshes lbl_8042C4F4 from +0x30 of lbl_8042C180,
// renders the clump (+0x2C, fn_8014FF2C) and restores the states. The roles are UNKNOWN.
#include "types.h"

struct RGBA800F4FDC {
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
};

struct Material800F4FDC {
	u8 pad0[4];
	RGBA800F4FDC color; // 0x4
};

struct Effect800F4FDC {
	u8 pad0[0x28];
	u8 alpha; // 0x28
	u8 pad29[0x2C - 0x29];
	void* clump; // 0x2C
};

struct State800F4FDC {
	u8 pad0[0x30];
	s32 unknown30; // 0x30
};

extern "C" {
extern Material800F4FDC* lbl_8042C4DC;
extern State800F4FDC* lbl_8042C180;
extern s32 lbl_8042C4F4;
void fn_80194294(s32 state, void* value);
void fn_80194234(s32 state, s32 value);
void fn_8014FF2C(void* clump);
}

extern "C" void fn_800F4FDC(Effect800F4FDC* effect)
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
	if (lbl_8042C4DC != NULL) {
		RGBA800F4FDC color;

		color.red           = 0xFF;
		color.green         = 0xFF;
		color.blue          = 0xFF;
		color.alpha         = effect->alpha;
		lbl_8042C4DC->color = color;
	}
	{
		s32 value = lbl_8042C180->unknown30;

		if (lbl_8042C4F4 != value) {
			lbl_8042C4F4 = value;
		}
	}
	fn_8014FF2C(effect->clump);
	fn_80194234(0xE, zWrite);
	fn_80194234(0x14, cullMode);
	fn_80194234(0xA, blendSource);
	fn_80194234(0xB, blendDest);
}
