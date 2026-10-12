#include "types.h"

// The item box's Disp (itemBoxDisp here). With the game not paused it shows the
// box's item icon on the icon effect's first layer and, on the second, one of
// the box's sign textures by the stage timer (four frames), then picks the
// box's glow texture from the timer (a sine wave over three frames) and draws
// the box.

typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;
typedef struct RwTexture RwTexture;

typedef struct ItemBoxIcon {
	RwTexture* texture; // 0x00
	char* name;         // 0x04
	s32 unk08;          // 0x08
} ItemBoxIcon;          // 0x0C

typedef struct ItemBox {
	u8 unk00[0xB8];
	s8 item; // 0xB8
	u8 unkB9[0x2F];
	RpClump* clump; // 0xE8
} ItemBox;

extern "C" u8* lbl_8042C180;
extern "C" ItemBoxIcon itemBoxIcons[];
extern "C" RwTexture* itemBoxSignTextures[3];
extern "C" RwTexture* itemBoxTexture0;
extern "C" RwTexture* itemBoxTexture1;
extern "C" RwTexture* itemBoxTexture2;
extern "C" RpMaterial* itemBoxMaterial;
extern "C" RpMaterial* itemBoxGlowMaterial;
extern "C" const f32 itemBoxBlinkScale[1];

extern "C" void* fn_80146BC8(RpMaterial* material, s32 kind);
extern "C" void fn_80146920(void* effect, s32 layer, RwTexture* texture);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void fn_8015498C(RpMaterial* material, RwTexture* texture);
extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" void itemBoxDisp(ItemBox* object)
{
	u8* game = lbl_8042C180;

	if ((s8)game[0x20] == 0) {
		s32 timer;
		RwTexture* texture;
		void* effect;

		texture = itemBoxIcons[object->item].texture;
		timer   = *(s32*)(game + 0x30);
		effect  = fn_80146BC8(itemBoxMaterial, 6);

		if (effect != NULL) {
			fn_80146920(effect, 1, texture);
			switch (timer & 3) {
				case 0:
					texture = itemBoxSignTextures[0];
					break;
				case 1:
					texture = itemBoxSignTextures[2];
					break;
				case 2:
					texture = itemBoxSignTextures[1];
					break;
				case 3:
					texture = itemBoxSignTextures[2];
					break;
			}
			fn_80146920(effect, 0, texture);
		}

		RwTexture* glow;
		f32 wave  = fn_800D7B00((timer << 11) % 0x10000);
		u32 frame = itemBoxBlinkScale[0] + itemBoxBlinkScale[0] * wave;

		switch ((s32)(frame >> 1)) {
			case 0:
				glow = itemBoxTexture0;
				break;
			case 1:
				glow = itemBoxTexture2;
				break;
			default:
				glow = itemBoxTexture1;
				break;
		}
		fn_8015498C(itemBoxGlowMaterial, glow);
		fn_8014FF2C(object->clump);
	}
}
