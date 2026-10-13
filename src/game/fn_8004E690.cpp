#include "types.h"

// Selects team 0: lbl_8042C1FC = 0 and lbl_8042C208 points at its block
// (0x40 into the 0x2324-byte records at lbl_802B908C). fn_8004EC9C does the
// same for any team.

extern "C" u8 lbl_802B908C[];
extern "C" s32 lbl_8042C1FC;
extern "C" void* lbl_8042C208;

extern "C" void fn_8004E690(void)
{
	lbl_8042C1FC = 0;
	lbl_8042C208 = lbl_802B908C + 0x40;
}
