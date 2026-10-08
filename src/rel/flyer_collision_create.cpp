#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// flyerColObjectCreate, the factory the editor record for TObjFlyerCollision
// points at, in the five stage modules that carry the class: stage05D, 07D,
// 09D, 13D and 26D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. This class lists its bases in another order: the
// collision block second, at 0x28, and the placement base third, at 0xB0,
// which is why the second vtable pointer is at 0xB4 and the PS2 build's
// EditOnChange thunk adjusts by 176. Like the capture collision it hangs off
// the task at lbl_8042C10C.
//
// The constructor is the three steps the PS2 build names: ResetVariable clears
// the fields, SetParameter copies the placement's, and SetColliParameter gives
// the collision base its shape, centred on the placement, with the radius from
// the parameter block.

struct FlyerColParam {
	u8 kind;      // 0x00
	f32 radius;   // 0x04
	RwV3d extent; // 0x08
	s32 unk14;    // 0x14
};

extern "C" char* CL_TObjFlyerCollision;
extern "C" CCL_INFO flyerColCclInfo;
extern "C" const f32 flyerColZero[1];
extern "C" TObject* lbl_8042C10C;

class TObjFlyerCollision : public TObject, public C_COLLI, public TObjSetObj
{
public:
	RwV3d pos;    // 0xB8
	sAngle ang;   // 0xC4
	u8 kind;      // 0xD0
	s32 unkD4;    // 0xD4
	RwV3d extent; // 0xD8

	TObjFlyerCollision(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjFlyerCollision;
		DispTime  = 0xE4;
		ResetVariable();
		SetParameter();
		SetColliParameter();
	}

	void ResetVariable()
	{
		kind     = 0;
		unkD4    = 0;
		extent.x = extent.y = extent.z = flyerColZero[0];
	}

	void SetParameter()
	{
		FlyerColParam* param = (FlyerColParam*)ObjParam->setData.setBuffer;

		kind   = param->kind;
		unkD4  = param->unk14;
		extent = param->extent;
		pos    = ObjParam->setData.pos;
		ang    = ObjParam->setData.ang;
	}

	void SetColliParameter()
	{
		Init(&flyerColCclInfo, 1, 4);
		if (info != NULL) {
			FlyerColParam* param = (FlyerColParam*)ObjParam->setData.setBuffer;

			C_COLLI::pos = pos;
			info->a      = param->radius;
		}
		CalcRange();
	}

	virtual ~TObjFlyerCollision();
	virtual void Exec();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void flyerColObjectCreate(void)
{
	new TObjFlyerCollision(lbl_8042C10C);
}
