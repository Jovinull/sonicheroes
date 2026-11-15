#include "types.h"

// Field 0x140 of the team view: the switch selector. The shared case body reads the same
// field through a second view type, which keeps the retail code's separate reload.
struct Team80091FAC {
	u8 pad0[0x140];
	u32 mode;
};

struct TeamMode80091FAC {
	u8 pad0[0x140];
	u32 mode;
};

extern "C" int fn_80091FAC(Team80091FAC* team)
{
	switch (team->mode) {
		case 0:
		case 1:
		case 2:
			return ((TeamMode80091FAC*)team)->mode;
		case 3:
		case 9:
		case 12:
			return 2;
		case 4:
		case 7:
		case 10:
			return 0;
		case 5:
		case 6:
		case 8:
		case 11:
			return 1;
	}
}
