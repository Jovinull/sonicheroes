// Returns word 0x90 of entry `i` of the third 0x114-byte array (at +0x1140) of the current team
// record (lbl_802B908C[lbl_8042C1FC]). The first argument is unused. The layout follows the other
// units of the team record (fn_8004DD18); the array and field roles are UNKNOWN.
#include "types.h"

struct Entry8004E564 {
	u8 pad0[0x90];
	s32 unknown90; // 0x90
	u8 pad94[0x114 - 0x94];
};

struct Team8004E564 {
	u8 pad0[0x1140];
	Entry8004E564 entries[8]; // 0x1140 (extent UNKNOWN)
	u8 pad19E0[0x2324 - 0x19E0];
};

extern "C" {
extern Team8004E564 lbl_802B908C[];
extern s32 lbl_8042C1FC;

s32 fn_8004E564(s32 unused, s32 i)
{
	return lbl_802B908C[lbl_8042C1FC].entries[i].unknown90;
}
}
