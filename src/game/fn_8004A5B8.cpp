// Looks up cell (x, y) of an object's 64-column byte grid (+0x308). While fn_80018EA8 reports the
// alternative mode on lbl_8029C310, it instead returns whether x lies in [v, v + 1] for one of the
// first one or two values of lbl_8042AF50 (two unless the byte +0x1E of lbl_8042C180 is 0).
// HYPOTHESIS: a stage map lookup with a demo override; the roles are UNKNOWN.
#include "types.h"

struct Grid8004A5B8 {
	u8 pad0[0x308];
	s8 cells[1][64]; // 0x308 (row count UNKNOWN)
};

struct State8004A5B8 {
	u8 pad0[0x1E];
	s8 unknown1E; // 0x1E
};

extern "C" {
extern u8 lbl_8029C310[];
extern s32 lbl_8042AF50[2];
extern State8004A5B8* lbl_8042C180;
s32 fn_80018EA8(void* state);

s32 fn_8004A5B8(Grid8004A5B8* grid, s32 x, s32 y)
{
	if (fn_80018EA8(lbl_8029C310) != 0) {
		s32 count = 2;
		s32 i;

		if (lbl_8042C180->unknown1E == 0) {
			count = 1;
		}
		for (i = 0; i < count; i++) {
			if (x >= lbl_8042AF50[i] && x <= lbl_8042AF50[i] + 1) {
				return 1;
			}
		}
		return 0;
	}
	return grid->cells[y][x];
}
}
