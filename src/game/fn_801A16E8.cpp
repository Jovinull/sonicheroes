// Unlocks the raster's palette through the driver standard function and clears its palette
// read/write lock flags (HYPOTHESIS: RwRasterUnlockPalette). Returns the raster.
#include "game/rw_engine.h"

#define RW_RASTER_PALETTE_LOCKED_READ  0x08
#define RW_RASTER_PALETTE_LOCKED_WRITE 0x10

extern "C" {
RwRaster* fn_801A16E8(RwRaster* raster)
{
	lbl_8042C9A4->stdFunc[rwSTANDARDRASTERUNLOCKPALETTE](0, raster, 0);
	raster->privateFlags &= ~(RW_RASTER_PALETTE_LOCKED_READ | RW_RASTER_PALETTE_LOCKED_WRITE);
	return raster;
}
}
