// Whether the team's leader is idle: 0 while the leader's action (+0x6F0) is one of 0x12, 0x1C,
// 0x21, 0x26, 0x28, 0x2A-0x2C or 0x55, while the team's word at +0x1FC is positive, or while
// either of the leader's vectors at +0x7C0 and +0x7A8 has a squared length above
// lbl_8042D91C; 1 otherwise. HYPOTHESIS: the vectors are velocities and the actions are the
// ones that keep a team busy; the names are UNKNOWN.
#include "types.h"

struct Vec80091330 {
	f32 x;
	f32 y;
	f32 z;
};

struct Player80091330 {
	u8 pad0[0x6F0];
	s16 action; // 0x6F0
	u8 pad6F2[0x7A8 - 0x6F2];
	Vec80091330 unknown7A8; // 0x7A8
	u8 pad7B4[0x7C0 - 0x7B4];
	Vec80091330 unknown7C0; // 0x7C0
};

struct Team80091330 {
	u8 pad0[0x3A];
	s8 leader; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player80091330* players[3]; // 0x114
	u8 pad120[0x1FC - 0x120];
	s16 unknown1FC; // 0x1FC
};

extern "C" {
extern f32 lbl_8042D91C;

bool fn_80091330(Team80091330* team)
{
	Player80091330* player = team->players[team->leader];

	switch (player->action) {
		case 0x12:
		case 0x1C:
		case 0x21:
		case 0x26:
		case 0x28:
		case 0x2A:
		case 0x2B:
		case 0x2C:
		case 0x55:
			return 0;
	}
	if (team->unknown1FC > 0) {
		return 0;
	}
	if (player->unknown7C0.x * player->unknown7C0.x + player->unknown7C0.y * player->unknown7C0.y
	        + player->unknown7C0.z * player->unknown7C0.z
	    > lbl_8042D91C) {
		return 0;
	}
	return !(player->unknown7A8.x * player->unknown7A8.x
	        + player->unknown7A8.y * player->unknown7A8.y
	        + player->unknown7A8.z * player->unknown7A8.z
	    > lbl_8042D91C);
}
}
