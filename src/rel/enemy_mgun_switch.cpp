#include "types.h"

// ENEMY_MGUN's EmptyBulletNum, Off and On (the PS2 build's names):
// EmptyBulletNum answers whether no bullet is flying; Off turns the
// collision's attribute bit 0x10 on and stops the gun; On turns it off,
// clears the bullets and starts the gun.

#define ENEMY_MGUN_EMPTY_TYPE bool
#include "src/rel/enemy_mgun.inc"

extern "C" void* memset(void* dst, s32 value, u32 size);

bool ENEMY_MGUN::EmptyBulletNum()
{
	return bulletNum == 0;
}

void ENEMY_MGUN::Off()
{
	if (info != NULL) {
		info->attr |= 0x10;
	}
	active = 0;
}

void ENEMY_MGUN::On()
{
	if (info != NULL) {
		info->attr &= ~0x10;
	}
	unk128    = 4;
	bulletNum = 0;
	memset(bullets, 0, sizeof(bullets));
	active = 1;
}
