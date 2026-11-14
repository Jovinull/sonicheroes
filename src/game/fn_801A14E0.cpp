// Asks the driver standard function which raster would hold the image for the given raster type
// and reports its width, height, depth and format (raster format bits | raster type)
// (HYPOTHESIS: RwImageFindRasterFormat). Returns the image, or null when the driver fails.
#include "game/rw_engine.h"

extern "C" {
RwImage* fn_801A14E0(
    RwImage* image, s32 rasterType, s32* width, s32* height, s32* depth, s32* format)
{
	RwRaster raster;
	if (!lbl_8042C9A4->stdFunc[rwSTANDARDIMAGEFINDRASTERFORMAT](&raster, image, rasterType)) {
		return 0;
	}
	*format = (raster.cFormat << 8) | raster.cType;
	*width  = raster.width;
	*height = raster.height;
	*depth  = raster.depth;
	return image;
}
}
