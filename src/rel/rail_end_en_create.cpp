#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// railendenCreate, the factory the editor record for TObjRailEndEn points at,
// in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0` (here r28);
// rel/sample1_create.cpp has the long form. The class has the collision block
// as its third base, as in rel/warp_create.cpp.
//
// It is rel/rail_cap_ex_create.cpp for skinned models: each of the module's four
// model files for "dobj0708_railend_en.dff" is cloned into its own part, the
// clone's animation hierarchy (fn_800F3074, as game/effect/eff_crash3d.cpp
// uses it) kept beside it, the clone added once to the world slot its file
// names, and the hierarchy set up (fn_8013F3A4) when there is one. These model
// files carry four more words than the plain ones.

// One of the module's animated model files.
struct AnimModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
	u8 unk10[0x10];   // 0x10
};

struct RpHAnimHierarchy;

struct AnimPart {
	RpClump* clump;              // 0x00
	RpHAnimHierarchy* hierarchy; // 0x04
	s32 added;                   // 0x08
};

extern "C" char* CL_TObjRailEndEn;
extern "C" AnimModelFile railEndEnModelFiles[4];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" RpHAnimHierarchy* fn_800F3074(RpClump* clump);
extern "C" RpHAnimHierarchy* fn_8013F3A4(RpHAnimHierarchy* hierarchy);

class TObjRailEndEn : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;         // 0xB8
	sAngle ang;        // 0xC4
	s32 unkD0;         // 0xD0
	AnimPart parts[4]; // 0xD4

	TObjRailEndEn(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjRailEndEn;
		DispTime  = 0x104;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		for (int i = 0; i < 4; i++) {
			AnimModelFile* file = &railEndEnModelFiles[i];
			parts[i].clump      = fn_80150588(file->model);
			parts[i].hierarchy  = fn_800F3074(parts[i].clump);
			parts[i].added      = 0;
			if (parts[i].added == 0) {
				fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
				parts[i].added = 1;
			}
			if (parts[i].hierarchy != NULL) {
				fn_8013F3A4(parts[i].hierarchy);
			}
		}
		unkD0 = 0;
	}
	virtual ~TObjRailEndEn();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void railendenCreate(void)
{
	new TObjRailEndEn(lbl_8042C110);
}
