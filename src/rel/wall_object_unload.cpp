#include "game/enemy/e_database.h"

// The wall enemy's unload hook (wallObjectUnload here): ends its texture set,
// releases its motions loaded from the enemy database's wall files (kind 8)
// and that database entry.

struct ENEMY_MOTION;

namespace nEnemyMotion
{
void ReleaseAnimationDataFromONEFILE(eEnemyDataBase kind, ENEMY_MOTION* motions);
}

class TEnemyMatTexture
{
public:
	void End();

	u8 unk00[0x14];
}; // 0x14

extern "C" TEnemyMatTexture wallObjectGlobalA;
extern "C" ENEMY_MOTION wallObjectMotions[];

extern "C" void wallObjectUnload(void)
{
	wallObjectGlobalA.End();
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)8, wallObjectMotions);
	TEnemyDataBase::GetInstance()->Delete((eEnemyDataBase)8);
}
