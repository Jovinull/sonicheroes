#include "types.h"

// SetEnemyMGun (the PS2 build's name): makes a machine gun under the parent
// (or the default parent), with the ground check on for a positive height,
// and inits it at the place and angle.

#include "src/rel/enemy_mgun.inc"

extern "C" TObject* lbl_8042C114;

ENEMY_MGUN* SetEnemyMGun(TObject* parent, f32 height, const RwV3d* place, const sAngle* turn)
{
	ENEMY_MGUN* mgun;

	if (parent != NULL) {
		mgun = new ENEMY_MGUN(parent);
	} else {
		mgun = new ENEMY_MGUN(lbl_8042C114);
	}
	if (mgun != NULL) {
		mgun->height = height;
		if (height > enemyMGunZero[0]) {
			mgun->SetFlagToCheckGround();
		} else {
			mgun->ClearFlagToCheckGround();
		}
		mgun->Init(place, turn);
	}
	return mgun;
}
