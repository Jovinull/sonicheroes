#include "types.h"

// Releases the members of a team (+0x114, count +0x39) from team actions: a member in action 9
// (+0x6F4) goes back to action 0 with flag 0x1000 (+0x6F6) cleared. A member in a formation mode
// (+0x6F0: 0x13..0x1B, 0x21, 0x29, 0x2B, 0x55, or 0x34/0x35 for the first formation slot +0x134;
// other members in 0x34/0x35 drop to mode 0x29) is ended with fn_80044A94 when it is the last
// formation slot (+0x121), and otherwise with fn_80044844, except for a player object in the
// formation (lbl_802AD070 by +0x760) already in mode 0x29. HYPOTHESIS: the roles are UNKNOWN.

struct Player80092DB8 {
	u8 pad0[0x6F0];
	s16 mode; // 0x6F0
	u8 pad6F2[0x6F4 - 0x6F2];
	s16 action; // 0x6F4
	s16 flags;  // 0x6F6
	u8 pad6F8[0x760 - 0x6F8];
	s8 number; // 0x760
};

struct Team80092DB8 {
	u8 pad0[0x39];
	s8 count; // 0x39
	u8 pad3A[0x114 - 0x3A];
	Player80092DB8* members[3]; // 0x114
	u8 pad120[0x121 - 0x120];
	s8 slots; // 0x121
	u8 pad122[0x134 - 0x122];
	Player80092DB8* formation[3]; // 0x134
};

extern "C" {
extern Player80092DB8* lbl_802AD070[];
void fn_80044A94(Player80092DB8* player);
void fn_80044844(Player80092DB8* player);
}

static inline BOOL InFormation(const Team80092DB8* team, const Player80092DB8* player)
{
	if (player == NULL) {
		return FALSE;
	}
	for (s32 i = 0; i < team->count; i++) {
		if (player == team->formation[i]) {
			return TRUE;
		}
	}
	return FALSE;
}

extern "C" void fn_80092DB8(Team80092DB8* team)
{
	for (s32 i = 0; i < team->count; i++) {
		Player80092DB8* member = team->members[i];
		switch (member->action) {
			case 9:
				member->action = 0;
				member->flags &= ~0x1000;
				break;
		}
		s32 mode = member->mode;
		switch (mode) {
			case 0x34:
			case 0x35:
				if (team->formation[0] != member) {
					member->mode = 0x29;
					break;
				}
			case 0x13:
			case 0x14:
			case 0x15:
			case 0x16:
			case 0x17:
			case 0x18:
			case 0x19:
			case 0x1A:
			case 0x1B:
			case 0x21:
			case 0x29:
			case 0x2B:
			case 0x55:
				s32 last = team->slots - 1;
				if (team->formation[last] == member) {
					fn_80044A94(member);
				} else if (InFormation(team, lbl_802AD070[member->number]) != TRUE
				    || mode != 0x29) {
					fn_80044844(member);
				}
				break;
		}
	}
}
