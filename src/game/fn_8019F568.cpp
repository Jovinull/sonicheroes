// Resizes an image that owns its pixels (HYPOTHESIS: RwImageResize): allocates a buffer for the new
// size (stride rounded up to four bytes, palette of 1 << depth RGBA entries after the pixels for
// 4- and 8-bit images), copies the palette and the overlapping rows, frees the old buffer and
// adopts the new one. On allocation failure records core error 0x80000013 (out of memory, with the
// requested size) and returns null. The new size is recorded in every other case. Returns the
// image.
// NonMatching: same 108 instructions; the callee-saved register assignment differs (retail keeps
// stride in r31 and the new buffer in r30 ahead of the parameters). Declaration orders tried with
// perm-style permutations did not reproduce it.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

#define RW_ERROR_NO_MEMORY ((s32)0x80000013)

extern "C" {
RwImage* fn_8019F568(RwImage* image, s32 width, s32 height)
{
	if ((image->flags & RW_IMAGE_ALLOCATED) && image->cpPixels != 0) {
		s32 depth      = image->depth;
		s32 palettized = 0;
		s32 paletteSize;
		s32 stride;
		s32 pixelSize;
		s32 size;
		u8* pixels;
		RwRGBA* palette;
		s32 copyWidth;
		s32 copyHeight;
		s32 rowSize;
		u8* dst;
		u8* src;
		s32 y;

		if (depth == 4 || depth == 8) {
			palettized = 1;
		}
		paletteSize = palettized ? (1 << depth) * (s32)sizeof(RwRGBA) : 0;
		stride      = (((depth + 7) >> 3) * width + 3) & ~3;
		pixelSize   = stride * height;
		size        = pixelSize + paletteSize;
		pixels      = (u8*)lbl_8042C9A4->rwmalloc(size);
		if (pixels == 0) {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
			fn_80193FE8(&error);
			return 0;
		}
		palette = palettized ? (RwRGBA*)(pixels + pixelSize) : 0;
		if (palettized) {
			memcpy(palette, image->palette, paletteSize);
		}
		copyWidth  = (width < image->width) ? width : image->width;
		copyHeight = (height < image->height) ? height : image->height;
		dst        = pixels;
		src        = image->cpPixels;
		rowSize    = ((image->depth + 7) >> 3) * copyWidth;
		for (y = 0; y < copyHeight; y++) {
			memcpy(dst, src, rowSize);
			dst += stride;
			src += image->stride;
		}
		lbl_8042C9A4->rwfree(image->cpPixels);
		image->cpPixels = pixels;
		image->palette  = palette;
		image->stride   = stride;
	}
	image->width  = width;
	image->height = height;
	return image;
}
}
