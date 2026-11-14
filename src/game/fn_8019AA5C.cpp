// Returns the stream size of a texture (HYPOTHESIS: RwTextureStreamGetSize): its 0x10-byte struct
// payload, its name and mask string chunks (the size computation of fn_8019A588 is inlined) and its
// plugin data (fn_801985BC, _rwPluginRegistryGetSize, on lbl_80290640). VERIFIED by the retail
// constants: only the string and plugin chunks add a 12-byte chunk header here.
#include "game/rw_engine.h"

#define RW_CHUNK_HEADER_SIZE   12
#define RW_STREAM_TEXTURE_SIZE 0x10

extern "C" {
extern const char lbl_8042F6C8[8];
// Texture plugin registry (HYPOTHESIS: textureTKList).
extern RwPluginRegistry lbl_80290640;
s32 fn_801985BC(const RwPluginRegistry* registry, const void* object);
}

// Same body as fn_8019A588 (_rwStringStreamGetSize).
static inline u32 StringStreamGetSize(const char* string)
{
	if (string == 0) {
		string = lbl_8042F6C8;
	}
	return (lbl_8042C9A4->rwstrlen(string) + 4) & ~3;
}

extern "C" {
u32 fn_8019AA5C(const RwTexture* texture)
{
	u32 size = RW_STREAM_TEXTURE_SIZE;
	size += StringStreamGetSize(texture->name) + RW_CHUNK_HEADER_SIZE;
	size += StringStreamGetSize(texture->mask) + RW_CHUNK_HEADER_SIZE;
	size += fn_801985BC(&lbl_80290640, texture) + RW_CHUNK_HEADER_SIZE;
	return size;
}
}
