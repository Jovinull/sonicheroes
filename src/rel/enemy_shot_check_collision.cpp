#include "game/effect/eff_bomb.h"
#include "game/object.h"

// ENEMY_SHOT::CheckCollision (the PS2 build's name): a shot that hit something
// (its collision's flags 0x20 or 0x10) or the ground blows up: mode 2, the
// blast's start size, and its collision switched off.

#include "src/rel/enemy_shot.inc"

extern "C" const f32 enemyShotBlastStart[1];
extern "C" const f32 enemyShotZero[1];

// the collision's hit flag
static inline s32 IsHit(ENEMY_SHOT* shot)
{
	if (shot->flag & 0x20) {
		return 1;
	}
	return 0;
}

void ENEMY_SHOT::CheckCollision()
{
	s32 hit = 0;

	if (IsHit(this) || (flag & 0x10) || (flagMOG & 2)) {
		hit = 1;
	}
	if (hit == 1) {
		done   = 2;
		hits   = 0;
		size   = enemyShotBlastStart[0];
		scaleX = enemyShotZero[0];
		info->attr |= 0x10;
	}
}
