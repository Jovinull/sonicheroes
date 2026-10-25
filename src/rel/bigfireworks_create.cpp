#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// bigfireworksCreate, the factory rel/bigfireworks_register.cpp puts in the
// editor record: a new TObjBigFireWorks (the class name its constructor
// stores) that copies the set data's position and angle and, for the set its
// first parameter picks, clones each of the set's 30 models 50 times, none of
// them in the world yet. The allocation is a real new-expression of the class
// (rel/sample1_create.cpp).

// one model of a set: the world slot its clones go into and the model once
// loaded (rel/bigfireworks_hooks.cpp)
typedef struct BigfireworksModel {
	s32 world;   // 0x00
	void* model; // 0x04
} BigfireworksModel;

struct BigfireworksPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
};

// the set data's parameters
struct BigfireworksParam {
	s32 set; // 0x00: the set of models used
};

extern "C" char* CL_TObjBigFireWorks;
extern "C" BigfireworksModel bigfireworksModels[5][30];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

class TObjBigFireWorks : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;                         // 0xB8
	sAngle ang;                        // 0xC4
	s32 unkD0;                         // 0xD0
	u8 padD4[0x18];                    // 0xD4
	BigfireworksPart parts[5][30][50]; // 0xEC

	TObjBigFireWorks(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjBigFireWorks;
		DispTime  = 0xEB4C;

		BigfireworksParam* param = (BigfireworksParam*)ObjParam->setData.setBuffer;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		s32 set = param->set;

		for (int j = 0; j < 30; j++) {
			for (int i = 0; i < 50; i++) {
				parts[set][j][i].clump = fn_80150588(bigfireworksModels[set][j].model);
				parts[set][j][i].added = 0;
				if (parts[set][j][i].added == 1) {
					fn_8015BBF8(
					    *(void**)(lbl_8042C1D0 + 0x7250 + bigfireworksModels[set][j].world * 4),
					    parts[set][j][i].clump);
					parts[set][j][i].added = 0;
				}
			}
		}
		unkD0 = 0;
	}
	virtual ~TObjBigFireWorks();
};

extern "C" void bigfireworksCreate(void)
{
	new TObjBigFireWorks(lbl_8042C110);
}
