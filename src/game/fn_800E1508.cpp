// Turns a player's velocity (+0x60 of the path record) toward a heading: converts it to the
// state's local frame (fn_8003E9B4), turns the state's angle (+0x10) toward `target` by 0x30 per
// call (0x38 with flag 0x1000 of +0x10), converts back (fn_8003EB18) and blends: above speed 0.4
// (+0x30) the velocity keeps 99% and takes 1% of the turned one, otherwise half and half. The
// second argument is unused. HYPOTHESIS: AI steering; the roles are UNKNOWN.
#include "types.h"

struct Vec800E1508 {
	f32 x;
	f32 y;
	f32 z;
};

struct State800E1508 {
	u8 pad0[0x10];
	s32 angle; // 0x10
};

struct Ctrl800E1508 {
	u8 pad0[0x10];
	s16 flags; // 0x10
	u8 pad12[0x30 - 0x12];
	f32 speed; // 0x30
	u8 pad34[0x60 - 0x34];
	Vec800E1508 velocity; // 0x60
};

int AdjustAngle(int first, int second, int limit);

extern "C" {
extern f32 lbl_8042E224; // 0.4f
extern f32 lbl_8042E228; // 0.99f
extern f32 lbl_8042E22C; // 0.01f
extern f32 lbl_8042E230; // 0.5f
void fn_8003E9B4(State800E1508* state, Vec800E1508* v);
void fn_8003EB18(State800E1508* state, Vec800E1508* v);

void fn_800E1508(State800E1508* state, void* unused, Ctrl800E1508* ctrl, s32 target)
{
	Vec800E1508 v;
	f32 keep;
	f32 take;

	v = ctrl->velocity;
	fn_8003E9B4(state, &v);
	state->angle = AdjustAngle(state->angle, target, (ctrl->flags & 0x1000) ? 0x38 : 0x30);
	fn_8003EB18(state, &v);
	if (ctrl->speed > lbl_8042E224) {
		keep = lbl_8042E228;
		take = lbl_8042E22C;
	} else {
		take = keep = lbl_8042E230;
	}
	ctrl->velocity.x = ctrl->velocity.x * keep + v.x * take;
	ctrl->velocity.y = ctrl->velocity.y * keep + v.y * take;
	ctrl->velocity.z = ctrl->velocity.z * keep + v.z * take;
}
}
