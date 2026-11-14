// Fills the raster from the image through the driver standard function and carries the image's
// gamma-corrected flag over (HYPOTHESIS: RwRasterSetFromImage). Returns the raster, or null when
// the driver fails.
#include "game/rw_engine.h"

extern "C" {
RwRaster* fn_801A146C(RwRaster* raster, RwImage* image)
{
	if (lbl_8042C9A4->stdFunc[rwSTANDARDRASTERSETIMAGE](raster, image, 0)) {
		if (image->flags & RW_IMAGE_GAMMA_CORRECTED) {
			raster->privateFlags |= RW_RASTER_GAMMA_CORRECTED;
		}
		return raster;
	}
	return 0;
}
}
