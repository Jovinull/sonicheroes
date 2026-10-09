#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// railendexCreate, the factory rel/railendex_register.cpp puts in the editor
// record for TObjRailEndEx, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what gives
// the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp has
// the long form. The class has the collision block as its third base, as in
// rel/warp_create.cpp.
//
// It is rel/rail_cap_ex_create.cpp for 2 models, starting with
// "dobj0708_railend_ex.dff": each is cloned into its own part and added once to
// the world slot its file names.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

struct ModelPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
};

extern "C" char* CL_TObjRailEndEx;
extern "C" ModelFile railEndExModelFiles[2];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjRailEndEx : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;          // 0xB8
	sAngle ang;         // 0xC4
	u8 unkD0[4];        // 0xD0
	ModelPart parts[2]; // 0xD4

	TObjRailEndEx(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjRailEndEx;
		DispTime  = 0xE4;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		for (int i = 0; i < 2; i++) {
			ModelFile* file = &railEndExModelFiles[i];
			parts[i].clump  = fn_80150588(file->model);
			parts[i].added  = 0;
			if (parts[i].added == 0) {
				fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
				parts[i].added = 1;
			}
		}
	}
	virtual ~TObjRailEndEx();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void railendexCreate(void)
{
	new TObjRailEndEx(lbl_8042C110);
}
