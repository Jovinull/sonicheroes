#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s14RoadsideBCreate and s14RoadsideACreate, the editor record factories for
// TObjS14RoadSide in stage13D, side 1 and side 0. Each is a real new-expression
// of the class with the model index as the second argument;
// rel/sample1_create.cpp has the long form of the allocation.
//
// The constructor takes its model from the module's table through fn_9_75908,
// lit with the light set the placement's condition bits 18-20 pick (plus 4),
// after keeping the side (the model index) in the byte at 0x30, and, if it got
// a model, turns its frame by the placement's angles and moves it to the
// placement's position, as rel/s13d_senkan_far_create.cpp does. The flags are
// read through a volatile access: the original loads them before the table's
// address, and a plain read is folded into the argument after it
// (docs/language-audit.md).

struct RwV3d;

// The part of a RenderWare frame used here: its modelling matrix.
struct LightFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

extern "C" char* CL_TObjS14RoadSide;
extern "C" u8 s14RoadSideModels[];
extern "C" const f32 s14RoadSideOne[1];
extern "C" RwV3d AxisX;
extern "C" RwV3d AxisY;
extern "C" RwV3d AxisZ;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75908(void* table, s16 index, s8 lightSet, RpClump** clump, void* frame);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void fn_80195790(void* matrix, RwV3d* axis, f32 oneMinusCosine, f32 sine, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* position, s32 combine);

class TObjS14RoadSide : public TObject, public TObjSetObj
{
public:
	s8 side;        // 0x30
	u8 pad31[3];    // 0x31
	RpClump* clump; // 0x34

	TObjS14RoadSide(TObject* parent, s8 index)
	    : TObject(parent)
	{
		ClassName = CL_TObjS14RoadSide;
		DispTime  = 0x38;

		side = index;

		u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		fn_9_75908(s14RoadSideModels, index, ((flag & 0x1C0000) >> 18) + 4, &clump, NULL);
		if (clump != NULL) {
			LightFrame* frame = *(LightFrame**)((u8*)clump + 4);
			f32 sine;

			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s14RoadSideOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.x);
			fn_80195790(frame->modelling, &AxisX,
			    s14RoadSideOne[0] - fn_800D7AE4(ObjParam->setData.ang.x), sine, 2);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.z);
			fn_80195790(frame->modelling, &AxisZ,
			    s14RoadSideOne[0] - fn_800D7AE4(ObjParam->setData.ang.z), sine, 2);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
		}
	}
	virtual ~TObjS14RoadSide();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s14RoadsideBCreate(void)
{
	new TObjS14RoadSide(lbl_8042C110, 1);
}

extern "C" void s14RoadsideACreate(void)
{
	new TObjS14RoadSide(lbl_8042C110, 0);
}
