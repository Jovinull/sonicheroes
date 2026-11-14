// Locks one mip level of the raster's pixels through the driver standard function; the level is
// passed in bits 8-15 of the lock flags (HYPOTHESIS: RwRasterLock). Returns the pixels, or null
// when the lock fails.
#include "game/rw_engine.h"

extern "C" {
u8* fn_801A1AC8(RwRaster* raster, u8 level, s32 lockMode)
{
	u8* pixels;
	if (lbl_8042C9A4->stdFunc[rwSTANDARDRASTERLOCK](&pixels, raster, lockMode + (level << 8))) {
		return pixels;
	}
	return 0;
}
}
