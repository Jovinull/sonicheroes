// Picks the next team member, walking the slots downward (wrapping at the member count, +0x39)
// from the previous pick (+0x3B) until a slot whose player is not in state 0x12 and whose byte at
// +0x20D is 0 is found; slot 1 only qualifies when the first player checked is "far" (its word at
// +0x99C is unset (-1e6), more than 40 (46 when +0x34 is set) above +0x70C, or flags 0x8002 at
// +0x98C are set). The pick goes to +0x3C and +0x3B; +0x3A is the walk cursor. HYPOTHESIS: this is
// the AI choice of which character leads; all field names are UNKNOWN.
#include "types.h"

struct Player800929E0 {
	u8 pad0[0x628];
	s32 state; // 0x628
	u8 pad62C[0x70C - 0x62C];
	f32 unknown70C; // 0x70C
	u8 pad710[0x98C - 0x710];
	u32 flags; // 0x98C
	u8 pad990[0x99C - 0x990];
	f32 unknown99C; // 0x99C
};

struct Team800929E0 {
	u8 pad0[0x34];
	s32 unknown34; // 0x34
	u8 pad38[1];
	s8 count;    // 0x39
	s8 cursor;   // 0x3A
	s8 previous; // 0x3B
	s8 pick;     // 0x3C
	u8 pad3D[0x114 - 0x3D];
	Player800929E0* players[3]; // 0x114
	u8 pad120[0x20D - 0x120];
	s8 blocked[3]; // 0x20D
};

extern "C" {
extern f32 lbl_8042D964; // 40.0f
extern f32 lbl_8042D968; // 46.0f
extern f32 lbl_8042D96C; // -1000000.0f

void fn_800929E0(Team800929E0* team)
{
	f32 limit;
	Player800929E0* player;
	s32 far;
	f32 height;

	limit        = team->unknown34 == 0 ? lbl_8042D964 : lbl_8042D968;
	team->cursor = team->previous;
	player       = team->players[team->cursor];
	height       = player->unknown99C;
	if (lbl_8042D96C == height || height - player->unknown70C > limit
	    || (player->flags & 0x8002) != 0) {
		far = 1;
	} else {
		far = 0;
	}
	do {
		if (team->cursor == 0) {
			team->cursor = team->count;
		}
		s8 cursor    = --team->cursor;
		team->cursor = cursor % team->count;
		if (team->players[team->cursor]->state != 0x12 && (team->cursor != 1 || far)
		    && team->blocked[team->cursor] == 0) {
			break;
		}
	} while (team->cursor != team->previous);
	team->pick     = team->cursor;
	team->previous = team->cursor;
}
}
