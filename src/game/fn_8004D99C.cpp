#include "types.h"

// Clears the first word of the current team's entry (lbl_8042C1FC indexes the
// 0xC-byte table at lbl_802D5AF0).

struct TeamEntry {
	s32 value; // 0x0
	u8 unk4[0x8];
};

extern "C" s32 lbl_8042C1FC;
extern "C" TeamEntry lbl_802D5AF0[4];

extern "C" void fn_8004D99C()
{
	s32 value = 0;
	s32 team  = lbl_8042C1FC;

	lbl_802D5AF0[team].value = value;
}
