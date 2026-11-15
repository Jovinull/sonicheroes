// Moves a player around its team leader: advances the orbit angle (+0x672) by 32 times the orbit
// speed (+0x670) plus 0x800, eases the radius (+0x674) toward lbl_8042E41C by lbl_8042E418, and
// sets the velocity (+0x720, filtered by fn_8003EB18 into +0x7C0) to the step from the player's
// position (+0x708) to the point at that angle and radius around the leader's position, raised by
// lbl_8042E394; the player faces a quarter turn ahead of the angle (+0x700, +0x73C). fn_800D7AE4
// and fn_800D7B00 are the angle's cosine and sine. HYPOTHESIS: the roles are UNKNOWN.
#include "game/miscs.h"

struct Player800EE9FC;

struct Team800EE9FC {
	u8 pad0[0x3A];
	s8 current; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player800EE9FC* members[3]; // 0x114
};

struct Player800EE9FC {
	u8 pad0[0x670];
	s16 orbitSpeed; // 0x670
	s16 orbitAngle; // 0x672
	f32 radius;     // 0x674
	u8 pad678[0x6F0 - 0x678];
	u8 action[0x700 - 0x6F0]; // 0x6F0 (the action state, see fn_8008A3C4)
	s32 yaw;                  // 0x700
	u8 pad704[0x708 - 0x704];
	RwV3d position; // 0x708
	u8 pad714[0x720 - 0x714];
	RwV3d velocity; // 0x720
	u8 pad72C[0x73C - 0x72C];
	s32 yaw73C; // 0x73C
	u8 pad740[0x7C0 - 0x740];
	RwV3d speed; // 0x7C0
	u8 pad7CC[0x9B8 - 0x7CC];
	Team800EE9FC* team; // 0x9B8
};

extern "C" {
extern const f32 lbl_8042E394;
extern const f32 lbl_8042E418;
extern const f32 lbl_8042E41C;
f32 fn_800D7AE4(s32 angle);
f32 fn_800D7B00(s32 angle);
void fn_8003EB18(void* action, RwV3d* velocity);
}

f32 AdjustFloat(f32 value, f32 target, f32 step);

extern "C" void fn_800EE9FC(Player800EE9FC* player)
{
	player->orbitAngle += player->orbitSpeed * 32 + 0x800;
	player->radius = AdjustFloat(player->radius, lbl_8042E41C, lbl_8042E418);

	Player800EE9FC* leader = player->team->members[player->team->current];
	f32 x                  = player->radius * fn_800D7AE4(player->orbitAngle);
	f32 z                  = player->radius * fn_800D7B00(player->orbitAngle);
	RwV3d center           = leader->position;
	RwV3d step;
	step.x = (center.x + x) - player->position.x;
	step.y = (center.y + lbl_8042E394) - player->position.y;
	step.z = (center.z + z) - player->position.z;

	player->yaw73C = player->yaw = player->orbitAngle + 0x4000;
	player->velocity             = step;
	fn_8003EB18(player->action, &step);
	player->speed = step;
}
