#include "types.h"

// The reel's Disp (reelDisp here): with the game not paused it picks the
// reel's texture from the stage timer (a slow sine wave over three frames)
// and gives it to the reel's material.

typedef struct RpMaterial RpMaterial;
typedef struct RwTexture RwTexture;

extern "C" u8* lbl_8042C180;
extern "C" RwTexture* reelTexture0;
extern "C" RwTexture* reelTexture1;
extern "C" RwTexture* reelTexture2;
extern "C" RpMaterial* reelMaterial;
extern "C" const f32 reelBlinkScale[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void fn_8015498C(RpMaterial* material, RwTexture* texture);

extern "C" void reelDisp(void* object)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		RwTexture* texture;
		f32 wave  = fn_800D7B00(*(s32*)(lbl_8042C180 + 0x30) << 11);
		u32 frame = reelBlinkScale[0] + reelBlinkScale[0] * wave;

		switch ((s32)(frame >> 1)) {
			case 0:
				texture = reelTexture0;
				break;
			case 1:
				texture = reelTexture2;
				break;
			default:
				texture = reelTexture1;
				break;
		}
		fn_8015498C(reelMaterial, texture);
	}
}
