#include "types.h"

// The weight's Disp (weightDisp here): with the game not paused and the stage
// timer moved on since the last time, it picks the weight's texture from the
// timer (a slow sine wave over three frames) and gives it to the weight's
// material.

typedef struct RpMaterial RpMaterial;
typedef struct RwTexture RwTexture;

extern "C" u8* lbl_8042C180;
extern "C" s32 weightLastTimer;
extern "C" RwTexture* weightTexture0;
extern "C" RwTexture* weightTexture1;
extern "C" RwTexture* weightTexture2;
extern "C" RpMaterial* weightMaterial;
extern "C" const f32 weightBlinkScale[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void fn_8015498C(RpMaterial* material, RwTexture* texture);

extern "C" void weightDisp(void* object)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		s32 timer = *(s32*)(lbl_8042C180 + 0x30);

		if (weightLastTimer != timer) {
			RwTexture* texture;

			weightLastTimer = timer;
			f32 wave        = fn_800D7B00(timer << 11);
			u32 frame       = weightBlinkScale[0] + weightBlinkScale[0] * wave;

			switch ((s32)(frame >> 1)) {
				case 0:
					texture = weightTexture0;
					break;
				case 1:
					texture = weightTexture2;
					break;
				default:
					texture = weightTexture1;
					break;
			}
			fn_8015498C(weightMaterial, texture);
		}
	}
}
