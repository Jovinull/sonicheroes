#include "game/effect/eff_bomb.h"

// TObjEnemyCloud::Create, in stage28D: the static factory the PS2 build names
// Create__14TObjEnemyCloudFv, called by the stage's own code. It is the same
// shape as rel/enemy_sky_create.cpp, which shares this class's module data.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. Single base, no placement, and the task at lbl_8042C10C.
//
// ResetVariable places the two cloud layers at heights -500 and -1000, the
// module's constants, and clears the angle and both clumps; CloneClump clones
// the module's second and third models when they are loaded, and SetPosition
// moves each clone's frame to its layer.

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

	TObjEnemyCloud(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjEnemyCloud;
		DispTime  = 0x54;
		ResetVariable();
		CloneClump();
		SetPosition();
	}

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

	virtual ~TObjEnemyCloud();
	virtual void Exec();
	virtual void Disp();

	static void Create();
};

void TObjEnemyCloud::Create()
{
	new TObjEnemyCloud(lbl_8042C10C);
}
