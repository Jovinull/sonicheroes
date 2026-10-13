#include "game/effect/eff_bomb.h"
#include "game/object.h"

// ENEMY_SHIELD's constructor and Init (the PS2 build's names): the out-of-line
// copies of what SetEnemyShield inlines (rel/enemy_shield.inc, which this unit
// includes with ENEMY_SHIELD_INLINE empty).

#define ENEMY_SHIELD_INLINE
#include "src/rel/enemy_shield.inc"
