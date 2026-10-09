// TObjRailBush, shared by rel/rail_bush_create.cpp, which defines RAIL_BUSH_CTOR
// as inline so its factory inlines the constructor, and rel/rail_bush_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" char* CL_TObjRailBush;
extern "C" ModelFile railBushModelFile;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjRailBush : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;      // 0xB8
	sAngle ang;     // 0xC4
	RpClump* clump; // 0xD0
	s32 added;      // 0xD4

	TObjRailBush(TObject* parent);
	virtual ~TObjRailBush();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

RAIL_BUSH_CTOR TObjRailBush::TObjRailBush(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjRailBush;
	DispTime  = 0xD8;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	ModelFile* file = &railBushModelFile;
	clump           = fn_80150588(file->model);
	added           = 0;
	if (added == 0) {
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), clump);
		added = 1;
	}
}
