// Fills a locked 16-bit raster from an image (HYPOTHESIS: a GameCube RenderWare raster-from-image
// helper; names inferred). Picks the RGBA packer of the raster's pixel format (555, 565, the
// RGB5A3 1555/4444 encoding, 888 or 8888; LUM8 raises error 2 with lbl_802906D8, others
// 0x8000000D), then converts a 4- or 8-bit image through a packed copy of its palette and a 32-bit
// image pixel by pixel, row by row. Other image depths raise error 0x80000008.
// NonMatching: retail builds each packer address straight into the saved register (lis/addi
// r31), while this source goes through r0 and a move, one extra instruction per format case (five
// in all; the rest only shifts). Tried a C-linkage typedef, a plain pointer declaration, casts,
// void* packers, a separate null assignment, C mode and compilers GC/1.3 to 2.7.
#include "game/rw_engine.h"

#define RW_ERROR_INVALID_RASTER_FORMAT ((s32)0x8000000D)
#define RW_ERROR_INVALID_IMAGE_DEPTH   ((s32)0x80000008)

extern "C" {
typedef s32 (*PixelPacker801AA804)(RwRGBA* color);

extern char lbl_802906D8[];
// Pixel packers (HYPOTHESIS: 555, 565, RGB5A3, 888 and 8888).
s32 fn_801A9208(RwRGBA* color);
s32 fn_801A9228(RwRGBA* color);
s32 fn_801A9248(RwRGBA* color);
s32 fn_801A9298(RwRGBA* color);
s32 fn_801A92BC(RwRGBA* color);

static inline void RecordError801AA804(s32 code)
{
	RwError error;
	error.pluginID  = RW_ID_CORE_PLUGIN;
	error.errorCode = fn_8019408C(code);
	fn_80193FE8(&error);
}

void fn_801AA804(RwRaster* raster, RwImage* image)
{
	PixelPacker801AA804 pack = 0;
	s32 x;
	s32 y;

	switch ((raster->cFormat & 0xF) << 8) {
		case 0x400: {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(2, lbl_802906D8);
			fn_80193FE8(&error);
			break;
		}
		case 0xA00:
			pack = fn_801A9208;
			break;
		case 0x200:
			pack = fn_801A9228;
			break;
		case 0x100:
		case 0x300:
			pack = fn_801A9248;
			break;
		case 0x600:
			pack = fn_801A9298;
			break;
		case 0x500:
			pack = fn_801A92BC;
			break;
		default:
			RecordError801AA804(RW_ERROR_INVALID_RASTER_FORMAT);
			break;
	}

	switch (image->depth) {
		case 4:
		case 8: {
			u16 table[256];
			u16* entry = table;
			s32 i;
			for (i = 0; i < (1 << image->depth); i++) {
				*entry++ = pack(&image->palette[i]);
			}
			for (y = 0; y < raster->height; y++) {
				u8* src  = image->cpPixels + image->stride * y;
				u16* dst = (u16*)(raster->cpPixels + raster->stride * y);
				for (x = 0; x < raster->width; x++) {
					*dst++ = table[*src++];
				}
			}
			break;
		}
		case 32:
			for (y = 0; y < raster->height; y++) {
				RwRGBA* src = (RwRGBA*)(image->cpPixels + image->stride * y);
				u16* dst    = (u16*)(raster->cpPixels + raster->stride * y);
				for (x = 0; x < raster->width; x++) {
					*dst++ = pack(src++);
				}
			}
			break;
		default:
			RecordError801AA804(RW_ERROR_INVALID_IMAGE_DEPTH);
			break;
	}
}
}
