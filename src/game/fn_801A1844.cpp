// Returns the number of mip levels of the raster (HYPOTHESIS: RwRasterGetNumLevels): 1 without the
// mipmap format bit, otherwise the driver's count, or -1 when the driver fails.
#include "game/rw_engine.h"

extern "C" {
s32 fn_801A1844(RwRaster* raster)
{
	s32 numLevels;
	if (!((raster->cFormat << 8) & RW_RASTER_FORMAT_MIPMAP)) {
		return 1;
	}
	if (lbl_8042C9A4->stdFunc[rwSTANDARDRASTERGETMIPLEVELS](&numLevels, raster, 0)) {
		return numLevels;
	}
	return -1;
}
}
