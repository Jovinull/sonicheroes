// Destroys a raster (HYPOTHESIS: RwRasterDestroy): runs the raster plugin destructors, releases
// the device raster through the driver standard function and returns it to the raster free list
// (at +0x60 in the raster module globals). Always returns 1.
#include "game/rw_engine.h"

extern "C" {
// Raster module bookkeeping (HYPOTHESIS: rasterModule) and plugin registry (rasterTKList).
extern RwModuleInfo lbl_8042C9B8;
extern RwPluginRegistry lbl_80290628;

s32 fn_801A173C(RwRaster* raster)
{
	fn_80198E04(&lbl_80290628, raster);
	lbl_8042C9A4->stdFunc[rwSTANDARDRASTERDESTROY](0, raster, 0);
	lbl_8042C9A4->freeListFree(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C9B8.globalsOffset + 0x60), raster);
	return 1;
}
}
