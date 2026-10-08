#include "game/effect/eff_bomb.h"

// TObjEnemyStg27Sky::Create, the static factory the PS2 build names
// Create__17TObjEnemyStg27SkyFv, in stage26D and stage27D, where the code is
// the same at different addresses. rel/enemy_sky_create.cpp is stage28D's
// TObjEnemySky, the same shape.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. Single base, no placement, and the task at lbl_8042C10C.
//
// ResetVariable copies the position from a vector constant of the module and
// clears the angle; CloneClump and SetPosition are TObjEnemySky's.

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

	TObjEnemyStg27Sky(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjEnemyStg27Sky;
		DispTime  = 0x44;
		ResetVariable();
		CloneClump();
		SetPosition();
	}

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

	virtual ~TObjEnemyStg27Sky();
	virtual void Exec();
	virtual void Disp();

	static void Create();
};

void TObjEnemyStg27Sky::Create()
{
	new TObjEnemyStg27Sky(lbl_8042C10C);
}
