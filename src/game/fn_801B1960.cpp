// Reads a native GameCube texture from a stream (HYPOTHESIS: the driver's native texture reader,
// RwTextureStreamReadNative's platform part; names inferred). Checks the struct chunk version
// (0x31000-0x35000) and the 0x58-byte texture header (platform 6), creates an unallocated raster
// from the 0x10-byte raster header (fn_801A19D4), records three header values in the raster
// extension (lbl_8042CA48) and builds its levels (fn_801AEC10). Reads the palette of a palettised
// raster and the pixel block into the extension buffers, flushing both from the data cache, then
// creates the texture and applies the header's filter and addressing modes, names and the values
// handled by fn_801B2620. Stores the texture and returns 1; returns 0 on any failure, destroying
// the raster when it was created.
extern "C" {
#include "dolphin/gx.h"
#include "dolphin/os/OSCache.h"
}
#include "game/rw_engine.h"

#define RW_CHUNK_STRUCT          0x1
#define RW_VERSION_MIN           0x31000
#define RW_VERSION_MAX           0x35000
#define RW_PLATFORM_GAMECUBE     6
#define RW_RASTER_FORMAT_PAL     0x6000 // PAL4 | PAL8 in the (cFormat << 8) raster format
#define RW_RASTER_FORMAT_AUTOMIP 0x10   // cFormat bit (HYPOTHESIS)

struct NativeTextureHeader801B1960 {
	s32 platformId;       // 0x0
	u32 filterAddressing; // 0x4
	s32 value8;           // 0x8 (UNKNOWN)
	s32 valueC;           // 0xC (UNKNOWN)
	s32 value10;          // 0x10 (UNKNOWN)
	f32 value14;          // 0x14 (UNKNOWN)
	char name[32];        // 0x18
	char mask[32];        // 0x38
};

struct NativeRasterHeader801B1960 {
	s32 format;    // 0x0
	u16 width;     // 0x4
	u16 height;    // 0x6
	u8 depth;      // 0x8
	u8 numLevels;  // 0x9
	u8 valueA;     // 0xA (UNKNOWN)
	u8 valueB;     // 0xB (UNKNOWN)
	u32 hasValueC; // 0xC (UNKNOWN; stored as a boolean)
};

// GameCube raster extension (plugin data at lbl_8042CA48; fields inferred).
struct RasterExt801B1960 {
	u8 pad0[0xC];
	s32 valueC;  // 0xC
	s32 value10; // 0x10
	s32 value14; // 0x14
	u8 pad18[0x1C - 0x18];
	void* pixels;  // 0x1C
	void* palette; // 0x20
};

extern "C" {
extern s32 lbl_8042CA48;

// HYPOTHESIS: RwStreamFindChunk, RwStreamRead, RwRasterCreate, RwRasterDestroy, RwTextureCreate,
// RwTextureSetName and RwTextureSetMaskName; fn_801AEC10 builds the raster levels and fn_801B2620
// applies the remaining header values.
s32 fn_80192F38(void* stream, u32 type, u32* length, u32* version);
u32 fn_801979AC(void* stream, void* buffer, u32 length);
RwRaster* fn_801A19D4(s32 width, s32 height, s32 depth, s32 flags);
s32 fn_801A173C(RwRaster* raster);
s32 fn_801AEC10(RwRaster* raster, u8 numLevels);
RwTexture* fn_801A4874(RwRaster* raster);
RwTexture* fn_801A49E4(RwTexture* texture, const char* name);
RwTexture* fn_801A4A90(RwTexture* texture, const char* mask);
void fn_801B2620(RwTexture* texture, f32 value, s32 a, s32 b, s32 c);

// HYPOTHESIS: RwTextureSetFilterMode, RwTextureSetAddressingU and RwTextureSetAddressingV.
static inline void SetFilterMode801B1960(RwTexture* texture, u8 mode)
{
	texture->filterAddressing = (texture->filterAddressing & ~0xFF) | (mode & 0xFF);
}

static inline void SetAddressingU801B1960(RwTexture* texture, u32 mode)
{
	texture->filterAddressing = (texture->filterAddressing & ~0xF00) | ((mode << 8) & 0xF00);
}

static inline void SetAddressingV801B1960(RwTexture* texture, u32 mode)
{
	texture->filterAddressing = (texture->filterAddressing & ~0xF000) | ((mode << 12) & 0xF000);
}

s32 fn_801B1960(void* stream, RwTexture** outTexture)
{
	NativeTextureHeader801B1960 texHeader;
	NativeRasterHeader801B1960 rasterHeader;
	u32 length;
	u32 version;
	u32 size;
	RwRaster* raster;
	RasterExt801B1960* ext;
	u32 autoMip;
	RwTexture* texture;

	if (fn_80192F38(stream, RW_CHUNK_STRUCT, &length, &version) == 0) {
		return 0;
	}
	if (version < RW_VERSION_MIN || version > RW_VERSION_MAX) {
		return 0;
	}
	if (fn_801979AC(stream, &texHeader, sizeof(texHeader)) != sizeof(texHeader)) {
		return 0;
	}
	if (texHeader.platformId != RW_PLATFORM_GAMECUBE) {
		return 0;
	}
	if (fn_801979AC(stream, &rasterHeader, sizeof(rasterHeader)) != sizeof(rasterHeader)) {
		return 0;
	}

	raster = fn_801A19D4(rasterHeader.width, rasterHeader.height, rasterHeader.depth,
	    rasterHeader.format | RW_RASTER_DONT_ALLOCATE);
	if (raster == 0) {
		return 0;
	}
	ext          = (RasterExt801B1960*)((u8*)raster + lbl_8042CA48);
	ext->valueC  = rasterHeader.valueA;
	ext->value10 = rasterHeader.valueB;
	ext->value14 = rasterHeader.hasValueC != 0;
	if (fn_801AEC10(raster, rasterHeader.numLevels) == 0) {
		fn_801A173C(raster);
		return 0;
	}
	raster->cFlags &= ~RW_RASTER_DONT_ALLOCATE;

	if ((raster->cFormat << 8) & RW_RASTER_FORMAT_PAL) {
		u32 paletteSize = (1 << raster->depth) * 2;
		if (paletteSize != fn_801979AC(stream, ext->palette, paletteSize)) {
			return 0;
		}
		DCFlushRange(ext->palette, (1 << raster->depth) * 2);
	}

	autoMip = raster->cFormat & RW_RASTER_FORMAT_AUTOMIP;
	raster->cFormat &= ~autoMip;
	if (fn_801979AC(stream, &size, sizeof(size)) != sizeof(size)) {
		return 0;
	}
	if (size != fn_801979AC(stream, ext->pixels, size)) {
		return 0;
	}
	DCFlushRange(ext->pixels, size);
	GXInvalidateTexAll();
	raster->cFormat |= autoMip;

	texture = fn_801A4874(raster);
	if (texture == 0) {
		fn_801A173C(raster);
		return 0;
	}
	SetFilterMode801B1960(texture, texHeader.filterAddressing & 0xFF);
	SetAddressingU801B1960(texture, (texHeader.filterAddressing >> 8) & 0xF);
	SetAddressingV801B1960(texture, (texHeader.filterAddressing >> 12) & 0xF);
	fn_801A49E4(texture, texHeader.name);
	fn_801A4A90(texture, texHeader.mask);
	fn_801B2620(texture, texHeader.value14, texHeader.valueC, texHeader.value10, texHeader.value8);
	*outTexture = texture;
	return 1;
}
}
