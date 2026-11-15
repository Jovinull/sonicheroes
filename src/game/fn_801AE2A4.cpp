// Unlocks a raster (HYPOTHESIS: the GameCube driver's raster unlock standard function): for
// normal, texture and camera-texture rasters a write lock converts the lock buffer back into the
// texture data (fn_801AD924, unless the raster keeps its pixels in place, private flag 0x20) and
// flushes the texture from the data cache; a top-level raster gets its original size back, the
// lock buffer is freed, the pixel pointer and stride are cleared, the locked mip level is reset
// and the lock flags dropped on the raster and its parent. A written top level of an auto-mipmap
// raster then regenerates its mipmaps (fn_801A4E80). Other types raise error 0x80000011 of
// plugin 1. Returns 1, or 0 on error. Names are inferred from this function only.
// NonMatching: instruction stream matches; retail keeps the raster in r31 and the extension in
// r29 where this source swaps them (32 words). Declaration orders and a raster local do not help.
extern "C" {
#include "dolphin/gx.h"
#include "dolphin/os/OSCache.h"
}
#include "game/rw_engine.h"

// GameCube raster extension at raster + lbl_8042CA48 (fields used here only).
struct RasterExt801AE2A4 {
	u8 pad0[0x24];
	void* textureData; // 0x24
	void* lockBuffer;  // 0x28
	u8 pad2C[0x33 - 0x2C];
	u8 lockedMipLevel; // 0x33: 0xFF when not locked
};

#define RW_RASTER_TYPE_MASK              0x7
#define RW_RASTER_TYPE_NORMAL            0
#define RW_RASTER_TYPE_ZBUFFER           1
#define RW_RASTER_TYPE_CAMERA            2
#define RW_RASTER_TYPE_TEXTURE           4
#define RW_RASTER_TYPE_CAMERA_TEXTURE    5
#define RW_RASTER_PIXELS_IN_PLACE        0x20 // privateFlags
#define RW_RASTER_LOCK_FLAGS             0x26 // privateFlags
#define RW_RASTER_LOCKED_WRITE_801AE2A4  0x04 // privateFlags
#define RW_RASTER_AUTO_MIPMAP            0x10 // cFormat
#define RW_ERROR_INVALID_RASTER_801AE2A4 ((s32)0x80000011)

extern "C" {
extern s32 lbl_8042CA48;
void fn_801AD924(void* textureData, void* lockBuffer, s32 width, s32 height, s32 depth, s32 stride);
u32 fn_801AD620(RwRaster* raster, u8 mipLevel);
RwRaster* fn_801A4E80(RwRaster* raster, s32 flags);

s32 fn_801AE2A4(void* out, RwRaster* raster, s32 flags)
{
	RasterExt801AE2A4* ext;
	RwRaster* parent;

	parent = raster->parent;
	ext    = (RasterExt801AE2A4*)((u8*)parent + lbl_8042CA48);

	switch (raster->cType & RW_RASTER_TYPE_MASK) {
		case RW_RASTER_TYPE_NORMAL:
		case RW_RASTER_TYPE_TEXTURE:
		case RW_RASTER_TYPE_CAMERA_TEXTURE:
			if (raster->privateFlags & RW_RASTER_LOCKED_WRITE_801AE2A4) {
				if (!(raster->privateFlags & RW_RASTER_PIXELS_IN_PLACE)) {
					fn_801AD924(ext->textureData, ext->lockBuffer, parent->width, parent->height,
					    raster->depth, raster->stride);
				}
				DCFlushRange(ext->textureData, fn_801AD620(raster, ext->lockedMipLevel));
				GXInvalidateTexAll();
			}
			if (parent == raster) {
				raster->width  = raster->originalWidth;
				raster->height = raster->originalHeight;
			}
			if (!(raster->privateFlags & RW_RASTER_PIXELS_IN_PLACE)) {
				lbl_8042C9A4->rwfree(ext->lockBuffer);
				ext->lockBuffer = 0;
			}
			raster->stride   = 0;
			raster->cpPixels = 0;
			if ((raster->privateFlags & RW_RASTER_LOCKED_WRITE_801AE2A4)
			    && (raster->cFormat & RW_RASTER_AUTO_MIPMAP) && ext->lockedMipLevel == 0) {
				ext->lockedMipLevel = 0xFF;
				raster->privateFlags &= ~RW_RASTER_LOCK_FLAGS;
				parent->privateFlags &= ~RW_RASTER_LOCK_FLAGS;
				fn_801A4E80(raster, 0);
			} else {
				ext->lockedMipLevel = 0xFF;
				raster->privateFlags &= ~RW_RASTER_LOCK_FLAGS;
				parent->privateFlags &= ~RW_RASTER_LOCK_FLAGS;
			}
			break;
		case RW_RASTER_TYPE_ZBUFFER:
		case RW_RASTER_TYPE_CAMERA:
		default: {
			RwError error;
			error.pluginID  = 1;
			error.errorCode = fn_8019408C(RW_ERROR_INVALID_RASTER_801AE2A4);
			fn_80193FE8(&error);
			return 0;
		}
	}
	return 1;
}
}
