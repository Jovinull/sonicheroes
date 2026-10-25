#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s14KowareCreate, the editor record factory for TObjS14Koware (the class name
// its constructor stores) in stage13D. It is a real new-expression of the
// class; rel/sample1_create.cpp has the long form of the allocation.
//
// The constructor takes its model through fn_9_75908 with the light set the
// placement's flags pick (bits 18 to 20, plus 4), as
// rel/s14_red_light_create.cpp does, reading the flags through a volatile so
// they load before the table. While the editor is on, a set data with no scale
// gets 1. The module's shape for its collision block (its third base) is
// scaled by it, and so is the clump's frame on X and Z before it is turned by
// the placement's Y angle and moved to the placement's position.

struct RwFrame;

// The part of a RenderWare frame used here: its modelling matrix.
struct KowareFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

// the set data's parameters
struct S14KowareParams {
	f32 scale; // 0x00
};

extern "C" char* CL_TObjS14Koware;
extern "C" u8 s14KowareModels[];
extern "C" CCL_INFO s14KowareCclInfo;
extern "C" const RwV3d s14KowareUnitScale;
extern "C" const f32 s14KowareEditMin[1];
extern "C" const f32 s14KowareOne[1];
extern "C" const RwV3d AxisY;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75908(void* table, s16 index, s8 lightSet, RpClump** clump, void* frame);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);
extern "C" void fn_8019EC30(void* frame, RwV3d* scale, s32 combine);

class TObjS14Koware : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s8 unkB8;       // 0xB8
	u8 padB9[3];    // 0xB9
	RpClump* clump; // 0xBC

	TObjS14Koware(TObject* parent)
	    : TObject(parent)
	{
		S14KowareParams* params = (S14KowareParams*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS14Koware;
		DispTime  = 0xC0;

		u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		fn_9_75908(s14KowareModels, 0, ((flag & 0x1C0000) >> 18) + 4, &clump, NULL);
		unkB8 = 0;
		if (OnEdit()) {
			if (s14KowareEditMin[0] == params->scale) {
				params->scale = s14KowareOne[0];
			}
		}
		Init(&s14KowareCclInfo, 1, 4);
		CCL_INFO* shape = info;

		shape->a        = shape->a * params->scale;
		shape->c        = shape->c * params->scale;
		shape->center.z = shape->center.z * params->scale;
		CalcRange();

		S14KowareParams* scaleParams = (S14KowareParams*)ObjParam->setData.setBuffer;

		if (clump != NULL) {
			KowareFrame* frame = *(KowareFrame**)((u8*)clump + 4);
			RwV3d scale        = s14KowareUnitScale;
			f32 sine;

			scale.z = scale.x = scaleParams->scale;
			fn_8019EC30(frame, &scale, 0);
			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s14KowareOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 2);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
		}
	}
	virtual ~TObjS14Koware();
};

extern "C" void s14KowareCreate(void)
{
	new TObjS14Koware(lbl_8042C110);
}
