// Destroys an image (HYPOTHESIS: RwImageDestroy): frees its pixels when it owns them, runs the
// image plugin destructors and returns it to the image free list. Always returns 1.
#include "game/rw_engine.h"

extern "C" {
// HYPOTHESIS: RwImageFreePixels.
RwImage* fn_8019F510(RwImage* image);

s32 fn_8019F378(RwImage* image)
{
	if (image->flags & RW_IMAGE_ALLOCATED) {
		fn_8019F510(image);
	}
	fn_80198E04(&lbl_80290610, image);
	lbl_8042C9A4->freeListFree(RW_IMAGE_FREE_LIST, image);
	return 1;
}
}
