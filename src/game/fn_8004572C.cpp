// Whether a player may grab its pending target: fn_80089204 must allow the action, a player with
// flag 0x2 (+0x98C) must be within 7 of its reference height (+0x99C vs +0x9A0), its action
// (+0x6F0) must be 0, 0xC-0xE, 0x34 or 0x35, or 0x29 while it is the team's previous leader
// (+0x3B), and fn_800415A4 must succeed; then fn_800412DC runs and the result is whether a pending
// target (+0x680) is set. HYPOTHESIS: the names are UNKNOWN.
#include "types.h"

extern "C" double __fabs(double x);

struct Team8004572C;

struct Player8004572C {
	u8 pad0[0x680];
	void* pending; // 0x680
	u8 pad684[0x6F0 - 0x684];
	s16 action; // 0x6F0
	u8 pad6F2[0x98C - 0x6F2];
	u32 flags98C; // 0x98C
	u8 pad990[0x99C - 0x990];
	f32 unknown99C; // 0x99C
	f32 unknown9A0; // 0x9A0
	u8 pad9A4[0x9B8 - 0x9A4];
	Team8004572C* team; // 0x9B8
};

struct Team8004572C {
	u8 pad0[0x3B];
	s8 previous; // 0x3B
	u8 pad3C[0x114 - 0x3C];
	Player8004572C* players[3]; // 0x114
};

extern "C" {
extern f32 lbl_8042D1C8; // 7.0f
s32 fn_80089204(Player8004572C* p);
s32 fn_800415A4(Player8004572C* p);
void fn_800412DC(Player8004572C* p);

s32 fn_8004572C(Player8004572C* p)
{
	if (fn_80089204(p) == 0) {
		return 0;
	}
	if ((p->flags98C & 2) && (f32)__fabs(p->unknown99C - p->unknown9A0) > lbl_8042D1C8) {
		return 0;
	}
	switch (p->action) {
		case 0:
		case 0xC:
		case 0xD:
		case 0xE:
		case 0x34:
		case 0x35:
			break;
		case 0x29:
			if (p->team->players[p->team->previous] == p) {
				break;
			}
			// fallthrough
		default:
			return 0;
	}
	if (fn_800415A4(p) != 0) {
		fn_800412DC(p);
		if (p->pending != NULL) {
			return 1;
		}
	}
	return 0;
}
}
