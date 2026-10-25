#include "game/enemy/e_database.h"

// The E-2000's unload hook (e2000ObjectUnload here), in stage13D and stage26D:
// clears its slots (e2000ObjectClearSlots), ends its four texture sets, last
// first, releases its motions loaded from the enemy database's E-2000 files
// (kind 9) and that database entry.

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

extern "C" TEnemyMatTexture e2000ObjectGlobalArray[4];
extern "C" ENEMY_MOTION e2000Motions[];

extern "C" void e2000ObjectClearSlots(void);

extern "C" void e2000ObjectUnload(void)
{
	e2000ObjectClearSlots();
	for (int i = 3; i >= 0; i--) {
		e2000ObjectGlobalArray[i].End();
	}
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)9, e2000Motions);
	TEnemyDataBase::GetInstance()->Delete((eEnemyDataBase)9);
}
