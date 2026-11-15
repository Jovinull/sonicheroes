// Chooses a player's next motion (+0x8AE) in the idle/run family, unless the current motion
// (+0x8B0) is 0x43 or 0x3E: in team mode 2 (+0x140 of the team record +0x9B8) a player allowed by
// fn_800892A0 whose team byte +0x121 is above 1 and without flag 0x8000 (+0x780) goes to 0x41;
// motion 0xB continues with 0xC; motions 0x19 are kept; around motion 0x3B it falls back to 0xD
// once the timer +0x774 is over and the speed +0x7C4 is below lbl_8042D1BC; otherwise the delay
// +0x668 (at most 3) counts down before 0xD. HYPOTHESIS: the names are UNKNOWN.
#include "types.h"

struct Team800465D8 {
	u8 pad0[0x121];
	s8 unknown121; // 0x121
	u8 pad122[0x140 - 0x122];
	s32 mode; // 0x140
};

struct Player800465D8 {
	u8 pad0[0x668];
	s16 delay; // 0x668
	u8 pad66A[0x774 - 0x66A];
	s16 timer; // 0x774
	u8 pad776[0x780 - 0x776];
	s32 flags780; // 0x780
	u8 pad784[0x7C4 - 0x784];
	f32 speed; // 0x7C4
	u8 pad7C8[0x8AE - 0x7C8];
	s16 nextMotion; // 0x8AE
	s16 motion;     // 0x8B0
	u8 pad8B2[0x9B8 - 0x8B2];
	Team800465D8* team; // 0x9B8
};

extern "C" {
extern f32 lbl_8042D1BC;
s32 fn_800892A0(Player800465D8* p);

void fn_800465D8(Player800465D8* p)
{
	Team800465D8* team = p->team;

	if (p->motion != 0x43 && p->motion != 0x3E) {
		if (team->mode == 2 && fn_800892A0(p) != 0 && p->team->unknown121 > 1
		    && !(p->flags780 & 0x8000)) {
			p->nextMotion = 0x41;
		} else if (p->motion == 0xB) {
			p->nextMotion = 0xC;
		} else if (p->motion != 0x19 && p->nextMotion != 0x19) {
			if (p->motion == 0x3B || p->nextMotion == 0x3B) {
				if (p->timer <= 0 && p->speed < lbl_8042D1BC) {
					p->nextMotion = 0xD;
				}
			} else if (p->delay > 0) {
				if (p->delay > 3) {
					p->delay = 3;
				}
				p->delay--;
			} else {
				p->nextMotion = 0xD;
			}
		}
	}
}
}
