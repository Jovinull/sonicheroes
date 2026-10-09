// TObjTrainAppear, shared by rel/train_appear_create.cpp, which defines TRAIN_APPEAR_CTOR
// as inline so its factory inlines the constructor, and rel/train_appear_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

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

	TObjTrainAppear(TObject* parent);
	virtual ~TObjTrainAppear();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

TRAIN_APPEAR_CTOR TObjTrainAppear::TObjTrainAppear(TObject* parent)
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
