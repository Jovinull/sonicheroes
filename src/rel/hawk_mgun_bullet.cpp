#include "types.h"

// bMachineGunBullet's Init, constructor, Alive and Move (the PS2 build's
// names), and its destructor, which the original emitted after them. Init puts
// the bullet at rest at the origin and sets up its collision the first time;
// the constructor inlines it. A bullet is alive until its life runs out; Move
// adds the velocity, moves the collision along (its previous position kept,
// no turn) and enters it, and counts the life down.

#define HAWK_MGUN_BULLET_INIT_INLINE
#include "src/rel/hawk_mgun.inc"

// {0, 0, 0}, the collision's turn
extern "C" const sAngle hawkMGunBulletTurn;

bMachineGunBullet::bMachineGunBullet()
{
	Init();
}

bool bMachineGunBullet::Alive()
{
	return life >= 0;
}

void bMachineGunBullet::Move()
{
	sAngle turn = hawkMGunBulletTurn;

	pos.x += vel.x;
	pos.y += vel.y;
	pos.z += vel.z;
	if (info != NULL) {
		pre_pos      = C_COLLI::pos;
		C_COLLI::pos = pos;
		ang          = turn;
		Entry();
	}
	life--;
}

bMachineGunBullet::~bMachineGunBullet() { }
