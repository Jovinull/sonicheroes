#include "types.h"

// Selects the given team: lbl_8042C1FC = team and lbl_8042C208 points at its
// block (0x40 into its 0x2324-byte record at lbl_802B908C). The first
// argument is unused.

extern "C" u8 lbl_802B908C[];
extern "C" s32 lbl_8042C1FC;
extern "C" void* lbl_8042C208;

extern "C" void fn_8004EC9C(void* self, s32 team)
{
	lbl_8042C1FC = team;
	lbl_8042C208 = lbl_802B908C + team * 0x2324 + 0x40;
}
