// Creates a character set raster (HYPOTHESIS: RtCharsetCreate): picks the smallest power-of-two
// square, at least 32 pixels, that holds the 90 glyphs of 9x15 pixels, creates a texture raster of
// that size (fn_801A19D4, HYPOTHESIS: RwRasterCreate) and draws the glyphs in the given colours
// (fn_801782D8); a raster that cannot be drawn is destroyed again (fn_801A173C, first ending the
// current print batch of lbl_8028D840 when it uses that raster). Null colours record error
// 0x80000016 of plugin 0x180. Returns the raster or null.
#include "game/rw_engine.h"

// Print batch state of the character set code (fields used here only).
struct CharsetBatch801784C8 {
	s32 active;       // 0x0
	RwRaster* raster; // 0x4
	u8 pad8[0x18 - 0x8];
};

#define RT_CHARSET_PLUGIN_ID  0x180
#define RW_ERROR_NULL_POINTER ((s32)0x80000016)

extern "C" {
extern CharsetBatch801784C8 lbl_8028D840;

RwRaster* fn_801A19D4(s32 width, s32 height, s32 depth, s32 flags);
s32 fn_801A173C(RwRaster* raster);
RwRaster* fn_801782D8(RwRaster* raster, const RwRGBA* foreground, const RwRGBA* background);
void fn_80177C50(void);
}

static inline void CharsetRecordNullError(void)
{
	RwError error;
	error.pluginID  = RT_CHARSET_PLUGIN_ID;
	error.errorCode = fn_8019408C(RW_ERROR_NULL_POINTER);
	fn_80193FE8(&error);
}

static inline void CharsetDestroy(RwRaster* raster)
{
	if (raster) {
		if (lbl_8028D840.active && lbl_8028D840.raster == raster) {
			fn_80177C50();
		}
		fn_801A173C(raster);
	} else {
		CharsetRecordNullError();
	}
}

extern "C" {
RwRaster* fn_801784C8(const RwRGBA* foreground, const RwRGBA* background)
{
	RwRaster* result = 0;

	if (foreground && background) {
		s32 size = 16;
		RwRaster* raster;
		do {
			size += size;
		} while (size < ((size / 9 + 90) / (size / 9)) * 15);
		raster = fn_801A19D4(size, size, 0, 4);
		if (raster) {
			if (fn_801782D8(raster, foreground, background)) {
				result = raster;
			} else {
				CharsetDestroy(raster);
			}
		}
	} else {
		CharsetRecordNullError();
	}
	return result;
}
}
