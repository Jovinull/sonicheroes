#include "types.h"

// TObjWeight's SetPosition and SetCollisionParameter (the PS2 build's names;
// weightSetPosition and weightSetCollisionParameter here). SetPosition turns
// the weight's model about Y by its angle, scales it and moves it to the
// weight's position. SetCollisionParameter sizes the collision's two shapes
// (their extents and centre heights) by the weight's scale, the first one 2
// smaller across, switches the first off (attribute bit 0x10) and works the
// range out again.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct RwFrame {
	u8 unk00[0x10];     // 0x00
	RwMatrixTag matrix; // 0x10
} RwFrame;

typedef struct WeightModel {
	u8 unk00[0x4];  // 0x00
	RwFrame* frame; // 0x04
} WeightModel;

typedef struct WeightInfo {
	u8 unk00[0x4]; // 0x00
	u32 attr;      // 0x04
	RwV3d center;  // 0x08
	f32 a;         // 0x14
	f32 b;         // 0x18
	f32 c;         // 0x1C
	u8 unk20[0x10];
} WeightInfo; // 0x30

typedef struct Weight {
	u8 unk00[0x30];     // 0x00
	u8 colli[0x10];     // 0x30 (C_COLLI)
	WeightInfo* info;   // 0x40
	u8 unk44[0x94];     // 0x44
	WeightModel* model; // 0xD8
	u8 unkDC[0x8];      // 0xDC
	RwV3d pos;          // 0xE4
	u8 unkF0[0x4];      // 0xF0
	s32 angle;          // 0xF4
	u8 unkF8[0xC];      // 0xF8
	RwV3d scale;        // 0x104
} Weight;

extern "C" const RwV3d AxisY;
extern "C" const f32 weightOne[1];
extern "C" const f32 weightColliMargin[1];
extern "C" WeightInfo weightCclInfo[2];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
extern "C" void CalcRange__7C_COLLIFv(void* colli);

extern "C" void weightSetPosition(Weight* object)
{
	if (object->model != NULL) {
		RwFrame* frame = object->model->frame;
		RwV3d scale;
		f32 sin;

		sin = fn_800D7B00(object->angle);
		fn_80195790(&frame->matrix, &AxisY, weightOne[0] - fn_800D7AE4(object->angle), sin, 0);
		scale.x = object->scale.x;
		scale.y = object->scale.y;
		scale.z = object->scale.z;
		fn_8019EC30(frame, &scale, 1);
		fn_8019EB94(frame, &object->pos, 2);
	}
}

extern "C" void weightSetCollisionParameter(Weight* object)
{
	if (object->info != NULL) {
		object->info[0].a        = object->scale.x * weightCclInfo[0].a - weightColliMargin[0];
		object->info[0].b        = object->scale.y * weightCclInfo[0].b;
		object->info[0].c        = object->scale.z * weightCclInfo[0].c - weightColliMargin[0];
		object->info[0].center.y = object->scale.y * weightCclInfo[0].center.y;
		object->info[1].a        = object->scale.x * weightCclInfo[1].a;
		object->info[1].b        = object->scale.y * weightCclInfo[1].b;
		object->info[1].c        = object->scale.z * weightCclInfo[1].c;
		object->info[1].center.y = object->scale.y * weightCclInfo[1].center.y;
		object->info[0].attr |= 0x10;
		CalcRange__7C_COLLIFv(object->colli);
	}
}
