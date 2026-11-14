// Reads a player's position and/or angle triple from the history rings `back` entries behind the
// current one (counterpart of fn_8003E244). Returns 0 when the player slot lbl_802AD090[index]
// is unused, otherwise 1; null output pointers are skipped.
#include "types.h"

struct Vec8003E2E4 {
	f32 x;
	f32 y;
	f32 z;
};

struct Angle8003E2E4 {
	s32 x;
	s32 y;
	s32 z;
};

extern "C" {
extern void* lbl_802AD090[8];
extern u8 lbl_8042C1A8[8];
extern Vec8003E2E4* lbl_8042C1B0;
extern Angle8003E2E4* lbl_8042C1B4;

s32 fn_8003E2E4(s32 index, s32 back, Vec8003E2E4* position, Angle8003E2E4* angle)
{
	if (!lbl_802AD090[index]) {
		return 0;
	}
	if (position) {
		u8 slot   = lbl_8042C1A8[index] - back;
		*position = lbl_8042C1B0[slot + (index << 8)];
	}
	if (angle) {
		u8 slot = lbl_8042C1A8[index] - back;
		*angle  = lbl_8042C1B4[slot + (index << 8)];
	}
	return 1;
}
}
