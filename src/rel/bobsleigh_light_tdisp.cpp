#include "types.h"

// TObjBobsleighLight::TDisp (the PS2 build's name). With the game not paused
// and the bobsleigh not finished (state 5), it draws the main light tinted by
// its shade at full alpha, then each of the eight lights that is on, the tint
// dimming by one factor after the first light and another after the rest.
// Render states 0xA, 0xB and 0x14 are set to 2, 2 and 1 and put back after.

#include "src/rel/bobsleigh_light_class.inc"

struct BobsleighParent {
	u8 unk000[0x100];
	s32 state; // 0x100
};

extern "C" u8* lbl_8042C180;
extern "C" const f32 bobsleighShadowBase[1];
extern "C" f32 bobsleighLightFirstFade;
extern "C" f32 bobsleighLightFade;

extern "C" void fn_8014FF2C(RpClump* clump);
extern "C" void fn_80194294(s32 state, void* value);
extern "C" void fn_80194234(s32 state, s32 value);

void TObjBobsleighLight::TDisp()
{
	if ((s8)lbl_8042C180[0x20] == 0 && ((BobsleighParent*)Parent)->state != 5) {
		f32 color[4];
		s32 src;
		s32 dst;
		s32 cull;

		color[0] = color[1] = color[2] = shade;
		color[3]                       = bobsleighShadowBase[0];
		fn_80194294(0xA, &src);
		fn_80194294(0xB, &dst);
		fn_80194294(0x14, &cull);
		fn_80194234(0xA, 2);
		fn_80194234(0xB, 2);
		fn_80194234(0x14, 1);
		material->MulColor(color);
		fn_8014FF2C(clump);
		material->DefaultColor();
		for (int i = 0; i < 8; i++) {
			if (i == 0) {
				color[0] *= bobsleighLightFirstFade;
				color[1] *= bobsleighLightFirstFade;
				color[2] *= bobsleighLightFirstFade;
			} else {
				color[0] *= bobsleighLightFade;
				color[1] *= bobsleighLightFade;
				color[2] *= bobsleighLightFade;
			}
			if (lit[i] != 0) {
				materials[i]->MulColor(color);
				fn_8014FF2C(clumps[i]);
				materials[i]->DefaultColor();
			}
		}
		fn_80194234(0x14, cull);
		fn_80194234(0xA, src);
		fn_80194234(0xB, dst);
	}
}
