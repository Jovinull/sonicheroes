#include "game/miscs.h"

// Moves a player toward its slot in the team formation: the slot offset for the formation
// (team +0x34: entries 0..2 of lbl_8023A610, else the fourth) is turned by the leader's action
// angle (fn_8003E9B4) and added to the leader's position; the step from the player's position to
// that point, scaled by lbl_8042E418, becomes the velocity (+0x720, filtered by fn_8003EB18 into
// +0x7C0) and the player takes the leader's yaw (+0x700, +0x73C). HYPOTHESIS: the formations
// (speed, fly, power) are UNKNOWN (see fn_800EE9FC).

struct Player800EE4D0;

struct Team800EE4D0 {
	u8 pad0[0x34];
	s32 formation; // 0x34
	u8 pad38[0x3B - 0x38];
	s8 current; // 0x3B
	u8 pad3C[0x114 - 0x3C];
	Player800EE4D0* members[3]; // 0x114
};

struct Player800EE4D0 {
	u8 pad0[0x6F0];
	u8 action[0x700 - 0x6F0]; // 0x6F0
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
	Team800EE4D0* team; // 0x9B8
};

extern "C" {
extern const RwV3d lbl_8023A610[4];
extern const f32 lbl_8042E418;
void fn_8003E9B4(void* action, RwV3d* vector);
void fn_8003EB18(void* action, RwV3d* velocity);
}

// The leader-relative slot offset of a formation (formation 3 and unknown ones use the last
// entry; the explicit case 3 gives the retail compare tree).
static inline void FormationOffset(RwV3d* offset, s32 formation)
{
	switch (formation) {
		case 0:
			*offset = lbl_8023A610[0];
			return;
		case 1:
			*offset = lbl_8023A610[1];
			return;
		case 2:
			*offset = lbl_8023A610[2];
			return;
		case 3:
			break;
	}
	*offset = lbl_8023A610[3];
}

extern "C" void fn_800EE4D0(Player800EE4D0* player)
{
	Team800EE4D0* team     = player->team;
	Player800EE4D0* leader = team->members[team->current];
	RwV3d offset;

	FormationOffset(&offset, team->formation);
	fn_8003E9B4(leader->action, &offset);
	RwV3d target = leader->position;
	RwV3d step;
	// Declared in reverse: the retail float register numbering.
	f32 z;
	f32 y;
	f32 x;
	step.x = x = (target.x + offset.x) - player->position.x;
	step.y = y = (target.y + offset.y) - player->position.y;
	step.z = z     = (target.z + offset.z) - player->position.z;
	step.x         = lbl_8042E418 * x;
	step.y         = lbl_8042E418 * y;
	step.z         = lbl_8042E418 * z;
	player->yaw73C = player->yaw = leader->yaw;
	player->velocity             = step;
	fn_8003EB18(player->action, &step);
	player->speed = step;
}
