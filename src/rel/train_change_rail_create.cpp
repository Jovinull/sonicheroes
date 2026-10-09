#include "game/effect/eff_bomb.h"
#include "game/setObj.h"
#include "MSL_C/string.h"

// trainchangerailCreate, the factory the editor record for TObjTrainChangeRail
// points at, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The third base is the empty TrainSwitchManager, as in
// rel/train_change_board_create.cpp.
//
// The constructor copies the placement and clears two vectors with memset and
// the word at 0x80.

class TrainSwitchManager
{
public:
	TrainSwitchManager();
};

extern "C" char* CL_TObjTrainChangeRail;
extern "C" TObject* lbl_8042C110;

class TObjTrainChangeRail : public TObject, public TObjSetObj, public TrainSwitchManager
{
public:
	RwV3d pos;      // 0x30
	sAngle ang;     // 0x3C
	u8 unk48[8];    // 0x48
	RwV3d unk50;    // 0x50
	u8 unk5C[0x10]; // 0x5C
	RwV3d unk6C;    // 0x6C
	u8 unk78[8];    // 0x78
	s32 unk80;      // 0x80

	TObjTrainChangeRail(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjTrainChangeRail;
		DispTime  = 0x84;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		memset(&unk50, 0, sizeof(unk50));
		memset(&unk6C, 0, sizeof(unk6C));
		unk80 = 0;
	}
	virtual ~TObjTrainChangeRail();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void trainchangerailCreate(void)
{
	new TObjTrainChangeRail(lbl_8042C110);
}
