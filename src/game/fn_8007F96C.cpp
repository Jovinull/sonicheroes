// Tries to put a player into state 2 through fn_800E22AC, like fn_80075BB0 (the third argument is
// unused here): refused (0) while either team mask of lbl_8042C180 (+0x1F, +0x20) has a bit set
// outside the player's team bit. On success it copies the motion's +0xE0 to +0x64, runs
// fn_8004675C, clears flags 0x2500 and sets 0x400 of the state (+0x6); when flags 0x3 remain it
// clears the player's +0x688 and sets +0x6A1; then clears flag 0x2 and the motion's +0x12 and runs
// fn_80046A04; returns 1. HYPOTHESIS: a landing transition; the roles are UNKNOWN.
#include "types.h"

struct State8007F96C {
	s16 kind; // 0x0
	u8 pad2[4];
	s16 flags; // 0x6
};

struct Motion8007F96C {
	u8 pad0[0x12];
	s16 unknown12; // 0x12
	u8 pad14[0x64 - 0x14];
	f32 unknown64; // 0x64
	u8 pad68[0xE0 - 0x68];
	f32 unknownE0; // 0xE0
};

struct Player8007F96C {
	u8 pad0[0x688];
	s16 unknown688; // 0x688
	u8 pad68A[0x6A1 - 0x68A];
	s8 unknown6A1; // 0x6A1
	u8 pad6A2[0x9BC - 0x6A2];
	s8 team; // 0x9BC
};

struct Masks8007F96C {
	u8 pad0[0x1F];
	s8 mask1F; // 0x1F
	s8 mask20; // 0x20
};

extern "C" {
extern Masks8007F96C* lbl_8042C180;
s32 fn_800E22AC(State8007F96C* state, Motion8007F96C* motion);
void fn_8004675C(Player8007F96C* p);
void fn_80046A04(Player8007F96C* p);

s32 fn_8007F96C(Player8007F96C* p, State8007F96C* state, void* unused, Motion8007F96C* motion)
{
	s32 others = ~(1 << p->team);

	if ((others & lbl_8042C180->mask1F) || (others & lbl_8042C180->mask20)) {
		return 0;
	}
	if (fn_800E22AC(state, motion) != 0) {
		state->kind       = 2;
		motion->unknown64 = motion->unknownE0;
		fn_8004675C(p);
		state->flags &= ~0x2500;
		state->flags |= 0x400;
		if (state->flags & 3) {
			p->unknown688 = 0;
			p->unknown6A1 = 1;
		}
		state->flags &= ~2;
		motion->unknown12 = 0;
		fn_80046A04(p);
		return 1;
	}
	return 0;
}
}
