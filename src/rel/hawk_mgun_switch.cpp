#include "types.h"

// HAWK_MGUN's EmptyBulletNum, Off and On (the PS2 build's names), like
// ENEMY_MGUN's (rel/enemy_mgun_switch.cpp): EmptyBulletNum answers whether no
// bullet is flying; Off turns the collision's attribute bit 0x10 on and stops
// the gun; On turns it off, sets every bullet back at rest and starts the gun.

#define HAWK_MGUN_EMPTY_TYPE bool
#include "src/rel/hawk_mgun.inc"

bool HAWK_MGUN::EmptyBulletNum()
{
	return bulletNum == 0;
}

void HAWK_MGUN::Off()
{
	if (info != NULL) {
		info->attr |= 0x10;
	}
	active = 0;
}

void HAWK_MGUN::On()
{
	if (info != NULL) {
		info->attr &= ~0x10;
	}
	unk128    = 4;
	bulletNum = 0;
	for (u32 i = 0; i < 40; i++) {
		bullets[i].Init();
	}
	active = 1;
}
