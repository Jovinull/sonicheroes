#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// leafaaCreate, the factory the editor record for TObjLeafAA points at, in
// stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// It is rel/water_plant_create.cpp for "dobj_leafAA.dff", with one more word
// in front of the position that the constructor clears last.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct LeafAAModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" char* CL_TObjLeafAA;
extern "C" LeafAAModelFile leafAAModelFile;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjLeafAA : public TObject, public TObjSetObj
{
public:
	s32 unk30;      // 0x30
	RwV3d pos;      // 0x34
	sAngle ang;     // 0x40
	RpClump* clump; // 0x4C
	s32 added;      // 0x50

	TObjLeafAA(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjLeafAA;
		DispTime  = 0x54;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		clump = fn_80150588(leafAAModelFile.model);
		added = 0;
		if (added == 0) {
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + leafAAModelFile.world * 4), clump);
			added = 1;
		}
		unk30 = 0;
	}
	virtual ~TObjLeafAA();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void leafaaCreate(void)
{
	new TObjLeafAA(lbl_8042C110);
}
