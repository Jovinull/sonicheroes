#include "game/enemy/e_database.h"

// TEnemyGadgetBomber::Finalize and Initialize (the PS2 build's names), static:
// the bomber's two models are found in the searcher files (enemy database
// kind 2) and its motions loaded; finalizing releases the motions.

struct ENEMY_MOTION;

namespace nEnemyMotion
{
void LoadAnimationDataFromONEFILE(eEnemyDataBase kind, ENEMY_MOTION* motions);
void ReleaseAnimationDataFromONEFILE(eEnemyDataBase kind, ENEMY_MOTION* motions);
} // namespace nEnemyMotion

class TEnemyGadgetBomber
{
public:
	static void Finalize();
	static void Initialize();

	static RpClump* pClumpStatic[2];
};

extern "C" u32 bomberModelIds[2];
extern "C" ENEMY_MOTION bomberMotions[];

void TEnemyGadgetBomber::Finalize()
{
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)2, bomberMotions);
}

void TEnemyGadgetBomber::Initialize()
{
	int i;

	for (i = 0; i < 2; i++) {
		pClumpStatic[i]
		    = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)2, bomberModelIds[i]);
	}
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)2, bomberMotions);
}
