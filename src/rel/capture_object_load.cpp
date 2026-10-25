#include "game/enemy/e_database.h"

// The capture enemy's load hook (captureObjectLoad here), in the six stage
// modules that have it besides stage11D: loads its files into the enemy
// database (kind 7) and, once its texture dictionary is found and filtered,
// finds its six models, has three of them modulate their material colour and
// the last ignore lights, loads its motions and sets up its eight texture sets,
// two for each of the first four models.

struct ENEMY_MOTION;
struct RwTexDictionary;
struct sEnTexture;
enum RwTextureFilterMode {
	rwFILTERLINEARMIPLINEAR = 6,
};

namespace nEnemyMotion
{
void LoadAnimationDataFromONEFILE(eEnemyDataBase kind, ENEMY_MOTION* motions);
}

class TEnemyMatTexture
{
public:
	void Init(RwTexDictionary* dict, RpClump* clump, sEnTexture* textures, int count);

	u8 unk00[0x14];
}; // 0x14

void objChangeTextureFilterMode(RwTexDictionary* dict, RwTextureFilterMode mode);
void objRpClumpForAllGeometrysToModulateMaterialColor(RpClump* clump);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);

extern "C" TEnemyMatTexture captureObjectGlobalArray[8];
extern "C" RpClump* captureModels[6];
extern "C" char captureFiles[];
extern "C" sEnTexture captureTexturesA[];
extern "C" sEnTexture captureTexturesB[];
extern "C" ENEMY_MOTION captureMotions[];

extern "C" void captureObjectLoad(void)
{
	TEnemyDataBase::GetInstance()->Add((eEnemyDataBase)7, captureFiles);
	RwTexDictionary* dict = TEnemyDataBase::GetInstance()->SearchTexDictonary((eEnemyDataBase)7, 4);
	if (dict != NULL) {
		objChangeTextureFilterMode(dict, rwFILTERLINEARMIPLINEAR);
	} else {
		return;
	}
	captureModels[0] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)7, 3);
	captureModels[1] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)7, 9);
	captureModels[2] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)7, 10);
	captureModels[3] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)7, 11);
	captureModels[4] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)7, 12);
	captureModels[5] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)7, 7);
	objRpClumpForAllGeometrysToModulateMaterialColor(captureModels[1]);
	objRpClumpForAllGeometrysToModulateMaterialColor(captureModels[2]);
	objRpClumpForAllGeometrysToModulateMaterialColor(captureModels[3]);
	if (captureModels[5] != NULL) {
		objRpClumpForAllGeometrysToIgnoreLights(captureModels[5]);
	}
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)7, captureMotions);
	captureObjectGlobalArray[0].Init(dict, captureModels[0], captureTexturesA, 2);
	captureObjectGlobalArray[1].Init(dict, captureModels[0], captureTexturesB, 2);
	captureObjectGlobalArray[2].Init(dict, captureModels[1], captureTexturesA, 2);
	captureObjectGlobalArray[3].Init(dict, captureModels[1], captureTexturesB, 2);
	captureObjectGlobalArray[4].Init(dict, captureModels[2], captureTexturesA, 2);
	captureObjectGlobalArray[5].Init(dict, captureModels[2], captureTexturesB, 2);
	captureObjectGlobalArray[6].Init(dict, captureModels[3], captureTexturesA, 2);
	captureObjectGlobalArray[7].Init(dict, captureModels[3], captureTexturesB, 2);
}
