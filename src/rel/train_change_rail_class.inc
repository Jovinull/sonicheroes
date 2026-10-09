// TObjTrainChangeRail, shared by rel/train_change_rail_create.cpp, which defines TRAIN_CHANGE_RAIL_CTOR
// as inline so its factory inlines the constructor, and rel/train_change_rail_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"
#include "game/obj_train_switch.h"
#include "MSL_C/string.h"

// One of the object's two rails: fn_6_908D0 releases it and the destructor
// then frees its buffer.
struct TrainChangeRailWork {
	u8 unk0[8];  // 0x00
	RwV3d vec;   // 0x08
	u8* buf;     // 0x14
	u8 unk18[4]; // 0x18
};

class TObjTrainChangeRail;

extern "C" char* CL_TObjTrainChangeRail;
extern "C" void fn_6_908D0(TObjTrainChangeRail* rail, int index, int arg);
extern "C" TObject* lbl_8042C110;

class TObjTrainChangeRail : public TObject, public TObjSetObj, public TrainSwitchManager
{
public:
	RwV3d pos;                   // 0x30
	sAngle ang;                  // 0x3C
	TrainChangeRailWork work[2]; // 0x48
	s32 unk80;                   // 0x80

	TObjTrainChangeRail(TObject* parent);
	virtual void Exec();
	virtual ~TObjTrainChangeRail();
	virtual void EditOnChange(SETDATA_PARAM*);
};

TRAIN_CHANGE_RAIL_CTOR TObjTrainChangeRail::TObjTrainChangeRail(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjTrainChangeRail;
	DispTime  = 0x84;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	memset(&work[0].vec, 0, sizeof(work[0].vec));
	memset(&work[1].vec, 0, sizeof(work[1].vec));
	unk80 = 0;
}
