#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s14RailendSignCreate, the editor record factory for TObjS14RailEnd (the
// class name its constructor stores) in stage13D. It is a real new-expression
// of the class; rel/sample1_create.cpp has the long form of the allocation.
//
// The constructor takes the sign and its second part through fn_9_75908 with
// the light set the placement's flags pick, as rel/s14_koware_create.cpp does.
// With the sign (and then with the second part too), each frame is turned by
// the placement's Y, X and Z angles and moved to the placement's position, as
// rel/s13d_screw_create.cpp does.

// The part of a RenderWare frame used here: its modelling matrix.
struct RailEndFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

extern "C" char* CL_TObjS14RailEnd;
extern "C" u8 s14RailendSignModels[];
extern "C" const f32 s14RailendSignOne[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75908(void* table, s16 index, s8 lightSet, RpClump** clump, void* frame);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

class TObjS14RailEnd : public TObject, public TObjSetObj
{
public:
	RpClump* clump;  // 0x30
	RpClump* clump2; // 0x34

	// turns the clump's frame by the placement's angles and moves it to the
	// placement's position
	inline void Place(RpClump* model)
	{
		RailEndFrame* frame = *(RailEndFrame**)((u8*)model + 4);
		f32 sine;

		sine = fn_800D7B00(ObjParam->setData.ang.y);
		fn_80195790(frame->modelling, &AxisY,
		    s14RailendSignOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
		fn_8019E880(frame);
		sine = fn_800D7B00(ObjParam->setData.ang.x);
		fn_80195790(frame->modelling, &AxisX,
		    s14RailendSignOne[0] - fn_800D7AE4(ObjParam->setData.ang.x), sine, 2);
		fn_8019E880(frame);
		sine = fn_800D7B00(ObjParam->setData.ang.z);
		fn_80195790(frame->modelling, &AxisZ,
		    s14RailendSignOne[0] - fn_800D7AE4(ObjParam->setData.ang.z), sine, 2);
		fn_8019E880(frame);
		fn_8019EB94(frame, &ObjParam->setData.pos, 2);
	}

	TObjS14RailEnd(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS14RailEnd;
		DispTime  = 0x38;

		u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		fn_9_75908(s14RailendSignModels, 0, ((flag & 0x1C0000) >> 18) + 4, &clump, NULL);
		flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		fn_9_75908(s14RailendSignModels, 1, ((flag & 0x1C0000) >> 18) + 4, &clump2, NULL);
		if (clump != NULL) {
			Place(clump);
			if (clump2 != NULL) {
				Place(clump2);
			}
		}
	}
	virtual ~TObjS14RailEnd();
};

extern "C" void s14RailendSignCreate(void)
{
	new TObjS14RailEnd(lbl_8042C110);
}
