#include "types.h"

// Resets a team after a team move: clears its timers (+0x1FC..+0x204) and +0x266, keeps only the
// flags 0x3000 (+0x206), clears the eight slot bytes that are set (+0x24C with +0x254/+0x25C), runs
// fn_8009B8BC with the main member (game2pGetMainMemberNo of +0x38) when play-mode flag 30 is set,
// sets the team states (+0x154/+0x158 = 4, +0x150 = 5) and for each member (+0x114, count +0x39)
// resets it (fn_800898F0: 0 for the current member +0x3A, else 4), ends a formation move (modes
// 0x26, 0x27, 0x2B..0x2D: fn_80044A94), runs fn_80092F58 and sets its slot (+0x110) to action 9
// with 0x2B for the main member and 0x2D for the others (fn_800E1208). HYPOTHESIS: names UNKNOWN.

struct Player8009C0D0 {
	u8 pad0[0x6F0];
	s16 mode; // 0x6F0
};

struct Team8009C0D0 {
	u8 pad0[0x38];
	s8 number;  // 0x38
	s8 count;   // 0x39
	s8 current; // 0x3A
	u8 pad3B[0x110 - 0x3B];
	s8 slots[4];                // 0x110
	Player8009C0D0* members[3]; // 0x114
	u8 pad120[0x150 - 0x120];
	s32 state;  // 0x150
	s32 state2; // 0x154
	s32 state3; // 0x158
	u8 pad15C[0x1FC - 0x15C];
	s16 timers[5]; // 0x1FC
	s16 flags;     // 0x206
	u8 pad208[0x24C - 0x208];
	s8 used[8];  // 0x24C
	s8 slotA[8]; // 0x254
	s8 slotB[8]; // 0x25C
	u8 pad264[0x266 - 0x264];
	s8 unknown266; // 0x266
};

struct PlayMode8009C0D0 {
	s8 flags[44];
};

extern "C" {
extern PlayMode8009C0D0* lbl_8042C180;
void fn_8009B8BC(Team8009C0D0* team, s32 member);
void fn_800898F0(Player8009C0D0* player, s32 unknown);
void fn_80044A94(Player8009C0D0* player);
void fn_80092F58(Team8009C0D0* team);
void fn_800E1208(s32 slot, s32 action, s32 mode);
}

s32 game2pGetMainMemberNo(s32 team);

static inline void ClearSlots(Team8009C0D0* team)
{
	for (s32 i = 0; i < 8; i++) {
		if (team->used[i] != 0) {
			team->used[i]  = 0;
			team->slotA[i] = 0;
			team->slotB[i] = 0;
		}
	}
}

extern "C" void fn_8009C0D0(Team8009C0D0* team)
{
	s32 main = game2pGetMainMemberNo(team->number);
	s32 i;

	team->timers[0]  = 0;
	team->timers[1]  = 0;
	team->timers[2]  = 0;
	team->timers[3]  = 0;
	team->timers[4]  = 0;
	team->unknown266 = 0;
	team->flags &= 0x3000;
	ClearSlots(team);
	if (lbl_8042C180->flags[30] != 0) {
		fn_8009B8BC(team, main);
	}
	team->state3 = team->state2 = 4;
	team->state                 = 5;
	for (i = 0; i < team->count; i++) {
		s32 slot               = team->slots[i];
		Player8009C0D0* member = team->members[i];
		if (i == team->current) {
			fn_800898F0(member, 0);
		} else {
			fn_800898F0(member, 4);
		}
		switch (member->mode) {
			case 0x26:
			case 0x27:
			case 0x2B:
			case 0x2C:
			case 0x2D:
				fn_80044A94(member);
				break;
		}
		fn_80092F58(team);
		if (i == main) {
			fn_800E1208(slot, 9, 0x2B);
		} else {
			fn_800E1208(slot, 9, 0x2D);
		}
	}
}
