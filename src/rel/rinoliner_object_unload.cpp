#include "game/effect/eff_bomb.h"
#include "game/enemy/e_database.h"

// The Rhinoliner's unload hook (rinolinerObjectUnload here), in stage05D and
// stage07D: the object it keeps is signalled to die and forgotten, fn_8_B52F4
// runs, its motions loaded from the enemy database's Rhinoliner files (kind 3)
// are released and that database entry deleted.

struct ENEMY_MOTION;

namespace nEnemyMotion
{
void ReleaseAnimationDataFromONEFILE(eEnemyDataBase kind, ENEMY_MOTION* motions);
}

extern "C" TObject* rinolinerObjectInstance;
extern "C" ENEMY_MOTION rinolinerMotions[];

extern "C" void fn_8_B52F4(void);

extern "C" void rinolinerObjectUnload(void)
{
	if (rinolinerObjectInstance != NULL) {
		rinolinerObjectInstance->Signal |= 1;
		rinolinerObjectInstance = NULL;
	}
	fn_8_B52F4();
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)3, rinolinerMotions);
	TEnemyDataBase::GetInstance()->Delete((eEnemyDataBase)3);
}
