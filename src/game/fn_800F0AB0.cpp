// Applies a player's forward acceleration (+0x54) to the x speed of its path record (+0x60) with a
// brake: a forward speed that crosses 0 or falls through 0.1, and a backward one that rises above
// -0.0 or through -0.1, stops at 0; y and z are cleared. The
// result, turned into the state's frame (fn_8003E9B4), goes to *out and fn_800E13DC finishes the
// step. HYPOTHESIS: AI throttle; the constants' roles are UNKNOWN.
#include "types.h"

struct Vec800F0AB0 {
	f32 x;
	f32 y;
	f32 z;
};

struct Ctrl800F0AB0 {
	u8 pad0[0x54];
	f32 acceleration; // 0x54
	u8 pad58[0x60 - 0x58];
	Vec800F0AB0 velocity; // 0x60
};

extern "C" {
extern f32 lbl_8042E394; // 0.0f
extern f32 lbl_8042E3B8; // 0.1f
extern f32 lbl_8042E460; // -0.0f
extern f32 lbl_8042E464; // -0.1f
void fn_8003E9B4(void* state, Vec800F0AB0* v);
void fn_800E13DC(void* state, Vec800F0AB0* out, Ctrl800F0AB0* ctrl);

void fn_800F0AB0(void* state, Vec800F0AB0* out, Ctrl800F0AB0* ctrl)
{
	f32 old = ctrl->velocity.x;
	Vec800F0AB0 v;

	ctrl->velocity.x += ctrl->acceleration;
	if (old > lbl_8042E394) {
		if (ctrl->velocity.x < lbl_8042E394) {
			ctrl->velocity.x = lbl_8042E394;
		} else if (old >= lbl_8042E3B8 && ctrl->velocity.x < lbl_8042E3B8) {
			ctrl->velocity.x = lbl_8042E394;
		}
	} else if (old < lbl_8042E394) {
		if (ctrl->velocity.x > lbl_8042E460) {
			ctrl->velocity.x = lbl_8042E394;
		} else if (old <= lbl_8042E464 && ctrl->velocity.x > lbl_8042E464) {
			ctrl->velocity.x = lbl_8042E394;
		}
	}
	ctrl->velocity.z = ctrl->velocity.y = lbl_8042E394;
	v                                   = ctrl->velocity;
	fn_8003E9B4(state, &v);
	*out = v;
	fn_800E13DC(state, out, ctrl);
}
}
