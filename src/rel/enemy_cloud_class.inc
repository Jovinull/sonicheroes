// TObjEnemyCloud, shared by rel/enemy_cloud_create.cpp, which defines ENEMY_CLOUD_CTOR
// as inline so its factory inlines the constructor, and rel/enemy_cloud_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"

extern "C" char* CL_TObjEnemyCloud;
extern "C" void* enemySkyModels[3];
extern "C" const f32 enemySkyZero[1];
extern "C" const f32 enemyCloudLowHeight[1];
extern "C" const f32 enemyCloudHighHeight[1];
extern "C" TObject* lbl_8042C10C;
extern "C" RpClump* fn_80150588(void* model);
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

	void ResetVariable()
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

	void CloneClump()
	{
		if (enemySkyModels[1] != NULL) {
			clump = fn_80150588(enemySkyModels[1]);
		}
		if (enemySkyModels[2] != NULL) {
			clump2 = fn_80150588(enemySkyModels[2]);
		}
	}

	void SetPosition()
	{
		if (clump != NULL) {
			fn_8019EB94(*(void**)((u8*)clump + 4), &pos, 0);
		}
		if (clump2 != NULL) {
			fn_8019EB94(*(void**)((u8*)clump2 + 4), &pos2, 0);
		}
	}

	virtual void Exec();
	virtual ~TObjEnemyCloud();
	virtual void Disp();

	static void Create();
};

ENEMY_CLOUD_CTOR TObjEnemyCloud::TObjEnemyCloud(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjEnemyCloud;
	DispTime  = 0x54;
	ResetVariable();
	CloneClump();
	SetPosition();
}
