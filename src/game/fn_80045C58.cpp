// Starts a player's grab/throw action from fn_800E1F28's result (HYPOTHESIS): result 4 gives
// action 9 with motion 0x26 in team play (team mode 3, or 2 with more than one member) or 0x21
// alone; any other non-zero result gives action 0x25 with motion 0x27 or 0x22. Both announce event
// 7 for the player (fn_80137D0C with its character +0x761 and number +0x760) and return 1; 0 when
// fn_800E1F28 returns 0. The names are UNKNOWN.
#include "types.h"

struct Team80045C58 {
	u8 pad0[0x121];
	s8 members; // 0x121
	u8 pad122[0x140 - 0x122];
	s32 mode; // 0x140
};

struct Player80045C58 {
	u8 pad0[0x6F0];
	s16 action; // 0x6F0
	u8 pad6F2[0x760 - 0x6F2];
	s8 number;    // 0x760
	s8 character; // 0x761
	u8 pad762[0x8AE - 0x762];
	s16 nextMotion; // 0x8AE
	u8 pad8B0[0x9B8 - 0x8B0];
	Team80045C58* team; // 0x9B8
};

extern "C" {
s32 fn_800E1F28(Player80045C58* p);
void fn_80137D0C(s32 event, s32 character, s32 player);
}

// Whether the team plays as a team (see fn_800464AC).
static inline s32 IsTeamPlay(Team80045C58* team)
{
	if (team->mode == 3 || (team->mode == 2 && team->members > 1)) {
		return 1;
	}
	return 0;
}

extern "C" s32 fn_80045C58(Player80045C58* p)
{
	s32 result = fn_800E1F28(p);

	if (result == 0) {
		return 0;
	}
	if (result == 4) {
		p->action = 9;
		if (IsTeamPlay(p->team)) {
			p->nextMotion = 0x26;
		} else {
			p->nextMotion = 0x21;
		}
		fn_80137D0C(7, p->character, p->number);
		return 1;
	}
	p->action = 0x25;
	if (IsTeamPlay(p->team)) {
		p->nextMotion = 0x27;
	} else {
		p->nextMotion = 0x22;
	}
	fn_80137D0C(7, p->character, p->number);
	return 1;
}
