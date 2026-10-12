#include "types.h"

// TObjRollDoor's model placement (rollDoorSetPosition here). It turns the door
// model by the placement's angles (Y half a turn further, then X and Z), moves
// it to the door's position and scales it; the third child down the door's
// frame tree keeps its own position and turns about X by the opening amount
// (scaled into an angle). The second model gets the same turn, position and
// scale, then its fixed offset and the same opening turn, and half a turn about
// Y when the door opens the other way.
//
// Every turn works the frame's matrix address out again, as common
// subexpression elimination off gives.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

// The two vector copies are block copies (word loads and stores), as a copy of
// a 12-byte struct without float members gives.
typedef struct RollDoorWords {
	u32 w[3];
} RollDoorWords;

typedef struct RollDoorModel {
	u8 unk00[0x4];
	void* frame; // 0x04
} RollDoorModel;

typedef struct RollDoor {
	u8 unk00[0xC0];
	RwV3d pos;             // 0xC0
	s32 angX;              // 0xCC
	s32 angY;              // 0xD0
	s32 angZ;              // 0xD4
	u8 unkD8[0xC];         // 0xD8
	f32 opening;           // 0xE4
	f32 side;              // 0xE8
	RollDoorModel* model;  // 0xEC
	RollDoorModel* model2; // 0xF0
} RollDoor;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const RwV3d lbl_8_rodata_AC0;
extern "C" const f32 lbl_8_rodata_AE8[1];
extern "C" const f32 lbl_8_rodata_AEC[1];
extern "C" const f32 lbl_8_rodata_B10[1];
extern "C" const f32 lbl_8_rodata_B14[1];
extern "C" f32 lbl_8_data_4618;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EB94(void* frame, const RwV3d* translation, s32 combine);
extern "C" void fn_8019EC30(void* frame, RwV3d* scale, s32 combine);
void* objRwFrameGetChildFrame(struct RwFrame* frame, struct RwFrame* after);

#pragma opt_common_subs off
extern "C" void rollDoorSetPosition(RollDoor* object)
{
	RwV3d scale;
	RwV3d childPos;
	RwV3d offset;
	void* frame = object->model->frame;
	void* child;
	s32 angle;
	f32 sin;
	f32 zero;

	sin = fn_800D7B00(object->angY + 0x8000);
	fn_80195790((u8*)frame + 0x10, &AxisY, lbl_8_rodata_AE8[0] - fn_800D7AE4(object->angY + 0x8000),
	    sin, 0);
	sin = fn_800D7B00(object->angX);
	fn_80195790((u8*)frame + 0x10, &AxisX, lbl_8_rodata_AE8[0] - fn_800D7AE4(object->angX), sin, 2);
	sin = fn_800D7B00(object->angZ);
	fn_80195790((u8*)frame + 0x10, &AxisZ, lbl_8_rodata_AE8[0] - fn_800D7AE4(object->angZ), sin, 2);
	fn_8019EB94(frame, &object->pos, 2);
	scale.x = scale.y = scale.z = lbl_8_data_4618;
	fn_8019EC30(frame, &scale, 1);

	child = objRwFrameGetChildFrame(
	    (struct RwFrame*)objRwFrameGetChildFrame(
	        (struct RwFrame*)objRwFrameGetChildFrame((struct RwFrame*)frame, NULL), NULL),
	    NULL);
	*(RollDoorWords*)&childPos = *(RollDoorWords*)((u8*)child + 0x40);
	angle                      = (s32)(lbl_8_rodata_B10[0] * object->opening);
	sin                        = fn_800D7B00(angle);
	fn_80195790((u8*)child + 0x10, &AxisX, lbl_8_rodata_AE8[0] - fn_800D7AE4(angle), sin, 0);
	fn_8019EB94(child, &childPos, 2);

	frame = object->model2->frame;
	sin   = fn_800D7B00(object->angY + 0x8000);
	fn_80195790((u8*)frame + 0x10, &AxisY, lbl_8_rodata_AE8[0] - fn_800D7AE4(object->angY + 0x8000),
	    sin, 0);
	sin = fn_800D7B00(object->angX);
	fn_80195790((u8*)frame + 0x10, &AxisX, lbl_8_rodata_AE8[0] - fn_800D7AE4(object->angX), sin, 2);
	sin = fn_800D7B00(object->angZ);
	fn_80195790((u8*)frame + 0x10, &AxisZ, lbl_8_rodata_AE8[0] - fn_800D7AE4(object->angZ), sin, 2);
	fn_8019EB94(frame, &object->pos, 2);
	fn_8019EC30(frame, &scale, 1);
	*(RollDoorWords*)&offset = *(const RollDoorWords*)&lbl_8_rodata_AC0;
	fn_8019EB94(frame, &offset, 1);
	sin = fn_800D7B00(angle);
	fn_80195790((u8*)frame + 0x10, &AxisX, lbl_8_rodata_AE8[0] - fn_800D7AE4(angle), sin, 1);
	if (object->side < (zero = lbl_8_rodata_AEC[0])) {
		fn_80195790((u8*)frame + 0x10, &AxisY, lbl_8_rodata_B14[0], zero, 1);
	}
}
#pragma opt_common_subs reset
