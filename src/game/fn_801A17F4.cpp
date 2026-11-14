// Locks the raster's palette through the driver standard function
// (HYPOTHESIS: RwRasterLockPalette). Returns the palette, or null when the lock fails.
#include "game/rw_engine.h"

extern "C" {
u8* fn_801A17F4(RwRaster* raster, s32 lockMode)
{
	u8* palette;
	if (lbl_8042C9A4->stdFunc[rwSTANDARDRASTERLOCKPALETTE](&palette, raster, lockMode)) {
		return palette;
	}
	return 0;
}
}
