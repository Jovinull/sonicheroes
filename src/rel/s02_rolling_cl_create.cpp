#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// fn_3_9FC0C, the factory for TObjS02Rolling_CL in stage01D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// In the editor a zero size in the placement's parameter block becomes 50, the
// module's constants 0 and 50. The kind byte at 4 then picks the two bytes at
// 0xB8: a bit (1, 2, 4 or 8) and whether it is one of the upper two kinds. The
// parameter block pointer is read first, before the class name.

struct S02RollingParam {
	f32 size; // 0x00
	s8 kind;  // 0x04
};

extern "C" char* CL_TObjS02Rolling_CL;
extern "C" const f32 s02RollingZero[1];
extern "C" const f32 s02RollingDefault[1];
extern "C" TObject* lbl_8042C110;

class TObjS02Rolling_CL : public TObject, public TObjSetObj, public C_COLLI
{
public:
	u8 bit;   // 0xB8
	u8 upper; // 0xB9
	u8 padBA[2];

	TObjS02Rolling_CL(TObject* parent)
	    : TObject(parent)
	{
		S02RollingParam* param = (S02RollingParam*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS02Rolling_CL;
		DispTime  = 0xBC;

		if (OnEdit()) {
			if (s02RollingZero[0] == param->size) {
				param->size = s02RollingDefault[0];
			}
		}

		switch (param->kind) {
			case 0:
				bit   = 1;
				upper = 0;
				break;
			case 1:
				bit   = 2;
				upper = 0;
				break;
			case 2:
				bit   = 4;
				upper = 1;
				break;
			case 3:
				bit   = 8;
				upper = 1;
				break;
		}
	}
	virtual ~TObjS02Rolling_CL();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void fn_3_9FC0C(void)
{
	new TObjS02Rolling_CL(lbl_8042C110);
}
