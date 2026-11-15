#ifndef GAME_RP_MATFX_H
#define GAME_RP_MATFX_H

#include "game/rw_engine.h"

// Material effects plugin data (HYPOTHESIS: RpMatFX material extension, at the lbl_8042C858 offset
// of a material). Effect types (HYPOTHESIS): 1 bump map (textures at 0x4 and 0x8), 2 environment
// map (texture at 0x4), 3 none, 4 dual texture (texture at 0x0), 5 UV transform.
struct RpMatFXEffect {
	void* word0; // 0x0
	void* word4; // 0x4
	void* word8; // 0x8
	u8 padC[0x8];
	s32 type; // 0x14
};

struct RpMatFXMaterialData {
	RpMatFXEffect effects[2]; // 0x0
	s32 flags;                // 0x30
};

// Plugin bookkeeping (only the free list of the material data is named).
struct RpMatFXPlugin {
	u8 pad0[0x8];
	RwFreeList* freeList; // 0x8
};

extern "C" {
extern s32 lbl_8042C858;
extern RpMatFXPlugin lbl_8028D1E8;
}

#define RP_MATFX_DATA(material) (*(RpMatFXMaterialData**)((u8*)(material) + lbl_8042C858))

#endif
