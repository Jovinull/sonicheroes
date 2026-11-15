#include "game/misc.h"

// Updates a team's focus point (+0x40): the current member's position (members +0x114, current
// +0x3C; its +0x708), moved by lbl_8042D998 along the member's facing (fn_8003E9B4) in team modes
// 5 and 6 (+0x140). After a member switch (+0x3D still names the previous one) the point blends
// towards the new target by the factor +0x10C, which AdjustFloat raises towards lbl_8042D92C (1)
// by lbl_8042D9B4; the switch ends when the factor reaches 1 or the target is within 1.
// HYPOTHESIS: the roles are UNKNOWN.
// NonMatching (one instruction longer): the retail code copies the old focus member by member
// into a stack slot (lfs/stfs) and keeps its X in a register; this by-value copy uses words.
// Copying member-wise into a local, an array, an inline copy and a const reference to a
// constructed temporary all let MWCC keep the copy in registers (a smaller frame).

struct Action8009AFF0 {
	u8 unknown[0x18];
};

struct Player8009AFF0 {
	u8 pad0[0x6F0];
	Action8009AFF0 action; // 0x6F0
	RwV3d position;        // 0x708
};

struct Team8009AFF0 {
	u8 pad0[0x3C];
	s8 current;  // 0x3C
	s8 previous; // 0x3D
	u8 pad3E[0x40 - 0x3E];
	RwV3d focus; // 0x40
	u8 pad4C[0x10C - 0x4C];
	f32 blend; // 0x10C
	u8 pad110[0x114 - 0x110];
	Player8009AFF0* members[3]; // 0x114
	u8 pad120[0x140 - 0x120];
	s32 mode; // 0x140
};

extern "C" {
extern const f32 lbl_8042D91C; // 0.0f
extern const f32 lbl_8042D92C; // 1.0f
extern const f32 lbl_8042D998;
extern const f32 lbl_8042D9B4;
void fn_8003E9B4(Action8009AFF0* action, RwV3d* vector);
}

// out = from * (1 - *t) + to * *t.
static inline void Blend(RwV3d* out, RwV3d from, const RwV3d* to, const f32* t)
{
	f32 x = to->x * *t;
	f32 y = to->y * *t;
	f32 z = to->z * *t;

	out->x = from.x * (lbl_8042D92C - *t);
	out->y = from.y * (lbl_8042D92C - *t);
	out->z = from.z * (lbl_8042D92C - *t);
	out->x += x;
	out->y += y;
	out->z += z;
}

extern "C" void fn_8009AFF0(Team8009AFF0* team)
{
	f32 x;
	f32 y;
	f32 z;
	RwV3d target;
	RwV3d offset;

	switch (team->mode) {
		case 5:
		case 6: {
			Player8009AFF0* player = team->members[team->current];
			x                      = player->position.x;
			y                      = player->position.y;
			z                      = player->position.z;
			offset.x               = lbl_8042D998;
			offset.y               = lbl_8042D91C;
			offset.z               = lbl_8042D91C;
			fn_8003E9B4(&player->action, &offset);
			x += offset.x;
			y += offset.y;
			z += offset.z;
			break;
		}
		default: {
			Player8009AFF0* player = team->members[team->current];
			x                      = player->position.x;
			y                      = player->position.y;
			z                      = player->position.z;
			break;
		}
	}
	while (team->previous != team->current) {
		team->blend = AdjustFloat(team->blend, lbl_8042D92C, lbl_8042D9B4);
		if (team->blend >= lbl_8042D92C) {
			team->blend    = lbl_8042D91C;
			team->previous = team->current;
			break;
		}
		target.x = x;
		target.y = y;
		target.z = z;
		if (DistanceP2P(&team->focus, &target) < lbl_8042D92C) {
			team->blend    = lbl_8042D91C;
			team->previous = team->current;
			break;
		}
		Blend(&team->focus, team->focus, &target, &team->blend);
		return;
	}
	team->focus.x = x;
	team->focus.y = y;
	team->focus.z = z;
}
