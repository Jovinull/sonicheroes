#include "game/enemy/e_database.h"

// The capture enemy's unload hook (captureObjectUnload here): ends its eight
// texture sets, last first, releases its motions loaded from the enemy
// database's capture files (kind 7) and that database entry.

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

extern "C" TEnemyMatTexture captureObjectGlobalArray[8];
extern "C" ENEMY_MOTION captureMotions[];

extern "C" void captureObjectUnload(void)
{
	for (int i = 7; i >= 0; i--) {
		captureObjectGlobalArray[i].End();
	}
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)7, captureMotions);
	TEnemyDataBase::GetInstance()->Delete((eEnemyDataBase)7);
}
