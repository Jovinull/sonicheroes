#include "game/effect/eff_bomb.h"

// TObjEnemySky::Create, in stage28D: the static factory the PS2 build names
// Create__12TObjEnemySkyFv, which the stage's own code calls rather than an
// editor record.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The class has a single base and no placement, so there is
// one vtable store, and it hangs off the task at lbl_8042C10C.
//
// The constructor is the three steps the PS2 build names: ResetVariable clears
// the position and angle, CloneClump clones the module's model when it is
// loaded, and SetPosition moves the clone's frame to the position.

extern "C" char* CL_TObjEnemySky;
extern "C" void* enemySkyModels[3];
extern "C" const f32 enemySkyZero[1];
extern "C" TObject* lbl_8042C10C;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

class TObjEnemySky : public TObject
{
public:
	RwV3d pos;      // 0x28
	sAngle ang;     // 0x34
	RpClump* clump; // 0x40

	TObjEnemySky(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjEnemySky;
		DispTime  = 0x44;
		ResetVariable();
		CloneClump();
		SetPosition();
	}

	void ResetVariable()
	{
		pos.z = pos.y = pos.x = enemySkyZero[0];

		ang.x = 0;
		ang.y = 0;
		ang.z = 0;
	}

	void CloneClump()
	{
		if (enemySkyModels[0] != NULL) {
			clump = fn_80150588(enemySkyModels[0]);
		}
	}

	void SetPosition()
	{
		if (clump != NULL) {
			fn_8019EB94(*(void**)((u8*)clump + 4), &pos, 0);
		}
	}

	virtual ~TObjEnemySky();
	virtual void Exec();
	virtual void Disp();

	static void Create();
};

void TObjEnemySky::Create()
{
	new TObjEnemySky(lbl_8042C10C);
}
