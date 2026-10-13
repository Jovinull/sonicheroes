#include "types.h"

// Whether the current team's entry (lbl_8042C1FC indexes the 0x114-byte table
// at lbl_802C1D1C) has its first word set.

struct TeamRecord {
	s32 value; // 0x0
	u8 unk4[0x110];
};

extern "C" TeamRecord lbl_802C1D1C[4];
extern "C" s32 lbl_8042C1FC;

extern "C" s32 fn_8004DB18(void)
{
	// Keep the index first so MWCC scales it before materializing the base.
	return lbl_8042C1FC[lbl_802C1D1C].value != 0;
}
