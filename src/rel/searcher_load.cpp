#include "game/enemy/e_database.h"

// The searcher's load hook (initObjEnemySearcher in the PS2 build;
// searcherObjectLoad here): loads the searcher files (enemy database kind 2),
// filters their textures, finds the thirteen searcher models (the parts
// ignore the lights), loads the two motion sets, initializes the needle,
// bomber and laser gadgets and the shot pool, prepares both texture sets and
// creates the sound limit for the searcher sound 0x4000 (four at a time).
// The searcher* names are ours.

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
};

class TEnemyGadgetLaser
{
public:
	static void Initialize();
};

class TEnemyGadgetBomber
{
public:
	static void Initialize();
};

class TEnemyGadgetNeedle
{
public:
	static void Initialize();
};

typedef struct SELimit SELimit;

void objChangeTextureFilterMode(RwTexDictionary* dict, RwTextureFilterMode mode);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);
void InitEnemyShot();

// TEnemySELimit::Create (main)
extern "C" SELimit* fn_80139984(s32 type, u32 sound, s32 count);

extern "C" char searcherFiles[];
extern "C" RwTexDictionary* searcherTexDict;
extern "C" RpClump* searcherModels[13];
extern "C" u32 searcherModelIds[13];
extern "C" ENEMY_MOTION searcherMotions0[];
extern "C" ENEMY_MOTION searcherMotions1[];
extern "C" TEnemyMatTexture searcherObjectGlobalA;
extern "C" TEnemyMatTexture searcherObjectGlobalB;
extern "C" sEnTexture searcherTexturesA[];
extern "C" sEnTexture searcherTexturesB[];
extern "C" SELimit* searcherSELimit;

extern "C" void searcherObjectLoad(void)
{
	int i;

	TEnemyDataBase::GetInstance()->Add((eEnemyDataBase)2, searcherFiles);
	searcherTexDict = TEnemyDataBase::GetInstance()->SearchTexDictonary((eEnemyDataBase)2, 0x1C);
	if (searcherTexDict != NULL) {
		objChangeTextureFilterMode(searcherTexDict, rwFILTERLINEARMIPLINEAR);
	} else {
		return;
	}
	for (i = 0; i < 13; i++) {
		searcherModels[i] = NULL;
	}
	for (i = 0; i < 13; i++) {
		searcherModels[i]
		    = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)2, searcherModelIds[i]);
	}
	if (searcherModels[12] != NULL) {
		objRpClumpForAllGeometrysToIgnoreLights(searcherModels[12]);
	}
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)2, searcherMotions0);
	nEnemyMotion::LoadAnimationDataFromONEFILE((eEnemyDataBase)2, searcherMotions1);
	TEnemyGadgetNeedle::Initialize();
	TEnemyGadgetBomber::Initialize();
	TEnemyGadgetLaser::Initialize();
	InitEnemyShot();
	searcherObjectGlobalA.Init(searcherTexDict, searcherModels[0], searcherTexturesA, 7);
	searcherObjectGlobalB.Init(searcherTexDict, searcherModels[0], searcherTexturesB, 7);
	searcherSELimit = fn_80139984(1, 0x4000, 4);
}
