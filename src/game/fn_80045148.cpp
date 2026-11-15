// Whether a player (character 0, +0x761) should run the check fn_800EE0B4 on its position (+0x708):
// always 1 while the team record (+0x9B8) is in phase 9 (+0x154); otherwise only in team mode 0
// (+0x140), in actions 2-4, and while the team word +0x1FE is positive or flag 0x8000 of +0x780 is
// set, returning whether the check is positive. HYPOTHESIS: an ability trigger of the speed
// character; the names are UNKNOWN. The check is reached through a goto: the retail code places
// it after both `return 0` blocks.
#include "types.h"

struct Team80045148 {
	u8 pad0[0x140];
	s32 mode; // 0x140
	u8 pad144[0x154 - 0x144];
	s32 phase; // 0x154
	u8 pad158[0x1FE - 0x158];
	s16 unknown1FE; // 0x1FE
};

struct Player80045148 {
	u8 pad0[0x6F0];
	s16 action; // 0x6F0
	u8 pad6F2[0x708 - 0x6F2];
	u8 position[0xC]; // 0x708
	u8 pad714[0x761 - 0x714];
	s8 character; // 0x761
	u8 pad762[0x780 - 0x762];
	s32 flags780; // 0x780
	u8 pad784[0x9B8 - 0x784];
	Team80045148* team; // 0x9B8
};

extern "C" {
s32 fn_800EE0B4(Player80045148* p, void* position);

s32 fn_80045148(Player80045148* p)
{
	Team80045148* team;

	if (p->character != 0) {
		return 0;
	}
	team = p->team;
	if (team->phase == 9) {
		return 1;
	}
	if (team->mode == 0) {
		switch (p->action) {
			case 2:
			case 3:
			case 4:
				if (team->unknown1FE > 0 || (p->flags780 & 0x8000)) {
					goto check;
				}
		}
		return 0;
	}
	return 0;
check:
	if (fn_800EE0B4(p, p->position) > 0) {
		return 1;
	}
	return 0;
}
}
