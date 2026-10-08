#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s14LaserBeamCreate, the factory rel/s14_laser_beam_register.cpp puts in
// the editor record for TObjS14LaserBeamSet, in stage13D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// The first set object of a placement leaves an eight byte record on it, built
// with the global operator new; the record's constructor clears its count, and
// the set clears it again once the record is attached.

struct S14LaserStorage {
	s32 count; // 0x00
	u32 unk4;  // 0x04

	S14LaserStorage() { count = 0; }
};

extern "C" char* CL_TObjS14LaserBeamSet;
extern "C" TObject* lbl_8042C110;

class TObjS14LaserBeamSet : public TObject, public TObjSetObj
{
public:
	u8 unk30; // 0x30

	TObjS14LaserBeamSet(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS14LaserBeamSet;
		DispTime  = 0x34;
		unk30     = 0;

		if (ObjParam->originalWork == NULL) {
			S14LaserStorage* storage = new S14LaserStorage;
			ObjParam->originalWork   = storage;
			storage->count           = 0;
		}
	}
	virtual ~TObjS14LaserBeamSet();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s14LaserBeamCreate(void)
{
	new TObjS14LaserBeamSet(lbl_8042C110);
}
