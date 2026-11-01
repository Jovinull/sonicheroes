#include "types.h"

// The checkpoint star's move step (checkpointStarMove here; rel/checkpoint_star.cpp
// and the Exec call it), the same in the thirteen stage modules that share the
// engine core: the star drifts by its spin, which damps; its matrix is built
// from its angles and position (the inverse is kept), and its two models are
// placed: the star turned in its frames by its own spin angles, the effect
// facing a quarter turn off the star's heading. Both are scaled by the star's
// size.

typedef struct RwMatrixTag {
	u8 data[0x40];
} RwMatrixTag;

typedef struct RwFrame {
	u8 unk00[0x10];
	RwMatrixTag modelling; // 0x10
} RwFrame;

struct RpClump {
	u8 unk0[0x4];
	RwFrame* frame; // 0x04
};

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct Checkpoint {
	u8 unk00[0x38];
	RwV3d pos;  // 0x38
	sAngle ang; // 0x44
} Checkpoint;

typedef struct CheckpointStar {
	s32 mode;           // 0x00
	RwV3d pos;          // 0x04
	sAngle ang;         // 0x10
	RwV3d spin;         // 0x1C
	s16 unk28;          // 0x28
	s16 id;             // 0x2A
	Checkpoint* owner;  // 0x2C
	RpClump* model;     // 0x30
	RpClump* effect;    // 0x34
	RwMatrixTag matrix; // 0x38
	f32 alpha;          // 0x78
	s32 unk7C;          // 0x7C
	s32 unk80;          // 0x80
	f32 scale;          // 0x84
	s32 unk88;          // 0x88
	s32 unk8C;          // 0x8C
	s32 unk90;          // 0x90
} CheckpointStar;

extern "C" const f32 checkpointOne[1];
extern "C" const f32 checkpointStarDamping;
extern "C" RwV3d checkpointStarOffset;
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, const RwV3d* translation, s32 combine);
extern "C" void fn_80195B5C(RwMatrixTag* out, const RwMatrixTag* in);
extern "C" void fn_8019EB94(RwFrame* frame, const RwV3d* translation, s32 combine);
extern "C" void fn_8019ECCC(RwFrame* frame, const RwMatrixTag* matrix, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, const RwV3d* scale, s32 combine);
extern "C" void fn_8019E880(RwFrame* frame);
RwFrame* objRwFrameGetChildFrame(RwFrame* frame, RwFrame* after);

extern "C" void checkpointStarMove(CheckpointStar* star)
{
	RwMatrixTag matrix;
	RwV3d scale;
	RwFrame* frame;

	star->pos.x += star->spin.x;
	star->pos.y += star->spin.y;
	star->pos.z += star->spin.z;
	star->spin.x *= checkpointStarDamping;
	star->spin.y *= checkpointStarDamping;
	star->spin.z *= checkpointStarDamping;
	fn_80195790(
	    &matrix, &AxisY, checkpointOne[0] - fn_800D7AE4(star->ang.y), fn_800D7B00(star->ang.y), 0);
	fn_80195790(
	    &matrix, &AxisX, checkpointOne[0] - fn_800D7AE4(star->ang.x), fn_800D7B00(star->ang.x), 2);
	fn_80195790(
	    &matrix, &AxisZ, checkpointOne[0] - fn_800D7AE4(star->ang.z), fn_800D7B00(star->ang.z), 2);
	fn_80196050(&matrix, &star->pos, 2);
	fn_80195B5C(&star->matrix, &matrix);

	frame = star->model->frame;
	fn_8019EB94(frame, &checkpointStarOffset, 0);
	fn_8019ECCC(frame, &matrix, 2);
	scale.x = scale.y = star->scale;
	scale.z           = checkpointOne[0];
	fn_8019EC30(frame, &scale, 1);
	frame = objRwFrameGetChildFrame(frame, NULL);
	fn_80195790(&frame->modelling, &AxisY,
	    checkpointOne[0] - fn_800D7AE4(star->unk7C + star->unk88),
	    fn_800D7B00(star->unk7C + star->unk88), 0);
	fn_8019E880(frame);
	frame = objRwFrameGetChildFrame(frame, NULL);
	fn_80195790(&frame->modelling, &AxisZ, checkpointOne[0] - fn_800D7AE4(star->unk90),
	    fn_800D7B00(star->unk90), 0);
	fn_80195790(&frame->modelling, &AxisY,
	    checkpointOne[0] - fn_800D7AE4((star->unk8C - star->unk7C) - (star->unk7C + star->unk88)),
	    fn_800D7B00((star->unk8C - star->unk7C) - (star->unk7C + star->unk88)), 2);
	fn_8019E880(frame);

	frame = star->effect->frame;
	fn_8019EB94(frame, &checkpointStarOffset, 0);
	fn_80195790(&frame->modelling, &AxisY,
	    checkpointOne[0] - fn_800D7AE4(star->ang.y + star->unk8C - star->unk7C + 0x4000),
	    fn_800D7B00(star->ang.y + star->unk8C - star->unk7C + 0x4000), 2);
	fn_80195790(&frame->modelling, &AxisX, checkpointOne[0] - fn_800D7AE4(star->ang.x),
	    fn_800D7B00(star->ang.x), 2);
	fn_80195790(&frame->modelling, &AxisZ, checkpointOne[0] - fn_800D7AE4(star->ang.z),
	    fn_800D7B00(star->ang.z), 2);
	fn_8019EB94(frame, &star->pos, 2);
	scale.z = scale.x;
	fn_8019EC30(frame, &scale, 1);
}
