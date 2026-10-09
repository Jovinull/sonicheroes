#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s03TrainCreate, the factory the editor record for TObjS03Train points at, in
// stage03D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// In the editor an all-zero box in the placement's parameter block becomes
// 100 by 100 by 20, the module's constants. The constructor clears its state,
// and unless the collision base already has a shape it takes the module's,
// sized to the box; that step reads the parameter block again for itself.

struct S03TrainParam {
	RwV3d extent; // 0x00
};

extern "C" char* CL_TObjS03Train;
extern "C" CCL_INFO s03TrainCclInfo;
extern "C" const f32 s03TrainZero[1];
extern "C" const f32 s03TrainWide[1];
extern "C" const f32 s03TrainHigh[1];
extern "C" TObject* lbl_8042C110;

class TObjS03Train : public TObject, public TObjSetObj, public C_COLLI
{
public:
	u8 unkB8; // 0xB8
	u8 unkB9; // 0xB9
	u8 padBA[2];
	s32 unkBC; // 0xBC

	TObjS03Train(TObject* parent)
	    : TObject(parent)
	{
		S03TrainParam* param = (S03TrainParam*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS03Train;
		DispTime  = 0xC0;

		if (OnEdit()) {
			if (s03TrainZero[0] == param->extent.x && s03TrainZero[0] == param->extent.y
			    && s03TrainZero[0] == param->extent.z) {
				param->extent.x = s03TrainWide[0];
				param->extent.y = s03TrainWide[0];
				param->extent.z = s03TrainHigh[0];
			}
		}

		unkB8 = 0;
		unkBC = 0;
		unkB9 = 0;
		SetColliParameter();
	}

	void SetColliParameter()
	{
		S03TrainParam* param = (S03TrainParam*)ObjParam->setData.setBuffer;

		if (info == NULL) {
			Init(&s03TrainCclInfo, 1, 4);
			CCL_INFO* shape = info;
			shape->a        = param->extent.x;
			shape->b        = param->extent.y;
			shape->c        = param->extent.z;
			CalcRange();
		}
	}

	virtual ~TObjS03Train();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s03TrainCreate(void)
{
	new TObjS03Train(lbl_8042C110);
}
