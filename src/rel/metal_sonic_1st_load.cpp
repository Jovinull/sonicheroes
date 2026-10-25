#include "game/enemy/e_database.h"

// Metal Sonic's first fight's load hook (metalSonic1stLoad here): loads its
// files into the enemy database (kind 13) and, once its texture dictionary is
// found and filtered, sets up its material animation, finds its models (the
// body's atomics going through the fight's callback, two of the others set to
// ignore lights when found), loads both its motion tables, runs fn_11_74918,
// fn_11_70880 and fn_11_72F88 and clears the word at lbl_11_bss_1054.

struct ENEMY_MOTION;
struct RwTexDictionary;
enum RwTextureFilterMode {
	rwFILTERLINEARMIPLINEAR = 6,
};

namespace nEnemyMotion
{
void LoadAnimationDataFromONEFILE(eEnemyDataBase kind, ENEMY_MOTION* motions);
}

// the fight's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct MatAnim {
	u8 unk00[0x18];
} MatAnim;

void objChangeTextureFilterMode(RwTexDictionary* dict, RwTextureFilterMode mode);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);

extern "C" RpClump* metalSonic1stModels[7];
extern "C" MatAnim metalSonic1stMatAnim;
extern "C" char metalSonic1stFiles[];
extern "C" ENEMY_MOTION metalSonic1stMotionsA[];
extern "C" ENEMY_MOTION metalSonic1stMotionsB[];
extern "C" s32 lbl_11_bss_1054;

extern "C" void fn_8015C728(MatAnim* anim);
extern "C" void fn_8015C6F8(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(MatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(MatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(RpClump* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_11_6C180(void* atomic);
extern "C" void fn_11_74918(void);
extern "C" void fn_11_70880(void);
extern "C" void fn_11_72F88(void);

extern "C" void metalSonic1stLoad(void)
{
	TEnemyDataBase::GetInstance()->Add((eEnemyDataBase)13, metalSonic1stFiles);
	RwTexDictionary* dict
	    = TEnemyDataBase::GetInstance()->SearchTexDictonary((eEnemyDataBase)13, 0x3A);
	if (dict != NULL) {
		objChangeTextureFilterMode(dict, rwFILTERLINEARMIPLINEAR);
	} else {
		return;
	}
	fn_8015C728(&metalSonic1stMatAnim);
	fn_8015C6F8(&metalSonic1stMatAnim, 3, 6);
	fn_8015C704(&metalSonic1stMatAnim, 1, 0);
	fn_8015C710(&metalSonic1stMatAnim, 1, 3, 10);
	fn_8015C720(&metalSonic1stMatAnim, 3);
	RpClump* body = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)13, 0x15);
	fn_8014FFBC(body, fn_11_6C180, NULL);
	metalSonic1stModels[0] = body;
	metalSonic1stModels[2] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)13, 6);
	metalSonic1stModels[3] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)13, 8);
	metalSonic1stModels[4] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)13, 5);
	if (metalSonic1stModels[4] != NULL) {
		objRpClumpForAllGeometrysToIgnoreLights(metalSonic1stModels[4]);
	}
	metalSonic1stModels[5] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)13, 4);
	if (metalSonic1stModels[5] != NULL) {
		objRpClumpForAllGeometrysToIgnoreLights(metalSonic1stModels[5]);
	}
	metalSonic1stModels[6] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)13, 0x32);
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)13, metalSonic1stMotionsA);
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)13, metalSonic1stMotionsB);
	fn_11_74918();
	fn_11_70880();
	fn_11_72F88();
	lbl_11_bss_1054 = 0;
}
