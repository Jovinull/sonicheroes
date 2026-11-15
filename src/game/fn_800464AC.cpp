// Ends a player's airborne state (HYPOTHESIS: landing): unless fn_800E27D8 rejects it or the
// vertical speed (+0x60 of the record at +0x760) is not exactly lbl_8042D1BC, a player in state 9,
// 0x22, 0x23 or 0x25 (+0x6F0) goes to state 0x22 with motion 0x29 in team play (team mode 3, or 2
// with more than one member) or 0x24 otherwise (+0x14E of the record); any other state is reset to
// 0 and handed to fn_800474C4. Returns 1 when handled, else 0. The names are UNKNOWN.
#include "types.h"

struct State800464AC {
	s16 kind; // 0x0
};

struct Info800464AC {
	u8 pad0[0x18];
	s16 unknown18; // 0x18
	u8 pad1A[0x60 - 0x1A];
	f32 speedY; // 0x60
	u8 pad64[0x14E - 0x64];
	s16 motion; // 0x14E
};

struct Team800464AC {
	u8 pad0[0x121];
	s8 members; // 0x121
	u8 pad122[0x140 - 0x122];
	s32 mode; // 0x140
};

struct Player800464AC {
	u8 pad0[0x6F0];
	State800464AC state; // 0x6F0
	u8 pad6F2[0x720 - 0x6F2];
	u8 motion[0x40];   // 0x720
	Info800464AC info; // 0x760
	u8 pad8B0[0x9B8 - 0x8B0];
	Team800464AC* team; // 0x9B8
};

extern "C" {
extern f32 lbl_8042D1BC;
s32 fn_800E27D8(State800464AC* state, Info800464AC* info, s32 a, s32 b);
void fn_800474C4(State800464AC* state, void* motion, Info800464AC* info);
}

// Whether the team plays as a team (mode 3, or mode 2 with more than one member).
static inline s32 IsTeamPlay(Team800464AC* team)
{
	if (team->mode == 3 || (team->mode == 2 && team->members > 1)) {
		return 1;
	}
	return 0;
}

extern "C" s32 fn_800464AC(Player800464AC* p)
{
	State800464AC* state = &p->state;
	void* motion         = p->motion;
	Info800464AC* info   = &p->info;

	if (fn_800E27D8(state, info, 0, 0) == 0 && lbl_8042D1BC == info->speedY) {
		switch (state->kind) {
			case 9:
			case 0x22:
			case 0x23:
			case 0x25:
				state->kind = 0x22;
				if (IsTeamPlay(p->team)) {
					info->motion = 0x29;
				} else {
					info->motion = 0x24;
				}
				break;
			default:
				state->kind     = 0;
				info->unknown18 = 0;
				fn_800474C4(state, motion, info);
				break;
		}
		return 1;
	}
	return 0;
}
