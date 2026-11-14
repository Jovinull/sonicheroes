// Frees the image's pixel buffer with the engine memory function, forgets its pixels and palette
// and clears the "pixels allocated" flag (HYPOTHESIS: RwImageFreePixels). Returns the image.
#include "game/rw_engine.h"

extern "C" {
RwImage* fn_8019F510(RwImage* image)
{
	lbl_8042C9A4->rwfree(image->cpPixels);
	image->cpPixels = 0;
	image->palette  = 0;
	image->flags &= ~RW_IMAGE_ALLOCATED;
	return image;
}
}
