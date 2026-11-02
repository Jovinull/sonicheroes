// TObjEnemyStg27Cloud, shared by rel/enemy_stg27_cloud_create.cpp and the units
// that define its out-of-line members. Each unit defines ENEMY_STG27_CLOUD_CTOR
// (inline where the factory inlines the constructor, empty in
// rel/enemy_stg27_cloud_ctor.cpp); ENEMY_STG27_CLOUD_HELPER, inline unless a
// unit defines it empty (rel/enemy_stg27_cloud_helpers.cpp), does the same for
// the small members the constructor and destructor inline.

#ifndef ENEMY_STG27_CLOUD_HELPER
#define ENEMY_STG27_CLOUD_HELPER inline
#endif

#include "game/effect/eff_bomb.h"

struct sObjEnemyStg27Cloud {
	f32 lowHeight;  // 0x00
	f32 highHeight; // 0x04
};

extern "C" char* CL_TObjEnemyStg27Cloud;
extern "C" void* enemyStg27SkyModels[3];
extern "C" const RwV3d enemyStg27CloudLow;
extern "C" const RwV3d enemyStg27CloudHigh;
extern "C" TObject* lbl_8042C10C;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

class TObjEnemyStg27Cloud : public TObject
{
public:
	RwV3d pos;       // 0x28
	RwV3d pos2;      // 0x34
	sAngle ang;      // 0x40
	RpClump* clump;  // 0x4C
	RpClump* clump2; // 0x50

	TObjEnemyStg27Cloud(TObject* parent, const sObjEnemyStg27Cloud& param);

	void SetPosition();
	void DestroyClump();
	void CloneClump();
	void ResetVariable();

	// The first virtual declared is the key function, and the unit that defines
	// it emits the vtable. These are all overrides, whose order does not move
	// their slots: rel/enemy_stg27_cloud_exec.cpp (Exec) declares Disp first.
#ifdef ENEMY_STG27_CLOUD_DISP_FIRST
	virtual void Disp();
#endif
	virtual void Exec();
	virtual ~TObjEnemyStg27Cloud();
#ifndef ENEMY_STG27_CLOUD_DISP_FIRST
	virtual void Disp();
#endif

	static void Create(const sObjEnemyStg27Cloud& param);
};

ENEMY_STG27_CLOUD_HELPER void TObjEnemyStg27Cloud::SetPosition()
{
	if (clump != NULL) {
		fn_8019EB94(*(void**)((u8*)clump + 4), &pos, 0);
	}
	if (clump2 != NULL) {
		fn_8019EB94(*(void**)((u8*)clump2 + 4), &pos2, 0);
	}
}

ENEMY_STG27_CLOUD_HELPER void TObjEnemyStg27Cloud::DestroyClump()
{
	if (clump2 != NULL) {
		fn_80150958(clump2);
		clump2 = NULL;
	}
	if (clump != NULL) {
		fn_80150958(clump);
		clump = NULL;
	}
}

ENEMY_STG27_CLOUD_HELPER void TObjEnemyStg27Cloud::CloneClump()
{
	if (enemyStg27SkyModels[1] != NULL) {
		clump = fn_80150588(enemyStg27SkyModels[1]);
	}
	if (enemyStg27SkyModels[2] != NULL) {
		clump2 = fn_80150588(enemyStg27SkyModels[2]);
	}
}

ENEMY_STG27_CLOUD_HELPER void TObjEnemyStg27Cloud::ResetVariable()
{
	pos    = enemyStg27CloudLow;
	pos2   = enemyStg27CloudHigh;
	ang.x  = 0;
	ang.y  = 0;
	ang.z  = 0;
	clump  = NULL;
	clump2 = NULL;
}

ENEMY_STG27_CLOUD_CTOR TObjEnemyStg27Cloud::TObjEnemyStg27Cloud(TObject* parent, const sObjEnemyStg27Cloud& param)
    : TObject(parent)
{
	ClassName = CL_TObjEnemyStg27Cloud;
	DispTime  = 0x54;
	ResetVariable();
	pos.y  = param.lowHeight;
	pos2.y = param.highHeight;
	CloneClump();
	SetPosition();
}
