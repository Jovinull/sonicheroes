#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s14ThunderCreate, the factory the editor record for TObjS14ThunderSet points
// at, in stage13D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// In the editor an all-zero parameter block gets the defaults 100, 10 and 100,
// and a zero float at 0x8 becomes 1 with the next one cleared; the 0 and 1 are
// the module's constants, read as externals. The set keeps pointers to its
// placement and to the placement's angle, and finishes in fn_9_A215C, a
// function of the class the PS2 build's names do not settle. The parameter
// block pointer is read first, before the class name.

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
	u8 unk34[4];             // 0x34
	SETOBJ_PARAM* placement; // 0x38
	sAngle* angle;           // 0x3C

	TObjS14ThunderSet(TObject* parent)
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
	virtual ~TObjS14ThunderSet();
	virtual void Exec();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s14ThunderCreate(void)
{
	new TObjS14ThunderSet(lbl_8042C110);
}
