// TObjEnemyStg27Sky, shared by rel/enemy_stg27_sky_create.cpp, which defines ENEMY_STG27_SKY_CTOR
// as inline so its factory inlines the constructor, and rel/enemy_stg27_sky_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"

extern "C" char* CL_TObjEnemyStg27Sky;
extern "C" void* enemyStg27SkyModels[3];
extern "C" const RwV3d enemyStg27SkyOrigin;
extern "C" TObject* lbl_8042C10C;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

class TObjEnemyStg27Sky : public TObject
{
public:
	RwV3d pos;      // 0x28
	sAngle ang;     // 0x34
	RpClump* clump; // 0x40

	TObjEnemyStg27Sky(TObject* parent);

	void ResetVariable()
	{
		pos = enemyStg27SkyOrigin;

		ang.x = 0;
		ang.y = 0;
		ang.z = 0;
	}

	void CloneClump()
	{
		if (enemyStg27SkyModels[0] != NULL) {
			clump = fn_80150588(enemyStg27SkyModels[0]);
		}
	}

	void SetPosition()
	{
		if (clump != NULL) {
			fn_8019EB94(*(void**)((u8*)clump + 4), &pos, 0);
		}
	}

	virtual void Exec();
	virtual ~TObjEnemyStg27Sky();
	virtual void Disp();

	static void Create();
};

ENEMY_STG27_SKY_CTOR TObjEnemyStg27Sky::TObjEnemyStg27Sky(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjEnemyStg27Sky;
	DispTime  = 0x44;
	ResetVariable();
	CloneClump();
	SetPosition();
}
