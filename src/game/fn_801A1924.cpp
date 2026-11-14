// Makes subRaster a view of the rectangle rect of raster (HYPOTHESIS: RwRasterSubRaster): only for
// a sub-raster created without its own pixels; it takes the rectangle's size, offsets its origin
// inside raster by the rectangle position and is set up by the driver standard function, then
// shares raster's parent. Returns subRaster, or null on failure.
#include "game/rw_engine.h"

// Rectangle (HYPOTHESIS: RwRect).
struct RwRect801A1924 {
	s32 x;
	s32 y;
	s32 w;
	s32 h;
};

extern "C" {
RwRaster* fn_801A1924(RwRaster* subRaster, RwRaster* raster, RwRect801A1924* rect)
{
	if (!(subRaster->cFlags & RW_RASTER_DONT_ALLOCATE)) {
		return 0;
	}
	subRaster->width    = rect->w;
	subRaster->height   = rect->h;
	subRaster->nOffsetX = raster->nOffsetX + (s16)rect->x;
	subRaster->nOffsetY = raster->nOffsetY + (s16)rect->y;
	if (lbl_8042C9A4->stdFunc[rwSTANDARDRASTERSUBRASTER](subRaster, raster, 0)) {
		subRaster->parent = raster->parent;
		return subRaster;
	}
	return 0;
}
}
