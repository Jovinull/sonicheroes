#include "types.h"

// sMachineGunBullet's constructor (the PS2 build's sMachineGunBullet::__ct):
// a new bullet's speed, range and life of 60 frames, at the muzzle.

#include "src/rel/enemy_mgun.inc"

extern "C" const f32 machineGunBulletSpeed[1];
extern "C" const f32 machineGunBulletRange[1];
extern "C" const f32 enemyMGunZero[1];

sMachineGunBullet::sMachineGunBullet()
{
	speed = machineGunBulletSpeed[0];
	dist  = enemyMGunZero[0];
	range = machineGunBulletRange[0];
	life  = 60;
}
