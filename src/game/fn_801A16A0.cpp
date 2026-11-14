// Unlocks the raster's pixels through the driver standard function
// (HYPOTHESIS: RwRasterUnlock). Returns the raster.
#include "game/rw_engine.h"

extern "C" {
RwRaster* fn_801A16A0(RwRaster* raster)
{
	lbl_8042C9A4->stdFunc[rwSTANDARDRASTERUNLOCK](0, raster, 0);
	return raster;
}
}
