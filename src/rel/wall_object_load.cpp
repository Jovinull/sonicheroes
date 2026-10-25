#include "game/enemy/e_database.h"

// The wall enemy's load hook (wallObjectLoad here): loads its files into the
// enemy database (kind 8) and, once its texture dictionary is found and
// filtered, finds its five models and its UV animation, hands the animation to
// the fifth model through its FX record, clears the animation's frame, loads
// its motions and, when the fourth model is there, has it ignore lights and
// sets up its texture set on it.

struct ENEMY_MOTION;
struct RwTexDictionary;
struct sEnTexture;
enum RwTextureFilterMode {
	rwFILTERLINEARMIPLINEAR = 6,
};

struct UVFXInfo {
	RpUVAnimAnimation* anim; // 0x00
	u8 unk04[0x40];
}; // 0x44

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
void SetClumpCustomFXTexture(RpClump* clump, UVFXInfo* info);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);

extern "C" TEnemyMatTexture wallObjectGlobalA;
extern "C" RpClump* wallObjectModels[5];
extern "C" RpUVAnimAnimation* wallObjectFxAnim;
extern "C" UVFXInfo wallObjectFxData;
extern "C" s32 wallObjectFxFrame;
extern "C" char wallObjectFiles[];
extern "C" sEnTexture wallObjectTextures[];
extern "C" ENEMY_MOTION wallObjectMotions[];

extern "C" void wallObjectLoad(void)
{
	TEnemyDataBase::GetInstance()->Add((eEnemyDataBase)8, wallObjectFiles);
	RwTexDictionary* dict = TEnemyDataBase::GetInstance()->SearchTexDictonary((eEnemyDataBase)8, 9);
	if (dict != NULL) {
		objChangeTextureFilterMode(dict, rwFILTERLINEARMIPLINEAR);
	} else {
		return;
	}
	wallObjectModels[0] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)8, 8);
	wallObjectModels[1] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)8, 0x14);
	wallObjectModels[2] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)8, 7);
	wallObjectModels[3] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)8, 4);
	wallObjectModels[4] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)8, 5);
	wallObjectFxAnim    = TEnemyDataBase::GetInstance()->SearchUVAnim((eEnemyDataBase)8, 6);
	if (wallObjectModels[4] != NULL && wallObjectFxAnim != NULL) {
		wallObjectFxData.anim = wallObjectFxAnim;
		SetClumpCustomFXTexture(wallObjectModels[4], &wallObjectFxData);
	}
	wallObjectFxFrame = 0;
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)8, wallObjectMotions);
	if (wallObjectModels[3] != NULL) {
		objRpClumpForAllGeometrysToIgnoreLights(wallObjectModels[3]);
		wallObjectGlobalA.Init(dict, wallObjectModels[3], wallObjectTextures, 3);
	}
}
