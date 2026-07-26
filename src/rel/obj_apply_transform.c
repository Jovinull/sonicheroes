#include "types.h"

// Pushes an object's placement onto the model it drives: three rotations, then
// the position.
//
// The claim is .text 0x7E20 to 0x7EB0 and nothing else. Everything it touches
// is a DOL symbol, so there is no data to take and nothing to rename per
// module.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out.
//
// The three constants the rotations are given are the unit axes the DOL keeps
// at .rodata 0x80239978 and after: {1,0,0}, {0,1,0} and {0,0,1}. So the order
// is yaw first with mode zero, then pitch and roll with mode two.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Handle {
	u8 unk0[0x4]; // 0x00
	void* model;  // 0x04
} Handle;

typedef struct Object {
	u8 unk0[0x40];  // 0x00
	Vec3 position;  // 0x40
	f32 pitch;      // 0x4C
	f32 yaw;        // 0x50
	f32 roll;       // 0x54
	u8 unk58[0x8];  // 0x58
	Handle* handle; // 0x60
} Object;

extern "C" const Vec3 lbl_80239978; // {1, 0, 0}
extern "C" const Vec3 lbl_80239984; // {0, 1, 0}
extern "C" const Vec3 lbl_80239990; // {0, 0, 1}

extern "C" void fn_8019EB94(void* model, const Vec3* position, s32 mode);
extern "C" void fn_8019ED68(void* model, const Vec3* axis, f32 angle, s32 mode);

extern "C" void objApplyTransform(Object* object)
{
	void* model = object->handle->model;

	fn_8019ED68(model, &lbl_80239984, object->yaw, 0);
	fn_8019ED68(model, &lbl_80239978, object->pitch, 2);
	fn_8019ED68(model, &lbl_80239990, object->roll, 2);
	fn_8019EB94(model, &object->position, 2);
}
