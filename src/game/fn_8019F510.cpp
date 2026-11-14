// Frees the image's pixel buffer with the engine memory function, forgets its pixels and palette
// and clears the "pixels allocated" flag (HYPOTHESIS: RwImageFreePixels). Returns the image.
#include "game/rw_engine.h"

#define RW_IMAGE_ALLOCATED 0x1

// Image header (HYPOTHESIS: RwImage); fields after the palette are not used here.
struct RwImage8019F510 {
	s32 flags;
	s32 width;
	s32 height;
	s32 depth;
	s32 stride;
	u8* cpPixels;  // 0x14
	void* palette; // 0x18
};

extern "C" {
RwImage8019F510* fn_8019F510(RwImage8019F510* image)
{
	lbl_8042C9A4->rwfree(image->cpPixels);
	image->cpPixels = 0;
	image->palette  = 0;
	image->flags &= ~RW_IMAGE_ALLOCATED;
	return image;
}
}
