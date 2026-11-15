#include "types.h"

// Chooses a player's render settings for its action: the render block (+0x38) loses flags 0x4000
// and 0x800000 (+0x4); the two 2-bit modes of its +0x3 start at 3 with flag 0x8000 (+0x770), 1
// with action flag 0x400 (+0x6F6) or 0, and become 1 in team state 2 (+0x140) when fn_8008915C
// refuses and the team member (+0x114 by +0x3A) is in mode 2 with flags 0x500 while the player is
// not in mode 0x11/0x12 (+0x628). Modes 0x1C (team state 1), 0x3B, 0x3E..0x40 (or +0x6F2 = 0x40)
// and 0x50 pick the kinds 0xE, 0xF, 0xC (with flag 0x800000) and 0x11 (+0x0) and the value +0x2C.
// HYPOTHESIS: the roles (outline, shadow, blur) are UNKNOWN.
// NonMatching (17 words, registers only): retail keeps the player in r25 and the mode in r26;
// MWCC swaps them. All declaration orders (perm.py), an s16 mode and a parameter copy were tried.
// The +0x3 modes are masked by hand in the retail code (no bitfield inserts).

struct Render8007A640 {
	u8 kind; // 0x0
	u8 pad1[0x3 - 0x1];
	u8 modes;  // 0x3 (bits 0-1: first mode, bits 2-3: second mode)
	u32 flags; // 0x4
};

struct Player8007A640;

struct Team8007A640 {
	u8 pad0[0x3A];
	s8 member; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player8007A640* members[3]; // 0x114
	u8 pad120[0x140 - 0x120];
	s32 state; // 0x140
	u8 pad144[0x209 - 0x144];
	s8 unknown209; // 0x209
};

struct Player8007A640 {
	u8 pad0[0x2C];
	s16 unknown2C; // 0x2C
	u8 pad2E[0x38 - 0x2E];
	Render8007A640* render; // 0x38
	u8 pad3C[0x628 - 0x3C];
	s32 mode628; // 0x628
	u8 pad62C[0x6F0 - 0x62C];
	s16 mode;       // 0x6F0
	s16 unknown6F2; // 0x6F2
	u8 pad6F4[0x6F6 - 0x6F4];
	s16 actionFlags; // 0x6F6
	u8 pad6F8[0x770 - 0x6F8];
	s16 flags; // 0x770
	u8 pad772[0x9B8 - 0x772];
	Team8007A640* team; // 0x9B8
};

extern "C" s32 fn_8008915C(Player8007A640* player);

extern "C" void fn_8007A640(Player8007A640* player)
{
	s32 first;
	s32 second;
	s32 value;
	s32 kind;
	Render8007A640* render;
	s32 mode;
	s32 state;

	render = player->render;
	render->flags &= ~0x804000;
	value = 1;
	kind  = 0;
	if (player->flags & 0x8000) {
		first  = 3;
		second = 3;
	} else if (player->actionFlags & 0x400) {
		first  = 1;
		second = 1;
	} else {
		first  = 0;
		second = 0;
	}
	mode  = player->mode;
	state = player->team->state;
	if (fn_8008915C(player) == 0 && state == 2) {
		Player8007A640* member = player->team->members[player->team->member];
		if (member->mode == 2 && (member->actionFlags & 0x500) && player->mode628 != 0x11
		    && player->mode628 != 0x12) {
			first  = 1;
			second = 1;
		}
	}
	switch (mode) {
		case 0x1C:
			if (state == 1) {
				kind   = 0xE;
				value  = 3;
				first  = 2;
				second = 1;
			}
			break;
		case 0x3B:
			kind = 0xF;
			if (player->team->unknown209 >= 2) {
				value = 3;
			} else {
				value = 0;
			}
			first  = 2;
			second = 1;
			break;
		default:
			if (player->unknown6F2 != 0x40) {
				break;
			}
		case 0x40:
			value = 3;
		case 0x3E:
		case 0x3F:
			kind   = 0xC;
			first  = 2;
			second = 1;
			render->flags |= 0x800000;
			break;
		case 0x50:
			kind = 0x11;
			break;
	}
	player->unknown2C = value;
	render->kind      = kind;
	render->modes     = (render->modes & ~3) | (first & 3);
	render->modes     = (render->modes & ~0xC) | ((second << 2) & 0xC);
}
