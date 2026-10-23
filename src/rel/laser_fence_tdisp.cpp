#include "types.h"

// TObjLaserfence::TDisp (the PS2 build's name, by its place in the PS2 order;
// laserFenceTDisp here). Unless the game is paused or the fence is off
// (state 3), the laser model is drawn with light set 0x10 and render states
// 0xA, 0xB and 0xE set to 2, 2 and 0 (the old values put back after): scaled
// to the fence's width, turned by its angles and moved to its position, then
// either drawn once at its radius (kind 3) or, from half the height below,
// drawn once per step of 5 up to half the height above.

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

typedef struct LaserFence {
	u8 unk00[0xB8];
	s32 kind;   // 0xB8
	s32 state;  // 0xBC
	RwV3d pos;  // 0xC0
	s32 angX;   // 0xCC
	s32 angY;   // 0xD0
	s32 angZ;   // 0xD4
	f32 width;  // 0xD8
	f32 height; // 0xDC
	f32 radius; // 0xE0
} LaserFence;

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

extern "C" u8* lbl_8042C180;
extern "C" CLIGHT lbl_802D5E80;
extern "C" RpClump* laserFenceLaser;
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 laserFenceWidthScale[1];
extern "C" const f32 laserFenceOne[1];
extern "C" const f32 laserFenceHalf[1];
extern "C" const f32 laserFenceMinEdit[1];
extern "C" const f32 laserFenceMinSize[1];

extern "C" void fn_80194294(s32 state, s32* value);
extern "C" void fn_80194234(s32 state, s32 value);
extern "C" void fn_8014FF2C(RpClump* clump);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);

extern "C" void laserFenceTDisp(LaserFence* object)
{
	if ((s8)lbl_8042C180[0x20] == 0 && object->state != 3) {
		s32 state0A;
		s32 state0B;
		s32 state0E;
		RwV3d offset;
		RwV3d scale;
		RwV3d step;

		lbl_802D5E80.SetCurrentNum(0x10);
		lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
		fn_80194294(0xA, &state0A);
		fn_80194294(0xB, &state0B);
		fn_80194294(0xE, &state0E);
		fn_80194234(0xA, 2);
		fn_80194234(0xB, 2);
		fn_80194234(0xE, 0);
		RwFrame* frame = laserFenceLaser->frame;
		scale.y        = laserFenceWidthScale[0] * object->width;
		scale.x = scale.z = laserFenceOne[0];
		fn_8019EC30(frame, &scale, 0);
		fn_80195790(&frame->modelling, &AxisY, laserFenceOne[0] - fn_800D7AE4(object->angY),
		    fn_800D7B00(object->angY), 2);
		fn_80195790(&frame->modelling, &AxisX, laserFenceOne[0] - fn_800D7AE4(object->angX),
		    fn_800D7B00(object->angX), 2);
		fn_80195790(&frame->modelling, &AxisZ, laserFenceOne[0] - fn_800D7AE4(object->angZ),
		    fn_800D7B00(object->angZ), 2);
		fn_8019EB94(frame, &object->pos, 2);
		switch (object->kind) {
			case 0:
			case 1:
			case 2:
			case 4: {
				f32 length;
				f32 half = laserFenceHalf[0] * object->height;
				f32 at   = -half;

				offset.x = at;
				offset.y = offset.z = laserFenceMinEdit[0];
				fn_8019EB94(frame, &offset, 1);
				// read twice through the pointer, as the retail does (a
				// plain read is shared)
				const volatile f32* size = laserFenceMinSize;
				step.x                   = *size;
				step.y = step.z = laserFenceMinEdit[0];
				length          = *size;
				do {
					fn_8014FF2C(laserFenceLaser);
					fn_8019EB94(frame, &step, 1);
				} while ((at += length) <= half);
				break;
			}
			case 3:
				offset.x = object->radius;
				offset.y = offset.z = laserFenceMinEdit[0];
				fn_8019EB94(frame, &offset, 1);
				fn_8014FF2C(laserFenceLaser);
				break;
		}
		fn_80194234(0xE, state0E);
		fn_80194234(0xA, state0A);
		fn_80194234(0xB, state0B);
	}
}
