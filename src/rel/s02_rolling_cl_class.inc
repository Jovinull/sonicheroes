// TObjS02Rolling_CL, shared by rel/s02_rolling_cl_create.cpp, which defines S02_ROLLING_CL_CTOR
// as inline so its factory inlines the constructor, and rel/s02_rolling_cl_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

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

	TObjS02Rolling_CL(TObject* parent);
	virtual ~TObjS02Rolling_CL();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

S02_ROLLING_CL_CTOR TObjS02Rolling_CL::TObjS02Rolling_CL(TObject* parent)
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
