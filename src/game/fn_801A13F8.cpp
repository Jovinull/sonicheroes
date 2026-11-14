// Fills the image from the raster through the driver standard function and carries the raster's
// gamma-corrected flag over (HYPOTHESIS: RwImageSetFromRaster). Returns the image, or null when the
// driver fails.
#include "game/rw_engine.h"

extern "C" {
RwImage* fn_801A13F8(RwImage* image, RwRaster* raster)
{
	if (lbl_8042C9A4->stdFunc[rwSTANDARDIMAGEGETRASTER](image, raster, 0)) {
		if (raster->privateFlags & RW_RASTER_GAMMA_CORRECTED) {
			image->flags |= RW_IMAGE_GAMMA_CORRECTED;
		}
		return image;
	}
	return 0;
}
}
