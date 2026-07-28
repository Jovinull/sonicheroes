#include "types.h"

// A box trigger: build the object's inverse transform once, then sweep the four
// carried objects and the eight players, and fire on whoever is inside the box.
//
// The claim is .text 0x7770 to 0x7AF0 and .rodata 0x130 to 0x14C. The seven
// constants are the two box sizes and a zero, read here and nowhere else in the
// module, and they start on the eight byte boundary a compiled object's .rodata
// needs.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out. The adjustor
// thunk at 0x7768 just before is not included: it tail calls, which is not
// something the compiler emits from C.
//
// The two boxes are different sizes. Carried objects have to be within 20 across
// and 2 up; players get 15 and 1. Both are half extents, tested on the absolute
// value, and the depth is tested as a range rather than an absolute value.
//
// The matrix is built once and kept on the object: three rotations off the same
// unit axes rel/obj_apply_transform.cpp uses, then the position, then inverted, so
// that a world position transformed through it lands in the box's own space.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Rot3 {
	s32 x;
	s32 y;
	s32 z;
} Rot3;

typedef struct Frame {
	u8 unk0[0xC];  // 0x00
	Rot3 rotation; // 0x0C
} Frame;

typedef struct Carried {
	u8 unk0[0x104];  // 0x000
	Vec3 position;   // 0x104
	u8 unk110[0x48]; // 0x110
	f32 power;       // 0x158
	u8 unk15C[0x40]; // 0x15C
	s32 actor;       // 0x19C
} Carried;

typedef struct Actor {
	u8 unk0[0x14C]; // 0x000
	s8 voice;       // 0x14C
} Actor;

typedef struct Player {
	u8 unk0[0x6]; // 0x00
	s16 flags;    // 0x06
} Player;

typedef struct Team {
	u8 unk0[0x25E]; // 0x000
	s8 voice;       // 0x25E
} Team;

typedef struct Clock {
	u8 unk0[0x20]; // 0x00
	s8 paused;     // 0x20
	s8 stopped;    // 0x21
	s8 frozen;     // 0x22
} Clock;

typedef struct Trigger {
	u8 unk0[0x28]; // 0x00
	Frame* frame;  // 0x28
	u8 unk2C[0x8]; // 0x2C
	s8 hits[8];    // 0x34
	s16 time;      // 0x3C
	u8 unk3E[0x2]; // 0x3E
	Vec3 position; // 0x40
	f32 pitch;     // 0x4C
	f32 yaw;       // 0x50
	f32 roll;      // 0x54
	u8 unk58[0x4]; // 0x58
	f32 power;     // 0x5C
	u8 unk60[0x4]; // 0x60
	void* matrix;  // 0x64
} Trigger;

extern "C" Clock* lbl_8042C180;
extern "C" void* lbl_8042C388;
extern "C" Carried* lbl_80288E0C[];
extern "C" Actor* lbl_80303DC8[];
extern "C" Player* lbl_802AD090[];
extern "C" Team* lbl_802AD0D0[];

extern "C" const Vec3 lbl_80239978; // {1, 0, 0}
extern "C" const Vec3 lbl_80239984; // {0, 1, 0}
extern "C" const Vec3 lbl_80239990; // {0, 0, 1}

extern "C" void fn_8001F674(s32 voice, s32 a, s32 b, s32 c);
extern "C" s32 fn_8003E2E4(s32 player, s32 part, Vec3* out, s32 flags);
extern "C" void* fn_80057644(s32 size);
extern "C" void fn_800B52E8(void* handle, s32 sound, s32 a, s32 b);
extern "C" void fn_800E0880(s32 player, const Vec3* impulse, const Rot3* rotation, s16 time);
extern "C" void fn_80195A74(void* matrix, const Vec3* axis, f32 angle, s32 mode);
extern "C" void fn_80195B5C(void* out, const void* matrix);
extern "C" void fn_80196050(void* matrix, const Vec3* position, s32 mode);
extern "C" void fn_8019941C(Vec3* out, const Vec3* in, s32 count, void* matrix);

extern "C" void objBoxTrigger(Trigger* object)
{
	u8 build[0x40];
	s32 i;

	if (lbl_8042C180->frozen != 0 || lbl_8042C180->paused != 0 || lbl_8042C180->stopped != 0) {
		return;
	}

	if (object->matrix == NULL) {
		void* matrix;

		object->matrix = fn_80057644(0x40);
		matrix         = object->matrix;

		fn_80195A74(build, &lbl_80239984, object->yaw, 0);
		fn_80195A74(build, &lbl_80239978, object->pitch, 2);
		fn_80195A74(build, &lbl_80239990, object->roll, 2);
		fn_80196050(build, &object->position, 2);
		fn_80195B5C(matrix, build);
	}

	for (i = 0; i < 4; i++) {
		Carried* carried = lbl_80288E0C[i];

		if (carried == NULL) {
			continue;
		}

		{
			Vec3 local = carried->position;

			fn_8019941C(&local, &local, 1, object->matrix);

			if ((f32)__fabs(local.x) > 20.0f) {
				continue;
			}
			if ((f32)__fabs(local.y) > 2.0f) {
				continue;
			}
			if (local.z > 20.0f || local.z < -20.0f) {
				continue;
			}

			carried->power = object->power;

			if (lbl_8042C388 != NULL) {
				fn_800B52E8(lbl_8042C388, 0x101D, 0, 0);
			}
			fn_8001F674(lbl_80303DC8[carried->actor]->voice, 4, 0xF, 0);
		}
	}

	{
		Vec3 local;
		Vec3 impulse;

		for (i = 0; i < 8; i++) {
			Player* player;

			if (object->hits[i] > 0) {
				continue;
			}
			if (fn_8003E2E4(i, 1, &local, 0) == 0) {
				continue;
			}

			fn_8019941C(&local, &local, 1, object->matrix);

			player = lbl_802AD090[i];
			if (player == NULL) {
				continue;
			}
			if ((player->flags & 1) == 0) {
				continue;
			}

			if ((f32)__fabs(local.x) > 15.0f) {
				continue;
			}
			if ((f32)__fabs(local.y) > 1.0f) {
				continue;
			}
			if (local.z > 15.0f || local.z < -15.0f) {
				continue;
			}

			impulse.x = object->power;
			impulse.z = 0.0f;
			impulse.y = 0.0f;

			{
				Rot3 rotation = object->frame->rotation;

				rotation.y -= 0x8000;
				fn_800E0880(i, &impulse, &rotation, object->time);
			}

			object->hits[i] = 4;

			if (lbl_8042C388 != NULL) {
				fn_800B52E8(lbl_8042C388, 0x101D, 0, 0);
			}
			fn_8001F674(lbl_802AD0D0[i]->voice, 4, 0xF, 0);
		}
	}
}
