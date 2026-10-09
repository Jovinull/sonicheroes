// TObjEnemyStg27Cloud, shared by rel/enemy_stg27_cloud_create.cpp and the units
// that define its out-of-line members. The constructor stays inline in the
// class: the factory inlines it.

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
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

class TObjEnemyStg27Cloud : public TObject
{
public:
	RwV3d pos;       // 0x28
	RwV3d pos2;      // 0x34
	sAngle ang;      // 0x40
	RpClump* clump;  // 0x4C
	RpClump* clump2; // 0x50

	TObjEnemyStg27Cloud(TObject* parent, const sObjEnemyStg27Cloud& param)
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

	void ResetVariable()
	{
		pos    = enemyStg27CloudLow;
		pos2   = enemyStg27CloudHigh;
		ang.x  = 0;
		ang.y  = 0;
		ang.z  = 0;
		clump  = NULL;
		clump2 = NULL;
	}

	void CloneClump()
	{
		if (enemyStg27SkyModels[1] != NULL) {
			clump = fn_80150588(enemyStg27SkyModels[1]);
		}
		if (enemyStg27SkyModels[2] != NULL) {
			clump2 = fn_80150588(enemyStg27SkyModels[2]);
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
	virtual ~TObjEnemyStg27Cloud();
	virtual void Disp();

	static void Create(const sObjEnemyStg27Cloud& param);
};
