#include "game/enemy/e_database.h"

// The pawn's unload hook (endObjEnemyPawn in the PS2 build; pawnUnload here):
// releases the shield textures and the shot pool, the four motion sets loaded
// from the enemy database's pawn files (kind 6), and that database entry.

struct ENEMY_MOTION;

namespace nEnemyMotion
{
void ReleaseAnimationDataFromONEFILE(eEnemyDataBase kind, ENEMY_MOTION* motions);
}

void ReleaseEnemyShieldTexture();
void EndEnemyShot();

extern "C" ENEMY_MOTION pawnMotions0[];
extern "C" ENEMY_MOTION pawnMotions1[];
extern "C" ENEMY_MOTION pawnMotions2[];
extern "C" ENEMY_MOTION pawnMotions3[];

extern "C" void pawnUnload(void)
{
	ReleaseEnemyShieldTexture();
	EndEnemyShot();
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)6, pawnMotions3);
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)6, pawnMotions2);
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)6, pawnMotions1);
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)6, pawnMotions0);
	TEnemyDataBase::GetInstance()->Delete((eEnemyDataBase)6);
}
