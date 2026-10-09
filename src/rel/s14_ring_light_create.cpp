#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s14RingLightCreate, the editor record factory for TObjS14RingLight in
// stage13D. It is a real new-expression of the class; rel/sample1_create.cpp
// has the long form of the allocation.
//
// The constructor takes its model from the module's table through fn_9_75D2C
// and the animation that follows it in the table (+0x14) through fn_9_756F4,
// and, if it got a model, turns its frame by the placement's angles and moves
// it to the placement's position, as rel/s13d_senkan_far_create.cpp does.

struct RwV3d;

// The part of a RenderWare frame used here: its modelling matrix.
struct LightFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

extern "C" char* CL_TObjS14RingLight;
extern "C" u8 s14RingLightModels[];
extern "C" const f32 s14RingLightOne[1];
extern "C" RwV3d AxisX;
extern "C" RwV3d AxisY;
extern "C" RwV3d AxisZ;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75D2C(void* table, s16 index, RpClump** clump, void* frame);
extern "C" void fn_9_756F4(RpClump* clump, void* animation, s32 arg);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void fn_80195790(void* matrix, RwV3d* axis, f32 oneMinusCosine, f32 sine, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* position, s32 combine);

class TObjS14RingLight : public TObject, public TObjSetObj
{
public:
	RpClump* clump;  // 0x30
	void* animation; // 0x34

	TObjS14RingLight(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS14RingLight;
		DispTime  = 0x38;

		fn_9_75D2C(s14RingLightModels, 0, &clump, NULL);
		animation = s14RingLightModels + 0x14;
		fn_9_756F4(clump, animation, 0);
		if (clump != NULL) {
			LightFrame* frame = *(LightFrame**)((u8*)clump + 4);
			f32 sine;

			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s14RingLightOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.x);
			fn_80195790(frame->modelling, &AxisX,
			    s14RingLightOne[0] - fn_800D7AE4(ObjParam->setData.ang.x), sine, 2);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.z);
			fn_80195790(frame->modelling, &AxisZ,
			    s14RingLightOne[0] - fn_800D7AE4(ObjParam->setData.ang.z), sine, 2);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
		}
	}
	virtual ~TObjS14RingLight();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s14RingLightCreate(void)
{
	new TObjS14RingLight(lbl_8042C110);
}
