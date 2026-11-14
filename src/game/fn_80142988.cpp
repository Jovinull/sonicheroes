// Hooked render step: runs the saved callback lbl_8042C83C on (object, target) and, when it
// succeeds and the shared state block of the current world (plugin slot at lbl_8042C934) has its
// +0xD flag set, applies it to target through fn_80145004 with the object's halfword at +0x8A.
// Names are UNKNOWN. Returns the object, or null when the saved callback fails.
#include "game/rw_engine.h"

struct Object80142988 {
	u8 pad0[0x8A];
	u16 f8A; // 0x8A
};

struct State80142988 {
	u8 pad0[0xD];
	u8 enabled; // 0xD
};

extern "C" {
extern void* (*lbl_8042C83C)(Object80142988* object, void* target);
extern s32 lbl_8042C934;
void fn_80145004(void* target, State80142988* state, u32 value);

Object80142988* fn_80142988(Object80142988* object, void* target)
{
	State80142988* state;
	if (lbl_8042C83C(object, target) == 0) {
		return 0;
	}
	state = *(State80142988**)((u8*)lbl_8042C9A4->curWorld + lbl_8042C934);
	if (state != 0 && state->enabled != 0) {
		fn_80145004(target, state, object->f8A);
	}
	return object;
}
}
