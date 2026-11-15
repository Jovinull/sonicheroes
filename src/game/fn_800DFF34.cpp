// Stores three floats into the player record lbl_802AD0B0[index] (+0xC/+0x10/+0x14, as
// fn_800DFF14 does), unless the player's state record (lbl_802AD090[index]) has flag 0x1000 set and
// state 0x3F. Unless the record's kind (+0x0) is 0x43, it first sets that flag and state 8.
// Field roles are UNKNOWN (HYPOTHESIS: a forced-motion request with an override state).
#include "types.h"

struct State800DFF34 {
	s16 kind;  // 0x0
	s16 pad2;  // 0x2
	s16 state; // 0x4
	s16 flags; // 0x6
};

struct Motion800DFF34 {
	u8 pad0[0xC];
	f32 x; // 0xC
	f32 y; // 0x10
	f32 z; // 0x14
};

extern "C" {
extern State800DFF34* lbl_802AD090[8];
extern Motion800DFF34* lbl_802AD0B0[8];

void fn_800DFF34(s32 index, f32 x, f32 y, f32 z)
{
	State800DFF34* state = lbl_802AD090[index];
	Motion800DFF34* motion;

	if ((state->flags & 0x1000) && state->state == 0x3F) {
		return;
	}
	if (state->kind != 0x43) {
		state->flags |= 0x1000;
		state->state = 8;
	}
	motion    = lbl_802AD0B0[index];
	motion->x = x;
	motion->y = y;
	motion->z = z;
}
}
