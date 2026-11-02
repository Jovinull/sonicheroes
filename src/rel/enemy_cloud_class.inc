// TObjEnemyCloud, shared by rel/enemy_cloud_create.cpp, which defines ENEMY_CLOUD_CTOR
// as inline so its factory inlines the constructor, and rel/enemy_cloud_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.
// ENEMY_CLOUD_HELPER, inline unless a unit defines it empty
// (rel/enemy_cloud_helpers.cpp), does the same for the small members the
// constructor and destructor inline.

#ifndef ENEMY_CLOUD_HELPER
#define ENEMY_CLOUD_HELPER inline
#endif

#include "game/effect/eff_bomb.h"

extern "C" char* CL_TObjEnemyCloud;
extern "C" void* enemySkyModels[3];
extern "C" const f32 enemySkyZero[1];
extern "C" const f32 enemyCloudLowHeight[1];
extern "C" const f32 enemyCloudHighHeight[1];
extern "C" TObject* lbl_8042C10C;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

class TObjEnemyCloud : public TObject
{
public:
	RwV3d pos;       // 0x28
	RwV3d pos2;      // 0x34
	sAngle ang;      // 0x40
	RpClump* clump;  // 0x4C
	RpClump* clump2; // 0x50

	TObjEnemyCloud(TObject* parent);

	void SetPosition();
	void DestroyClump();
	void CloneClump();
	void ResetVariable();

	// The first virtual declared is the key function, and the unit that defines
	// it emits the vtable. These are all overrides, whose order does not move
	// their slots: rel/enemy_cloud_exec.cpp (Exec) declares Disp first.
#ifdef ENEMY_CLOUD_DISP_FIRST
	virtual void Disp();
#endif
	virtual void Exec();
	virtual ~TObjEnemyCloud();
#ifndef ENEMY_CLOUD_DISP_FIRST
	virtual void Disp();
#endif

	static void Create();
};

ENEMY_CLOUD_HELPER void TObjEnemyCloud::SetPosition()
{
	if (clump != NULL) {
		fn_8019EB94(*(void**)((u8*)clump + 4), &pos, 0);
	}
	if (clump2 != NULL) {
		fn_8019EB94(*(void**)((u8*)clump2 + 4), &pos2, 0);
	}
}

ENEMY_CLOUD_HELPER void TObjEnemyCloud::DestroyClump()
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

ENEMY_CLOUD_HELPER void TObjEnemyCloud::CloneClump()
{
	if (enemySkyModels[1] != NULL) {
		clump = fn_80150588(enemySkyModels[1]);
	}
	if (enemySkyModels[2] != NULL) {
		clump2 = fn_80150588(enemySkyModels[2]);
	}
}

ENEMY_CLOUD_HELPER void TObjEnemyCloud::ResetVariable()
{
	pos.x  = enemySkyZero[0];
	pos.y  = enemyCloudLowHeight[0];
	pos.z  = enemySkyZero[0];
	ang.x  = 0;
	ang.y  = 0;
	ang.z  = 0;
	pos2.x = enemySkyZero[0];
	pos2.y = enemyCloudHighHeight[0];
	pos2.z = enemySkyZero[0];
	clump  = NULL;
	clump2 = NULL;
}

ENEMY_CLOUD_CTOR TObjEnemyCloud::TObjEnemyCloud(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjEnemyCloud;
	DispTime  = 0x54;
	ResetVariable();
	CloneClump();
	SetPosition();
}
