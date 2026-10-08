#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// traincollisionCreate, the factory rel/traincollision_register.cpp puts in the editor record for
// TObjTrainCollision, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// A placed collision volume. The radius of the module's shape comes from the
// first word of the placement's parameter block. The parameter block pointer is
// read together with the position, from the one load of the placement.

struct TrainColliParam {
	f32 radius; // 0x00
};

extern "C" char* CL_TObjTrainCollision;
extern "C" CCL_INFO trainCollisionCclInfo;
extern "C" TObject* lbl_8042C110;

class TObjTrainCollision : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;  // 0xB8
	sAngle ang; // 0xC4

	TObjTrainCollision(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjTrainCollision;
		DispTime  = 0xD0;

		TrainColliParam* param = (TrainColliParam*)ObjParam->setData.setBuffer;
		pos                    = ObjParam->setData.pos;
		ang                    = ObjParam->setData.ang;

		trainCollisionCclInfo.a = param->radius;
		Init(&trainCollisionCclInfo, 1, 4);
	}
	virtual ~TObjTrainCollision();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void traincollisionCreate(void)
{
	new TObjTrainCollision(lbl_8042C110);
}
