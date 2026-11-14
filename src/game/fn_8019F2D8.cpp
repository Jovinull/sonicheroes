// Creates an image header of the given size and depth without pixels or palette
// (HYPOTHESIS: RwImageCreate): takes one from the image free list and runs the image plugin
// constructors. Returns the image, or null when allocation fails.
#include "game/rw_engine.h"

extern "C" {
RwImage* fn_8019F2D8(s32 width, s32 height, s32 depth)
{
	RwImage* image = (RwImage*)lbl_8042C9A4->freeListAlloc(RW_IMAGE_FREE_LIST);
	if (image == 0) {
		return 0;
	}
	image->width    = width;
	image->height   = height;
	image->depth    = depth;
	image->cpPixels = 0;
	image->palette  = 0;
	image->flags    = 0;
	fn_80198D5C(&lbl_80290610, image);
	return image;
}
}
