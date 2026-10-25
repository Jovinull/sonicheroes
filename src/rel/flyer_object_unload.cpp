#include "game/enemy/e_database.h"

// The Flyer's unload hook (flyerObjectUnload here): its motion path data is
// deleted and forgotten, fn_8_A8D1C and fn_8_A9E18 run, both its motion
// tables loaded from the enemy database's Flyer files (kind 5) are released,
// and the database entries of kinds 12 and 5 are deleted.

struct ENEMY_MOTION;

// the motion path data (game/enemy/e_mtnpath.h has the whole class, but its
// own copy of eEnemyDataBase clashes with the database header's)
class TEnemyMtnPathData
{
public:
	~TEnemyMtnPathData();
};

namespace nEnemyMotion
{
void ReleaseAnimationDataFromONEFILE(eEnemyDataBase kind, ENEMY_MOTION* motions);
}

extern "C" TEnemyMtnPathData* flyerObjectPathData;
extern "C" ENEMY_MOTION flyerObjectMotionsA[];
extern "C" ENEMY_MOTION flyerObjectMotionsB[];

extern "C" void fn_8_A8D1C(void);
extern "C" void fn_8_A9E18(void);

extern "C" void flyerObjectUnload(void)
{
	if (flyerObjectPathData != NULL) {
		delete flyerObjectPathData;
		flyerObjectPathData = NULL;
	}
	fn_8_A8D1C();
	fn_8_A9E18();
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)5, flyerObjectMotionsB);
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)5, flyerObjectMotionsA);
	TEnemyDataBase::GetInstance()->Delete((eEnemyDataBase)12);
	TEnemyDataBase::GetInstance()->Delete((eEnemyDataBase)5);
}
