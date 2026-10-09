// TObjRailCapEx, shared by rel/rail_cap_ex_create.cpp, which defines RAIL_CAP_EX_CTOR
// as inline so its factory inlines the constructor, and rel/rail_cap_ex_ctor.cpp,
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

struct RailPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
};

extern "C" char* CL_TObjRailCapEx;
extern "C" ModelFile railCapExModelFiles[2];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjRailCapEx : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;         // 0xB8
	sAngle ang;        // 0xC4
	s32 unkD0;         // 0xD0
	RailPart parts[2]; // 0xD4

	TObjRailCapEx(TObject* parent);
	virtual ~TObjRailCapEx();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

RAIL_CAP_EX_CTOR TObjRailCapEx::TObjRailCapEx(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjRailCapEx;
	DispTime  = 0xE4;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	for (int i = 0; i < 2; i++) {
		ModelFile* file = &railCapExModelFiles[i];
		parts[i].clump  = fn_80150588(file->model);
		parts[i].added  = 0;
		if (parts[i].added == 0) {
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
			parts[i].added = 1;
		}
	}
	unkD0 = 0;
}
