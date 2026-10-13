#include "types.h"

// The propeller's model placement (propellerSetPosition here), the out-of-line
// copy nothing calls. The base model turns by the placement's angles (Y, X, Z)
// and moves to the placement. The two upper models take the propeller's size as
// their scale and the first fixed offset; the blade model also spins about Y by
// its own angle. Both then turn by the head's angles, take the second fixed
// offset and move to the head's position.
//
// Every turn works the frame's matrix address out again, as common
// subexpression elimination off gives.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct PropellerModel {
	u8 unk00[0x4];
	void* frame; // 0x04
} PropellerModel;

typedef struct Propeller {
	u8 unk00[0xC0];
	RwV3d pos;                 // 0xC0
	s32 angX;                  // 0xCC
	s32 angY;                  // 0xD0
	s32 angZ;                  // 0xD4
	f32 size;                  // 0xD8
	s32 spin;                  // 0xDC
	u8 unkE0[0x4];             // 0xE0
	RwV3d headPos;             // 0xE4
	s32 headAngX;              // 0xF0
	s32 headAngY;              // 0xF4
	s32 headAngZ;              // 0xF8
	u8 unkFC[0x54];            // 0xFC
	PropellerModel* models[3]; // 0x150
} Propeller;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const RwV3d propellerArmOffset;
extern "C" const RwV3d propellerHeadOffset;
extern "C" const f32 propellerOne[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EB94(void* frame, const RwV3d* translation, s32 combine);
extern "C" void fn_8019EC30(void* frame, RwV3d* scale, s32 combine);

#pragma opt_common_subs off
extern "C" void propellerSetPosition(Propeller* object)
{
	RwV3d scale;
	void* frame;
	f32 sin;

	scale.x = scale.y = scale.z = object->size;

	frame = object->models[0]->frame;
	sin   = fn_800D7B00(object->angY);
	fn_80195790((u8*)frame + 0x10, &AxisY, propellerOne[0] - fn_800D7AE4(object->angY), sin, 0);
	sin = fn_800D7B00(object->angX);
	fn_80195790((u8*)frame + 0x10, &AxisX, propellerOne[0] - fn_800D7AE4(object->angX), sin, 2);
	sin = fn_800D7B00(object->angZ);
	fn_80195790((u8*)frame + 0x10, &AxisZ, propellerOne[0] - fn_800D7AE4(object->angZ), sin, 2);
	fn_8019EB94(frame, &object->pos, 2);

	frame = object->models[1]->frame;
	fn_8019EC30(frame, &scale, 0);
	fn_8019EB94(frame, &propellerArmOffset, 2);
	sin = fn_800D7B00(object->headAngY);
	fn_80195790((u8*)frame + 0x10, &AxisY, propellerOne[0] - fn_800D7AE4(object->headAngY), sin, 2);
	sin = fn_800D7B00(object->headAngX);
	fn_80195790((u8*)frame + 0x10, &AxisX, propellerOne[0] - fn_800D7AE4(object->headAngX), sin, 2);
	sin = fn_800D7B00(object->headAngZ);
	fn_80195790((u8*)frame + 0x10, &AxisZ, propellerOne[0] - fn_800D7AE4(object->headAngZ), sin, 2);
	fn_8019EB94(frame, &propellerHeadOffset, 2);
	fn_8019EB94(frame, &object->headPos, 2);

	frame = object->models[2]->frame;
	fn_8019EC30(frame, &scale, 0);
	fn_8019EB94(frame, &propellerArmOffset, 2);
	sin = fn_800D7B00(object->spin);
	fn_80195790((u8*)frame + 0x10, &AxisY, propellerOne[0] - fn_800D7AE4(object->spin), sin, 2);
	sin = fn_800D7B00(object->headAngY);
	fn_80195790((u8*)frame + 0x10, &AxisY, propellerOne[0] - fn_800D7AE4(object->headAngY), sin, 2);
	sin = fn_800D7B00(object->headAngX);
	fn_80195790((u8*)frame + 0x10, &AxisX, propellerOne[0] - fn_800D7AE4(object->headAngX), sin, 2);
	sin = fn_800D7B00(object->headAngZ);
	fn_80195790((u8*)frame + 0x10, &AxisZ, propellerOne[0] - fn_800D7AE4(object->headAngZ), sin, 2);
	fn_8019EB94(frame, &propellerHeadOffset, 2);
	fn_8019EB94(frame, &object->headPos, 2);
}
#pragma opt_common_subs reset
