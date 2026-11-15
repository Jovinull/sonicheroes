// Picks the raster pixel format for an image from its alpha values (HYPOTHESIS: the GameCube
// driver's image-find-raster-format helper): an alpha that is neither opaque (0xFF) nor at most
// 0xF needs 8888 (0x300); otherwise any non-opaque alpha gives 1555 (0x100) and a fully opaque
// image 565 (0x200). 4- and 8-bit images are judged by their palette entries and get the PAL4
// (0x4000) or PAL8 (0x2000) flag.
// NonMatching: the retail early return builds 8888 | PAL from a register (li/ori) instead of one
// folded constant, and the final format lands in r3 directly (76 vs 75 instructions).
#include "game/rw_engine.h"

#define RW_RASTER_FORMAT_1555 0x100
#define RW_RASTER_FORMAT_565  0x200
#define RW_RASTER_FORMAT_8888 0x300
#define RW_RASTER_FORMAT_PAL8 0x2000
#define RW_RASTER_FORMAT_PAL4 0x4000

extern "C" {
s32 fn_801AAEC4(const RwImage* image)
{
	s32 depth    = image->depth;
	s32 hasAlpha = 0;
	s32 format;

	if (depth == 4 || depth == 8) {
		s32 width             = image->width;
		s32 height            = image->height;
		const u8* row         = image->cpPixels;
		const RwRGBA* palette = image->palette;
		s32 y;
		for (y = 0; y < height; y++) {
			const u8* pixel = row;
			s32 x;
			for (x = 0; x < width; x++) {
				u32 alpha = palette[*pixel].alpha;
				if (alpha != 0xFF) {
					hasAlpha = 1;
					if (alpha > 0xF) {
						format = RW_RASTER_FORMAT_8888;
						return format
						    | (depth == 4 ? RW_RASTER_FORMAT_PAL4 : RW_RASTER_FORMAT_PAL8);
					}
				}
				pixel++;
			}
			row += image->stride;
		}
	} else {
		s32 width     = image->width;
		s32 height    = image->height;
		const u8* row = image->cpPixels;
		s32 y;
		for (y = 0; y < height; y++) {
			const RwRGBA* pixel = (const RwRGBA*)row;
			s32 x;
			for (x = 0; x < width; x++) {
				u32 alpha = pixel->alpha;
				if (alpha != 0xFF) {
					hasAlpha = 1;
					if (alpha > 0xF) {
						return RW_RASTER_FORMAT_8888;
					}
				}
				pixel++;
			}
			row += image->stride;
		}
	}

	format = hasAlpha ? RW_RASTER_FORMAT_1555 : RW_RASTER_FORMAT_565;
	if (depth == 4) {
		format |= RW_RASTER_FORMAT_PAL4;
	} else if (depth == 8) {
		format |= RW_RASTER_FORMAT_PAL8;
	}
	return format;
}
}
