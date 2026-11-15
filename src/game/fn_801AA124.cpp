// Copies an image into a raster (HYPOTHESIS: the GameCube driver's raster-set-image standard
// function): locks the raster pixels for writing (fn_801A1AC8, HYPOTHESIS: RwRasterLock) and, for
// palettised formats (0x6000), the palette (fn_801A17F4, HYPOTHESIS: RwRasterLockPalette) unless
// they are already locked, converts the 4-, 8- or 32-bit image (fn_801A97FC, fn_801A9A50,
// fn_801A9D44) and unlocks what it locked (fn_801A16E8, fn_801A16A0). Other depths record core
// error 0x80000008. Always returns 1.
#include "game/rw_engine.h"

#define RW_RASTER_PIXEL_LOCKED   0x2
#define RW_RASTER_PALETTE_LOCKED 0x8
#define RW_RASTER_FORMAT_PAL     0x6000

extern "C" {
void* fn_801A1AC8(RwRaster* raster, u8 level, s32 mode);
void* fn_801A17F4(RwRaster* raster, s32 mode);
RwRaster* fn_801A16E8(RwRaster* raster);
RwRaster* fn_801A16A0(RwRaster* raster);
void fn_801A97FC(RwImage* image, RwRaster* raster);
void fn_801A9A50(RwImage* image, RwRaster* raster);
void fn_801A9D44(RwImage* image, RwRaster* raster);

// Standard-function signature (RwStandardFunc): the image comes in as out, the raster as inOut.
s32 fn_801AA124(void* out, void* inOut, s32)
{
	RwImage* image    = (RwImage*)out;
	RwRaster* raster  = (RwRaster*)inOut;
	s32 lockedPixels  = 0;
	s32 lockedPalette = 0;

	if (!(raster->privateFlags & RW_RASTER_PIXEL_LOCKED)) {
		fn_801A1AC8(raster, 0, 2);
		lockedPixels = 1;
	}
	if (((raster->cFormat << 8) & RW_RASTER_FORMAT_PAL)
	    && !(raster->privateFlags & RW_RASTER_PALETTE_LOCKED)) {
		fn_801A17F4(raster, 2);
		lockedPalette = 1;
	}
	switch (image->depth) {
		case 4:
			fn_801A97FC(image, raster);
			break;
		case 8:
			fn_801A9A50(image, raster);
			break;
		case 32:
			fn_801A9D44(image, raster);
			break;
		default: {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C((s32)0x80000008);
			fn_80193FE8(&error);
			break;
		}
	}
	if (lockedPalette == 1) {
		fn_801A16E8(raster);
	}
	if (lockedPixels == 1) {
		fn_801A16A0(raster);
	}
	return 1;
}
}
