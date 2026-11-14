// Converts an image to a palettised image of the given depth (HYPOTHESIS: _rwImagePalettize):
// builds a palette quantizer from the source pixels, resolves a palette of 1 << depth entries,
// creates and fills a new image of that depth, destroys the source image and stores the new one
// through the handle. Returns 1 on success, 0 when the quantizer or the new image cannot be
// created (the retail code skips fn_801A7B04 on the second failure).
#include "game/rw_engine.h"
#include "MSL_C/string.h"

// Palette quantizer state on the stack (HYPOTHESIS: RwPalQuant); its 16 bytes are only handled
// by the quantizer routines.
struct RwPalQuant {
	u32 opaque[4];
};

extern "C" {
// Image create, pixel allocation and destroy (fn_8019F2D8, fn_8019F3E0, fn_8019F378).
RwImage* fn_8019F2D8(s32 width, s32 height, s32 depth);
RwImage* fn_8019F3E0(RwImage* image);
s32 fn_8019F378(RwImage* image);
// HYPOTHESIS: _rwPalQuantInit, _rwPalQuantAddImage, _rwPalQuantResolvePalette,
// _rwPalQuantMatchImage and _rwPalQuantTerm.
s32 fn_801A75BC(RwPalQuant* quant);
void fn_801A579C(RwPalQuant* quant, RwImage* image, f32 weight);
s32 fn_801A6B4C(RwRGBA* palette, s32 maxColors, RwPalQuant* quant);
void fn_801A7194(
    u8* pixels, s32 stride, s32 depth, s32 palettised, RwPalQuant* quant, RwImage* image);
void fn_801A7B04(RwPalQuant* quant);
// .sdata2 1.0f weight of the added image.
extern f32 lbl_8042F748;

s32 fn_801A3314(RwImage** image, s32 depth)
{
	RwPalQuant quant;
	RwRGBA palette[256];
	s32 numColors;
	RwImage* palettised;

	if (!fn_801A75BC(&quant)) {
		return 0;
	}

	fn_801A579C(&quant, *image, lbl_8042F748);
	numColors = 1 << depth;
	fn_801A6B4C(palette, numColors, &quant);

	palettised = fn_8019F2D8((*image)->width, (*image)->height, depth);
	if (palettised) {
		fn_8019F3E0(palettised);
		fn_801A7194(palettised->cpPixels, palettised->stride, palettised->depth, 0, &quant, *image);
		memcpy(palettised->palette, palette, numColors * sizeof(RwRGBA));
		fn_8019F378(*image);
		*image = palettised;
	} else {
		return 0;
	}

	fn_801A7B04(&quant);
	return 1;
}
}
