#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// railpollexCreate, the factory rel/railpollex_register.cpp puts in the editor
// record for TObjRailPollEx, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The class has the collision block as its third base, as
// in rel/warp_create.cpp, though nothing here gives it a shape.
//
// It is rel/tenkyu_create.cpp for two models at once: the module keeps two
// model files for "dobj0708_railpoll_ex.dff" side by side, and each one is
// cloned into its own part and added once to the world slot its file names.

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

extern "C" char* CL_TObjRailPollEx;
extern "C" ModelFile railPollExModelFiles[2];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjRailPollEx : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;         // 0xB8
	sAngle ang;        // 0xC4
	s32 unkD0;         // 0xD0
	RailPart parts[2]; // 0xD4

	TObjRailPollEx(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjRailPollEx;
		DispTime  = 0xE4;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		for (int i = 0; i < 2; i++) {
			ModelFile* file = &railPollExModelFiles[i];
			parts[i].clump  = fn_80150588(file->model);
			parts[i].added  = 0;
			if (parts[i].added == 0) {
				fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
				parts[i].added = 1;
			}
		}
		unkD0 = 0;
	}
	virtual ~TObjRailPollEx();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void railpollexCreate(void)
{
	new TObjRailPollEx(lbl_8042C110);
}
