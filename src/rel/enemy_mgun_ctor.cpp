#include "types.h"

// ENEMY_MGUN's constructor (the PS2 build's ENEMY_MGUN::__ct): like
// ENEMY_SHOT's, a collision of one sphere (attribute bit 0x40 cleared), the
// bullet speed and size, and the gun stopped with no flash model.
// SetEnemyMGun inlines it; this copy has no caller (force_active).

#include "src/rel/enemy_mgun.inc"

extern "C" char* CL_EnemyMGun;
extern "C" CCL_INFO enemyMGunCclInfo[];
extern "C" const f32 enemyMGunSpeed[1];
extern "C" const f32 enemyMGunSize[1];
extern "C" const f32 enemyMGunOne[1];

ENEMY_MGUN::ENEMY_MGUN(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_EnemyMGun;
	DispTime  = sizeof(ENEMY_MGUN);
	hits      = 0;
	done      = 0;
	C_COLLI::Init(enemyMGunCclInfo, 1, 3);
	flag &= ~0x40;
	speed     = enemyMGunSpeed[0];
	size      = enemyMGunSize[0];
	radObject = enemyMGunOne[0];
	active    = 0;
	unk338    = 0;
	unk32C    = 0;
	clump     = NULL;
}
