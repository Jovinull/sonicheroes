#ifndef GAME_RW_PALQUANT_H
#define GAME_RW_PALQUANT_H

#include "game/rw_engine.h"

// RenderWare palette quantizer around 0x801A5490 (HYPOTHESIS: palquant.c, used by the image
// palettisation code). Function names in comments are HYPOTHESIS; symbols stay fn_ addresses.

// Colour tree node (HYPOTHESIS). Interior nodes use the child table; leaves keep their palette
// index at 0x18, overlapping it.
union RwPalQuantNode {
	RwPalQuantNode* child[16];
	struct {
		u8 pad0[0x18];
		u8 paletteIndex; // 0x18
	} leaf;
};

// Quantizer state, built on the caller's stack (field names inferred from fn_801A7B04).
struct RwPalQuant {
	void* buffer0;            // 0x0: heap block released by the terminator (role UNKNOWN)
	void* buffer4;            // 0x4: heap block released by the terminator (role UNKNOWN)
	RwPalQuantNode* root;     // 0x8: colour tree
	RwFreeList* nodeFreeList; // 0xC: tree node free list
};

extern "C" {
// Depth of the colour tree (.sdata byte).
extern u8 lbl_8042BE60;

// HYPOTHESIS: _rwPalQuantInit.
s32 fn_801A75BC(RwPalQuant* quant);
// HYPOTHESIS: _rwPalQuantAddImage.
void fn_801A579C(RwPalQuant* quant, RwImage* image, f32 weight);
// HYPOTHESIS: _rwPalQuantResolvePalette.
s32 fn_801A6B4C(RwRGBA* palette, s32 maxColors, RwPalQuant* quant);
// HYPOTHESIS: _rwPalQuantMatchImage.
void fn_801A7194(
    u8* pixels, s32 stride, s32 depth, s32 palettised, RwPalQuant* quant, RwImage* image);
// Palette index of the leaf `depth` levels below the node along the 4-bit digits of the key.
u8 fn_801A7098(RwPalQuantNode* node, u32 key, s32 depth);
// HYPOTHESIS: deletes a colour subtree of the given depth.
void fn_801A77E0(RwPalQuant* quant, RwPalQuantNode* node, s32 depth);
// HYPOTHESIS: _rwPalQuantTerm.
void fn_801A7B04(RwPalQuant* quant);
}

#endif
