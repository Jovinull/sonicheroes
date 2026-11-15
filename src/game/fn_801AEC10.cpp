// Allocates the pixel memory of a GameCube raster (HYPOTHESIS: the driver's raster level
// allocator; names inferred): records the requested top mip level in the raster extension
// (lbl_8042CA48), takes the level count from the parent raster's extension, or from the size for
// a mipmapped raster (fn_801A91E8 gives the log2 of the larger side), or 1, sums the level sizes
// (fn_801AD620) and allocates them 32-byte aligned. A palettised raster also gets its palette
// after the pixels and an initialised TLUT object; a camera texture (type 5) has its pixel range
// invalidated in the data cache. Raises the out-of-memory error and returns 0 when the allocation
// fails; returns 1.
// NonMatching: retail keeps the level count in a 32-bit stack slot (stored and reloaded around
// every use, compared signed), as it does with the pixel of fn_801A92E0; this source keeps it in
// a register, which drops seven instructions and shifts the rest. An s32 count, byte casts and an
// inline level-count helper writing through a pointer do not reproduce the slot.
extern "C" {
#include "dolphin/gx.h"
#include "dolphin/os/OSCache.h"
}
#include "game/rw_engine.h"

#define RW_RASTER_TYPE_CAMERA_TEXTURE 5
#define RW_RASTER_FORMAT_PAL          0x6000 // PAL4 | PAL8 in the (cFormat << 8) raster format

// GameCube raster extension (plugin data at lbl_8042CA48; fields inferred).
struct RasterExt801AEC10 {
	GXTlutObj tlut; // 0x0
	u8 padC[0x10 - 0xC];
	GXTlutFmt tlutFormat; // 0x10
	u8 pad14[0x18 - 0x14];
	void* block; // 0x18: unaligned allocation
	u8* pixels;  // 0x1C: 32-byte aligned
	u8* palette; // 0x20
	u8 pad24[0x32 - 0x24];
	u8 maxLevel; // 0x32: index of the last mip level, 0xFF when unset
};

extern "C" {
extern s32 lbl_8042CA48;

// HYPOTHESIS: a log2 helper and the byte size of one raster level.
u8 fn_801A91E8(s32 value);
s32 fn_801AD620(RwRaster* raster, u8 level);

static inline RasterExt801AEC10* RasterExt801AEC10Get(RwRaster* raster)
{
	return (RasterExt801AEC10*)((u8*)raster + lbl_8042CA48);
}

s32 fn_801AEC10(RwRaster* raster, u8 numLevels)
{
	RasterExt801AEC10* ext = RasterExt801AEC10Get(raster);
	s32 size               = 0;
	u8 levels;

	ext->maxLevel = numLevels - 1;
	if (RasterExt801AEC10Get(raster->parent)->maxLevel != 0xFF) {
		levels = RasterExt801AEC10Get(raster->parent)->maxLevel + 1;
	} else if ((raster->cFormat << 8) & RW_RASTER_FORMAT_MIPMAP) {
		if (raster->width > raster->height) {
			levels = (u8)(fn_801A91E8(raster->width) + 1);
		} else {
			levels = (u8)(fn_801A91E8(raster->height) + 1);
		}
	} else {
		levels = 1;
	}
	while (levels--) {
		size += fn_801AD620(raster, levels);
	}

	if ((raster->cFormat << 8) & RW_RASTER_FORMAT_PAL) {
		s32 total  = size + (1 << raster->depth) * 2 + 0x1F;
		ext->block = lbl_8042C9A4->rwmalloc(total);
		if (ext->block == 0) {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, total);
			fn_80193FE8(&error);
			return 0;
		}
		ext->pixels  = (u8*)(((u32)ext->block + 0x1F) & ~0x1F);
		ext->palette = ext->pixels + size;
		GXInitTlutObj(&ext->tlut, ext->palette, ext->tlutFormat, (u16)(1 << raster->depth));
	} else {
		ext->block = lbl_8042C9A4->rwmalloc(size + 0x1F);
		if (ext->block == 0) {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size + 0x1F);
			fn_80193FE8(&error);
			return 0;
		}
		ext->pixels = (u8*)(((u32)ext->block + 0x1F) & ~0x1F);
		if (raster->cType == RW_RASTER_TYPE_CAMERA_TEXTURE) {
			DCInvalidateRange(ext->pixels, size);
		}
	}
	return 1;
}
}
