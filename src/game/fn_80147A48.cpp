// Destructor of the material effects plugin (HYPOTHESIS: RpMatFX material data, two 0x18-byte
// effect slots at the lbl_8042C858 offset): releases the textures each effect holds by type (1:
// two at 0x4/0x8, 2: one at 0x4, 4: one at 0x0; type 5 only clears its two pointers) with
// fn_801A491C (HYPOTHESIS: RwTextureDestroy), clears the data and returns it to the plugin's free
// list (word 0x8 of lbl_8028D1E8). Returns the material.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

struct Effect80147A48 {
	void* word0; // 0x0
	void* word4; // 0x4
	void* word8; // 0x8
	u8 padC[0x8];
	s32 type; // 0x14
};

struct EffectData80147A48 {
	Effect80147A48 effects[2]; // 0x0
	u32 flags;                 // 0x30
};

struct Plugin80147A48 {
	u8 pad0[0x8];
	RwFreeList* freeList; // 0x8
};

extern "C" {
extern s32 lbl_8042C858;
extern Plugin80147A48 lbl_8028D1E8;

s32 fn_801A491C(void* texture);

void* fn_80147A48(void* material, s32, s32)
{
	u8 i;
	Effect80147A48* effect;
	EffectData80147A48* data;

	data = *(EffectData80147A48**)((u8*)material + lbl_8042C858);
	if (data) {
		for (i = 0; i < 2; i++) {
			effect = &data->effects[i];
			switch (effect->type) {
				case 1:
					if (effect->word4) {
						fn_801A491C(effect->word4);
					}
					if (effect->word8) {
						fn_801A491C(effect->word8);
					}
					break;
				case 2:
					if (effect->word4) {
						fn_801A491C(effect->word4);
					}
					break;
				case 4:
					if (effect->word0) {
						fn_801A491C(effect->word0);
					}
					break;
				case 5:
					effect->word0 = 0;
					effect->word4 = 0;
					break;
			}
		}
		memset(data, 0, sizeof(*data));
		lbl_8042C9A4->freeListFree(lbl_8028D1E8.freeList, data);
		*(EffectData80147A48**)((u8*)material + lbl_8042C858) = 0;
	}
	return material;
}
}
