#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s04FloatingPathCreate, the factory rel/s04_floating_path_register.cpp puts
// in the editor record for TObjS04FloatWay, in stage03D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// Unless the collision base already has a shape, it takes the module's. The
// shape is then sized from the placement's parameter block: half its three
// extents, and centred half the last two along y and z with x at 0, the
// module's constants 0.5 and 0. The halfword at 0xB8 comes from the module's
// data.

struct S04FloatWayParam {
	u8 pad0[8];
	RwV3d extent; // 0x08
};

extern "C" char* CL_TObjS04FloatWay;
extern "C" CCL_INFO s04FloatWayCclInfo;
extern "C" const f32 s04FloatWayHalf[1];
extern "C" const f32 s04FloatWayZero[1];
extern "C" s16 s04FloatWayUnkB8;
extern "C" TObject* lbl_8042C110;

class TObjS04FloatWay : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s16 unkB8;   // 0xB8
	u8 padBA[2]; // 0xBA

	TObjS04FloatWay(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS04FloatWay;
		DispTime  = 0xBC;

		S04FloatWayParam* param = (S04FloatWayParam*)ObjParam->setData.setBuffer;

		if (info == NULL) {
			Init(&s04FloatWayCclInfo, 1, 4);
		}

		CCL_INFO* shape = info;
		f32 half        = s04FloatWayHalf[0];
		shape->a        = half * param->extent.x;
		shape->b        = half * param->extent.y;
		shape->c        = half * param->extent.z;
		shape->center.x = s04FloatWayZero[0];
		shape->center.y = half * param->extent.y;
		shape->center.z = half * param->extent.z;
		CalcRange();

		unkB8 = s04FloatWayUnkB8;
	}
	virtual ~TObjS04FloatWay();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s04FloatingPathCreate(void)
{
	new TObjS04FloatWay(lbl_8042C110);
}
