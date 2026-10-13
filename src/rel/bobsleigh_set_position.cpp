#include "types.h"

// TObjBobsleigh::SetPosition (the PS2 build's name): moves the sled's model
// frame to the sled and turns it by the sled's Z, X and Y angles and then by
// the path's; the same turns (without the move) give the seat angles; with a
// rider frame (0x344) it keeps where that frame lands on the sled (0x2C4).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwMatrixTag {
	RwV3d right; // 0x00
	u32 flags;   // 0x0C
	RwV3d up;    // 0x10
	u32 pad1;    // 0x1C
	RwV3d at;    // 0x20
	u32 pad2;    // 0x2C
	RwV3d pos;   // 0x30
	u32 pad3;    // 0x3C
} RwMatrixTag;

typedef struct RwFrame {
	u8 unk00[0x10];
	RwMatrixTag modelling; // 0x10
} RwFrame;

typedef struct RpClump {
	u8 unk00[0x4];
	RwFrame* frame; // 0x04
} RpClump;

typedef struct Bobsleigh {
	u8 unk000[0x104];
	RwV3d pos;    // 0x104
	s32 pathAngX; // 0x110
	s32 pathAngY; // 0x114
	s32 pathAngZ; // 0x118
	u8 unk11C[0xC];
	s32 seatAngX; // 0x128
	s32 seatAngY; // 0x12C
	s32 seatAngZ; // 0x130
	u8 unk134[0xCC];
	s32 angX; // 0x200
	s32 angY; // 0x204
	s32 angZ; // 0x208
	u8 unk20C[0xB8];
	RwV3d riderPos; // 0x2C4
	u8 unk2D0[0x40];
	RpClump* clump; // 0x310
	u8 unk314[0x30];
	RwFrame* rider; // 0x344
} Bobsleigh;

extern "C" const f32 bobsleighOne[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern RwMatrixTag* pCurrentMatrix;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
extern "C" void fn_80195674(RwMatrixTag* out, RwMatrixTag* a, RwMatrixTag* b);
void GetRotYXZ(RwMatrixTag* matrix, s32* x, s32* y, s32* z);

static inline RwV3d* bobsleighMatrixPos(RwMatrixTag* matrix)
{
	return matrix == NULL ? &pCurrentMatrix->pos : &matrix->pos;
}

static inline void bobsleighTurn(RwMatrixTag* matrix, Bobsleigh* object, s32 combine)
{
	fn_80195790(matrix, &AxisZ, bobsleighOne[0] - fn_800D7AE4(object->angZ),
	    fn_800D7B00(object->angZ), combine);
	fn_80195790(
	    matrix, &AxisX, bobsleighOne[0] - fn_800D7AE4(object->angX), fn_800D7B00(object->angX), 1);
	fn_80195790(
	    matrix, &AxisY, bobsleighOne[0] - fn_800D7AE4(object->angY), fn_800D7B00(object->angY), 1);
	fn_80195790(matrix, &AxisZ, bobsleighOne[0] - fn_800D7AE4(object->pathAngZ),
	    fn_800D7B00(object->pathAngZ), 1);
	fn_80195790(matrix, &AxisX, bobsleighOne[0] - fn_800D7AE4(object->pathAngX),
	    fn_800D7B00(object->pathAngX), 1);
	fn_80195790(matrix, &AxisY, bobsleighOne[0] - fn_800D7AE4(object->pathAngY),
	    fn_800D7B00(object->pathAngY), 1);
}

extern "C" void SetPosition__13TObjBobsleighFv(Bobsleigh* object)
{
	RwMatrixTag matrix;
	RwMatrixTag rider;
	RwFrame* frame = object->clump->frame;

	fn_8019EB94(frame, &object->pos, 0);
	bobsleighTurn(&frame->modelling, object, 1);
	bobsleighTurn(&matrix, object, 0);
	GetRotYXZ(&matrix, &object->seatAngX, &object->seatAngY, &object->seatAngZ);
	if (object->rider != NULL) {
		fn_80195674(&rider, &object->rider->modelling, &frame->modelling);
		object->riderPos = *bobsleighMatrixPos(&rider);
	}
}
