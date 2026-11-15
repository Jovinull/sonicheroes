// Unpacks one pixel of the given raster format into an RwRGBA colour (HYPOTHESIS: the GameCube
// RenderWare pixel-to-RGB converter, inverse of fn_801A92E0): the default format goes through
// fn_801A94F0, 555 and 565 expand to opaque colours, 1555 and 4444 decode the GameCube RGB5A3
// encoding (1555 keeps a zero alpha for translucent pixels, 4444 its 3-bit alpha), 888 and 8888
// split 32-bit ARGB. LUM8 raises error 2 with the message at lbl_802906D8 and other formats raise
// 0x8000000D; 1 is returned in every case, as retail does.
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

// RGB5A3 pixels with this bit set are opaque 555 colours.
#define GX_RGB5A3_OPAQUE 0x8000

extern "C" {
// Message for the unsupported LUM8 format (UNKNOWN text).
extern char lbl_802906D8[];
// HYPOTHESIS: the default-format unpacker.
void fn_801A94F0(RwRGBA* color, u32 pixel);

s32 fn_801A95F4(RwRGBA* color, u32* pixelIn, s32 format)
{
	u32 pixel = *pixelIn;

	switch (format & RW_RASTER_FORMAT_PIXEL_MASK) {
		case RW_RASTER_FORMAT_DEFAULT:
			fn_801A94F0(color, pixel);
			break;
		case RW_RASTER_FORMAT_LUM8: {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(2, lbl_802906D8);
			fn_80193FE8(&error);
			break;
		}
		case RW_RASTER_FORMAT_555:
			color->red   = (pixel >> 7) & 0xF8;
			color->green = (pixel >> 2) & 0xF8;
			color->blue  = (pixel & 0x1F) << 3;
			color->alpha = 0xFF;
			break;
		case RW_RASTER_FORMAT_1555:
			if (pixel & GX_RGB5A3_OPAQUE) {
				color->red   = (pixel >> 7) & 0xF8;
				color->green = (pixel >> 2) & 0xF8;
				color->blue  = (pixel & 0x1F) << 3;
				color->alpha = 0xFF;
			} else {
				color->red   = (pixel >> 4) & 0xF0;
				color->green = pixel & 0xF0;
				color->blue  = (pixel & 0xF) << 4;
				color->alpha = 0;
			}
			break;
		case RW_RASTER_FORMAT_565:
			color->red   = (pixel >> 8) & 0xF8;
			color->green = (pixel >> 3) & 0xFC;
			color->blue  = (pixel & 0x1F) << 3;
			color->alpha = 0xFF;
			break;
		case RW_RASTER_FORMAT_4444:
			if (pixel & GX_RGB5A3_OPAQUE) {
				color->red   = (pixel >> 7) & 0xF8;
				color->green = (pixel >> 2) & 0xF8;
				color->blue  = (pixel & 0x1F) << 3;
				color->alpha = 0xFF;
			} else {
				color->red   = (pixel >> 4) & 0xF0;
				color->green = pixel & 0xF0;
				color->blue  = (pixel & 0xF) << 4;
				color->alpha = (pixel >> 7) & 0xE0;
			}
			break;
		case RW_RASTER_FORMAT_888:
			color->alpha = 0xFF;
			color->red   = (pixel >> 16) & 0xFF;
			color->green = (pixel >> 8) & 0xFF;
			color->blue  = pixel & 0xFF;
			break;
		case RW_RASTER_FORMAT_8888:
			color->alpha = pixel >> 24;
			color->red   = (pixel >> 16) & 0xFF;
			color->green = (pixel >> 8) & 0xFF;
			color->blue  = pixel & 0xFF;
			break;
		default: {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(RW_ERROR_INVALID_RASTER_FORMAT);
			fn_80193FE8(&error);
			break;
		}
	}
	return 1;
}
}
