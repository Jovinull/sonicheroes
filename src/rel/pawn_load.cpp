#include "game/enemy/e_database.h"

// The pawn's load hook (initObjEnemyPawn in the PS2 build; pawnLoad here): in
// the stages with the roulette pawns (5, 6 and 0x16) it loads that file and
// turns on the material effects, else the plain pawn file; filters the pawn
// textures, finds the eleven pawn models, and with the effects finds the four
// UV animations and hands them to the effect bodies and shields; then loads the
// four motion sets, the shot pool and the shield textures. The pawn* names
// are ours.

struct ENEMY_MOTION;
struct RwTexDictionary;
enum RwTextureFilterMode {
	rwFILTERLINEARMIPLINEAR = 6,
};
struct UVFXInfo {
	RpUVAnimAnimation* anim; // 0x00
	u8 unk04[0x40];
};

namespace nEnemyMotion
{
void LoadAnimationDataFromONEFILE(eEnemyDataBase kind, ENEMY_MOTION* motions);
}

void objChangeTextureFilterMode(RwTexDictionary* dict, RwTextureFilterMode mode);
void SetClumpCustomFXTexture(RpClump* clump, UVFXInfo* info);
void InitEnemyShot();
void LoadEnemyShieldTexture();
extern "C" int fn_800194A8(u8* game);

extern "C" u8 lbl_8029C310[];
extern "C" s32 pawnFxReady;
extern "C" s32 pawnFxFrame[4];
extern "C" RpUVAnimAnimation* pawnFxAnim[4];
extern "C" UVFXInfo pawnFxData[4];
extern "C" RpClump* pawnModels[11];
extern "C" u32 pawnModelIds[11];
extern "C" RwTexDictionary* pawnTexDict;
extern "C" char pawnFxFiles[];
extern "C" char pawnFiles[];
extern "C" ENEMY_MOTION pawnMotions0[];
extern "C" ENEMY_MOTION pawnMotions1[];
extern "C" ENEMY_MOTION pawnMotions2[];
extern "C" ENEMY_MOTION pawnMotions3[];

extern "C" void pawnLoad(void)
{
	int stage;
	int i;

	pawnFxReady = 0;
	stage       = fn_800194A8(lbl_8029C310);
	if (stage == 0x16 || stage == 5 || stage == 6) {
		pawnFxReady = 1;
	}
	if (pawnFxReady) {
		TEnemyDataBase::GetInstance()->Add((eEnemyDataBase)6, pawnFxFiles);
	} else {
		TEnemyDataBase::GetInstance()->Add((eEnemyDataBase)6, pawnFiles);
	}
	pawnTexDict = TEnemyDataBase::GetInstance()->SearchTexDictonary((eEnemyDataBase)6, 0xA);
	if (pawnTexDict != NULL) {
		objChangeTextureFilterMode(pawnTexDict, rwFILTERLINEARMIPLINEAR);
	} else {
		return;
	}
	for (i = 0; i < 11; i++) {
		pawnModels[i]
		    = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)6, pawnModelIds[i]);
	}
	for (i = 0; i < 4; i++) {
		pawnFxAnim[i]  = NULL;
		pawnFxFrame[i] = 0;
	}
	if (pawnFxReady) {
		pawnFxAnim[0] = TEnemyDataBase::GetInstance()->SearchUVAnim((eEnemyDataBase)6, 0x21);
		pawnFxAnim[1] = TEnemyDataBase::GetInstance()->SearchUVAnim((eEnemyDataBase)6, 0x23);
		pawnFxAnim[2] = TEnemyDataBase::GetInstance()->SearchUVAnim((eEnemyDataBase)6, 0x24);
		pawnFxAnim[3] = TEnemyDataBase::GetInstance()->SearchUVAnim((eEnemyDataBase)6, 0x24);
		if (pawnModels[7] != NULL && pawnFxAnim[0] != NULL) {
			pawnFxData[0].anim = pawnFxAnim[0];
			SetClumpCustomFXTexture(pawnModels[7], &pawnFxData[0]);
		}
		if (pawnModels[8] != NULL && pawnFxAnim[1] != NULL) {
			pawnFxData[1].anim = pawnFxAnim[1];
			SetClumpCustomFXTexture(pawnModels[8], &pawnFxData[1]);
		}
		if (pawnModels[9] != NULL && pawnFxAnim[2] != NULL) {
			pawnFxData[2].anim = pawnFxAnim[2];
			SetClumpCustomFXTexture(pawnModels[9], &pawnFxData[2]);
		}
		if (pawnModels[10] != NULL && pawnFxAnim[3] != NULL) {
			pawnFxData[3].anim = pawnFxAnim[3];
			SetClumpCustomFXTexture(pawnModels[10], &pawnFxData[3]);
		}
		pawnFxFrame[0] = 0;
		pawnFxFrame[1] = 0;
		pawnFxFrame[2] = 0;
		pawnFxFrame[3] = 0;
	}
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)6, pawnMotions0);
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)6, pawnMotions1);
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)6, pawnMotions2);
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)6, pawnMotions3);
	InitEnemyShot();
	LoadEnemyShieldTexture();
}
