// Creates a raster (HYPOTHESIS: RwRasterCreate): takes one from the raster free list, initializes
// it as its own parent with the given size and depth, no pixels, palette, offset or flags, and asks
// the driver standard function to create the device raster for the type/format flags. On driver
// failure the raster is released; otherwise the raster plugin constructors run. Returns the raster,
// or null.
#include "game/rw_engine.h"

extern "C" {
RwRaster* fn_801A19D4(s32 width, s32 height, s32 depth, s32 flags)
{
	RwRaster* raster = (RwRaster*)lbl_8042C9A4->freeListAlloc(RW_RASTER_FREE_LIST);
	if (raster != 0) {
		RwStandardFunc createRaster = lbl_8042C9A4->stdFunc[rwSTANDARDRASTERCREATE];
		raster->privateFlags        = 0;
		raster->cFlags              = 0;
		raster->width               = width;
		raster->height              = height;
		raster->nOffsetX            = 0;
		raster->nOffsetY            = 0;
		raster->depth               = depth;
		raster->parent              = raster;
		raster->cpPixels            = 0;
		raster->palette             = 0;
		if (!createRaster(0, raster, flags)) {
			lbl_8042C9A4->freeListFree(RW_RASTER_FREE_LIST, raster);
			return 0;
		}
		fn_80198D5C(&lbl_80290628, raster);
		return raster;
	}
	return 0;
}
}
