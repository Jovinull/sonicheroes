#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// trainchangeboardCreate, the factory the editor record for
// TObjTrainChangeBoard points at, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The third base is TrainSwitchManager, the PS2 build's
// empty class with an out of line constructor (a lone blr at 0x95704 in this
// module): it takes no room, so the position starts at 0x30 where the base is
// constructed.
//
// It is rel/rail_cap_ex_create.cpp for seven models, starting with
// "obj07_ChangeBoard.dff": each is cloned into its own part and added once to
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

class TrainSwitchManager
{
public:
	TrainSwitchManager();
};

extern "C" char* CL_TObjTrainChangeBoard;
extern "C" ModelFile trainChangeBoardModelFiles[7];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjTrainChangeBoard : public TObject, public TObjSetObj, public TrainSwitchManager
{
public:
	RwV3d pos;          // 0x30
	sAngle ang;         // 0x3C
	ModelPart parts[7]; // 0x48

	TObjTrainChangeBoard(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjTrainChangeBoard;
		DispTime  = 0x80;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		for (int i = 0; i < 7; i++) {
			ModelFile* file = &trainChangeBoardModelFiles[i];
			parts[i].clump  = fn_80150588(file->model);
			parts[i].added  = 0;
			if (parts[i].added == 0) {
				fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
				parts[i].added = 1;
			}
		}
	}
	virtual ~TObjTrainChangeBoard();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void trainchangeboardCreate(void)
{
	new TObjTrainChangeBoard(lbl_8042C110);
}
