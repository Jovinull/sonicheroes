#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// watersurfaceCreate, the factory the editor record for TObjWaterSurface points
// at, in stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// It is rel/water_plant_create.cpp for "obj10_waterSurface.dff": clone the
// module's model and, unless it is already in, add it to the world slot the
// model file names, with the slot's address written the way that file explains.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct WaterSurfaceModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" char* CL_TObjWaterSurface;
extern "C" WaterSurfaceModelFile waterSurfaceModelFile;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjWaterSurface : public TObject, public TObjSetObj
{
public:
	RwV3d pos;      // 0x30
	sAngle ang;     // 0x3C
	RpClump* clump; // 0x48
	s32 added;      // 0x4C

	TObjWaterSurface(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjWaterSurface;
		DispTime  = 0x50;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		clump = fn_80150588(waterSurfaceModelFile.model);
		added = 0;
		if (added == 0) {
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + waterSurfaceModelFile.world * 4), clump);
			added = 1;
		}
	}
	virtual ~TObjWaterSurface();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void watersurfaceCreate(void)
{
	new TObjWaterSurface(lbl_8042C110);
}
