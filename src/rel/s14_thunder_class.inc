// TObjS14ThunderSet, shared by rel/s14_thunder_create.cpp, which defines S14_THUNDER_CTOR
// as inline so its factory inlines the constructor, and rel/s14_thunder_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct S14ThunderParam {
	u16 unk0; // 0x00
	u16 unk2; // 0x02
	u16 unk4; // 0x04
	u8 pad6[2];
	f32 unk8; // 0x08
	f32 unkC; // 0x0C
};

class TObjS14ThunderSet;

extern "C" char* CL_TObjS14ThunderSet;
extern "C" const f32 s14ThunderZero[1];
extern "C" const f32 s14ThunderOne[1];
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_A215C(TObjS14ThunderSet* set);

class TObjS14ThunderSet : public TObject, public TObjSetObj
{
public:
	s32 unk30;               // 0x30
	TObjS14ThunderSet* next; // 0x34, the chain fn_9_A215C links into
	SETOBJ_PARAM* placement; // 0x38
	sAngle* angle;           // 0x3C

	TObjS14ThunderSet(TObject* parent);
	virtual void Exec();
	virtual ~TObjS14ThunderSet();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

S14_THUNDER_CTOR TObjS14ThunderSet::TObjS14ThunderSet(TObject* parent)
    : TObject(parent)
{
	S14ThunderParam* param = (S14ThunderParam*)ObjParam->setData.setBuffer;

	ClassName = CL_TObjS14ThunderSet;
	DispTime  = 0x40;

	if (OnEdit()) {
		if (param->unk0 == 0 && param->unk2 == 0 && param->unk4 == 0) {
			param->unk0 = 100;
			param->unk2 = 10;
			param->unk4 = 100;
		}
		if (s14ThunderZero[0] == param->unk8) {
			param->unk8 = s14ThunderOne[0];
			param->unkC = s14ThunderZero[0];
		}
	}

	placement = ObjParam;
	angle     = &ObjParam->setData.ang;
	unk30     = 0;
	fn_9_A215C(this);
}
