#include "types.h"

// Picks the first team member (+0x114, count +0x39) not in action 0x27 and puts the team into the
// state (+0x150) for that member's character (+0x9B4, 0..2): in team mode 0x13 (+0x154) state 7
// when the member is the next one after the current leader (+0x3B; character 0 after 1, 1 after 2,
// 2 after 0) and 6 otherwise, else 0x14 + character. The member is then reset (fn_800898F0(0),
// fn_80089524), loses its flag 0x800 (+0x770) and gets a 0x78-frame timer (+0x6F8). Does nothing
// when every member is in action 0x27. HYPOTHESIS: the roles (leader switch) are UNKNOWN.

struct Player800914A4 {
	u8 pad0[0x6F0];
	s16 action; // 0x6F0
	u8 pad6F2[0x6F8 - 0x6F2];
	s16 timer; // 0x6F8
	u8 pad6FA[0x770 - 0x6FA];
	s16 flags; // 0x770
	u8 pad772[0x9B4 - 0x772];
	s32 character; // 0x9B4
};

struct Team800914A4 {
	u8 pad0[0x39];
	s8 count; // 0x39
	u8 pad3A;
	s8 current; // 0x3B
	u8 pad3C[0x114 - 0x3C];
	Player800914A4* members[3]; // 0x114
	u8 pad120[0x150 - 0x120];
	s32 state; // 0x150
	s32 mode;  // 0x154
};

extern "C" {
void fn_800898F0(Player800914A4* player, s32 unknown);
void fn_80089524(Player800914A4* player);
}

extern "C" void fn_800914A4(Team800914A4* team)
{
	s32 i;

	for (i = 0; i < team->count; i++) {
		if (team->members[i]->action != 0x27) {
			break;
		}
	}
	if (i >= team->count) {
		return;
	}
	Player800914A4* member = team->members[i];
	if (team->mode == 0x13) {
		BOOL next = FALSE;
		switch (member->character) {
			case 0:
				if (team->current == 1) {
					next = TRUE;
				}
				break;
			case 1:
				if (team->current == 2) {
					next = TRUE;
				}
				break;
			case 2:
				if (team->current == 0) {
					next = TRUE;
				}
				break;
		}
		if (!next) {
			team->state = 6;
		} else {
			team->state = 7;
		}
	} else {
		switch (member->character) {
			case 0:
				team->state = 0x14;
				break;
			case 1:
				team->state = 0x15;
				break;
			case 2:
				team->state = 0x16;
				break;
		}
	}
	fn_800898F0(member, 0);
	fn_80089524(member);
	member->flags &= ~0x800;
	member->timer = 0x78;
}
