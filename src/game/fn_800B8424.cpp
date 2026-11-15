// Sets up an object's render target once (its texture at +0x28): when the player/slot pair
// (+0x0/+0x1) is unset, takes `player` (0-7) and `slot` (0-2) unless either is -1; then creates a
// 128x128 raster (fn_801A19D4, +0x20) and its texture (fn_801A4874, +0x28) and, when the raster
// exists, an empty raster (+0x24) made the 124x124 sub-raster of it at (2, 2) (fn_801A1924).
// HYPOTHESIS: RwRasterCreate/RwTextureCreate/
// RwRasterSubRaster for a player portrait; the roles are UNKNOWN.
#include "types.h"

struct RwRect800B8424 {
	s32 x;
	s32 y;
	s32 w;
	s32 h;
};

struct Obj800B8424 {
	s8 player; // 0x0
	s8 slot;   // 0x1
	u8 pad2[0x20 - 0x2];
	void* raster;    // 0x20
	void* subRaster; // 0x24
	void* texture;   // 0x28
};

extern "C" {
void* fn_801A19D4(s32 width, s32 height, s32 depth, s32 flags);
void* fn_801A4874(void* raster);
void fn_801A1924(void* sub, void* raster, RwRect800B8424* rect);

void fn_800B8424(Obj800B8424* o, s32 player, s32 slot)
{
	if (o->texture != NULL) {
		return;
	}
	if (o->player == -1 || o->slot == -1) {
		if (player == -1 || slot == -1) {
			return;
		}
		if (player < 8 && player >= 0) {
			o->player = player;
			if (slot < 3 && slot >= 0) {
				o->slot = slot;
			}
		}
	}
	o->raster  = fn_801A19D4(0x80, 0x80, 0, 5);
	o->texture = fn_801A4874(o->raster);
	if (o->raster != NULL) {
		RwRect800B8424 rect;

		o->subRaster = fn_801A19D4(0, 0, 0, 5);
		rect.y = rect.x = 2;
		rect.w = rect.h = 0x7C;
		fn_801A1924(o->subRaster, o->raster, &rect);
	}
}
}
