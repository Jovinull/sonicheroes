// TObjLeafAA, shared by rel/leaf_aa_create.cpp and the units
// that define its out-of-line members. The constructor stays inline in the
// class: the factory inlines it.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

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
	virtual void Exec();
	virtual ~TObjLeafAA();
	virtual void EditOnChange(SETDATA_PARAM*);
};
