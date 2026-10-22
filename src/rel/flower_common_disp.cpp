#include "types.h"

// TObjFlowerCommon::Disp (the PS2 build's name, by its place in the PS2
// order): unless the game is paused, the flower model is drawn; out of the
// editor a flower of kind 1 draws its stem first (Draw_Stem inlined).

#include "src/rel/flower_common.inc"

extern "C" u8* lbl_8042C180;

extern "C" s32 OnEdit__10TObjSetObjFv(void* setObj);
extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" void Disp__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		if (OnEdit__10TObjSetObjFv(&flower->frame)) {
			fn_8014FF2C(flower->model);
		} else {
			if (flower->kind == 1) {
				flowerDrawStem(flower);
			}
			fn_8014FF2C(flower->model);
		}
	}
}
