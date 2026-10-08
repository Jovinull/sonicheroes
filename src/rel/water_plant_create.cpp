#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// waterplantCreate, the factory the editor record for TObjWaterPlant points
// at, in stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// The plant clones the model the module loaded for "obj10_WaterPlant.dff" and,
// unless it is already in, adds it to the world the model file names: one of
// the world slots from 0x7250 in the stage block. The flag is written and read
// back before the test, as the original does. The slot's address is written
// as the base plus 0x7250 plus the index scaled, which is the order the
// original adds them in; indexing an array member scales and adds the base
// first.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct WaterPlantModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" char* CL_TObjWaterPlant;
extern "C" WaterPlantModelFile waterPlantModelFile;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjWaterPlant : public TObject, public TObjSetObj
{
public:
	RwV3d pos;      // 0x30
	sAngle ang;     // 0x3C
	RpClump* clump; // 0x48
	s32 added;      // 0x4C

	TObjWaterPlant(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjWaterPlant;
		DispTime  = 0x50;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		clump = fn_80150588(waterPlantModelFile.model);
		added = 0;
		if (added == 0) {
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + waterPlantModelFile.world * 4), clump);
			added = 1;
		}
	}
	virtual ~TObjWaterPlant();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void waterplantCreate(void)
{
	new TObjWaterPlant(lbl_8042C110);
}
