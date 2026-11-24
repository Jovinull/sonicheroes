// For every other member of the team (count at 0x39, own index at 0x3A, members at 0x114), picks
// by the member's action state (0x6F0, jump table in owned .data): states 18 and 40 call
// fn_80044A94 only when the member's word 0x9B4 is 1 and the team's word 0x140 is 2; the states
// listed with no action are skipped; every other state calls fn_80044A94 unless the member's word
// 0x628 is 0x11 or 0x12. When any call was made, the team's word 0x150 becomes 8. Names and roles
// are inferred.
// The jump table starts on a 4-byte boundary (0x8024F154); MWCC marks .data 8-aligned, so the
// object uses the existing data_section_alignment=4 option (see docs/advertiseD-decomp.md).
#include "types.h"

struct Player80091FF0 {
	u8 pad0[0x628];
	s32 f628; // 0x628
	u8 pad62C[0x6F0 - 0x62C];
	s16 state; // 0x6F0
	u8 pad6F2[0x9B4 - 0x6F2];
	s32 f9B4; // 0x9B4
};

struct Team80091FF0 {
	u8 pad0[0x39];
	s8 count; // 0x39
	s8 self;  // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player80091FF0* players[(0x140 - 0x114) / 4]; // 0x114
	s32 f140;                                     // 0x140
	u8 pad144[0x150 - 0x144];
	s32 f150; // 0x150
};

extern "C" {
void fn_80044A94(Player80091FF0* player);

void fn_80091FF0(Team80091FF0* team)
{
	s32 hit = 0;
	for (s32 i = 0; i < team->count; i++) {
		if (i != team->self) {
			Player80091FF0* player = team->players[i];
			if (player != NULL) {
				switch (player->state) {
					case 18:
					case 40:
						if (player->f9B4 == 1 && team->f140 == 2) {
							fn_80044A94(player);
							hit = 1;
						}
						break;
					case 10:
					case 19:
					case 20:
					case 21:
					case 22:
					case 23:
					case 24:
					case 25:
					case 26:
					case 27:
					case 28:
					case 30:
					case 33:
					case 34:
					case 35:
					case 38:
					case 39:
					case 41:
					case 42:
					case 44:
					case 51:
					case 52:
					case 54:
					case 55:
					case 59:
					case 60:
					case 83:
						break;
					default:
						switch (player->f628) {
							case 0x11:
							case 0x12:
								break;
							default:
								fn_80044A94(player);
								hit = 1;
								break;
						}
						break;
				}
			}
		}
	}
	if (hit != 0) {
		team->f150 = 8;
	}
}
}
