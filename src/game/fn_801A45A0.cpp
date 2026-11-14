// Attaches a raster to the texture through the driver standard function, or detaches the current
// one when raster is null (HYPOTHESIS: RwTextureSetRaster). Returns the texture, or null when the
// driver fails.
#include "game/rw_engine.h"

extern "C" {
RwTexture* fn_801A45A0(RwTexture* texture, RwRaster* raster)
{
	if (raster != 0) {
		if (lbl_8042C9A4->stdFunc[rwSTANDARDTEXTURESETRASTER](texture, raster, 0)) {
			return texture;
		}
		return 0;
	}
	texture->raster = 0;
	return texture;
}
}
