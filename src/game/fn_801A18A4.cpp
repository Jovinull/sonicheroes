// Presents the raster on the output device through the driver standard function, after running
// fn_80197434 (HYPOTHESIS: RwRasterShowRaster). Returns the raster, or null when the driver fails.
#include "game/rw_engine.h"

extern "C" {
void fn_80197434(void);

RwRaster* fn_801A18A4(RwRaster* raster, void* device, u32 flags)
{
	RwStandardFunc showRaster = lbl_8042C9A4->stdFunc[rwSTANDARDRASTERSHOWRASTER];
	fn_80197434();
	if (showRaster(raster, device, flags)) {
		return raster;
	}
	return 0;
}
}
