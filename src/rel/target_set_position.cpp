#include "types.h"

// TObjTarget::SetPosition (the PS2 build's name, by its place in the PS2
// order; targetSetPosition here): the target's frame is turned about Y by its
// heading plus its spin, then by its pitch and roll, and moved to its
// position.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct RwFrame {
	u8 unk00[0x10];
	RwMatrixTag modelling; // 0x10
} RwFrame;

typedef struct RpClump {
	u8 unk0[0x4];
	RwFrame* frame; // 0x04
} RpClump;

typedef struct Target {
	u8 unk00[0xC8];
	RwV3d pos;      // 0xC8
	s32 angX;       // 0xD4
	s32 angY;       // 0xD8
	s32 angZ;       // 0xDC
	f32 spin;       // 0xE0
	u8 unkE4[0x8];  // 0xE4
	RpClump* model; // 0xEC
} Target;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 targetOne[1];
extern "C" const f32 targetAngleScale[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);

extern "C" void targetSetPosition(Target* object)
{
	if (object->model != NULL) {
		RwFrame* frame = object->model->frame;
		s32 spin       = targetAngleScale[0] * object->spin;
		s32 yaw        = spin + object->angY;

		fn_80195790(
		    &frame->modelling, &AxisY, targetOne[0] - fn_800D7AE4(yaw), fn_800D7B00(yaw), 0);
		fn_80195790(&frame->modelling, &AxisX, targetOne[0] - fn_800D7AE4(object->angX),
		    fn_800D7B00(object->angX), 2);
		fn_80195790(&frame->modelling, &AxisZ, targetOne[0] - fn_800D7AE4(object->angZ),
		    fn_800D7B00(object->angZ), 2);
		fn_8019EB94(frame, &object->pos, 2);
	}
}
