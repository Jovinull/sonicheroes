#include "types.h"

// Rebuilds the switch model transforms from its three rotation channels and
// position. A target carrying the engine sentinel may first override that
// position. The secondary model receives the switch direction in the primary
// model's local space, and the same vector is published to the collision frame.
//
// The claim is .text 0x43D8 to 0x4580. The routine is identical in the thirteen
// stage modules that share the common object engine.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Target {
	u32 sentinel;
	Vec3 position;
} Target;

typedef struct SetEntry {
	u8 unk0[0x30];
	Target* target;
} SetEntry;

typedef struct ModelOwner {
	u8 unk0[0x4];
	u8* model;
} ModelOwner;

typedef struct CollisionFrame {
	u8 unk0[0x8];
	Vec3 direction;
} CollisionFrame;

typedef struct Switch {
	u8 unk0[0x28];
	SetEntry* entry;
	u8 unk2C[0x14];
	CollisionFrame* frame;
	u8 unk44[0x80];
	Vec3 position;
	Vec3 direction;
	s32 rotationX;
	s32 rotationY;
	s32 rotationZ;
	u8 unkE8[0x4];
	ModelOwner* primary;
	ModelOwner* secondary;
} Switch;

extern "C" const f32 switchOne;
extern "C" const Vec3 lbl_80239978;
extern "C" const Vec3 lbl_80239984;
extern "C" const Vec3 lbl_80239990;

extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void fn_80195790(void* matrix, const Vec3* axis, f32 a, f32 b, s32 mode);
extern "C" void fn_80195B5C(void* out, const void* matrix);
extern "C" void fn_8019941C(Vec3* out, const Vec3* in, s32 count, void* matrix);
extern "C" void* fn_8019E8EC(void* matrix);
extern "C" void fn_8019EB94(void* model, const Vec3* position, s32 mode);

extern "C" void switchTransform(Switch* object)
{
	u8 inverse[0x40];
	Vec3 local;
	Target* target = object->entry->target;
	u8* primary;
	u8* secondary;
	f32 wave;

	if (target != NULL && target->sentinel == 0x12345678) {
		object->position = target->position;
	}

	primary = object->primary->model;

	wave = fn_800D7B00(object->rotationY);
	fn_80195790(primary + 0x10, &lbl_80239984, switchOne - fn_800D7AE4(object->rotationY), wave, 0);

	wave = fn_800D7B00(object->rotationX);
	fn_80195790(primary + 0x10, &lbl_80239978, switchOne - fn_800D7AE4(object->rotationX), wave, 2);

	wave = fn_800D7B00(object->rotationZ);
	fn_80195790(primary + 0x10, &lbl_80239990, switchOne - fn_800D7AE4(object->rotationZ), wave, 2);

	fn_8019EB94(primary, &object->position, 2);

	secondary = object->secondary->model;
	fn_80195B5C(inverse, fn_8019E8EC(primary));
	fn_8019941C(&local, &object->direction, 1, inverse);
	fn_8019EB94(secondary, &local, 0);

	object->frame->direction = local;
}
