#include "types.h"

// HAWK_MGUN's constructor (the PS2 build's name), like ENEMY_MGUN's
// (rel/enemy_mgun.inc): the bullets built in place, a collision of one sphere
// (attribute bit 0x40 cleared), the speed and size, and the gun stopped.

#include "src/rel/hawk_mgun.inc"

extern "C" const f32 hawkMGunSpeed[1];
extern "C" const f32 hawkMGunSize[1];
extern "C" const f32 hawkMGunOne[1];

HAWK_MGUN::HAWK_MGUN(TObject* parent)
    : TObject(parent)
{
	hits = 0;
	done = 0;
	C_COLLI::Init(&hawkMGunCclInfo, 1, 3);
	flag &= ~0x40;
	speed     = hawkMGunSpeed[0];
	size      = hawkMGunSize[0];
	radObject = hawkMGunOne[0];
	active    = 0;
}
