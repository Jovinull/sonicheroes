// Releases everything a PNG read structure owns and clears it (HYPOTHESIS: libpng 1.2
// png_read_destroy): destroys the info structures, frees the work buffers, the dither and gamma
// tables, the palette, transparency and histogram when they are owned (free_me), and the 16-bit
// gamma tables row by row, ends the zlib stream, then clears the structure while keeping the
// error callbacks, error pointer and free callback.
#include "game/png_internal.h"
#include "MSL_C/string.h"

extern "C" {
// HYPOTHESIS: png_info_destroy, png_free, png_zfree and inflateEnd.
void fn_8017C48C(PngStruct* png, void* info);
void fn_8017CE74(PngStruct* png, void* ptr);
void fn_8017BEAC(PngStruct* png, void* ptr);
s32 fn_801789A8(void* zstream);

void fn_8017E4B4(PngStruct* png, void* info, void* endInfo)
{
	void* errorFn;
	void* warningFn;
	void* errorPtr;
	void* freeFn;

	if (info != 0) {
		fn_8017C48C(png, info);
	}
	if (endInfo != 0) {
		fn_8017C48C(png, endInfo);
	}

	fn_8017CE74(png, png->zbuf);
	fn_8017CE74(png, png->bigRowBuf);
	fn_8017CE74(png, png->prevRow);
	fn_8017CE74(png, png->paletteLookup);
	fn_8017CE74(png, png->ditherIndex);
	fn_8017CE74(png, png->gammaTable);
	fn_8017CE74(png, png->gammaFrom1);
	fn_8017CE74(png, png->gammaTo1);
	if (png->freeMe & PNG_FREE_PLTE) {
		fn_8017BEAC(png, png->palette);
	}
	png->freeMe &= ~PNG_FREE_PLTE;
	if (png->freeMe & PNG_FREE_TRNS) {
		fn_8017CE74(png, png->trans);
	}
	png->freeMe &= ~PNG_FREE_TRNS;
	if (png->freeMe & PNG_FREE_HIST) {
		fn_8017CE74(png, png->hist);
	}
	png->freeMe &= ~PNG_FREE_HIST;
	if (png->gamma16Table != 0) {
		s32 i;
		s32 istop = 1 << (8 - png->gammaShift);
		for (i = 0; i < istop; i++) {
			fn_8017CE74(png, png->gamma16Table[i]);
		}
		fn_8017CE74(png, png->gamma16Table);
	}
	if (png->gamma16From1 != 0) {
		s32 i;
		s32 istop = 1 << (8 - png->gammaShift);
		for (i = 0; i < istop; i++) {
			fn_8017CE74(png, png->gamma16From1[i]);
		}
		fn_8017CE74(png, png->gamma16From1);
	}
	if (png->gamma16To1 != 0) {
		s32 i;
		s32 istop = 1 << (8 - png->gammaShift);
		for (i = 0; i < istop; i++) {
			fn_8017CE74(png, png->gamma16To1[i]);
		}
		fn_8017CE74(png, png->gamma16To1);
	}
	fn_801789A8(png->zstream);

	errorFn   = png->errorFn;
	warningFn = png->warningFn;
	errorPtr  = png->errorPtr;
	freeFn    = png->freeFn;
	memset(png, 0, PNG_STRUCT_SIZE);
	png->errorFn   = errorFn;
	png->warningFn = warningFn;
	png->errorPtr  = errorPtr;
	png->freeFn    = freeFn;
}
}
