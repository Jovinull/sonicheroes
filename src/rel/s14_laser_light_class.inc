// TObjS14LaserLightSet, shared by rel/s14_laser_light_create.cpp, which defines S14_LASER_LIGHT_CTOR
// as inline so its factory inlines the constructor, and rel/s14_laser_light_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct S14LaserStorage {
	s32 count; // 0x00
	u32 unk4;  // 0x04

	S14LaserStorage() { count = 0; }
};

extern "C" char* CL_TObjS14LaserLightSet;
extern "C" TObject* lbl_8042C110;

class TObjS14LaserLightSet : public TObject, public TObjSetObj
{
public:
	u8 unk30;  // 0x30
	s32 unk34; // 0x34

	TObjS14LaserLightSet(TObject* parent);
	virtual ~TObjS14LaserLightSet();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

S14_LASER_LIGHT_CTOR TObjS14LaserLightSet::TObjS14LaserLightSet(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjS14LaserLightSet;
	DispTime  = 0x38;
	unk34     = 0;
	unk30     = 0;

	if (ObjParam->originalWork == NULL) {
		S14LaserStorage* storage = new S14LaserStorage;
		ObjParam->originalWork   = storage;
		storage->count           = 0;
	}
}
