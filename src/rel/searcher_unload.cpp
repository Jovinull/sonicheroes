#include "game/enemy/e_database.h"

// The searcher's unload hook (endObjEnemySearcher in the PS2 build;
// searcherObjectUnload here): kills its sound limit, ends both texture sets
// and the shot pool, finalizes the laser, bomber and needle gadgets, releases
// the two motion sets loaded from the enemy database's searcher files (kind 2)
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
};

class TEnemyGadgetLaser
{
public:
	static void Finalize();
};

class TEnemyGadgetBomber
{
public:
	static void Finalize();
};

class TEnemyGadgetNeedle
{
public:
	static void Finalize();
};

typedef struct SELimit {
	u8 unk00[0x4];
	u16 signal; // 0x04, 1: kill
} SELimit;

void EndEnemyShot();

extern "C" SELimit* searcherSELimit;
extern "C" TEnemyMatTexture searcherObjectGlobalA;
extern "C" TEnemyMatTexture searcherObjectGlobalB;
extern "C" ENEMY_MOTION searcherMotions0[];
extern "C" ENEMY_MOTION searcherMotions1[];

extern "C" void searcherObjectUnload(void)
{
	if (searcherSELimit != NULL) {
		searcherSELimit->signal |= 1;
		searcherSELimit = NULL;
	}
	searcherObjectGlobalB.End();
	searcherObjectGlobalA.End();
	EndEnemyShot();
	TEnemyGadgetLaser::Finalize();
	TEnemyGadgetBomber::Finalize();
	TEnemyGadgetNeedle::Finalize();
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)2, searcherMotions1);
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)2, searcherMotions0);
	TEnemyDataBase::GetInstance()->Delete((eEnemyDataBase)2);
}
