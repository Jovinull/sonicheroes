#include "types.h"

// Places a player in its team pose: the position (+0x708) becomes its target (+0x5F0). In team
// state 6 or 5 (+0x140) with formation 2 or 3 (+0x34) the player copies the team member's (team
// +0x9B8, +0x114 by +0x3A) angles (+0x738 and +0x6FC); with other formations it faces away from
// the member (state 6: +0x8000) or by its slot (+0x9B0) times 0x5555 (state 5), turning its yaw
// (+0x700) at most 0x1000 a frame (AdjustAngle). In other states both angles are copied.
// HYPOTHESIS: the roles (team moves) are UNKNOWN.

struct Angle8008A5C0 {
	s32 x;
	s32 y;
	s32 z;
};

struct Player8008A5C0;

struct Team8008A5C0 {
	u8 pad0[0x34];
	s32 formation; // 0x34
	u8 pad38[0x3A - 0x38];
	s8 member; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player8008A5C0* members[3]; // 0x114
	u8 pad120[0x140 - 0x120];
	s32 state; // 0x140
};

struct Player8008A5C0 {
	u8 pad0[0x5F0];
	f32 targetX; // 0x5F0
	f32 targetY; // 0x5F4
	f32 targetZ; // 0x5F8
	u8 pad5FC[0x6FC - 0x5FC];
	Angle8008A5C0 angle; // 0x6FC
	f32 x;               // 0x708
	f32 y;               // 0x70C
	f32 z;               // 0x710
	u8 pad714[0x738 - 0x714];
	Angle8008A5C0 angle738; // 0x738
	u8 pad744[0x9B0 - 0x744];
	s32 slot; // 0x9B0
	u8 pad9B4[0x9B8 - 0x9B4];
	Team8008A5C0* team; // 0x9B8
};

// game/misc.h declares AdjustAngle returning u16; the callers use the full register.
s32 AdjustAngle(s32 first, s32 second, s32 limit);

static inline void CopyPose(Player8008A5C0* player, const Player8008A5C0* member)
{
	player->angle738.x = member->angle738.x;
	player->angle738.y = member->angle738.y;
	player->angle738.z = member->angle738.z;
	player->angle.x    = member->angle.x;
	player->angle.y    = member->angle.y;
	player->angle.z    = member->angle.z;
}

extern "C" void fn_8008A5C0(Player8008A5C0* player)
{
	Team8008A5C0* team     = player->team;
	Player8008A5C0* member = team->members[team->member];

	player->x = player->targetX;
	player->y = player->targetY;
	player->z = player->targetZ;
	if (team->state == 6) {
		switch (team->formation) {
			case 2:
				CopyPose(player, member);
				break;
			case 3:
				CopyPose(player, member);
				break;
			default:
				player->angle738.y = member->angle738.y + 0x8000;
				player->angle.y    = AdjustAngle(player->angle.y, member->angle.y + 0x8000, 0x1000);
				break;
		}
	} else if (team->state == 5) {
		switch (team->formation) {
			case 2:
				CopyPose(player, member);
				break;
			case 3:
				CopyPose(player, member);
				break;
			default: {
				s32 offset         = player->slot * 0x5555;
				player->angle738.y = member->angle738.y - offset;
				player->angle.y    = AdjustAngle(player->angle.y, member->angle.y - offset, 0x1000);
				break;
			}
		}
	} else {
		player->angle.x    = member->angle.x;
		player->angle.y    = member->angle.y;
		player->angle.z    = member->angle.z;
		player->angle738.x = member->angle738.x;
		player->angle738.y = member->angle738.y;
		player->angle738.z = member->angle738.z;
	}
}
