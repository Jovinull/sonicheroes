// TObjEnemySky, shared by rel/enemy_sky_create.cpp, which defines ENEMY_SKY_CTOR
// as inline so its factory inlines the constructor, and rel/enemy_sky_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"

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

	TObjEnemySky(TObject* parent);

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

ENEMY_SKY_CTOR TObjEnemySky::TObjEnemySky(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjEnemySky;
	DispTime  = 0x44;
	ResetVariable();
	CloneClump();
	SetPosition();
}
