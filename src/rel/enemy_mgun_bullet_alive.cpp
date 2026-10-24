#include "types.h"

// sMachineGunBullet::Alive and Move (the PS2 build's names): the out-of-line
// copies of the bodies in rel/enemy_mgun.inc, which the gun inlines. A bullet
// lives while its life lasts and it has not passed its range; it moves by its
// speed, a frame of its life gone.

#define ENEMY_MGUN_BULLET_ALIVE_INLINE
#include "src/rel/enemy_mgun.inc"
