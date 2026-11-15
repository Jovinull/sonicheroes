#include "game/miscs.h"

// Turns a following team member toward its leader's heading: only when it can move (fn_8008915C
// refuses, no action flag 0x2000 at +0x6F6, no stun timer +0x774) and not while the leader (team
// +0x9B8, +0x114 by +0x3A) is in mode 0x4C or in mode 0x12/0x28 with the team's +0x265 set, in
// character state 9 with +0x6A0 = 1, or the member is in mode 0x11/0x12 (+0x628). In action 0x43
// it faces away from the leader (team state 6) or by its slot (+0x9B0) times 0x5555. Slow and
// close (speed +0x7C0 below lbl_8042B2BC, the leader record's speed below its limit and the
// member within range +0x604) it copies the leader's yaw (+0x73C), as it does when the target is
// within range and the yaws are within 0x1000; otherwise it faces its target offset (+0x610).
// HYPOTHESIS: the roles are UNKNOWN.

struct Player8008FE1C;

struct Record8008FE1C {
	u8 pad0[0x60];
	f32 speed; // 0x60
	u8 pad64[0xEC - 0x64];
	f32 limit; // 0xEC
};

struct Team8008FE1C {
	u8 pad0[0x3A];
	s8 member; // 0x3A
	u8 pad3B[0x110 - 0x3B];
	s8 slots[4];                // 0x110
	Player8008FE1C* members[3]; // 0x114
	u8 pad120[0x140 - 0x120];
	s32 state; // 0x140
	u8 pad144[0x265 - 0x144];
	s8 unknown265; // 0x265
};

struct Player8008FE1C {
	u8 pad0[0x604];
	f32 range;    // 0x604
	f32 distance; // 0x608
	u8 pad60C[0x610 - 0x60C];
	RwV3d offset; // 0x610
	u8 pad61C[0x628 - 0x61C];
	s32 mode628; // 0x628
	u8 pad62C[0x6A0 - 0x62C];
	s8 unknown6A0; // 0x6A0
	u8 pad6A1[0x6F0 - 0x6A1];
	s16 mode; // 0x6F0
	u8 pad6F2[0x6F6 - 0x6F2];
	s16 actionFlags; // 0x6F6
	u8 pad6F8[0x73C - 0x6F8];
	s32 yaw; // 0x73C
	u8 pad740[0x761 - 0x740];
	s8 character; // 0x761
	u8 pad762[0x774 - 0x762];
	s16 stun; // 0x774
	u8 pad776[0x7C0 - 0x776];
	f32 speed; // 0x7C0
	u8 pad7C4[0x9B0 - 0x7C4];
	s32 slot; // 0x9B0
	u8 pad9B4[0x9B8 - 0x9B4];
	Team8008FE1C* team; // 0x9B8
};

extern "C" {
extern Record8008FE1C* lbl_802AD0D0[];
extern f32 lbl_8042B2BC;
double __fabs(double x);
s32 fn_8008915C(Player8008FE1C* player);
f32 fn_801991B4(const RwV3d* v);
}

// game/misc.h declares DiffAngle returning u16; the callers use the full register.
s32 DiffAngle(s32 first, s32 second);

static inline BOOL CanTurn(Player8008FE1C* player)
{
	if (fn_8008915C(player)) {
		return FALSE;
	}
	if (player->actionFlags & 0x2000) {
		return FALSE;
	}
	if (player->stun > 0) {
		return FALSE;
	}
	return TRUE;
}

extern "C" void fn_8008FE1C(Player8008FE1C* player)
{
	if (!CanTurn(player)) {
		return;
	}
	Team8008FE1C* team     = player->team;
	Player8008FE1C* leader = team->members[team->member];
	f32 speed              = player->speed;
	switch (leader->mode) {
		case 0x12:
		case 0x28:
			if (team->unknown265 == 0) {
				break;
			}
			// fall through
		case 0x4C:
			return;
	}
	if (leader->unknown6A0 == 1 && leader->character == 9) {
		return;
	}
	switch (player->mode628) {
		case 0x11:
		case 0x12:
			return;
	}
	if (player->mode == 0x43) {
		if (team->state == 6) {
			player->yaw = leader->yaw + 0x8000;
		} else {
			player->yaw = leader->yaw + player->slot * 0x5555;
		}
		return;
	}
	if ((f32)__fabs(speed) < lbl_8042B2BC) {
		Team8008FE1C* own      = player->team;
		BOOL moving            = TRUE;
		Record8008FE1C* record = lbl_802AD0D0[own->slots[own->member]];
		if (!((f32)__fabs(record->speed) >= record->limit)
		    && !(player->distance >= player->range)) {
			moving = FALSE;
		}
		if (!moving) {
			player->yaw = leader->yaw;
			return;
		}
	}
	if (fn_801991B4(&player->offset) < player->range
	    && DiffAngle(leader->yaw, player->yaw) < 0x1000) {
		player->yaw = leader->yaw;
		return;
	}
	player->yaw = SetPlayerYAngle(GetYangle(player->offset.x, player->offset.z));
}
