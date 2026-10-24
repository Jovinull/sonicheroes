#include "types.h"

// bMachineGunBullet's Init, constructor, Alive and Move (the PS2 build's
// names), and its destructor, which the original emitted after them. Init puts
// the bullet at rest at the origin and sets up its collision the first time;
// the constructor inlines it. Alive and Move are in
// rel/hawk_mgun_bullet_move.inc.

#define HAWK_MGUN_BULLET_INIT_INLINE
#define HAWK_MGUN_BULLET_MOVE_INLINE
#define HAWK_MGUN_ALIVE_TYPE bool
#include "src/rel/hawk_mgun.inc"

bMachineGunBullet::bMachineGunBullet()
{
	Init();
}

#include "src/rel/hawk_mgun_bullet_move.inc"

bMachineGunBullet::~bMachineGunBullet() { }
