// Clears the active word (+0x90) of entry `index` of the current team record
// (lbl_802B908C[lbl_8042C1FC]); when that entry was the last one counted (+0x8C of the record),
// the count drops to the highest entry still active and words +0x98 of that entry and of its
// counterpart in the third 0x114-byte array (+0x1140) are cleared. Entry 0 is never cleared.
// The first argument is unused; field roles are UNKNOWN (HYPOTHESIS: team member slots).
// NonMatching (30 words): the retail code runs the search as a counted loop of `count - 1`
// iterations that never tests entry 0 and forces the result to -1 when the count is 0, and
// loads the record address before the team index. Tried: >= 0 / > 0 for and while loops, a local
// team index.
#include "types.h"

struct Entry8004DE10 {
	u8 pad0[0x8C];
	s32 count;  // 0x8C (used in entry 0 only: the record's count)
	s32 active; // 0x90
	u8 pad94[4];
	s32 unknown98; // 0x98
	u8 pad9C[0x114 - 0x9C];
};

struct Team8004DE10 {
	Entry8004DE10 entries[16]; // 0x0 (extent UNKNOWN)
	Entry8004DE10 entries2[8]; // 0x1140 (extent UNKNOWN)
	u8 pad19E0[0x2324 - 0x19E0];
};

extern "C" {
extern Team8004DE10 lbl_802B908C[];
extern s32 lbl_8042C1FC;

void fn_8004DE10(s32 unused, s32 index)
{
	s32 t;
	Team8004DE10* team;
	s32* count;
	s32 i;

	if (index == 0) {
		return;
	}
	t                           = lbl_8042C1FC;
	team                        = &lbl_802B908C[t];
	team->entries[index].active = 0;
	count                       = &team->entries[0].count;
	if (index != *count) {
		return;
	}
	for (i = *count - 1; i >= 0; i--) {
		if (team->entries[i].active != 0) {
			break;
		}
	}
	if (i < 0) {
		return;
	}
	*count                                = i;
	lbl_802B908C[t].entries[i].unknown98  = 0;
	lbl_802B908C[t].entries2[i].unknown98 = 0;
}
}
