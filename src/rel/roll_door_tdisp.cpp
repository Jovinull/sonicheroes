#include "types.h"

// The roll door's TDisp (rollDoorTDisp here). With the game not paused and the
// door spinning faster than its threshold, it draws the door's blur: alpha
// from the spin speed (capped), render states 0xA, 0xB, 0x14, 0xE and 0xC set
// to 5, 2, 1, 0 and 1 (put back after), light set 0x10 with the regular light,
// and the blur material's colour set to that alpha on all four channels.
//
// The threshold, the cap and the blur material keep the names the shared roll
// door unit already uses for them (rel/roll_door_set_position.cpp).

typedef struct RpClump RpClump;

typedef struct RwRGBA {
	u8 red, green, blue, alpha;
} RwRGBA;

typedef struct RollDoorMaterial {
	u8 unk00[0x4];
	RwRGBA color; // 0x04
} RollDoorMaterial;

typedef struct RollDoor {
	u8 unk00[0xE8];
	f32 spin; // 0xE8
	u8 unkEC[0x4];
	RpClump* blur; // 0xF0
} RollDoor;

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

extern "C" u8* lbl_8042C180;
extern "C" CLIGHT lbl_802D5E80;
extern "C" RollDoorMaterial* lbl_8_bss_9E8;
extern "C" const f32 lbl_8_rodata_AD4[1];
extern "C" const f32 rollDoorBlurScale[1];
extern "C" const f32 lbl_8_rodata_AE8[1];
extern "C" const f32 rollDoorAlphaScale[1];

extern "C" void fn_8014FF2C(RpClump* clump);
extern "C" void fn_80194294(s32 state, void* value);
extern "C" void fn_80194234(s32 state, s32 value);

extern "C" void rollDoorTDisp(RollDoor* object)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		const f32* limit;
		f32 spin = object->spin;

		if ((f32)__fabs(spin) > *(limit = lbl_8_rodata_AD4)) {
			double magnitude = __fabs(rollDoorBlurScale[0] * spin);
			f32 blur         = magnitude;
			s32 src;
			s32 dst;
			s32 cull;
			s32 zwrite;
			s32 ztest;

			if (blur > *(limit = lbl_8_rodata_AE8)) {
				blur = *limit;
			}
			fn_80194294(0xA, &src);
			fn_80194294(0xB, &dst);
			fn_80194294(0x14, &cull);
			fn_80194294(0xE, &zwrite);
			fn_80194294(0xC, &ztest);
			fn_80194234(0xA, 5);
			fn_80194234(0xB, 2);
			fn_80194234(0x14, 1);
			fn_80194234(0xE, 0);
			fn_80194234(0xC, 1);
			lbl_802D5E80.SetCurrentNum(0x10);
			lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);

			RollDoorMaterial* material = lbl_8_bss_9E8;
			RwRGBA color               = material->color;

			color.alpha = color.blue = color.red = color.green = rollDoorAlphaScale[0] * blur;
			material->color                                    = color;
			fn_8014FF2C(object->blur);
			fn_80194234(0xC, ztest);
			fn_80194234(0xE, zwrite);
			fn_80194234(0x14, cull);
			fn_80194234(0xA, src);
			fn_80194234(0xB, dst);
		}
	}
}
