#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s13KankyohakaiCreate, the editor record factory for TObjS13ShipDestroy (the
// class name its constructor stores) in stage13D. It is a real new-expression
// of the class; rel/sample1_create.cpp has the long form of the allocation.
//
// The set data keeps a work word: when it is there and 1 (the ship was already
// destroyed), the object starts in state 6 and builds the wrecked clump (model
// 4) instead of the whole one (model 0); when it is not there, a cleared one
// is made. Either clump goes through the module's atomic callback
// (fn_9_885A8), and its frame is turned by the placement's Y angle and moved
// to the placement's position.

// The part of a RenderWare frame used here: its modelling matrix.
struct ShipDestroyFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

extern "C" char* CL_TObjS13ShipDestroy;
extern "C" u32 s13KankyohakaiModels[];
extern "C" const f32 s13KankyohakaiOne[1];
extern "C" const RwV3d AxisY;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75A80(void* info, s32 index, RpClump** clump, s32 flags);
extern "C" void* fn_9_885A8(void* atomic);
extern "C" void fn_8014FFBC(RpClump* clump, void* (*callback)(void*), void* data);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

class TObjS13ShipDestroy : public TObject, public TObjSetObj
{
public:
	s8 state; // 0x30
	u8 pad31;
	s16 unk32;      // 0x32
	RpClump* clump; // 0x34

	TObjS13ShipDestroy(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS13ShipDestroy;
		DispTime  = 0x38;
		state     = 0;
		if (ObjParam->originalWork != NULL) {
			if (*(s32*)ObjParam->originalWork == 1) {
				state = 6;
			}
		} else {
			s32* work              = new s32;
			ObjParam->originalWork = work;
			*work                  = 0;
		}
		if (state == 6) {
			fn_9_75A80(s13KankyohakaiModels, 4, &clump, 0);
			fn_8014FFBC(clump, fn_9_885A8, NULL);
			if (clump != NULL) {
				ShipDestroyFrame* frame = *(ShipDestroyFrame**)((u8*)clump + 4);
				f32 sine;

				sine = fn_800D7B00(ObjParam->setData.ang.y);
				fn_80195790(frame->modelling, &AxisY,
				    s13KankyohakaiOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
				fn_8019E880(frame);
				fn_8019EB94(frame, &ObjParam->setData.pos, 2);
			}
		} else {
			fn_9_75A80(s13KankyohakaiModels, 0, &clump, 0);
			fn_8014FFBC(clump, fn_9_885A8, NULL);
			if (clump != NULL) {
				ShipDestroyFrame* frame = *(ShipDestroyFrame**)((u8*)clump + 4);
				f32 sine;

				sine = fn_800D7B00(ObjParam->setData.ang.y);
				fn_80195790(frame->modelling, &AxisY,
				    s13KankyohakaiOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
				fn_8019E880(frame);
				fn_8019EB94(frame, &ObjParam->setData.pos, 2);
			}
		}
		unk32 = 0;
	}
	virtual ~TObjS13ShipDestroy();
};

extern "C" void s13KankyohakaiCreate(void)
{
	new TObjS13ShipDestroy(lbl_8042C110);
}
