// TObjTrainChangeRail, shared by rel/train_change_rail_create.cpp, which defines TRAIN_CHANGE_RAIL_CTOR
// as inline so its factory inlines the constructor, and rel/train_change_rail_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"
#include "MSL_C/string.h"

class TrainSwitchManager
{
public:
	TrainSwitchManager();
};

extern "C" char* CL_TObjTrainChangeRail;
extern "C" TObject* lbl_8042C110;

class TObjTrainChangeRail : public TObject, public TObjSetObj, public TrainSwitchManager
{
public:
	RwV3d pos;      // 0x30
	sAngle ang;     // 0x3C
	u8 unk48[8];    // 0x48
	RwV3d unk50;    // 0x50
	u8 unk5C[0x10]; // 0x5C
	RwV3d unk6C;    // 0x6C
	u8 unk78[8];    // 0x78
	s32 unk80;      // 0x80

	TObjTrainChangeRail(TObject* parent);
	virtual ~TObjTrainChangeRail();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

TRAIN_CHANGE_RAIL_CTOR TObjTrainChangeRail::TObjTrainChangeRail(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjTrainChangeRail;
	DispTime  = 0x84;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	memset(&unk50, 0, sizeof(unk50));
	memset(&unk6C, 0, sizeof(unk6C));
	unk80 = 0;
}
