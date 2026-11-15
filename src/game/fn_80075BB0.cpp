// Tries to put a player into state 2 through fn_800E22AC (on its state record and motion record):
// refused (0) while either game-wide team mask of lbl_8042C180 (+0x1F, +0x20) has a bit set outside
// the player's team bit. On success it copies the motion's +0xE0 to +0x64, runs
// fn_8004675C, clears flags 0x2 and 0x2500 and sets 0x400 of the state (+0x6), clears the motion's
// +0x12 and runs fn_80046A04; returns 1. HYPOTHESIS: a landing transition; the roles are UNKNOWN.
#include "types.h"

struct State80075BB0 {
	s16 kind; // 0x0
	u8 pad2[4];
	s16 flags; // 0x6
};

struct Motion80075BB0 {
	u8 pad0[0x12];
	s16 unknown12; // 0x12
	u8 pad14[0x64 - 0x14];
	f32 unknown64; // 0x64
	u8 pad68[0xE0 - 0x68];
	f32 unknownE0; // 0xE0
};

struct Player80075BB0 {
	u8 pad0[0x9BC];
	s8 team; // 0x9BC
};

struct Masks80075BB0 {
	u8 pad0[0x1F];
	s8 mask1F; // 0x1F
	s8 mask20; // 0x20
};

extern "C" {
extern Masks80075BB0* lbl_8042C180;
s32 fn_800E22AC(State80075BB0* state, Motion80075BB0* motion);
void fn_8004675C(Player80075BB0* p);
void fn_80046A04(Player80075BB0* p);

s32 fn_80075BB0(Player80075BB0* p, State80075BB0* state, Motion80075BB0* motion)
{
	s32 others = ~(1 << p->team);

	if ((others & lbl_8042C180->mask1F) || (others & lbl_8042C180->mask20)) {
		return 0;
	}
	if (fn_800E22AC(state, motion) != 0) {
		state->kind       = 2;
		motion->unknown64 = motion->unknownE0;
		fn_8004675C(p);
		state->flags &= ~2;
		motion->unknown12 = 0;
		state->flags &= ~0x2500;
		state->flags |= 0x400;
		fn_80046A04(p);
		return 1;
	}
	return 0;
}
}
