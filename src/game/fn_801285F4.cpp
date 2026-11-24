// Per-frame step of an object tied to a player slot (HYPOTHESIS: an Exec; the class is UNKNOWN).
// It stays alive only while its mode (0xB4) is 0 or 1, the player lbl_802AD0D0[0xB0] is in state
// 4 (byte 0x1) with the value 0x1F or 0x20 at 0x150, and the game flag at lbl_8029C310+0x18 is
// clear; then it runs fn_801286B8. Otherwise it sets bit 0 of its signal word (0x4), which the
// task system reads as a kill request. The early returns of the inline helper reproduce the
// retail block order.
#include "types.h"

struct Player801285F4 {
	u8 pad0;
	s8 f1; // 0x1
	u8 pad2[0x150 - 0x2];
	s16 f150; // 0x150
};

struct Obj801285F4 {
	u8 pad0[0x4];
	u16 signal; // 0x4
	u8 pad6[0xB0 - 0x6];
	s8 playerNo; // 0xB0
	u8 padB1[0xB4 - 0xB1];
	s32 mode; // 0xB4
};

struct Game801285F4 {
	u8 pad0[0x18];
	s32 f18; // 0x18
};

extern "C" {
extern Player801285F4* lbl_802AD0D0[8];
extern Game801285F4 lbl_8029C310;
void fn_801286B8(Obj801285F4* o);
}

static inline s32 IsDone801285F4(Obj801285F4* o)
{
	Player801285F4* p = lbl_802AD0D0[o->playerNo];
	switch (o->mode) {
		case 0:
		case 1:
			switch (p->f1) {
				case 4:
					switch (p->f150) {
						case 0x1F:
						case 0x20:
							break;
						default:
							return 1;
					}
					break;
				default:
					return 1;
			}
			break;
		default:
			return 1;
	}
	return 0;
}

extern "C" void fn_801285F4(Obj801285F4* o)
{
	if (IsDone801285F4(o) || lbl_8029C310.f18 != 0) {
		o->signal |= 1;
	} else {
		fn_801286B8(o);
	}
}
