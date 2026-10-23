#include "types.h"

// TObjTarget::CheckHitPoint (the PS2 build's name, by its place in the PS2
// order; targetCheckHitPoint here): the point is taken into the target's
// frame (turned like SetPosition, at the target's position). A target of kind
// 1 or 3 is marked hit (2), which its set object learns. A point within the
// bull's-eye scores 2, one within reach 1, any other 0.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct TargetSetData {
	u8 unk00[0x10];
	s32 hit; // 0x10
} TargetSetData;

typedef struct TargetFrame {
	u8 unk00[0x30];
	TargetSetData* data; // 0x30
} TargetFrame;

typedef struct Target {
	u8 unk00[0x28];
	TargetFrame* frame; // 0x28, the set object's
	u8 unk2C[0x90];     // 0x2C
	s8 kind;            // 0xBC
	u8 unkBD[0x7];      // 0xBD
	s32 hit;            // 0xC4
	RwV3d pos;          // 0xC8
	s32 angX;           // 0xD4
	s32 angY;           // 0xD8
	s32 angZ;           // 0xDC
	f32 spin;           // 0xE0
} Target;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 targetOne[1];
extern "C" const f32 targetAngleScale[1];
extern "C" const f32 targetBullsEye[1];
extern "C" const f32 targetEscapeReach[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
extern "C" RwMatrixTag* fn_80195B5C(RwMatrixTag* out, const RwMatrixTag* in);
extern "C" void fn_8019941C(RwV3d* out, const RwV3d* in, s32 count, RwMatrixTag* matrix);

extern "C" s32 targetCheckHitPoint(Target* object, const RwV3d* point)
{
	RwMatrixTag matrix;
	RwMatrixTag inverse;
	RwV3d local;
	s32 spin = targetAngleScale[0] * object->spin;
	s32 yaw  = spin + object->angY;

	fn_80195790(&matrix, &AxisY, targetOne[0] - fn_800D7AE4(yaw), fn_800D7B00(yaw), 0);
	fn_80195790(
	    &matrix, &AxisX, targetOne[0] - fn_800D7AE4(object->angX), fn_800D7B00(object->angX), 2);
	fn_80195790(
	    &matrix, &AxisZ, targetOne[0] - fn_800D7AE4(object->angZ), fn_800D7B00(object->angZ), 2);
	fn_80196050(&matrix, &object->pos, 2);
	fn_80195B5C(&inverse, &matrix);
	fn_8019941C(&local, point, 1, &inverse);
	switch (object->kind) {
		case 1:
		case 3:
			object->hit              = 2;
			object->frame->data->hit = object->hit;
			break;
	}
	// read y first, and each square kept on its own (no fused multiply-add)
	f32 y        = local.y;
	f32 x        = local.x;
	f32 xx       = x * x;
	f32 yy       = y * y;
	f32 distance = xx + yy;
	if (distance < targetBullsEye[0]) {
		return 2;
	}
	return distance < targetEscapeReach[0];
}
