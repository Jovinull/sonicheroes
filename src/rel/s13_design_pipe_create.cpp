#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s13DesignPipeCreate, the editor record factory for TObjS13EnergyPipe (the
// class name its constructor stores) in stage13D. It is a real new-expression
// of the class; rel/sample1_create.cpp has the long form of the allocation.
//
// The constructor takes its two models from the module's table through
// fn_9_75D2C and starts the second one's animation (+0x40 in the table)
// through fn_9_756F4. Then, for each model it has, it turns the frame by the
// placement's Y angle and moves it to the placement's position, as
// rel/s13d_screw_create.cpp does with all three angles.

struct RwV3d;

// The part of a RenderWare frame used here: its modelling matrix.
struct EnergyPipeFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

extern "C" char* CL_TObjS13EnergyPipe;
extern "C" u8 s13DesignPipeModels[];
extern "C" const f32 s13DesignPipeOne[1];
extern "C" RwV3d AxisY;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75D2C(void* table, s16 index, RpClump** clump, void* frame);
extern "C" void fn_9_756F4(RpClump* clump, void* animation, s32 arg);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void fn_80195790(void* matrix, RwV3d* axis, f32 oneMinusCosine, f32 sine, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* position, s32 combine);

class TObjS13EnergyPipe : public TObject, public TObjSetObj
{
public:
	RpClump* clump;  // 0x30
	RpClump* clump2; // 0x34

	TObjS13EnergyPipe(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS13EnergyPipe;
		DispTime  = 0x38;

		fn_9_75D2C(s13DesignPipeModels, 0, &clump, NULL);
		fn_9_75D2C(s13DesignPipeModels, 1, &clump2, NULL);
		fn_9_756F4(clump2, s13DesignPipeModels + 0x40, 0);
		if (clump != NULL) {
			EnergyPipeFrame* frame = *(EnergyPipeFrame**)((u8*)clump + 4);
			f32 sine;

			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s13DesignPipeOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
		}
		if (clump2 != NULL) {
			EnergyPipeFrame* frame = *(EnergyPipeFrame**)((u8*)clump2 + 4);
			f32 sine;

			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s13DesignPipeOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
		}
	}
	virtual ~TObjS13EnergyPipe();
};

extern "C" void s13DesignPipeCreate(void)
{
	new TObjS13EnergyPipe(lbl_8042C110);
}
