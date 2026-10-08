#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s04BallColliCreate, the factory rel/s04_ball_colli_register.cpp puts in the
// editor record for TObjS04BallColli, in stage03D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp, and
// the class adds nothing to its three bases.
//
// A zero radius in the placement's parameter block becomes the module's
// default of 10; the shape takes that radius, and bit 0x40 of the collision's
// flags is cleared. The two floats are the module's constants, read as
// externals.

struct S04BallColliParam {
	f32 radius; // 0x00
};

extern "C" char* CL_TObjS04BallColli;
extern "C" CCL_INFO s04BallColliCclInfo;
extern "C" const f32 s04BallColliZero[1];
extern "C" const f32 s04BallColliTen[1];
extern "C" TObject* lbl_8042C110;

class TObjS04BallColli : public TObject, public TObjSetObj, public C_COLLI
{
public:
	TObjS04BallColli(TObject* parent)
	    : TObject(parent)
	{
		S04BallColliParam* param = (S04BallColliParam*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS04BallColli;
		DispTime  = 0xB8;

		if (s04BallColliZero[0] == param->radius) {
			param->radius = s04BallColliTen[0];
		}

		Init(&s04BallColliCclInfo, 1, 4);
		info->a = param->radius;
		CalcRange();
		flag &= ~0x40;
	}
	virtual ~TObjS04BallColli();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s04BallColliCreate(void)
{
	new TObjS04BallColli(lbl_8042C110);
}
