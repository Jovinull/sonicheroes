#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s13Cloud1Create, the factory the editor record for TObjS13Cloud1 points at,
// in stage13D, stage27D and stage28D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0` (here r30);
// rel/sample1_create.cpp has the long form. The third base is TObjS13Cloud,
// which the PS2 build names through SetTopPtcl and GetTopPtcl: it holds the
// first particle of the cloud and its inline constructor clears it, which is
// why that store comes before the vtable stores.
//
// In the editor two zero halfwords of the parameter block become 20 and 60.
// The parameter block pointer is read first, before the class name.

struct S13Cloud1Param {
	s16 unk0; // 0x00
	s16 unk2; // 0x02
	s16 unk4; // 0x04
};

class TObjS13CloudPtcl;

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

	TObjS13Cloud1(TObject* parent)
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
	virtual ~TObjS13Cloud1();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s13Cloud1Create(void)
{
	new TObjS13Cloud1(lbl_8042C110);
}
