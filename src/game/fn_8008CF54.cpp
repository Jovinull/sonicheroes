#include "game/octree.h"

// Pushes a player out of the stage geometry along a line (lbl_8042C150's
// DetectLineCollisionWithPolygons with the filter fn_8008FDF4): normally from the player's slot
// reference point (fn_8003E2E4 of the number +0x760) to its position (+0x708); while the stage is
// busy (fn_80018EA8 on lbl_8029C310) from its position along the team leader's +0x80C scaled by
// lbl_8042D8D4 (team +0x9B8, members +0x114 by +0x3A). A hit moves the player to the hit point and
// turns its angle (+0x6FC) onto the polygon normal (fn_800EC828); a miss sets +0x774 to 3.
// HYPOTHESIS: the roles are UNKNOWN.

struct Angle8008CF54 {
	s32 x;
	s32 y;
	s32 z;
};

struct Player8008CF54;

struct Team8008CF54 {
	u8 pad0[0x3A];
	s8 member; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player8008CF54* members[3]; // 0x114
};

struct Player8008CF54 {
	u8 pad0[0x6FC];
	Angle8008CF54 angle; // 0x6FC
	RwV3d position;      // 0x708
	u8 pad714[0x760 - 0x714];
	s8 number; // 0x760
	u8 pad761[0x774 - 0x761];
	s16 unknown774; // 0x774
	u8 pad776[0x80C - 0x776];
	RwV3d unknown80C; // 0x80C
	u8 pad818[0x9B8 - 0x818];
	Team8008CF54* team; // 0x9B8
};

extern "C" {
extern OCTREE* lbl_8042C150;
extern u8 lbl_8029C310[];
extern const f32 lbl_8042D8D4;
s32 fn_80018EA8(void* stage);
void fn_8003E2E4(s32 number, s32 unknown, RwV3d* point, s32 unknown2);
void fn_800EC828(Player8008CF54* player, RwV3d* normal, Angle8008CF54* angle);
s32 fn_8008FDF4(POLYDATA* poly);
}

extern "C" void fn_8008CF54(Player8008CF54* player)
{
	if (fn_80018EA8(lbl_8029C310) == 0) {
		RwV3d start;
		RwV3d line;
		RwV3d hit;
		fn_8003E2E4(player->number, 1, &start, 0);
		line.x = player->position.x - start.x;
		line.y = player->position.y - start.y;
		line.z = player->position.z - start.z;
		POLYDATA* poly
		    = lbl_8042C150->DetectLineCollisionWithPolygons(&start, &line, &hit, fn_8008FDF4);
		if (poly != NULL) {
			player->position.x  = hit.x;
			player->position.y  = hit.y;
			player->position.z  = hit.z;
			Angle8008CF54 angle = player->angle;
			fn_800EC828(player, &poly->norm, &angle);
			player->angle = angle;
		} else {
			player->unknown774 = 3;
		}
	} else {
		Player8008CF54* leader = player->team->members[player->team->member];
		RwV3d line;
		RwV3d hit;
		line.x         = lbl_8042D8D4 * leader->unknown80C.x;
		line.y         = lbl_8042D8D4 * leader->unknown80C.y;
		line.z         = lbl_8042D8D4 * leader->unknown80C.z;
		POLYDATA* poly = lbl_8042C150->DetectLineCollisionWithPolygons(
		    &player->position, &line, &hit, fn_8008FDF4);
		if (poly != NULL) {
			player->position.x  = hit.x;
			player->position.y  = hit.y;
			player->position.z  = hit.z;
			Angle8008CF54 angle = player->angle;
			fn_800EC828(player, &poly->norm, &angle);
			player->angle = angle;
		} else {
			player->unknown774 = 3;
		}
	}
}
