#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s02MovingLandCreate, the factory rel/s02_moving_land_register.cpp puts in
// the editor record: a new TObjS02MovingLand (the class name its constructor
// stores). While the editor is on, a set data with no speed gets 2 and one
// with a kind out of range gets kind 0. It clones the kind's model (and, for
// kind 0, the third model as its second part) and moves both to the kind's
// starting point. The allocation is a real new-expression of the class
// (rel/sample1_create.cpp).

// the set data's parameters
struct S02MovingLandParam {
	s8 kind; // 0x00: the land moved
	u8 pad01[0x3];
	f32 speed; // 0x04
};

// a kind's path: where it starts and where it ends
struct S02MovingLandPath {
	RwV3d start; // 0x00
	RwV3d end;   // 0x0C
};

struct RwFrame;

extern "C" char* CL_TObjS02MovingLand;
extern "C" void* s02MovingLandModels[3];
extern "C" S02MovingLandPath s02MovingLandPaths[2];
extern "C" const f32 s02MovingLandZero;
extern "C" const f32 s02MovingLandDefaultSpeed;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);

// the frame of a clump (its object's parent)
inline RwFrame* ClumpFrame(RpClump* clump)
{
	return *(RwFrame**)((u8*)clump + 0x4);
}

class TObjS02MovingLand : public TObject, public TObjSetObj
{
public:
	RpClump* clump;  // 0x30
	RpClump* clump2; // 0x34
	u8 pad38[0x4];
	s32 unk3C; // 0x3C
	s8 unk40;  // 0x40
	s8 kind;   // 0x41
	u8 pad42[0x2];
	RwV3d pos; // 0x44

	TObjS02MovingLand(TObject* parent)
	    : TObject(parent)
	{
		S02MovingLandParam* param = (S02MovingLandParam*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS02MovingLand;
		DispTime  = 0x50;
		if (OnEdit()) {
			if (s02MovingLandZero == param->speed) {
				param->speed = s02MovingLandDefaultSpeed;
			}
			if (param->kind < 0 || param->kind >= 2) {
				param->kind = 0;
			}
		}
		kind  = param->kind;
		unk3C = unk40 = 0;
		clump         = fn_80150588(s02MovingLandModels[kind]);
		if (kind == 0) {
			clump2 = fn_80150588(s02MovingLandModels[2]);
		} else {
			clump2 = NULL;
		}
		pos = s02MovingLandPaths[kind].start;
		fn_8019EB94(ClumpFrame(clump), &pos, 0);
		if (clump2 != NULL) {
			fn_8019EB94(ClumpFrame(clump2), &pos, 0);
		}
		unk3C = 0;
	}
	virtual ~TObjS02MovingLand();
};

extern "C" void s02MovingLandCreate(void)
{
	new TObjS02MovingLand(lbl_8042C110);
}
