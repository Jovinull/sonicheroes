#include "game/effect/eff_bomb.h"
#include "game/object.h"

// ENEMY_SHOT's constructor and Init (the PS2 build's names): the out-of-line
// copies of what ENEMY_SHOT::Create and SetEnemyShot inline
// (rel/enemy_shot.inc, which this unit includes with ENEMY_SHOT_INLINE empty).

#define ENEMY_SHOT_INLINE
#include "src/rel/enemy_shot.inc"
