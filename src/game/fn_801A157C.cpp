// Reads a raster from an image file (HYPOTHESIS: RwRasterRead): reads the image (fn_801A01C0,
// HYPOTHESIS: RwImageRead), asks the driver for the matching raster format, resamples the image
// to that size when it differs (fn_801A24FC, replacing the original), creates the raster
// (fn_801A19D4, HYPOTHESIS: RwRasterCreate) and copies the image into it, flagging the raster
// gamma-corrected (private flag 0x1) when the image was. The image is destroyed (fn_8019F378) in
// every case. Returns the raster, or null when the image or the raster cannot be created.
#include "game/rw_engine.h"

extern "C" {
RwImage* fn_801A01C0(const char* name);
RwImage* fn_801A24FC(RwImage* image, s32 width, s32 height);
RwRaster* fn_801A19D4(s32 width, s32 height, s32 depth, s32 flags);
s32 fn_8019F378(RwImage* image);

RwRaster* fn_801A157C(const char* name)
{
	RwImage* image = fn_801A01C0(name);
	RwRaster format;
	s32 width;
	s32 height;
	s32 depth;
	s32 flags;
	RwRaster* raster;

	if (!image) {
		return 0;
	}
	if (lbl_8042C9A4->stdFunc[rwSTANDARDIMAGEFINDRASTERFORMAT](&format, image, 0)) {
		flags  = (format.cFormat << 8) | format.cType;
		width  = format.width;
		height = format.height;
		depth  = format.depth;
	}
	if (width != image->width || height != image->height) {
		RwImage* resampled = fn_801A24FC(image, width, height);
		fn_8019F378(image);
		image = resampled;
	}
	raster = fn_801A19D4(width, height, depth, flags);
	if (!raster) {
		fn_8019F378(image);
		return 0;
	}
	if (lbl_8042C9A4->stdFunc[rwSTANDARDRASTERSETIMAGE](raster, image, 0)
	    && (image->flags & RW_IMAGE_GAMMA_CORRECTED)) {
		raster->privateFlags |= 0x1;
	}
	fn_8019F378(image);
	return raster;
}
}
