#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s14dSearchLightCreate, the editor record factory for TObjS14SearchLight (the
// class name its constructor stores) in stage13D. It is a real new-expression
// of the class; rel/sample1_create.cpp has the long form of the allocation.
//
// While the editor is on, a set data with no length or no width gets 1. The
// constructor clears its time, takes its model from the module's table
// through fn_9_75D2C and, when the table has an animation after it (+0x14),
// starts it through fn_9_757C4. Its position is the placement's, 35000 lower,
// and its scale the width across and the length down; with the model, the
// frame is scaled, turned by the placement's Y, X and Z angles and moved to
// that position.

// The part of a RenderWare frame used here: its modelling matrix.
struct SearchLightFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

// the set data's parameters
struct S14dSearchLightParams {
	f32 length; // 0x00
	f32 width;  // 0x04
};

// the module's table: the model entry, then the animation entry
struct S14dSearchLightTable {
	u8 model[0x14];
	struct {
		s8 type; // 0x14
	} animation;
};

extern "C" char* CL_TObjS14SearchLight;
extern "C" s8 s14dSearchLightModels[];
extern "C" const f32 s14dSearchLightEditMin[1];
extern "C" const f32 s14dSearchLightOne[1];
extern "C" const f32 s14dSearchLightDrop[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75D2C(void* table, s16 index, RpClump** clump, void* frame);
extern "C" void fn_9_757C4(RpClump* clump, void* animation, void* state);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);
extern "C" void fn_8019EC30(void* frame, RwV3d* scale, s32 combine);

class TObjS14SearchLight : public TObject, public TObjSetObj
{
public:
	f32 time;       // 0x30
	RwV3d pos;      // 0x34
	RwV3d scale;    // 0x40
	RpClump* clump; // 0x4C

	TObjS14SearchLight(TObject* parent)
	    : TObject(parent)
	{
		S14dSearchLightParams* params = (S14dSearchLightParams*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS14SearchLight;
		DispTime  = 0x50;
		if (OnEdit()) {
			if (s14dSearchLightEditMin[0] == params->length) {
				params->length = s14dSearchLightOne[0];
			}
			if (s14dSearchLightEditMin[0] == params->width) {
				params->width = s14dSearchLightOne[0];
			}
		}
		time = s14dSearchLightEditMin[0];
		fn_9_75D2C(s14dSearchLightModels, 0, &clump, NULL);
		S14dSearchLightTable* table = (S14dSearchLightTable*)s14dSearchLightModels;

		if (table->animation.type != 0) {
			fn_9_757C4(clump, &table->animation, NULL);
		}
		pos     = ObjParam->setData.pos;
		pos.y   = pos.y - s14dSearchLightDrop[0];
		scale.x = scale.z = params->width;
		scale.y           = params->length;
		if (clump != NULL) {
			SearchLightFrame* frame = *(SearchLightFrame**)((u8*)clump + 4);
			f32 sine;

			fn_8019EC30(frame, &scale, 0);
			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s14dSearchLightOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 2);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.x);
			fn_80195790(frame->modelling, &AxisX,
			    s14dSearchLightOne[0] - fn_800D7AE4(ObjParam->setData.ang.x), sine, 2);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.z);
			fn_80195790(frame->modelling, &AxisZ,
			    s14dSearchLightOne[0] - fn_800D7AE4(ObjParam->setData.ang.z), sine, 2);
			fn_8019E880(frame);
			fn_8019EB94(frame, &pos, 2);
		}
	}
	virtual ~TObjS14SearchLight();
};

extern "C" void s14dSearchLightCreate(void)
{
	new TObjS14SearchLight(lbl_8042C110);
}
