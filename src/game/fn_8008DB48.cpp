#include "game/rw_types.h"

// Updates a partner's view target (HYPOTHESIS: the camera framing of an AI team member): when the
// member is active (fn_8008FBB8), not in mode 1 (fn_8008F880) and has a target count
// (fn_8008F77C), the target point from fn_8008DDB0 becomes +0x5F0 and the view range +0x600/+0x604
// is lbl_8042B2A0/lbl_8042B2A8 plus lbl_8042D8D8 times +0x89C. A member of a team in formation 2
// or 3 (+0x140; one of the three members +0x134) with flag 0x10 (+0x30) hands its offset
// (+0x7A8) to the target and the leader (+0x114 by +0x3A) and clears it. Unless the member's
// action (+0x628) is 4..6, the range then widens towards lbl_8042B2A4/lbl_8042B2AC as the
// leader's speed (+0x7C0) falls below its limit (+0x850), fully below lbl_8042B2BC. The roles
// are UNKNOWN.

struct Player8008DB48;

struct Team8008DB48 {
	u8 pad0[0x3A];
	s8 current; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player8008DB48* members[3]; // 0x114
	u8 pad120[0x134 - 0x120];
	Player8008DB48* slots[3]; // 0x134
	s32 formation;            // 0x140
};

struct Player8008DB48 {
	u8 pad0[0x30];
	u16 flags; // 0x30
	u8 pad32[0x5F0 - 0x32];
	RwV3d target; // 0x5F0
	u8 pad5FC[0x600 - 0x5FC];
	f32 rangeNear; // 0x600
	f32 rangeFar;  // 0x604
	u8 pad608[0x628 - 0x608];
	s32 action; // 0x628
	u8 pad62C[0x7A8 - 0x62C];
	RwV3d offset; // 0x7A8
	u8 pad7B4[0x7C0 - 0x7B4];
	f32 speed; // 0x7C0
	u8 pad7C4[0x850 - 0x7C4];
	f32 speedLimit; // 0x850
	u8 pad854[0x89C - 0x854];
	f32 scale; // 0x89C
	u8 pad8A0[0x9B8 - 0x8A0];
	Team8008DB48* team; // 0x9B8
};

extern "C" {
extern f32 lbl_8042B2A0;
extern f32 lbl_8042B2A4;
extern f32 lbl_8042B2A8;
extern f32 lbl_8042B2AC;
extern f32 lbl_8042B2BC;
extern const f32 lbl_8042D878; // 0.0f
extern const f32 lbl_8042D8C8; // 1.0f
extern const f32 lbl_8042D8D8;
s32 fn_8008FBB8(Player8008DB48* player);
s32 fn_8008F880(Player8008DB48* player);
s32 fn_8008F77C(Player8008DB48* player);
void* fn_8008DDB0(Player8008DB48* player, s32 count, s32 unknown, RwV3d* target);
}

extern "C" void fn_8008DB48(Player8008DB48* player)
{
	if (fn_8008FBB8(player) == 0) {
		return;
	}
	if (fn_8008F880(player) == 1) {
		return;
	}
	s32 count = fn_8008F77C(player);
	if (count <= 0) {
		return;
	}
	RwV3d target;
	if (fn_8008DDB0(player, count, 0, &target) == NULL) {
		return;
	}
	player->rangeNear = lbl_8042B2A0 + lbl_8042D8D8 * player->scale;
	player->rangeFar  = lbl_8042B2A8 + lbl_8042D8D8 * player->scale;
	if (player->flags & 0x10) {
		Team8008DB48* team = player->team;
		if (team->slots[0] == player || team->slots[1] == player || team->slots[2] == player) {
			if (team->formation == 2 || team->formation == 3) {
				target.x += player->offset.x;
				target.y += player->offset.y;
				target.z += player->offset.z;
				team->members[team->current]->offset.x
				    = player->offset.x + team->members[team->current]->offset.x;
				team->members[team->current]->offset.y
				    = player->offset.y + team->members[team->current]->offset.y;
				team->members[team->current]->offset.z
				    = player->offset.z + team->members[team->current]->offset.z;
				player->offset.x = player->offset.y = player->offset.z = lbl_8042D878;
			}
		}
	}
	player->target.x = target.x;
	player->target.y = target.y;
	player->target.z = target.z;
	// Actions 4, 5 and 6 (5..6 as one unsigned range test, the retail shape).
	if (player->action == 4) {
		return;
	}
	if ((u32)(player->action - 5) <= 1) {
		return;
	}
	Player8008DB48* leader = player->team->members[player->team->current];
	f32 limit;
	f32 speed;
	speed = leader->speed;
	limit = leader->speedLimit;
	if (speed > limit) {
		return;
	}
	if (speed < lbl_8042B2BC) {
		player->rangeNear = lbl_8042B2A4 + lbl_8042D8D8 * player->scale;
		player->rangeFar  = lbl_8042B2AC + lbl_8042D8D8 * player->scale;
	} else {
		f32 ratio = lbl_8042D8C8 - speed / limit;
		player->rangeNear += ratio * (lbl_8042B2A4 - lbl_8042B2A0);
		player->rangeFar += ratio * (lbl_8042B2AC - lbl_8042B2A8);
	}
}
