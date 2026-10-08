#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// noOttottoCollisionCreate, the factory the editor record for
// TObjSetNoOttottoCollision points at. The PS2 build keeps the class in
// o_setNoOttottoCollision.cpp; there the constructor is a function of its own,
// here it is inlined into the factory.
//
// It is the same 76 instructions in twelve of the stage modules that share the
// engine core, at a different address in each, so each module's splits.txt
// names its own range. stage11D has the whole class carved already, in
// rel/no_ottotto_collision_stage11.cpp, where a post-processor inserts the
// register copy this file gets from the compiler.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp,
// because the original builds it before the vtable stores.
//
// The placement's parameter block picks one of the module's two collision
// shapes and gives it its three extents; the shape is then handed to the
// collision base. The index is read again for every store because each store
// is a float the compiler cannot prove does not alias it.

struct NoOttottoParam {
	s32 shape; // 0x00
	f32 a;     // 0x04
	f32 b;     // 0x08
	f32 c;     // 0x0C
};

extern "C" char* CL_TObjSetNoOttottoCollision;
extern "C" CCL_INFO noOttottoCclInfo[2];
extern "C" TObject* lbl_8042C110;

class TObjSetNoOttottoCollision : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;  // 0xB8
	sAngle ang; // 0xC4

	TObjSetNoOttottoCollision(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjSetNoOttottoCollision;
		DispTime  = 0xD0;

		NoOttottoParam* param = (NoOttottoParam*)ObjParam->setData.setBuffer;
		pos                   = ObjParam->setData.pos;
		ang                   = ObjParam->setData.ang;

		noOttottoCclInfo[param->shape].a = param->a;
		noOttottoCclInfo[param->shape].b = param->b;
		noOttottoCclInfo[param->shape].c = param->c;
		Init(&noOttottoCclInfo[param->shape], 1, 4);
	}
	virtual ~TObjSetNoOttottoCollision();
	virtual void Exec();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void noOttottoCollisionCreate(void)
{
	new TObjSetNoOttottoCollision(lbl_8042C110);
}
