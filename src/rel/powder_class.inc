// TObjPowder, shared by rel/powder_create.cpp, which defines POWDER_CTOR
// as inline so its factory inlines the constructor, and rel/powder_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"
#include "MSL_C/string.h"

extern "C" char* CL_TObjPowder;
extern "C" TObject* lbl_8042C110;

class TObjPowder : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;       // 0xB8
	sAngle ang;      // 0xC4
	u8 work[0x1000]; // 0xD0
	s32 unk10D0;     // 0x10D0

	TObjPowder(TObject* parent);
	virtual ~TObjPowder();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

POWDER_CTOR TObjPowder::TObjPowder(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjPowder;
	DispTime  = 0x10D4;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	memset(work, 0, sizeof(work));
	unk10D0 = 0;
}
