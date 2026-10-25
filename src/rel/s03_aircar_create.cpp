#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s03AircarCreate, the factory rel/s03_aircar_register.cpp puts in the editor
// record: a new TObjS03AircarSet (the class name its constructor stores). In
// the editor an out-of-range car kind becomes 0 (1 on stage 0x11); the object
// makes its own frame, keeps the set data's second halfword, position and
// angle, and turns the frame by the angle (Y, then X and Z) and moves it to the
// position. The allocation is a real new-expression of the class
// (rel/sample1_create.cpp); the parameter block pointer is read before the
// class name.

struct RwMatrixTag;

// the frame: only its modelling matrix is used here
typedef struct AircarFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
} AircarFrame;

// the set data's parameter block
typedef struct AircarParams {
	s8 kind; // 0x00
	u8 unk01[0x3];
	s16 unk04; // 0x04
} AircarParams;

extern "C" char* CL_TObjS03AircarSet;
extern "C" u8 lbl_4_data_777F;
extern "C" s32 s03AircarStage;
extern "C" const f32 s03AircarOne;
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" TObject* lbl_8042C110;

extern "C" AircarFrame* fn_8019E344(void);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(AircarFrame* frame);
extern "C" void fn_8019EB94(AircarFrame* frame, RwV3d* translation, s32 combine);

class TObjS03AircarSet : public TObject, public TObjSetObj
{
public:
	RwV3d pos;          // 0x30
	sAngle ang;         // 0x3C
	s16 unk48;          // 0x48
	AircarFrame* frame; // 0x4C

	TObjS03AircarSet(TObject* parent)
	    : TObject(parent)
	{
		AircarParams* params = (AircarParams*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS03AircarSet;
		DispTime  = 0x50;
		if (OnEdit()) {
			if (params->kind < 0 || params->kind >= (s8)lbl_4_data_777F) {
				params->kind = 0;
				if (s03AircarStage == 0x11) {
					params->kind = 1;
				}
			}
		}
		frame             = fn_8019E344();
		unk48             = params->unk04;
		AircarFrame* turn = frame;
		pos               = ObjParam->setData.pos;
		ang               = ObjParam->setData.ang;
		fn_80195790(
		    turn->modelling, &AxisY, s03AircarOne - fn_800D7AE4(ang.y), fn_800D7B00(ang.y), 0);
		fn_8019E880(turn);
		fn_80195790(
		    turn->modelling, &AxisX, s03AircarOne - fn_800D7AE4(ang.x), fn_800D7B00(ang.x), 2);
		fn_8019E880(turn);
		fn_80195790(
		    turn->modelling, &AxisZ, s03AircarOne - fn_800D7AE4(ang.z), fn_800D7B00(ang.z), 2);
		fn_8019E880(turn);
		fn_8019EB94(turn, &pos, 2);
	}
	virtual ~TObjS03AircarSet();
};

extern "C" void s03AircarCreate(void)
{
	new TObjS03AircarSet(lbl_8042C110);
}
