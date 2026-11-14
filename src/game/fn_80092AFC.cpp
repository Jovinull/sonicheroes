// Passes a team's leadership to the next eligible member (HYPOTHESIS): starting after the current
// leader (0x3B), cycles through the team's members (count at 0x39) until one is found that is not
// in state 0x12, is enabled in the byte table at 0x20D and, for position 1, only when the current
// leader is unavailable (no reference value, too far below it or flagged 0x8002); the walk stops
// at the leader again. Records the previous leader at 0x3C and the result as leader. The limit
// depends on the mode word 0x34 (.sdata2 lbl_8042D964/lbl_8042D968). Field names are inferred
// from this function only.
// NonMatching: in the walk the raw and sign-extended copies of the member index swap r5/r6
// (7 words differ).
#include "types.h"

struct Member80092AFC {
	u8 pad0[0x628];
	s32 state; // 0x628
	u8 pad62C[0x70C - 0x62C];
	f32 height; // 0x70C
	u8 pad710[0x98C - 0x710];
	u32 flags; // 0x98C
	u8 pad990[0x99C - 0x990];
	f32 reference; // 0x99C
};

struct Team80092AFC {
	u8 pad0[0x34];
	s32 mode; // 0x34
	u8 pad38[0x1];
	s8 count;    // 0x39
	s8 current;  // 0x3A
	s8 leader;   // 0x3B
	s8 previous; // 0x3C
	u8 pad3D[0x114 - 0x3D];
	Member80092AFC* members[4]; // 0x114
	u8 pad124[0x20D - 0x124];
	s8 enabled[4]; // 0x20D
};

extern "C" {
extern f32 lbl_8042D964;
extern f32 lbl_8042D968;
extern f32 lbl_8042D96C;

void fn_80092AFC(Team80092AFC* team)
{
	f32 limit;
	Member80092AFC* leader;
	s8 next;
	s32 leaderUnavailable;
	f32 reference;

	if (team->mode == 0) {
		limit = lbl_8042D964;
	} else {
		limit = lbl_8042D968;
	}
	team->current = team->leader;
	leader        = team->members[team->current];
	reference     = leader->reference;
	if (lbl_8042D96C == reference || reference - leader->height > limit
	    || (leader->flags & 0x8002) != 0) {
		leaderUnavailable = 1;
	} else {
		leaderUnavailable = 0;
	}

	do {
		s8 incremented = ++team->current;
		team->current  = incremented % team->count;
		next           = team->current;
		if (team->members[next]->state != 0x12 && (next != 1 || leaderUnavailable)
		    && !team->enabled[next]) {
			break;
		}
	} while (next != team->leader);

	team->previous = next;
	team->leader   = team->current;
}
}
