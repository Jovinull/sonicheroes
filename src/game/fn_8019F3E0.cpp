// Allocates the image's pixel buffer (HYPOTHESIS: RwImageAllocatePixels): the stride is the row
// size rounded up to four bytes, and 4- or 8-bit images get a palette of 1 << depth RGBA entries
// placed after the pixels. On allocation failure records core error 0x80000013 (out of memory,
// with the requested size) and returns null; otherwise flags the pixels as owned and returns the
// image.
#include "game/rw_engine.h"

extern "C" {
RwImage* fn_8019F3E0(RwImage* image)
{
	s32 palettized = 0;
	s32 paletteSize;
	s32 pixelSize;
	s32 size;
	// The retail code compares the depth unsigned (cmplwi) but shifts it signed for the stride.
	if ((u32)image->depth == 4 || (u32)image->depth == 8) {
		palettized = 1;
	}
	paletteSize   = palettized ? (1 << image->depth) * (s32)sizeof(RwRGBA) : 0;
	image->stride = (image->depth + 7) >> 3;
	image->stride *= image->width;
	image->stride   = (image->stride + 3) & ~3;
	pixelSize       = image->stride * image->height;
	size            = pixelSize + paletteSize;
	image->cpPixels = (u8*)lbl_8042C9A4->rwmalloc(size);
	if (image->cpPixels == 0) {
		RwError error;
		error.pluginID  = RW_ID_CORE_PLUGIN;
		error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
		fn_80193FE8(&error);
		return 0;
	}
	image->palette = palettized ? (RwRGBA*)(image->cpPixels + pixelSize) : 0;
	image->flags |= RW_IMAGE_ALLOCATED;
	return image;
}
}
