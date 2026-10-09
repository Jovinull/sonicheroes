// TObjTrainCollision, shared by rel/train_collision_create.cpp, which defines TRAIN_COLLISION_CTOR
// as inline so its factory inlines the constructor, and rel/train_collision_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

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

	TObjTrainCollision(TObject* parent);
	virtual void Exec();
	virtual ~TObjTrainCollision();
	virtual void EditOnChange(SETDATA_PARAM*);
};

TRAIN_COLLISION_CTOR TObjTrainCollision::TObjTrainCollision(TObject* parent)
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
