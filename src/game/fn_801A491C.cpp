// Drops one reference to a texture (HYPOTHESIS: RwTextureDestroy). When it was the last one, the
// texture plugin destructors run (with the reference restored meanwhile), the texture leaves its
// dictionary, its raster is destroyed and it returns to the texture free list. Always returns 1.
#include "game/rw_engine.h"

extern "C" {
// Texture plugin registry (HYPOTHESIS: textureTKList).
extern RwPluginRegistry lbl_80290640;
// HYPOTHESIS: RwRasterDestroy.
s32 fn_801A173C(RwRaster* raster);
}

// Releases everything owned by a texture whose last reference is being dropped.
static inline s32 TextureRelease(RwTexture* texture)
{
	texture->refCount++;
	fn_80198E04(&lbl_80290640, texture);
	if (texture->dict != 0) {
		RwLLLinkRemove(&texture->lInDictionary);
	}
	if (texture->raster != 0) {
		fn_801A173C(texture->raster);
		texture->raster = 0;
	}
	texture->refCount--;
	lbl_8042C9A4->freeListFree(RW_TEXTURE_FREE_LIST, texture);
	return 1;
}

extern "C" {
s32 fn_801A491C(RwTexture* texture)
{
	s32 result = 1;
	texture->refCount--;
	if (texture->refCount <= 0) {
		result = TextureRelease(texture);
	}
	return result;
}
}
