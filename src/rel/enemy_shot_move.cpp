#include "game/effect/eff_bomb.h"
#include "game/object.h"

// ENEMY_SHOT's Disp and Move (the PS2 build's names): the shot draws nothing
// in Disp (TDisp does it), and moves by its velocity.

#include "src/rel/enemy_shot.inc"

void ENEMY_SHOT::Disp() { }

void ENEMY_SHOT::Move()
{
	pos.x += vel.x;
	pos.y += vel.y;
	pos.z += vel.z;
}
