#include "types.h"

// The breakable weight's Disp (the PS2 build's TObjWeightExt::Disp;
// breakableWeightDisp here). Like the weight's (rel/weight_disp.cpp), with the
// game not paused and the stage timer moved on it picks the weight's texture
// from the timer. Then, unless the weight is broken (mode 5), it draws the
// model; once the weight's timer is past the warning time it blinks: every
// other blink period the model is drawn untextured in grey.

typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;
typedef struct RwTexture RwTexture;

typedef struct RwRGBA {
	u8 red, green, blue, alpha;
} RwRGBA;

class DealMaterial
{
public:
	void NoTexture();
	void SetColor(RwRGBA* color);
	void DefaultTexture();
	void DefaultColor();
};

typedef struct BreakableWeight {
	u8 unk00[0xD0];         // 0x00
	s32 timer;              // 0xD0
	u8 unkD4[0x20];         // 0xD4
	RpClump* model;         // 0xF4
	u8 unkF8[0x4];          // 0xF8
	DealMaterial* material; // 0xFC
	s32 mode;               // 0x100
} BreakableWeight;

extern "C" u8* lbl_8042C180;
extern "C" s32 breakableWeightLastTimer;
extern "C" RwTexture* breakableWeightTexture0;
extern "C" RwTexture* breakableWeightTexture1;
extern "C" RwTexture* breakableWeightTexture2;
extern "C" RpMaterial* breakableWeightMaterial;
extern "C" s32 breakableWeightBreakTime;
extern "C" s32 breakableWeightBlinkTime;
extern "C" s32 breakableWeightBlinkPeriod;
extern "C" u8 breakableWeightBlinkGray;
// 3.0, the texture wave's scale
extern "C" const f32 breakableWeightNear[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void fn_8015498C(RpMaterial* material, RwTexture* texture);
extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" void breakableWeightDisp(BreakableWeight* object)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		s32 timer = *(s32*)(lbl_8042C180 + 0x30);

		if (breakableWeightLastTimer != timer) {
			RwTexture* texture;

			breakableWeightLastTimer = timer;
			f32 wave                 = fn_800D7B00(timer << 11);
			u32 frame                = breakableWeightNear[0] + breakableWeightNear[0] * wave;

			switch ((s32)(frame >> 1)) {
				case 0:
					texture = breakableWeightTexture0;
					break;
				case 1:
					texture = breakableWeightTexture2;
					break;
				default:
					texture = breakableWeightTexture1;
					break;
			}
			fn_8015498C(breakableWeightMaterial, texture);
		}
		if (object->mode != 5) {
			s32 blink = (bool)(object->timer > breakableWeightBreakTime - breakableWeightBlinkTime
			    && (object->timer / breakableWeightBlinkPeriod) % 2 != 0);

			if (blink) {
				RwRGBA color;

				color.red = color.green = color.blue = breakableWeightBlinkGray;
				color.alpha                          = 0xFF;
				object->material->NoTexture();
				object->material->SetColor(&color);
			}
			fn_8014FF2C(object->model);
			if (blink) {
				object->material->DefaultTexture();
				object->material->DefaultColor();
			}
		}
	}
}
