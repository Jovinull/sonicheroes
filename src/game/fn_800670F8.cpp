#include "game/rw_types.h"

// Emits a player's periodic effect: unless the play-mode flags 31 or 32 (lbl_8042C180) are set for
// another team than the player's (+0x9BC), and only in state 3 (+0xA48). In animation 0x5E
// (+0x8B0), every eighth frame (+0x8B6), it spawns fn_8011ECAC at the offset +0x3FC scaled by
// lbl_8042D518 from the point +0x42C, along +0x40C scaled by lbl_8042D514 plus that offset, and
// plays sound 0x2035 at the player's position (+0x708, fn_800B4A38 on lbl_8042C388). In any other
// animation the state is reset from the team's +0x20A. HYPOTHESIS: the roles are UNKNOWN.

struct Team800670F8 {
	u8 pad0[0x20A];
	s8 state; // 0x20A
};

struct Player800670F8 {
	u8 pad0[0x3FC];
	RwV3d offset; // 0x3FC
	u8 pad408[0x40C - 0x408];
	RwV3d direction; // 0x40C
	u8 pad418[0x42C - 0x418];
	RwV3d point; // 0x42C
	u8 pad438[0x708 - 0x438];
	RwV3d position; // 0x708
	u8 pad714[0x8B0 - 0x714];
	s16 animation; // 0x8B0
	u8 pad8B2[0x8B6 - 0x8B2];
	s16 frame; // 0x8B6
	u8 pad8B8[0x9B8 - 0x8B8];
	Team800670F8* team; // 0x9B8
	s8 teamNumber;      // 0x9BC
	u8 pad9BD[0xA48 - 0x9BD];
	s8 state; // 0xA48
};

struct PlayMode800670F8 {
	s8 flags[44];
};

extern "C" {
extern PlayMode800670F8* lbl_8042C180;
extern void* lbl_8042C388;
extern const f32 lbl_8042D514;
extern const f32 lbl_8042D518;
void fn_8011ECAC(s32 unknown, s32 team, RwV3d* point, RwV3d* direction);
void fn_800B4A38(
    void* sound, s32 id, RwV3d* position, s32 unknown3, s32 unknown4, s32 unknown5, s32 unknown6);
}

extern "C" void fn_800670F8(Player800670F8* player)
{
	s32 others = ~(1 << player->teamNumber);

	if ((others & lbl_8042C180->flags[31]) || (others & lbl_8042C180->flags[32])) {
		return;
	}
	if (player->state != 3) {
		return;
	}
	Team800670F8* team = player->team;
	s32 sound          = -1;
	switch (player->animation) {
		case 0x5E:
			if ((player->frame & 7) == 0) {
				RwV3d direction;
				RwV3d point;
				// Declared in reverse: the retail float register numbering.
				f32 dz;
				f32 dy;
				f32 dx;
				direction.x = dx = lbl_8042D514 * player->direction.x;
				direction.y = dy = lbl_8042D514 * player->direction.y;
				direction.z = dz = lbl_8042D514 * player->direction.z;
				f32 x            = lbl_8042D518 * player->offset.x;
				f32 y            = lbl_8042D518 * player->offset.y;
				f32 z            = lbl_8042D518 * player->offset.z;
				direction.x      = dx + x;
				direction.y      = dy + y;
				direction.z      = dz + z;
				point.x          = x + player->point.x;
				point.y          = y + player->point.y;
				point.z          = z + player->point.z;
				fn_8011ECAC(0, player->teamNumber, &point, &direction);
				sound = 0x2035;
			}
			break;
		default:
			player->state = (s32)team->state;
			break;
	}
	if (sound != -1 && lbl_8042C388 != NULL) {
		fn_800B4A38(lbl_8042C388, (u16)sound, &player->position, 0, 1, 0, 0);
	}
}
