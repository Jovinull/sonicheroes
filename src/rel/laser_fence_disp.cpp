#include "types.h"

// TObjLaserfence::Disp (the PS2 build's name, by its place in the PS2 order;
// laserFenceDisp here), the same in the thirteen stage modules that share the
// engine core. Unless the game is paused, the fence model is drawn with the
// placement's light set, twice: turned by the fence's angles and moved to its
// position, and again flipped a half turn about X first. Each time it is
// either drawn once at the fence's radius (kind 3) or, from half the height
// below, once per step up to half the height above, set back by half the
// width. The class is laid out as in rel/laser_fence_tdisp.cpp.

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

typedef struct LaserFenceParam {
	u8 unk00[0x18];
	u32 flags; // 0x18
} LaserFenceParam;

typedef struct LaserFence {
	u8 unk00[0x28];
	LaserFenceParam* param; // 0x28
	u8 unk2C[0x8C];
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
extern "C" RpClump* laserFenceModel;
extern "C" const f32 laserFenceFlip;
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

extern "C" void laserFenceDisp(LaserFence* object)
{
	RwV3d offset;
	RwV3d front;
	RwV3d back;
	RwFrame* frame;

	if ((s8)lbl_8042C180[0x20] != 0) {
		return;
	}
	lbl_802D5E80.SetCurrentNum(((object->param->flags & 0x1C0000) >> 18) + 4);
	lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
	frame = laserFenceModel->frame;
	fn_80195790(&frame->modelling, &AxisY, laserFenceOne[0] - fn_800D7AE4(object->angY),
	    fn_800D7B00(object->angY), 0);
	fn_80195790(&frame->modelling, &AxisX, laserFenceOne[0] - fn_800D7AE4(object->angX),
	    fn_800D7B00(object->angX), 2);
	fn_80195790(&frame->modelling, &AxisZ, laserFenceOne[0] - fn_800D7AE4(object->angZ),
	    fn_800D7B00(object->angZ), 2);
	fn_8019EB94(frame, &object->pos, 2);
	{
		f32 length;
		f32 half;
		f32 at;

		switch (object->kind) {
			case 0:
			case 1:
			case 2:
			case 4: {
				half     = laserFenceHalf[0] * object->height;
				at       = -half;
				offset.x = at;
				offset.y = laserFenceHalf[0] * -object->width;
				offset.z = laserFenceMinEdit[0];
				fn_8019EB94(frame, &offset, 1);
				// read twice through the pointer, as the retail does (a
				// plain read is shared)
				const volatile f32* size = laserFenceMinSize;
				front.x                  = *size;
				front.z = front.y = laserFenceMinEdit[0];
				length            = *size;
				do {
					fn_8014FF2C(laserFenceModel);
					fn_8019EB94(frame, &front, 1);
				} while ((at += length) <= half);
				break;
			}
			case 3:
				offset.x = object->radius;
				offset.y = laserFenceHalf[0] * -object->width;
				offset.z = laserFenceMinEdit[0];
				fn_8019EB94(frame, &offset, 1);
				fn_8014FF2C(laserFenceModel);
				break;
		}
	}
	frame = laserFenceModel->frame;
	fn_80195790(&frame->modelling, &AxisX, laserFenceFlip, laserFenceMinEdit[0], 0);
	fn_80195790(&frame->modelling, &AxisY, laserFenceOne[0] - fn_800D7AE4(object->angY),
	    fn_800D7B00(object->angY), 2);
	fn_80195790(&frame->modelling, &AxisX, laserFenceOne[0] - fn_800D7AE4(object->angX),
	    fn_800D7B00(object->angX), 2);
	fn_80195790(&frame->modelling, &AxisZ, laserFenceOne[0] - fn_800D7AE4(object->angZ),
	    fn_800D7B00(object->angZ), 2);
	fn_8019EB94(frame, &object->pos, 2);
	{
		f32 half;
		f32 at;
		f32 length;

		switch (object->kind) {
			case 0:
			case 1:
			case 2:
			case 4: {
				half     = laserFenceHalf[0] * object->height;
				at       = -half;
				offset.x = at;
				offset.y = laserFenceHalf[0] * -object->width;
				offset.z = laserFenceMinEdit[0];
				fn_8019EB94(frame, &offset, 1);
				// read twice through the pointer, as the retail does (a
				// plain read is shared)
				const volatile f32* size = laserFenceMinSize;
				back.x                   = *size;
				back.z = back.y = laserFenceMinEdit[0];
				length          = *size;
				do {
					fn_8014FF2C(laserFenceModel);
					fn_8019EB94(frame, &back, 1);
				} while ((at += length) <= half);
				break;
			}
			case 3:
				offset.x = object->radius;
				offset.y = laserFenceHalf[0] * -object->width;
				offset.z = laserFenceMinEdit[0];
				fn_8019EB94(frame, &offset, 1);
				fn_8014FF2C(laserFenceModel);
				break;
		}
	}
	if (object->state == 3) {
		return;
	}
}
