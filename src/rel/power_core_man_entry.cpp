#include "types.h"

// TEnemyPowerCoreMan::Entry (the PS2 build's name), the same in the bonus
// stages (31D-33D): one more request for a power core of the given type at a
// place, with no leader chosen yet.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct PowerCoreMan {
	u8 unk00[0x28];
	s32 count; // 0x28
	s32 type;  // 0x2C
	RwV3d pos; // 0x30
	u8 unk3C[0x14];
	s32 leader; // 0x50
} PowerCoreMan;

extern "C" void Entry__18TEnemyPowerCoreManFPC5RwV3di(
    PowerCoreMan* object, const RwV3d* pos, s32 type)
{
	object->count++;
	object->pos.x  = pos->x;
	object->pos.y  = pos->y;
	object->pos.z  = pos->z;
	object->leader = 0;
	object->type   = type;
}
