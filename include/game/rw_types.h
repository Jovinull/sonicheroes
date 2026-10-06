#ifndef GAME_RW_TYPES_H
#define GAME_RW_TYPES_H

#include "types.h"

// Shared layouts reconstructed from retail metadata and GameCube field accesses.
struct RwV3d {
	f32 x, y, z;
};
struct RwRGBA {
	u8 red, green, blue, alpha;
};

#endif
