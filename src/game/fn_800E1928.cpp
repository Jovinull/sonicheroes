// Turns a player's velocity (+0x60 of the path record) toward a heading (see fn_800E1508): the
// state's angle (+0x10) turns toward `target` by 0x400 per call while more than 0x2000 away, then
// by 1/16 and, within 0x1000, by 1/32 of the difference; the velocity then keeps 10% and takes 90%
// of the turned one. The second argument is unused. HYPOTHESIS: AI steering; the roles are UNKNOWN.
// NonMatching (3 words): the retail code loads the 0.9 constant after the first multiply (both
// constants then stay in f3/f2); MWCC loads it with the 0.1 constant. Tried: assignments inside the
// first expression (either operand), declaration orders.
#include "types.h"

struct Vec800E1928 {
	f32 x;
	f32 y;
	f32 z;
};

struct State800E1928 {
	u8 pad0[0x10];
	s32 angle; // 0x10
};

struct Ctrl800E1928 {
	u8 pad0[0x10];
	s16 flags; // 0x10
	u8 pad12[0x30 - 0x12];
	f32 speed; // 0x30
	u8 pad34[0x60 - 0x34];
	Vec800E1928 velocity; // 0x60
};

int AdjustAngle(int first, int second, int limit);
int DiffAngle(int first, int second);

extern "C" {
extern f32 lbl_8042E240; // 0.1f
extern f32 lbl_8042E244; // 0.9f
void fn_8003E9B4(State800E1928* state, Vec800E1928* v);
void fn_8003EB18(State800E1928* state, Vec800E1928* v);

void fn_800E1928(State800E1928* state, void* unused, Ctrl800E1928* ctrl, s32 target)
{
	Vec800E1928 v;
	s32 diff;
	f32 take;
	f32 keep;

	v = ctrl->velocity;
	fn_8003E9B4(state, &v);
	diff = DiffAngle(state->angle, target);
	if (diff > 0x2000) {
		state->angle = AdjustAngle(state->angle, target, 0x400);
	} else if (diff > 0x1000) {
		state->angle = AdjustAngle(state->angle, target, diff >> 4);
	} else {
		state->angle = AdjustAngle(state->angle, target, diff >> 5);
	}
	fn_8003EB18(state, &v);
	keep             = lbl_8042E240;
	take             = lbl_8042E244;
	ctrl->velocity.x = keep * ctrl->velocity.x + take * v.x;
	ctrl->velocity.y = keep * ctrl->velocity.y + take * v.y;
	ctrl->velocity.z = keep * ctrl->velocity.z + take * v.z;
}
}
