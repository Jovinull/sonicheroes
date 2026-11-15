// Decides whether a player follows its own way (1) or the team (0), and in the latter cases
// points the player's target (+0x5F0) at another player's position (+0x708). Returns 0 while the
// player's action (+0x6F0) is one of the busy actions; when the player is the team's reference
// player (+0x128 of the team record at +0x9B8), it takes the target, and the words +0x5FC..+0x604,
// from the player at +0x134 (its own position when there is none or it is itself); in state 0x11
// (+0x628) it targets the +0x134 player too. Otherwise the leader's state decides: 0 when its
// byte +0x6A0 is 1 or its action is 0xA, 0x26, 0x27, 0x2C or 0x4C (0x12/0x28 only while the team
// byte +0x265 is set); for leader action 0x1C a player not itself in action 0x1C targets the
// leader and returns 0. HYPOTHESIS: AI follow logic; all field and action names are UNKNOWN.
#include "types.h"

struct Vec8008FBB8 {
	f32 x;
	f32 y;
	f32 z;
};

struct Team8008FBB8;

struct Player8008FBB8 {
	u8 pad0[0x5F0];
	Vec8008FBB8 target; // 0x5F0
	s32 unknown5FC;     // 0x5FC
	f32 unknown600;     // 0x600
	f32 unknown604;     // 0x604
	u8 pad608[0x628 - 0x608];
	s32 state; // 0x628
	u8 pad62C[0x6A0 - 0x62C];
	s8 unknown6A0; // 0x6A0
	u8 pad6A1[0x6F0 - 0x6A1];
	s16 action; // 0x6F0
	u8 pad6F2[0x708 - 0x6F2];
	Vec8008FBB8 position; // 0x708
	u8 pad714[0x9B8 - 0x714];
	Team8008FBB8* team; // 0x9B8
};

struct Team8008FBB8 {
	u8 pad0[0x3A];
	s8 leader; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player8008FBB8* players[3]; // 0x114
	u8 pad120[0x128 - 0x120];
	Player8008FBB8* reference; // 0x128
	u8 pad12C[0x134 - 0x12C];
	Player8008FBB8* followed; // 0x134
	u8 pad138[0x265 - 0x138];
	s8 unknown265; // 0x265
};

static inline void TargetPlayer(Player8008FBB8* p, Player8008FBB8* other)
{
	if (other) {
		p->target = other->position;
	} else {
		p->target = p->position;
	}
}

extern "C" s32 fn_8008FBB8(Player8008FBB8* p)
{
	Team8008FBB8* team;
	Player8008FBB8* other;

	switch (p->action) {
		case 0x12:
		case 0x1F:
		case 0x21:
		case 0x26:
		case 0x27:
		case 0x28:
		case 0x2A:
		case 0x2B:
		case 0x2C:
		case 0x33:
		case 0x53:
		case 0x55:
			return 0;
	}
	team = p->team;
	if (team->reference == p) {
		other = team->followed;
		if (other && p != other) {
			p->target     = other->position;
			p->unknown5FC = other->unknown5FC;
			p->unknown600 = other->unknown600;
			p->unknown604 = other->unknown604;
		} else {
			p->target = p->position;
		}
		return 0;
	}
	if (p->state == 0x11) {
		TargetPlayer(p, team->followed);
		return 0;
	}
	other = team->players[team->leader];
	if (other->unknown6A0 == 1) {
		return 0;
	}
	switch (other->action) {
		case 0x12:
		case 0x28:
			if (team->unknown265 == 0) {
				break;
			}
			// fallthrough
		case 0xA:
		case 0x26:
		case 0x27:
		case 0x2C:
		case 0x4C:
			return 0;
		case 0x1C:
			if (p->action == 0x1C) {
				break;
			}
			TargetPlayer(p, other);
			return 0;
	}
	return 1;
}
