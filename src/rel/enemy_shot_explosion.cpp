#include "game/effect/eff_bomb.h"
#include "game/object.h"

// ENEMY_SHOT::Explosion (the PS2 build's name): the shot's blast grows to its
// full size, then fades out and ends the shot (mode 3); it spins all along.

#include "src/rel/enemy_shot.inc"

extern "C" const f32 enemyShotBlastSize[1];
extern "C" const f32 enemyShotFadeStep[1];
extern "C" const f32 enemyShotFadeEnd[1];

void ENEMY_SHOT::Explosion()
{
	if (size < enemyShotBlastSize[0]) {
		size += enemyShotOne[0];
	} else {
		scaleX -= enemyShotFadeStep[0];
		if (scaleX < enemyShotFadeEnd[0]) {
			done = 3;
			hits = 0;
		}
	}
	angY += 0x100;
}
