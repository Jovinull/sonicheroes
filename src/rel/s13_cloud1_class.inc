// TObjS13Cloud1, shared by rel/s13_cloud1_create.cpp, which defines S13_CLOUD1_CTOR
// as inline so its factory inlines the constructor, and rel/s13_cloud1_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct S13Cloud1Param {
	s16 unk0; // 0x00
	s16 unk2; // 0x02
	s16 unk4; // 0x04
};

// One of the cloud's particles. Each unlinks itself from the cloud's list when
// it is deleted.
class TObjS13CloudPtcl : public TObject
{
public:
	virtual ~TObjS13CloudPtcl();
};

class TObjS13Cloud
{
public:
	TObjS13CloudPtcl* topPtcl; // 0x00

	TObjS13Cloud() { topPtcl = NULL; }
};

extern "C" char* CL_TObjS13Cloud1;
extern "C" TObject* lbl_8042C110;

class TObjS13Cloud1 : public TObject, public TObjSetObj, public TObjS13Cloud
{
public:
	s16 unk34;   // 0x34
	u8 pad36[2]; // 0x36

	TObjS13Cloud1(TObject* parent);
	virtual void Exec();
	virtual ~TObjS13Cloud1();
	virtual void EditOnChange(SETDATA_PARAM*);
};

S13_CLOUD1_CTOR TObjS13Cloud1::TObjS13Cloud1(TObject* parent)
    : TObject(parent)
{
	S13Cloud1Param* param = (S13Cloud1Param*)ObjParam->setData.setBuffer;

	ClassName = CL_TObjS13Cloud1;
	DispTime  = 0x38;
	unk34     = 0;

	if (OnEdit()) {
		if (param->unk2 == 0) {
			param->unk2 = 20;
		}
		if (param->unk4 == 0) {
			param->unk4 = 60;
		}
	}
}
