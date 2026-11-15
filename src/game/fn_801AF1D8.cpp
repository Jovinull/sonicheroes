// Destroys the device data of a raster (HYPOTHESIS: the GameCube driver's raster-destroy standard
// function): for a top-level raster that owns its pixels and is of type 0, 4 or 5, waits until the
// GPU has passed the raster's draw-sync token (issuing the pending token lbl_8042BE88 first when it
// is the raster's, then advancing it modulo 0xE000), unbinds it from the texture slot lbl_8042CA54
// (fn_801AF31C) when bound there, and frees its pixel block. Types 1 and 2 need nothing; other
// types record core error 0x8000000D and return 0. Field names are inferred.
#include "dolphin/gx/GXManage.h"
#include "game/rw_engine.h"

// Driver extension of a raster (at the lbl_8042CA48 offset).
struct RasterExt801AF1D8 {
	u8 pad0[0x18];
	void* pixels; // 0x18
	u8 pad1C[0x30 - 0x1C];
	u16 drawSyncToken; // 0x30
};

struct TextureSlot801AF1D8 {
	RwRaster* raster; // 0x0
};

#define RW_RASTER_DONT_ALLOCATE 0x80

extern "C" {
extern s32 lbl_8042CA48;
// Next GX draw-sync token; volatile because it is shared with the draw-sync handling and the
// retail code re-reads it on every use.
extern volatile u16 lbl_8042BE88;
extern TextureSlot801AF1D8* lbl_8042CA54;

s32 fn_801B2894(u16 token);
s32 fn_801AF31C(TextureSlot801AF1D8* slot, s32 a, s32 b);

s32 fn_801AF1D8(void* out, void* inOut, s32)
{
	RwRaster* raster = (RwRaster*)inOut;

	if (raster->parent == raster && !(raster->cFlags & RW_RASTER_DONT_ALLOCATE)) {
		switch (raster->cType) {
			case 0:
			case 4:
			case 5: {
				RasterExt801AF1D8* ext = (RasterExt801AF1D8*)((u8*)raster + lbl_8042CA48);
				if (ext->drawSyncToken == lbl_8042BE88) {
					GXSetDrawSync(lbl_8042BE88);
					lbl_8042BE88 = (lbl_8042BE88 + 1) % 0xE000;
				}
				while (!fn_801B2894(ext->drawSyncToken)) {
				}
				if (lbl_8042CA54 && raster == lbl_8042CA54->raster) {
					fn_801AF31C(lbl_8042CA54, 0, 0);
				}
				lbl_8042C9A4->rwfree(ext->pixels);
				break;
			}
			case 1:
			case 2:
				break;
			default: {
				RwError error;
				error.pluginID  = RW_ID_CORE_PLUGIN;
				error.errorCode = fn_8019408C((s32)0x8000000D);
				fn_80193FE8(&error);
				return 0;
			}
		}
	}
	return 1;
}
}
