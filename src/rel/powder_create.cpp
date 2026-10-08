#include "game/effect/eff_bomb.h"
#include "game/setObj.h"
#include "MSL_C/string.h"

// powderCreate, the factory the editor record for TObjPowder points at, in
// stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The object carries a 4 KiB work area that the constructor clears with
// memset, and a word after it; the instance is 0x10D4 bytes.

extern "C" char* CL_TObjPowder;
extern "C" TObject* lbl_8042C110;

class TObjPowder : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;       // 0xB8
	sAngle ang;      // 0xC4
	u8 work[0x1000]; // 0xD0
	s32 unk10D0;     // 0x10D0

	TObjPowder(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjPowder;
		DispTime  = 0x10D4;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		memset(work, 0, sizeof(work));
		unk10D0 = 0;
	}
	virtual ~TObjPowder();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void powderCreate(void)
{
	new TObjPowder(lbl_8042C110);
}
