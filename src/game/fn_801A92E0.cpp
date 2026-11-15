// Packs an RwRGBA colour into one pixel of the given raster format (HYPOTHESIS: the GameCube
// RenderWare RGB-to-pixel converter): default and 565 give RGB565, 1555 and 4444 give the
// GameCube RGB5A3 encoding (opaque 555 with the top bit set, otherwise 3-bit alpha and 4-bit
// colour), 555 gives opaque 555, 8888 and 888 give 32-bit ARGB. LUM8 raises error 2 with the
// message at lbl_802906D8 and other formats raise 0x8000000D; the pixel is stored and 1 returned
// in every case, as retail does.
// NonMatching: retail keeps the pixel in a stack slot (0x8) and gives each error record its own
// slot (0x30-byte frame), while this source keeps the pixel in r30 and shares one error slot, so
// the prologue, epilogue and stack offsets differ (same 123 instructions). Tried array, union and
// memcpy pixel locals and a C-mode probe.
#include "game/rw_engine.h"

#define RW_RASTER_FORMAT_PIXEL_MASK 0xF00
#define RW_RASTER_FORMAT_DEFAULT    0x000
#define RW_RASTER_FORMAT_1555       0x100
#define RW_RASTER_FORMAT_565        0x200
#define RW_RASTER_FORMAT_4444       0x300
#define RW_RASTER_FORMAT_LUM8       0x400
#define RW_RASTER_FORMAT_8888       0x500
#define RW_RASTER_FORMAT_888        0x600
#define RW_RASTER_FORMAT_555        0xA00

#define RW_ERROR_INVALID_RASTER_FORMAT ((s32)0x8000000D)

extern "C" {
// Message for the unsupported LUM8 format (UNKNOWN text).
extern char lbl_802906D8[];

s32 fn_801A92E0(u32* pixelOut, RwRGBA* color, s32 format)
{
	u32 pixel;

	switch (format & RW_RASTER_FORMAT_PIXEL_MASK) {
		case RW_RASTER_FORMAT_DEFAULT:
			pixel
			    = ((color->red << 8) & 0xF800) | ((color->green << 3) & 0x7E0) | (color->blue >> 3);
			break;
		case RW_RASTER_FORMAT_LUM8: {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(2, lbl_802906D8);
			fn_80193FE8(&error);
			break;
		}
		case RW_RASTER_FORMAT_1555:
		case RW_RASTER_FORMAT_4444:
			if (color->alpha != 0xFF) {
				pixel = ((color->alpha << 7) & 0x7000) | ((color->red << 4) & 0xF00)
				    | (color->green & 0xF0) | (color->blue >> 4);
			} else {
				pixel = 0x8000 | ((color->red << 7) & 0x7C00) | ((color->green << 2) & 0x3E0)
				    | (color->blue >> 3);
			}
			break;
		case RW_RASTER_FORMAT_555:
			pixel = 0x8000 | ((color->red << 7) & 0x7C00) | ((color->green << 2) & 0x3E0)
			    | (color->blue >> 3);
			break;
		case RW_RASTER_FORMAT_565:
			pixel
			    = ((color->red << 8) & 0xF800) | ((color->green << 3) & 0x7E0) | (color->blue >> 3);
			break;
		case RW_RASTER_FORMAT_8888:
			pixel = (color->alpha << 24) | (color->red << 16) | (color->green << 8) | color->blue;
			break;
		case RW_RASTER_FORMAT_888:
			pixel = 0xFF000000 | (color->red << 16) | (color->green << 8) | color->blue;
			break;
		default: {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(RW_ERROR_INVALID_RASTER_FORMAT);
			fn_80193FE8(&error);
			break;
		}
	}
	*pixelOut = pixel;
	return 1;
}
}
