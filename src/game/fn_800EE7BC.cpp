#include "game/rw_types.h"

// Steers a following team member towards its place in the formation (HYPOTHESIS: the follow
// movement of the AI partners): the team (+0x9B8) leader (members +0x114, current +0x3A) gives
// the place: for formation 3 (+0x34) the leader's point +0x42C plus lbl_8042E3BC times its +0x3FC
// (the offset is slowed by lbl_8042E418 beyond lbl_8042E404, kept at lbl_8042E3E4 when longer
// than that, and left alone otherwise); for the others the formation offset lbl_8023A5E0 in the
// leader's frame (fn_8003E9B4) added to its position (+0x708), the offset to it scaled by
// lbl_8042E418. The member takes the leader's yaw (+0x700, +0x73C), the offset as its push
// (+0x720) and, in its action frame (fn_8003EB18), as its velocity (+0x7C0). Roles UNKNOWN.
// NonMatching (one instruction longer, float registers): the retail switch tests 0 and then
// branches unconditionally to the shared code (MWCC keeps a beq and a b to the same label; with
// case 1 or without case 0 the tree changes), and numbers the float temporaries differently
// (the scale factors in f1/f0 instead of f4). The case values 0 and 2 are a HYPOTHESIS.

struct Action800EE7BC {
	u8 pad0[0xC];
	s32 angle[3]; // 0xC (angle[1] is the yaw)
};

struct Player800EE7BC;

struct Team800EE7BC {
	u8 pad0[0x34];
	s32 formation; // 0x34
	u8 pad38[0x3A - 0x38];
	s8 current; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player800EE7BC* members[3]; // 0x114
};

struct Player800EE7BC {
	u8 pad0[0x3FC];
	RwV3d unknown3FC; // 0x3FC
	u8 pad408[0x42C - 0x408];
	RwV3d unknown42C; // 0x42C
	u8 pad438[0x6F0 - 0x438];
	Action800EE7BC action; // 0x6F0
	RwV3d position;        // 0x708
	u8 pad714[0x720 - 0x714];
	RwV3d push; // 0x720
	u8 pad72C[0x73C - 0x72C];
	s32 yaw; // 0x73C
	u8 pad740[0x7C0 - 0x740];
	RwV3d velocity; // 0x7C0
	u8 pad7CC[0x9B8 - 0x7CC];
	Team800EE7BC* team; // 0x9B8
};

extern "C" {
extern RwV3d lbl_8023A5E0[4];
extern const f32 lbl_8042E3BC;
extern const f32 lbl_8042E3E4;
extern const f32 lbl_8042E404;
extern const f32 lbl_8042E418;
f32 fn_801991B4(RwV3d* v);
void fn_801990E0(RwV3d* dst, RwV3d* src);
void fn_8003E9B4(Action800EE7BC* action, RwV3d* vector);
void fn_8003EB18(Action800EE7BC* action, RwV3d* vector);
}

extern "C" void fn_800EE7BC(Player800EE7BC* player)
{
	Team800EE7BC* team     = player->team;
	Player800EE7BC* leader = team->members[team->current];
	RwV3d point;
	RwV3d offset;
	s32 formation = team->formation;

	switch (formation) {
		default:
		case 0:
		case 2: {
			RwV3d* place = &lbl_8023A5E0[formation];
			point.x      = place->x;
			point.y      = place->y;
			point.z      = place->z;
			fn_8003E9B4(&leader->action, &point);
			f32 y    = leader->position.y + point.y;
			f32 z    = leader->position.z + point.z;
			f32 x    = leader->position.x + point.x;
			offset.x = x - player->position.x;
			offset.y = y - player->position.y;
			offset.z = z - player->position.z;
			offset.x = lbl_8042E418 * offset.x;
			offset.y = lbl_8042E418 * offset.y;
			offset.z = lbl_8042E418 * offset.z;
			break;
		}
		case 3: {
			point.x    = leader->unknown3FC.x;
			point.y    = leader->unknown3FC.y;
			point.z    = leader->unknown3FC.z;
			point.x    = lbl_8042E3BC * point.x;
			point.y    = lbl_8042E3BC * point.y;
			point.z    = lbl_8042E3BC * point.z;
			f32 x      = point.x + leader->unknown42C.x;
			f32 y      = point.y + leader->unknown42C.y;
			f32 z      = point.z + leader->unknown42C.z;
			offset.x   = x - player->position.x;
			offset.y   = y - player->position.y;
			offset.z   = z - player->position.z;
			f32 length = fn_801991B4(&offset);
			if (length > lbl_8042E404) {
				offset.x = lbl_8042E418 * offset.x;
				offset.y = lbl_8042E418 * offset.y;
				offset.z = lbl_8042E418 * offset.z;
			} else if (length > lbl_8042E3E4) {
				fn_801990E0(&offset, &offset);
				offset.x = lbl_8042E3E4 * offset.x;
				offset.y = lbl_8042E3E4 * offset.y;
				offset.z = lbl_8042E3E4 * offset.z;
			}
			break;
		}
	}
	player->action.angle[1] = player->yaw = leader->action.angle[1];
	player->push.x                        = offset.x;
	player->push.y                        = offset.y;
	player->push.z                        = offset.z;
	fn_8003EB18(&player->action, &offset);
	player->velocity.x = offset.x;
	player->velocity.y = offset.y;
	player->velocity.z = offset.z;
}
