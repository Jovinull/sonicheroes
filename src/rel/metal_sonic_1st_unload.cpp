#include "game/enemy/e_database.h"

// Metal Sonic's first fight's unload hook (metalSonic1stUnload here): clears
// the word at lbl_11_bss_1054, runs fn_11_72F50, fn_11_70854 and fn_11_748EC,
// releases both its motion tables loaded from the enemy database's Metal Sonic
// files (kind 13), clears the seven words at lbl_11_bss_1038 and deletes that
// database entry.

struct ENEMY_MOTION;

namespace nEnemyMotion
{
void ReleaseAnimationDataFromONEFILE(eEnemyDataBase kind, ENEMY_MOTION* motions);
}

extern "C" s32 lbl_11_bss_1054;
extern "C" s32 lbl_11_bss_1038[7];
extern "C" ENEMY_MOTION metalSonic1stMotionsA[];
extern "C" ENEMY_MOTION metalSonic1stMotionsB[];

extern "C" void fn_11_72F50(void);
extern "C" void fn_11_70854(void);
extern "C" void fn_11_748EC(void);

extern "C" void metalSonic1stUnload(void)
{
	lbl_11_bss_1054 = 0;
	fn_11_72F50();
	fn_11_70854();
	fn_11_748EC();
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)13, metalSonic1stMotionsB);
	nEnemyMotion::ReleaseAnimationDataFromONEFILE((eEnemyDataBase)13, metalSonic1stMotionsA);
	for (int i = 0; i < 7; i++) {
		lbl_11_bss_1038[i] = 0;
	}
	TEnemyDataBase::GetInstance()->Delete((eEnemyDataBase)13);
}
