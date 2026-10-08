#ifndef GAME_ENEMY_E_DATABASE_H
#define GAME_ENEMY_E_DATABASE_H
#include "types.h"
#include "game/one.h"
enum eEnemyDataBase {
	ENEMY_DB_COMMON     = 0,
	ENEMY_DB_ICON       = 1,
	ENEMY_DB_SEARCHER   = 2,
	ENEMY_DB_RINOLINER  = 3,
	ENEMY_DB_TURTLE     = 4,
	ENEMY_DB_FLYER      = 5,
	ENEMY_DB_PAWN       = 6,
	ENEMY_DB_CAPTURE    = 7,
	ENEMY_DB_WALL       = 8,
	ENEMY_DB_E2000      = 9,
	ENEMY_DB_MAGICIAN   = 10,
	ENEMY_DB_EGGMOBILE  = 11,
	ENEMY_DB_MTNPATH    = 12,
	ENEMY_DB_METALSONIC = 13,
	ENEMY_DB_NUM        = 14
};
enum eEnemyDataBaseKind {
	DB_KIND_UNKNOWN      = 0,
	DB_KIND_CLUMP        = 1,
	DB_KIND_ANIMATION    = 2,
	DB_KIND_UVANIMATION  = 3,
	DB_KIND_SPLINE       = 4,
	DB_KIND_CAMERAMOTION = 5,
	DB_KIND_TEX          = 6
};
struct sEnemyData {
	eEnemyDataBaseKind kind;
	void* addr;
};
struct sEnemyDataBase {
	sEnemyData* addr;
	s32 filenum;
};
class TEnemyDataBase
{
public:
	TEnemyDataBase();
	~TEnemyDataBase();
	s32 GetAnimationNum(eEnemyDataBase);
	s32 GetFileNum(eEnemyDataBase);
	NJS_MOTION* SearchCameraMotion(eEnemyDataBase, u32);
	RpUVAnimAnimation* SearchUVAnim(eEnemyDataBase, u32);
	RtAnimAnimation* SearchHAnim(eEnemyDataBase, u32);
	RwTexDictionary* SearchTexDictonary(eEnemyDataBase, u32);
	RpClump* SearchClump(eEnemyDataBase, u32);
	s32 SetUpFiles(ONEFILE*, eEnemyDataBase);
	s32 Delete(eEnemyDataBase);
	s32 Add(eEnemyDataBase, char*);
	static TEnemyDataBase* GetInstance()
	{
		if (!mpDataBase)
			new TEnemyDataBase;
		return mpDataBase;
	}
	sEnemyDataBase EnemyDataBase[ENEMY_DB_NUM];
	static TEnemyDataBase* mpDataBase;
};

#endif
