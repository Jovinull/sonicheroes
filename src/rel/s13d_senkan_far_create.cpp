#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s13dSenkanFar1Create to s13dSenkanFar8Create, the factories the editor
// records for the eight far-away battleships point at, in stage13D, laid out
// from the eighth to the first. Each is a real new-expression of
// TObjS13ShipFarDistance (the class name the original gives it), with the
// ship's model index as the second argument (0 to 5, then 7 and 8: the table's
// seventh entry has no factory of its own); rel/sample1_create.cpp has the
// long form of the allocation.
//
// The constructor takes the model from the module's table through fn_9_75A80
// and, if it got one, turns its frame by the placement's angles, Y first
// (replacing the matrix) and then X and Z (post-concatenated), each through
// fn_80195790 with one minus the cosine and the sine (fn_800D7AE4 and
// fn_800D7B00), and moves it to the placement's position (fn_8019EB94). The
// matrix is the frame's member, not an offset added to the frame pointer: the
// sum would be kept in a saved register instead of recomputed for each call.

struct RwV3d;

extern "C" char* CL_TObjS13ShipFarDistance;
extern "C" u8 s13ShipFarModels[];
extern "C" const f32 s13dObjectOne[1];
extern "C" RwV3d AxisX;
extern "C" RwV3d AxisY;
extern "C" RwV3d AxisZ;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75A80(void* table, s16 index, RpClump** clump, void* frame);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void fn_80195790(void* matrix, RwV3d* axis, f32 oneMinusCosine, f32 sine, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* position, s32 combine);

// The part of a RenderWare frame used here: its modelling matrix.
struct ShipFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

class TObjS13ShipFarDistance : public TObject, public TObjSetObj
{
public:
	RpClump* clump; // 0x30

	TObjS13ShipFarDistance(TObject* parent, s16 index)
	    : TObject(parent)
	{
		ClassName = CL_TObjS13ShipFarDistance;
		DispTime  = 0x34;

		fn_9_75A80(s13ShipFarModels, index, &clump, NULL);
		if (clump != NULL) {
			ShipFrame* frame = *(ShipFrame**)((u8*)clump + 4);
			f32 sine;

			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s13dObjectOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.x);
			fn_80195790(frame->modelling, &AxisX,
			    s13dObjectOne[0] - fn_800D7AE4(ObjParam->setData.ang.x), sine, 2);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.z);
			fn_80195790(frame->modelling, &AxisZ,
			    s13dObjectOne[0] - fn_800D7AE4(ObjParam->setData.ang.z), sine, 2);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
		}
	}
	virtual ~TObjS13ShipFarDistance();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s13dSenkanFar8Create(void)
{
	new TObjS13ShipFarDistance(lbl_8042C110, 8);
}

extern "C" void s13dSenkanFar7Create(void)
{
	new TObjS13ShipFarDistance(lbl_8042C110, 7);
}

extern "C" void s13dSenkanFar6Create(void)
{
	new TObjS13ShipFarDistance(lbl_8042C110, 5);
}

extern "C" void s13dSenkanFar5Create(void)
{
	new TObjS13ShipFarDistance(lbl_8042C110, 4);
}

extern "C" void s13dSenkanFar4Create(void)
{
	new TObjS13ShipFarDistance(lbl_8042C110, 3);
}

extern "C" void s13dSenkanFar3Create(void)
{
	new TObjS13ShipFarDistance(lbl_8042C110, 2);
}

extern "C" void s13dSenkanFar2Create(void)
{
	new TObjS13ShipFarDistance(lbl_8042C110, 1);
}

extern "C" void s13dSenkanFar1Create(void)
{
	new TObjS13ShipFarDistance(lbl_8042C110, 0);
}
