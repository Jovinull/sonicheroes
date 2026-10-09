// TObjTrainChangeSwitch, shared by rel/train_change_switch_create.cpp, which defines TRAIN_CHANGE_SWITCH_CTOR
// as inline so its factory inlines the constructor, and rel/train_change_switch_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"
#include "game/obj_train_switch.h"

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

struct ModelPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
};

extern "C" char* CL_TObjTrainChangeSwitch;
extern "C" ModelFile trainChangeSwitchModelFiles[3];
extern "C" CCL_INFO trainChangeSwitchCclInfo;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);

// C_COLLI::InitShare, still fn_8003BF04 in main's symbols. Taking the
// collision base by reference adjusts `this` to it without the null test a
// pointer conversion would add, which is what calling the member does.
inline void InitShare(C_COLLI& colli, CCL_INFO* info, int count, u8 kind)
{
	fn_8003BF04(&colli, info, count, kind);
}

class TObjTrainChangeSwitch : public TObject,
                              public TObjSetObj,
                              public C_COLLI,
                              public TrainSwitchManager
{
public:
	RwV3d pos;          // 0xB8
	sAngle ang;         // 0xC4
	u8 unkD0[4];        // 0xD0
	s32 unkD4;          // 0xD4
	ModelPart parts[3]; // 0xD8

	TObjTrainChangeSwitch(TObject* parent);
	virtual void Exec();
	virtual ~TObjTrainChangeSwitch();
	virtual void EditOnChange(SETDATA_PARAM*);
};

TRAIN_CHANGE_SWITCH_CTOR TObjTrainChangeSwitch::TObjTrainChangeSwitch(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjTrainChangeSwitch;
	DispTime  = 0xF0;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	for (int i = 0; i < 3; i++) {
		parts[i].clump = fn_80150588(trainChangeSwitchModelFiles[i].model);
		parts[i].added = 0;
	}
	if (parts[0].added == 0) {
		fn_8015BB08(((void**)(lbl_8042C1D0 + 0x7250))[trainChangeSwitchModelFiles[0].world],
		    parts[0].clump);
		parts[0].added = 1;
	}

	InitShare(*this, &trainChangeSwitchCclInfo, 1, 4);
	unkD4 = 0;
}
