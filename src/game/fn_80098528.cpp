#include "game/gparam.h"

// Starts a team's team blast when it is allowed: not while its cooldown (+0x1FC) runs, while the
// leader (+0x114 by +0x3B) is in a formation move (modes 0x21, 0x2A..0x2D, 0x33, 0x55), while the
// play-mode flag 31 (lbl_8042C180) is set for another team than this one (+0x38) or flag 32 is
// set, or in team state 0x17 (+0x154 or +0x150). The leader must also lack flags 0x4800 (+0x770),
// the second timer (+0x204) must be over and the member +0x3A must be in mode 0, 0xC, 0xD or 0xE
// with fn_800E24FC agreeing; with the gauge full (PARAM_SFA::sfa_trigger 1) the team enters state
// 9, the trigger becomes 2 and the gauge and team-blast time are reset (setSFA, setTB).
// HYPOTHESIS: the roles are UNKNOWN.

struct Player80098528 {
	u8 pad0[0x6F0];
	s16 mode; // 0x6F0
	u8 pad6F2[0x770 - 0x6F2];
	s16 flags; // 0x770
};

struct Team80098528 {
	u8 pad0[0x2C];
	PARAM_SFA* sfa; // 0x2C
	u8 pad30[0x38 - 0x30];
	s8 number; // 0x38
	u8 pad39;
	s8 member;  // 0x3A
	s8 current; // 0x3B
	u8 pad3C[0x114 - 0x3C];
	Player80098528* members[3]; // 0x114
	u8 pad120[0x150 - 0x120];
	s32 state;  // 0x150
	s32 state2; // 0x154
	u8 pad158[0x1FC - 0x158];
	s16 cooldown; // 0x1FC
	u8 pad1FE[0x204 - 0x1FE];
	s16 timer; // 0x204
};

struct PlayMode80098528 {
	s8 flags[44];
};

extern "C" {
extern PlayMode80098528* lbl_8042C180;
extern const f32 lbl_8042D91C;
extern const f32 lbl_8042D92C;
s32 fn_800E24FC(Player80098528* leader, Player80098528* member);
}

static inline BOOL CanBlast(Team80098528* team)
{
	if (team->cooldown > 0) {
		return FALSE;
	}
	switch (team->members[team->current]->mode) {
		case 0x21:
		case 0x2A:
		case 0x2B:
		case 0x2C:
		case 0x2D:
		case 0x33:
		case 0x55:
			return FALSE;
	}
	BOOL ok    = TRUE;
	s32 others = ~(1U << team->number);
	if ((others & lbl_8042C180->flags[31]) || lbl_8042C180->flags[32]) {
		ok = FALSE;
	} else if (team->state2 == 0x17 || team->state == 0x17) {
		ok = FALSE;
	}
	return ok;
}

extern "C" void fn_80098528(Team80098528* team)
{
	if (!CanBlast(team)) {
		return;
	}
	Player80098528* leader = team->members[team->current];
	if (leader->flags & 0x4800) {
		return;
	}
	if (team->state2 == 0x17) {
		return;
	}
	if (team->timer > 0) {
		return;
	}
	Player80098528* member = team->members[team->member];
	switch (member->mode) {
		default:
			return;
		case 0:
		case 0xC:
		case 0xD:
		case 0xE:
			break;
	}
	if (fn_800E24FC(leader, member) == 0) {
		return;
	}
	if (PARAM_SFA::sfa_trigger[team->number] != 1) {
		return;
	}
	team->state                    = 9;
	s32 number                     = team->number;
	PARAM_SFA* sfa                 = team->sfa;
	PARAM_SFA::sfa_trigger[number] = 2;
	sfa->setSFA(number, lbl_8042D91C);
	sfa->setTB(number, lbl_8042D92C);
}
