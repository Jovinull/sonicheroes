#include "types.h"

// TObjPole's SetPosition and SetCollisionParameter (the PS2 build's names, in
// its order; poleSetPosition and poleSetCollisionParameter here). SetPosition
// turns the pole's frame by its angles and moves it to its position, stretches
// the shaft (the grandchild frame) to the pole's height and puts the top (the
// next child) back to its size at the top of the shaft. SetCollisionParameter
// sizes the three collision shapes to the height and the radius.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

struct RwFrame {
	u8 unk00[0x10];
	RwMatrixTag modelling; // 0x10
};

typedef struct RpClump {
	u8 unk0[0x4];
	RwFrame* frame; // 0x04
} RpClump;

typedef struct PoleShape {
	u8 unk00[0xC];
	f32 centerY; // 0x0C
	u8 unk10[0x4];
	f32 a; // 0x14
	f32 b; // 0x18
	u8 unk1C[0x14];
} PoleShape; // 0x30

typedef struct Pole {
	u8 unk000[0x30];
	u8 colli[0x10];  // 0x030 (C_COLLI)
	PoleShape* info; // 0x040
	u8 unk044[0x78]; // 0x044
	RwV3d pos;       // 0x0BC
	s32 angX;        // 0x0C8
	s32 angY;        // 0x0CC
	s32 angZ;        // 0x0D0
	u8 unk0D4[0x8];  // 0x0D4
	f32 radius;      // 0x0DC
	u8 unk0E0[0x4];  // 0x0E0
	f32 height;      // 0x0E4
	u8 unk0E8[0x24]; // 0x0E8
	RpClump* model;  // 0x10C
} Pole;

extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 poleOne[1];
extern "C" const f32 poleZero[1];
extern "C" const f32 poleShaftScale[1];
extern "C" const f32 poleHalf[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
extern "C" void CalcRange__7C_COLLIFv(void* colli);
RwFrame* objRwFrameGetChildFrame(RwFrame* frame, RwFrame* after);

extern "C" void poleSetPosition(Pole* object)
{
	RwFrame* frame = object->model->frame;
	RwV3d scale;
	RwV3d offset;

	fn_80195790(&frame->modelling, &AxisZ, poleOne[0] - fn_800D7AE4(object->angZ),
	    fn_800D7B00(object->angZ), 0);
	fn_80195790(&frame->modelling, &AxisY, poleOne[0] - fn_800D7AE4(object->angY),
	    fn_800D7B00(object->angY), 2);
	fn_8019EB94(frame, &object->pos, 2);
	frame   = objRwFrameGetChildFrame(objRwFrameGetChildFrame(frame, NULL), NULL);
	scale.x = poleOne[0];
	scale.y = poleShaftScale[0] * object->height;
	scale.z = poleOne[0];
	fn_8019EC30(frame, &scale, 0);
	frame    = objRwFrameGetChildFrame(frame, NULL);
	f32 inv  = poleOne[0] / scale.y;
	scale.y  = inv;
	offset.x = poleZero[0];
	offset.y = object->height * inv;
	offset.z = poleZero[0];
	fn_8019EC30(frame, &scale, 0);
	fn_8019EB94(frame, &offset, 2);
}

extern "C" void poleSetCollisionParameter(Pole* object)
{
	if (object->info != NULL) {
		object->info[0].centerY = poleHalf[0] * object->height;
		object->info[0].b       = poleHalf[0] * object->height;
		object->info[1].centerY = poleHalf[0] * object->height;
		object->info[1].b       = poleHalf[0] * object->height;
		object->info[1].a       = object->radius;
		object->info[2].centerY = object->height;
		CalcRange__7C_COLLIFv(object->colli);
	}
}
