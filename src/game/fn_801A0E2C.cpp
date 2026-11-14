// Copies the pixels (and the palette, for palettised depths) of one image into another of the
// same size (HYPOTHESIS: RwImageCopy). Images of different depths go through fn_801A0BD0; a
// failed conversion yields 0, which the retail code still dereferences for the flag update.
// The destination then takes the gamma-corrected flag of the source.
// NonMatching (GC/2.0): rowBytes and srcStride swap callee-saved registers (r29/r25), 4 words
// apart; no declaration or assignment order tried so far reproduces the retail allocation.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

extern "C" {
// HYPOTHESIS: depth-converting image copy.
s32 fn_801A0BD0(RwImage* dst, const RwImage* src);

RwImage* fn_801A0E2C(RwImage* dst, const RwImage* src)
{
	s32 rowBytes;
	u8* dstPixels;
	const u8* srcPixels;
	s32 y;
	s32 srcStride;

	if (dst->depth == src->depth) {
		if (dst->palette && src->palette && src->depth <= 8) {
			memcpy(dst->palette, src->palette, (1 << src->depth) * sizeof(RwRGBA));
		}

		rowBytes  = ((dst->depth + 7) >> 3) * dst->width;
		srcPixels = src->cpPixels;
		dstPixels = dst->cpPixels;
		srcStride = src->stride;
		for (y = 0; y < dst->height; y++) {
			memcpy(dstPixels, srcPixels, rowBytes);
			srcPixels += srcStride;
			dstPixels += dst->stride;
		}
	} else if (!fn_801A0BD0(dst, src)) {
		dst = 0;
	}

	dst->flags &= ~RW_IMAGE_GAMMA_CORRECTED;
	dst->flags |= src->flags & RW_IMAGE_GAMMA_CORRECTED;
	return dst;
}
}
