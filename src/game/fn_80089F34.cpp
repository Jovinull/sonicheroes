// Player condition check (HYPOTHESIS; the meaning is UNKNOWN): 0 when fn_8008915C reports
// something, when bit 13 of the flags at 0x6F6 is set or when the counter at 0x774 is positive;
// otherwise, when the word 0x5FC is -1 and the team's current member is not moving (squared speed
// at 0x61C not above lbl_8042D878), only the states 2, 6, 8 and 15 (0x628, jump table in owned
// .data) give 1. Every other path gives 1.
#include "types.h"

struct Leader80089F34 {
	u8 pad0[0x61C];
	f32 speedX; // 0x61C
	f32 speedY; // 0x620
	f32 speedZ; // 0x624
};

struct Team80089F34 {
	u8 pad0[0x3A];
	s8 current; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Leader80089F34* members[3]; // 0x114
};

struct Player80089F34 {
	u8 pad0[0x5FC];
	s32 f5FC; // 0x5FC
	u8 pad600[0x628 - 0x600];
	u32 state; // 0x628
	u8 pad62C[0x6F6 - 0x62C];
	s16 flags6F6; // 0x6F6
	u8 pad6F8[0x774 - 0x6F8];
	s16 f774; // 0x774
	u8 pad776[0x9B8 - 0x776];
	Team80089F34* team; // 0x9B8
};

extern "C" {
extern f32 lbl_8042D878;
s32 fn_8008915C(Player80089F34* player);

s32 fn_80089F34(Player80089F34* p)
{
	if (fn_8008915C(p) != 0) {
		return 0;
	}
	if (p->flags6F6 & 0x2000) {
		return 0;
	}
	if (p->f774 > 0) {
		return 0;
	}
	if (p->f5FC == -1) {
		Leader80089F34* leader = p->team->members[p->team->current];
		if (!(leader->speedZ * leader->speedZ
		            + (leader->speedX * leader->speedX + leader->speedY * leader->speedY)
		        > lbl_8042D878)) {
			switch (p->state) {
				case 2:
				case 6:
				case 8:
				case 15:
					break;
				case 0:
				case 1:
				case 3:
				case 4:
				case 5:
				case 7:
				case 9:
				case 10:
				case 11:
				case 12:
				case 13:
				case 14:
				default:
					return 0;
			}
		}
	}
	return 1;
}
}
