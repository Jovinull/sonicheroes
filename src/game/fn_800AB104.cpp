#include "types.h"

// Picks the player credited for player idx's points (used by PARAM_SCORE::addSomeonesScore): the
// team's current leader (team +0x258 of the record lbl_802AD0D0, its member list +0x110 indexed by
// +0x3B) while the team is in mode 0x17 or 9 (+0x154), when idx is the leader, while fn_80091FAC
// gives 2, in team state 5 or 6 (+0x140), or while idx's action (lbl_802AD090) is one of 0x13,
// 0x14, 0x16..0x19, 0x3E..0x41 or 0xF (unless fn_80091FAC gives 1); otherwise idx itself. A
// negative idx gives -1. HYPOTHESIS: the leader takes the points of team moves; roles UNKNOWN.

struct Team800AB104 {
	u8 pad0[0x3B];
	s8 current; // 0x3B
	u8 pad3C[0x110 - 0x3C];
	s8 members[3]; // 0x110
	u8 pad113[0x140 - 0x113];
	s32 state; // 0x140
	u8 pad144[0x154 - 0x144];
	s32 mode; // 0x154
};

struct Record800AB104 {
	u8 pad0[0x258];
	Team800AB104* team; // 0x258
};

struct Action800AB104 {
	s16 action; // 0x0
};

extern "C" {
extern Record800AB104* lbl_802AD0D0[];
extern Action800AB104* lbl_802AD090[];
s32 fn_80091FAC(Team800AB104* team);
}

extern "C" s32 fn_800AB104(s32 idx)
{
	if (idx < 0) {
		return -1;
	}
	Team800AB104* team = lbl_802AD0D0[idx]->team;
	s32 leader         = team->members[team->current];
	if (team->mode == 0x17) {
		return leader;
	}
	if (team->mode == 9) {
		return leader;
	}
	if (idx == leader) {
		return leader;
	}
	if (fn_80091FAC(team) == 2) {
		return leader;
	}
	if (team->state == 5 || team->state == 6) {
		return leader;
	}
	switch (lbl_802AD090[idx]->action) {
		case 0xF:
			if (fn_80091FAC(team) == 1) {
				return idx;
			}
			// fall through
		case 0x13:
		case 0x14:
		case 0x16:
		case 0x17:
		case 0x18:
		case 0x19:
		case 0x3E:
		case 0x3F:
		case 0x40:
		case 0x41:
			return leader;
	}
	return idx;
}
