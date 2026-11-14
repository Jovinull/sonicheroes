// Creates a texture around a raster (HYPOTHESIS: RwTextureCreate): takes one from the texture free
// list, with no dictionary, empty name and mask and one reference, sets wrap addressing on both
// axes and nearest filtering, and runs the texture plugin constructors. Returns the texture, or
// null when allocation fails.
#include "game/rw_engine.h"

#define RW_TEXTURE_ADDRESS_WRAP     1
#define RW_FILTER_NEAREST           1
#define RW_TEXTURE_ADDRESSING_MASK  0xFF00
#define RW_TEXTURE_FILTER_MODE_MASK 0xFF

extern "C" {
// Texture plugin registry (HYPOTHESIS: textureTKList).
extern RwPluginRegistry lbl_80290640;

RwTexture* fn_801A4874(RwRaster* raster)
{
	RwTexture* texture = (RwTexture*)lbl_8042C9A4->freeListAlloc(RW_TEXTURE_FREE_LIST);
	if (texture != 0) {
		texture->dict             = 0;
		texture->name[0]          = 0;
		texture->mask[0]          = 0;
		texture->raster           = raster;
		texture->refCount         = 1;
		texture->filterAddressing = 0;
		texture->filterAddressing = (texture->filterAddressing & ~RW_TEXTURE_ADDRESSING_MASK)
		    | (RW_TEXTURE_ADDRESS_WRAP << 8) | (RW_TEXTURE_ADDRESS_WRAP << 12);
		texture->filterAddressing
		    = (texture->filterAddressing & ~RW_TEXTURE_FILTER_MODE_MASK) | RW_FILTER_NEAREST;
		fn_80198D5C(&lbl_80290640, texture);
	}
	return texture;
}
}
