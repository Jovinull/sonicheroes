// Sets word 0x2320 of a team record to 60: team `team` when it is not negative, otherwise the
// current team (lbl_8042C1FC). The first argument is unused. HYPOTHESIS: 60 is a frame count
// (one second at 60 Hz); the field role is UNKNOWN.
#include "types.h"

struct Team8004CBF8 {
	u8 pad0[0x2320];
	s32 unknown2320; // 0x2320
};

extern "C" {
extern Team8004CBF8 lbl_802B908C[];
extern s32 lbl_8042C1FC;

void fn_8004CBF8(s32 unused, s32 team)
{
	if (team >= 0) {
		lbl_802B908C[team].unknown2320 = 60;
	} else {
		lbl_802B908C[lbl_8042C1FC].unknown2320 = 60;
	}
}
}
