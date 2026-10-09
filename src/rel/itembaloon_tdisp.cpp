// TObjItembaloon's TDisp: outside the mode flagged at +0x20 of lbl_8042C180,
// while the balloon's depth scale is strictly between 0 and 1 (it is fading),
// it paints the clump's materials with the scale as alpha and draws the clump
// twice with alpha blending (source alpha over inverse source alpha), first
// with cull mode 3 and then 2, putting the three render states back after.
// Render states are RenderWare's: 0xA source blend, 0xB destination blend, 0x14
// cull mode. The lower bound is a negated `<=`, which is the original's `cror`
// before the branch; `>` would branch on `ble`. The class is shared through
// itembaloon_class.inc.

#define ITEMBALOON_CTOR inline
#include "src/rel/itembaloon_class.inc"
#include "game/object.h"

// The mode object lbl_8042C180 points at.
struct BaloonGameMode {
	u8 unk00[0x20];
	s8 unk20; // 0x20
};

extern "C" BaloonGameMode* lbl_8042C180;
extern "C" const f32 itembaloonMinusOne[1];
extern "C" void fn_8014FF2C(RpClump* clump);
extern "C" void fn_80194294(s32 state, s32* value);
extern "C" void fn_80194234(s32 state, s32 value);
void objRpClumpForAllMaterialsToChangeMaterialColor(RpClump* clump, RwRGBAReal* color);

void TObjItembaloon::TDisp()
{
	if (lbl_8042C180->unk20 == 0) {
		if (!(scale.z <= itembaloonZero[0]) && scale.z < itembaloonOne[0]) {
			RwRGBAReal color;
			s32 srcBlend;
			s32 destBlend;
			s32 cull;

			color.alpha = scale.z;
			color.red = color.green = color.blue = itembaloonMinusOne[0];
			objRpClumpForAllMaterialsToChangeMaterialColor(clump, &color);

			fn_80194294(0xA, &srcBlend);
			fn_80194294(0xB, &destBlend);
			fn_80194294(0x14, &cull);
			fn_80194234(0xA, 5);
			fn_80194234(0xB, 6);
			fn_80194234(0x14, 3);
			fn_8014FF2C(clump);
			fn_80194234(0x14, 2);
			fn_8014FF2C(clump);
			fn_80194234(0x14, cull);
			fn_80194234(0xA, srcBlend);
			fn_80194234(0xB, destBlend);
		}
	}
}
