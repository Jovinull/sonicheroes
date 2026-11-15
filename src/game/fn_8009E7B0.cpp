// Moves an object by its velocity (+0x38) and publishes its position (+0x2C) at +0x10 of
// lbl_803EA4E8: while its timer (+0x28) runs it is counted down, afterwards it keeps moving unless
// fn_80018C98 reports state 0xC. HYPOTHESIS: a camera/target point; the roles are UNKNOWN.
#include "types.h"

struct Vec8009E7B0 {
	f32 x;
	f32 y;
	f32 z;
};

struct Obj8009E7B0 {
	u8 pad0[0x28];
	s32 timer;            // 0x28
	Vec8009E7B0 position; // 0x2C
	Vec8009E7B0 velocity; // 0x38
};

struct Shared8009E7B0 {
	u8 pad0[0x10];
	Vec8009E7B0 position; // 0x10
};

extern "C" {
extern Shared8009E7B0 lbl_803EA4E8;
s32 fn_80018C98(void);
}

static inline void Move(Obj8009E7B0* o)
{
	o->position.x += o->velocity.x;
	o->position.y += o->velocity.y;
	o->position.z += o->velocity.z;
	lbl_803EA4E8.position = o->position;
}

extern "C" void fn_8009E7B0(Obj8009E7B0* o)
{
	if (o->timer > 0) {
		o->timer--;
		Move(o);
	} else if (fn_80018C98() != 0xC) {
		Move(o);
	}
}
