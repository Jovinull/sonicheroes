#include "types.h"

// Puts the object's motion back to the angle and offset it starts from.
//
// The translation unit is the single function fn_1_5B08, .text 0x5B08 to
// 0x5B9C. It reaches nothing but a DOL global, which is why it cuts cleanly
// out of the run around it.
//
// The loop runs five times over the same thing. Nothing in the body advances,
// and the object it reads is the same on every turn, so the four turns after
// the first repeat work already done. That is what the original does and it is
// left alone here.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct AnimSlot {
	void* unk0;   // 0x00
	void* motion; // 0x04
} AnimSlot;

typedef struct Object {
	u8 unk0[0xC0];   // 0x000
	AnimSlot* slot;  // 0x0C0
	u8 unkC4[0x3C];  // 0x0C4
	Vec3 offset;     // 0x100
	u8 unk10C[0x18]; // 0x10C
	f32 angle;       // 0x124
} Object;

extern "C" const f32 lbl_80239984[];

extern "C" void fn_8019EB94(void* motion, Vec3* value, s32 index);
extern "C" void fn_8019ED68(void* motion, const f32* axis, f32 angle, s32 index);

extern "C" void fn_1_5B08(Object* object)
{
	s32 i;
	void* motion;

	for (i = 0; i != 5; i++) {
		if (object->slot != NULL) {
			motion = object->slot->motion;
			if (motion != NULL) {
				fn_8019ED68(motion, lbl_80239984, object->angle, 0);
				fn_8019EB94(motion, &object->offset, 2);
			}
		}
	}
}
