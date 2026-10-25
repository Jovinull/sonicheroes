#include "game/effect/eff_bomb.h"
#include "game/enemy/e_database.h"

// The Rhinoliner's load hook (rinolinerObjectLoad here), in stage05D and
// stage07D: loads its files into the enemy database (kind 3) and, once its
// texture dictionary is found and filtered, finds its three models, loads its
// motions, runs fn_8_B5308 and keeps the object fn_80139984 makes (the one the
// unload hook signals to die).

struct ENEMY_MOTION;
struct RwTexDictionary;
enum RwTextureFilterMode {
	rwFILTERLINEARMIPLINEAR = 6,
};

namespace nEnemyMotion
{
void LoadAnimationDataFromONEFILE(eEnemyDataBase kind, ENEMY_MOTION* motions);
}

void objChangeTextureFilterMode(RwTexDictionary* dict, RwTextureFilterMode mode);

extern "C" RpClump* rinolinerModels[3];
extern "C" char rinolinerFiles[];
extern "C" ENEMY_MOTION rinolinerMotions[];
extern "C" TObject* rinolinerObjectInstance;

extern "C" void fn_8_B5308(void);
extern "C" TObject* fn_80139984(s32 a, s32 b, s32 c);

extern "C" void rinolinerObjectLoad(void)
{
	TEnemyDataBase::GetInstance()->Add((eEnemyDataBase)3, rinolinerFiles);
	RwTexDictionary* dict = TEnemyDataBase::GetInstance()->SearchTexDictonary((eEnemyDataBase)3, 8);
	if (dict != NULL) {
		objChangeTextureFilterMode(dict, rwFILTERLINEARMIPLINEAR);
	} else {
		return;
	}
	rinolinerModels[0] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)3, 5);
	rinolinerModels[1] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)3, 3);
	rinolinerModels[2] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)3, 2);
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)3, rinolinerMotions);
	fn_8_B5308();
	rinolinerObjectInstance = fn_80139984(1, 0x4037, 4);
}
