// Whether a player may start the check fn_800452AC (with the limits lbl_8042D21C/lbl_8042D220):
// only for characters 0 and 3 (+0x761), while the team record (+0x9B8) is in mode 0 and the
// player's action (+0x6F0) is 0, 2-8 or 0xC-0xE. Returns 0 otherwise. HYPOTHESIS: an ability
// check of two characters; the names are UNKNOWN.
#include "types.h"

struct Team80045200 {
	u8 pad0[0x140];
	s32 mode; // 0x140
};

struct Player80045200 {
	u8 pad0[0x6F0];
	s16 action; // 0x6F0
	u8 pad6F2[0x761 - 0x6F2];
	s8 character; // 0x761
	u8 pad762[0x9B8 - 0x762];
	Team80045200* team; // 0x9B8
};

extern "C" {
extern f32 lbl_8042D21C;
extern f32 lbl_8042D220;
s32 fn_800452AC(Player80045200* p, f32 a, f32 b);

s32 fn_80045200(Player80045200* p)
{
	switch (p->character) {
		case 0:
		case 3:
			break;
		default:
			return 0;
	}
	if (p->team->mode != 0) {
		return 0;
	}
	switch (p->action) {
		case 0:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 0xC:
		case 0xD:
		case 0xE:
			break;
		default:
			return 0;
	}
	return fn_800452AC(p, lbl_8042D21C, lbl_8042D220) != 0;
}
}
