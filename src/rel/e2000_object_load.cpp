#include "game/enemy/e_database.h"

// The E-2000's load hook (e2000ObjectLoad here), in stage13D and stage26D:
// loads its files into the enemy database (kind 9) and, once its texture
// dictionary is found and filtered, finds its three models and two UV
// animations, hands each animation to its model through an FX record (the
// second model the first one, the third the second), clears the animations'
// frames, has the two animated models ignore lights, loads its motions, sets up
// its four texture sets on the first model and loads its parts
// (e2000ObjectLoadParts).

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

extern "C" TEnemyMatTexture e2000ObjectGlobalArray[4];
extern "C" RpClump* e2000Models[3];
extern "C" RpUVAnimAnimation* e2000FxAnim[2];
extern "C" UVFXInfo e2000FxData[2];
extern "C" s32 e2000FxFrame[2];
extern "C" char e2000Files[];
extern "C" sEnTexture e2000TexturesA[];
extern "C" sEnTexture e2000TexturesB[];
extern "C" sEnTexture e2000TexturesC[];
extern "C" sEnTexture e2000TexturesD[];
extern "C" ENEMY_MOTION e2000Motions[];

extern "C" void e2000ObjectLoadParts(void);

extern "C" void e2000ObjectLoad(void)
{
	TEnemyDataBase::GetInstance()->Add((eEnemyDataBase)9, e2000Files);
	RwTexDictionary* dict = TEnemyDataBase::GetInstance()->SearchTexDictonary((eEnemyDataBase)9, 2);
	if (dict != NULL) {
		objChangeTextureFilterMode(dict, rwFILTERLINEARMIPLINEAR);
	} else {
		return;
	}
	e2000Models[0] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)9, 4);
	e2000Models[1] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)9, 0x19);
	e2000Models[2] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)9, 0x1B);
	e2000FxAnim[0] = TEnemyDataBase::GetInstance()->SearchUVAnim((eEnemyDataBase)9, 0x1A);
	e2000FxAnim[1] = TEnemyDataBase::GetInstance()->SearchUVAnim((eEnemyDataBase)9, 0x1C);
	if (e2000Models[1] != NULL && e2000FxAnim[0] != NULL) {
		e2000FxData[0].anim = e2000FxAnim[0];
		SetClumpCustomFXTexture(e2000Models[1], &e2000FxData[0]);
	}
	if (e2000Models[2] != NULL && e2000FxAnim[1] != NULL) {
		e2000FxData[1].anim = e2000FxAnim[1];
		SetClumpCustomFXTexture(e2000Models[2], &e2000FxData[1]);
	}
	e2000FxFrame[0] = 0;
	e2000FxFrame[1] = 0;
	objRpClumpForAllGeometrysToIgnoreLights(e2000Models[1]);
	objRpClumpForAllGeometrysToIgnoreLights(e2000Models[2]);
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)9, e2000Motions);
	e2000ObjectGlobalArray[0].Init(dict, e2000Models[0], e2000TexturesA, 2);
	e2000ObjectGlobalArray[1].Init(dict, e2000Models[0], e2000TexturesB, 2);
	e2000ObjectGlobalArray[2].Init(dict, e2000Models[0], e2000TexturesC, 2);
	e2000ObjectGlobalArray[3].Init(dict, e2000Models[0], e2000TexturesD, 2);
	e2000ObjectLoadParts();
}
