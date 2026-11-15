// Whether a player has reached its target point (+0x5F0), optionally giving the yaw to face. A
// player that is not its team's leader (team at +0x9B8: members at +0x114, current at +0x3A)
// does not count when the leader is in character state 9 with fn_800AB32C set, in action 0x28, or
// in action 0x4C with character state 6; nor does a player in mode 0x11 (+0x628). The player
// arrives when its distance to the target (+0x608) reaches its range (+0x604; the yaw is then the
// direction from its position to the target) or when the leader's speed (+0x7C0) is at least its
// limit (+0x84C; the yaw is then the leader's, +0x73C). HYPOTHESIS: the roles are UNKNOWN.
#include "game/miscs.h"

struct Player8008A3C4;

struct Team8008A3C4 {
	u8 pad0[0x3A];
	s8 current; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player8008A3C4* members[3]; // 0x114
};

// The action state at +0x6F0.
struct Action8008A3C4 {
	s16 action; // 0x0
	u8 pad2[0x18 - 0x2];
	RwV3d position; // 0x18
	u8 pad24[0x4C - 0x24];
	s32 yaw; // 0x4C
};

struct Player8008A3C4 {
	u8 pad0[0x5F0];
	RwV3d target; // 0x5F0
	u8 pad5FC[0x604 - 0x5FC];
	f32 range;    // 0x604
	f32 distance; // 0x608
	u8 pad60C[0x628 - 0x60C];
	s32 mode; // 0x628
	u8 pad62C[0x6F0 - 0x62C];
	Action8008A3C4 action; // 0x6F0
	u8 pad740[0x761 - 0x740];
	s8 character; // 0x761
	u8 pad762[0x7C0 - 0x762];
	f32 speed; // 0x7C0
	u8 pad7C4[0x84C - 0x7C4];
	f32 speedLimit; // 0x84C
	u8 pad850[0x9B8 - 0x850];
	Team8008A3C4* team; // 0x9B8
};

extern "C" s32 fn_800AB32C(Player8008A3C4* player);
extern "C" double __fabs(double x);

extern "C" s32 fn_8008A3C4(Player8008A3C4* player, s32* yaw)
{
	Player8008A3C4* leader;
	Action8008A3C4* action;

	action = &player->action;
	leader = player->team->members[player->team->current];

	if (&leader->action != action) {
		if ((fn_800AB32C(leader) == 1 && leader->character == 9) || leader->action.action == 0x28
		    || (leader->action.action == 0x4C && leader->character == 6)) {
			return 0;
		}
	}
	if (player->mode == 0x11) {
		return 0;
	}
	if (player->distance >= player->range) {
		if (yaw != NULL) {
			*yaw = SetPlayerYAngle(GetYangle(
			    player->target.x - action->position.x, player->target.z - action->position.z));
		}
		return 1;
	}
	if ((f32)__fabs(leader->speed) >= leader->speedLimit) {
		if (yaw != NULL) {
			*yaw = leader->action.yaw;
		}
		return 1;
	}
	return 0;
}
