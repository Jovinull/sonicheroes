// TObjChao::SetPosition (the PS2 build's name): the chao takes its position
// from the cage's work block when SearchCage made one, turns by its spin and
// places its frame there; away from a cage it also moves out by its offset and
// turns a quarter towards the side its spin goes. It then keeps the frame's
// position and scales the frame by the module's 0.75. Exec inlines it; this
// copy has no caller and is kept with force_active. The class is in
// chao_class.inc.

#include "src/rel/chao_class.inc"
#include "game/object.h"

struct ChaoWork {
	u32 magic; // 0x00
	RwV3d pos; // 0x04
	u32 unk10; // 0x10
};

extern "C" const f32 chaoZero[1];
extern "C" const f32 chaoQuarter[1];
extern "C" const f32 chaoMinusQuarter[1];
extern "C" f32 chaoScale;
extern "C" RwV3d AxisY;
extern RwMatrix* pCurrentMatrix;
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
extern "C" void fn_8019ED68(RwFrame* frame, RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);

void TObjChao::SetPosition()
{
	s32 inCage     = 0;
	ChaoWork* work = (ChaoWork*)ObjParam->originalWork;

	if (work != NULL && work->magic == 0x12345678) {
		pos    = work->pos;
		inCage = 1;
	}

	RwFrame* frame = (RwFrame*)((RwObject*)clump)->parent;
	angle += spin;
	fn_8019EB94(frame, &pos, 0);
	fn_8019ED68(frame, &AxisY, angle, 1);
	if (!inCage) {
		RwV3d out;
		out.x = out.y = chaoZero[0];
		out.z         = offset;
		fn_8019EB94(frame, &out, 1);
		fn_8019ED68(frame, &AxisY, spin > chaoZero[0] ? chaoQuarter[0] : chaoMinusQuarter[0], 1);
	}

	// The shared matrix-position convention substitutes the current matrix for null.
	worldPos = (!&frame->modelling) ? pCurrentMatrix->pos : frame->modelling.pos;

	RwV3d scale;
	scale.x = scale.y = scale.z = chaoScale;
	fn_8019EC30(frame, &scale, 1);
}
