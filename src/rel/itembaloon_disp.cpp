// TObjItembaloon's Disp: outside the mode flagged at +0x20 of lbl_8042C180,
// and while the balloon's depth scale is 1, it paints the clump's materials
// with the scale as alpha (the colour channels at -1, which leaves them as
// they are) and renders the clump (fn_8014FF2C). The class is shared through
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
void objRpClumpForAllMaterialsToChangeMaterialColor(RpClump* clump, RwRGBAReal* color);

void TObjItembaloon::Disp()
{
	if (lbl_8042C180->unk20 == 0 && itembaloonOne[0] == scale.z) {
		RwRGBAReal color;

		color.alpha = scale.z;
		color.red = color.green = color.blue = itembaloonMinusOne[0];
		objRpClumpForAllMaterialsToChangeMaterialColor(clump, &color);
		fn_8014FF2C(clump);
	}
}
