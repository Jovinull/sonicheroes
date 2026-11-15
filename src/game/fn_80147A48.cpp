// Destructor of the material effects plugin (HYPOTHESIS: RpMatFX material data, two 0x18-byte
// effect slots at the lbl_8042C858 offset): releases the textures each effect holds by type (1:
// two at 0x4/0x8, 2: one at 0x4, 4: one at 0x0; type 5 only clears its two pointers) with
// fn_801A491C (HYPOTHESIS: RwTextureDestroy), clears the data and returns it to the plugin's free
// list (word 0x8 of lbl_8028D1E8). Returns the material.
#include "game/rp_matfx.h"
#include "MSL_C/string.h"

extern "C" {
s32 fn_801A491C(void* texture);

void* fn_80147A48(void* material, s32, s32)
{
	u8 i;
	RpMatFXEffect* effect;
	RpMatFXMaterialData* data;

	data = RP_MATFX_DATA(material);
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
		RP_MATFX_DATA(material) = 0;
	}
	return material;
}
}
