// Converts the pixels of one image into another of the same size (HYPOTHESIS: the RenderWare image
// depth conversion behind RwImageCopy). The depth pair (source << 8 | destination) selects the
// work: equal depths need nothing, 4-bit into 8-bit indices copies each row, 4- or 8-bit indices
// into 32 bits expand through the source palette, and any other pair raises error 0x80000009.
// Returns 1 on success, 0 for an unsupported pair.
// NonMatching: same 151 instructions; the image, pixel, result and loop registers are allocated
// differently (73 words). Tried permuted and hoisted declarations.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

#define RW_ERROR_INVALID_IMAGE_DEPTH ((s32)0x80000009)
#define IMAGE_DEPTHS(src, dst)       (((src) << 8) | (dst))

extern "C" {
s32 fn_801A0BD0(RwImage* dst, RwImage* src)
{
	s32 width;
	s32 height;
	u8* dstPixels;
	u32* palette;
	s32 result;
	u8* srcPixels;

	result    = 0;
	width     = dst->width;
	height    = dst->height;
	palette   = (u32*)src->palette; // RGBA entries moved as words
	srcPixels = src->cpPixels;
	dstPixels = dst->cpPixels;

	switch (IMAGE_DEPTHS(src->depth, dst->depth)) {
		case IMAGE_DEPTHS(4, 4):
		case IMAGE_DEPTHS(8, 8):
		case IMAGE_DEPTHS(32, 32):
			result = 1;
			break;
		case IMAGE_DEPTHS(4, 8): {
			s32 srcStride = src->stride;
			s32 y;
			for (y = 0; y < height; y++) {
				memcpy(dstPixels, srcPixels, width);
				srcPixels += srcStride;
				dstPixels += dst->stride;
			}
			result = 1;
			break;
		}
		case IMAGE_DEPTHS(4, 32):
		case IMAGE_DEPTHS(8, 32): {
			s32 srcStride = src->stride;
			s32 y;
			for (y = 0; y < height; y++) {
				s32 x;
				for (x = 0; x < width; x++) {
					((u32*)dstPixels)[x] = palette[srcPixels[x]];
				}
				srcPixels += srcStride;
				dstPixels += dst->stride;
			}
			result = 1;
			break;
		}
		case IMAGE_DEPTHS(8, 4):
		case IMAGE_DEPTHS(32, 4):
		case IMAGE_DEPTHS(32, 8):
		default: {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(RW_ERROR_INVALID_IMAGE_DEPTH);
			fn_80193FE8(&error);
			break;
		}
	}
	return result;
}
}
