#include "game/enemy/e_database.h"

// The Flyer's load hook (flyerObjectLoad here): loads its files into the enemy
// database (kind 5) and, when the stage has a name, the stage's own Flyer path
// files (kind 12, named from flyerObjectPathFormat, when the name fits); once
// its texture dictionary is found and filtered, finds its four models, loads
// both its motion tables, runs fn_8_A9E2C and fn_8_A8D30 and makes its motion
// path data from the path files.

struct ENEMY_MOTION;
struct RwTexDictionary;
enum RwTextureFilterMode {
	rwFILTERLINEARMIPLINEAR = 6,
};

namespace nEnemyMotion
{
void LoadAnimationDataFromONEFILE(eEnemyDataBase kind, ENEMY_MOTION* motions);
}

// the motion path data (game/enemy/e_mtnpath.h has the whole class, but its
// own copy of eEnemyDataBase clashes with the database header's)
class TEnemyMtnPathData
{
public:
	TEnemyMtnPathData(eEnemyDataBase kind);

	ENEMY_MOTION* mpEnemyMotionTblPtr;
	RpClump* mpClump;
	s32 mAnimNum;
};

void objChangeTextureFilterMode(RwTexDictionary* dict, RwTextureFilterMode mode);

typedef struct GameState GameState;

extern "C" GameState lbl_8029C310;
extern "C" RpClump* flyerObjectModels[4];
extern "C" char flyerObjectFiles[];
extern "C" char flyerObjectPathFormat[];
extern "C" ENEMY_MOTION flyerObjectMotionsA[];
extern "C" ENEMY_MOTION flyerObjectMotionsB[];
extern "C" TEnemyMtnPathData* flyerObjectPathData;

extern "C" char* fn_800194C4(GameState* state);
extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_8_A9E2C(void);
extern "C" void fn_8_A8D30(void);

extern "C" void flyerObjectLoad(void)
{
	char name[64];

	TEnemyDataBase::GetInstance()->Add((eEnemyDataBase)5, flyerObjectFiles);
	char* stage = fn_800194C4(&lbl_8029C310);
	if (stage != NULL) {
		int length = sprintf(name, flyerObjectPathFormat, stage);
		if (length >= 0 && length < 64) {
			TEnemyDataBase::GetInstance()->Add((eEnemyDataBase)12, name);
		}
	}
	RwTexDictionary* dict
	    = TEnemyDataBase::GetInstance()->SearchTexDictonary((eEnemyDataBase)5, 0xD);
	if (dict != NULL) {
		objChangeTextureFilterMode(dict, rwFILTERLINEARMIPLINEAR);
	} else {
		return;
	}
	flyerObjectModels[0] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)5, 0xC);
	flyerObjectModels[1] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)5, 0xF);
	flyerObjectModels[2] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)5, 0xE);
	flyerObjectModels[3] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)5, 6);
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)5, flyerObjectMotionsA);
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)5, flyerObjectMotionsB);
	fn_8_A9E2C();
	fn_8_A8D30();
	flyerObjectPathData = new TEnemyMtnPathData((eEnemyDataBase)12);
}
