// Returns the stream size of a material's effects data (HYPOTHESIS: RpMatFX material stream size):
// 4 bytes of header plus, for each of the two effects, 4 bytes for its type and its parameters with
// the textures it holds (each a texture chunk of fn_8019AA5C plus 0x10, or 4 for none); 0 when the
// material has no effects.
// NonMatching: the retail switch keeps a separate test for type 5 (81 instructions, ours 80) and
// allocates the walk registers differently.
#include "game/rp_matfx.h"

extern "C" {
u32 fn_8019AA5C(const void* texture);
}

// Stream size of an optional texture (the inlined body of fn_80147F64).
static inline u32 TextureStreamSize(const void* texture)
{
	u32 size = 4;
	if (texture) {
		size = fn_8019AA5C(texture) + 0x10;
	}
	return size;
}

extern "C" {
u32 fn_80148878(const void* material, s32, s32)
{
	RpMatFXEffect* effect;
	RpMatFXMaterialData* data;
	u32 size;
	u8 i;

	data = RP_MATFX_DATA(material);

	if (!data || !data->flags) {
		return 0;
	}
	size = 4;
	for (i = 0; i < 2; i++) {
		effect = &data->effects[i];
		size += 4;
		switch (effect->type) {
			case 1:
				size += 4;
				size += TextureStreamSize(effect->word4);
				size += TextureStreamSize(effect->word8);
				break;
			case 2:
				size += 8;
				size += TextureStreamSize(effect->word4);
				break;
			case 4:
				size += 8;
				size += TextureStreamSize(effect->word0);
				break;
		}
	}
	return size;
}
}
