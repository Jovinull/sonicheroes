#include "types.h"

// TObjCannonSmoke::TDisp (the PS2 build's name): while the game runs, the
// smoke is drawn additively without z writes; each of its three puffs still
// showing shades its material by its size and is drawn, the others hidden.

#include "src/rel/cannon_smoke_class.inc"

typedef struct CannonSmokeColor {
	u8 red, green, blue, alpha;
} CannonSmokeColor;

typedef struct CannonSmokeMaterial {
	u8 unk0[0x4];
	CannonSmokeColor color; // 0x4
} CannonSmokeMaterial;

typedef struct CannonSmokeAtomic {
	u8 unk0[0x2];
	u8 flags; // 0x2
} CannonSmokeAtomic;

extern "C" u8* lbl_8042C180;
extern "C" CannonSmokeMaterial* cannonEffectMaterials[3];
extern "C" const f32 cannonZero[1];
extern "C" const f32 cannonSmokeShade[1];

extern "C" void fn_80194294(s32 state, void* value);
extern "C" s32 fn_80194234(s32 state, void* value);
extern "C" void fn_8014FF2C(RpClump* clump);

void TObjCannonSmoke::TDisp()
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		void* srcBlend;
		void* dstBlend;
		void* zwrite;

		fn_80194294(0xA, &srcBlend);
		fn_80194294(0xB, &dstBlend);
		fn_80194294(0x14, &zwrite);
		fn_80194234(0xA, (void*)2);
		fn_80194234(0xB, (void*)2);
		fn_80194234(0x14, (void*)1);
		for (int i = 0; i < 3; i++) {
			if (scale[i] > cannonZero[0]) {
				CannonSmokeColor* color = &cannonEffectMaterials[i]->color;
				u8 shade                = scale[i] * cannonSmokeShade[0];

				color->red   = shade;
				color->green = shade;
				color->blue  = shade;
				color->alpha = shade;
				((CannonSmokeAtomic*)atoms[i])->flags |= 4;
			} else {
				((CannonSmokeAtomic*)atoms[i])->flags &= ~4;
			}
		}
		fn_8014FF2C(clump);
		fn_80194234(0x14, zwrite);
		fn_80194234(0xA, srcBlend);
		fn_80194234(0xB, dstBlend);
	}
}
