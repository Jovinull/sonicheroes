#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// trainappearCreate, the factory rel/trainappear_register.cpp puts in the editor record for
// TObjTrainAppear, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// A placed collision volume. The radius of the module's shape comes from the
// first word of the placement's parameter block. The parameter block pointer is
// read first, before the class name, which is where the original loads it.

struct TrainColliParam {
	f32 radius; // 0x00
};

extern "C" char* CL_TObjTrainAppear;
extern "C" CCL_INFO trainAppearCclInfo;
extern "C" TObject* lbl_8042C110;

class TObjTrainAppear : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;  // 0xB8
	sAngle ang; // 0xC4

	TObjTrainAppear(TObject* parent)
	    : TObject(parent)
	{
		TrainColliParam* param = (TrainColliParam*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjTrainAppear;
		DispTime  = 0xD0;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		trainAppearCclInfo.a = param->radius;
		Init(&trainAppearCclInfo, 1, 4);
	}
	virtual ~TObjTrainAppear();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void trainappearCreate(void)
{
	new TObjTrainAppear(lbl_8042C110);
}
