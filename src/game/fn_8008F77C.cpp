// Returns a player's position in its team formation (HYPOTHESIS: 0 front, 1 middle, 2 back; -1
// when the player is in neither formation list 0x12C/0x130 of its team at 0x9B8) and, for the
// front position or none, copies the position at 0x708 of the team's front member at 0x134 (or
// the player's own when there is none) to 0x5F0. Field names are inferred from this function
// only.
#include "types.h"

struct Vec8008F77C {
	f32 x;
	f32 y;
	f32 z;
};

struct Team8008F77C;

struct Player8008F77C {
	u8 pad0[0x5F0];
	Vec8008F77C formationPosition; // 0x5F0
	u8 pad5FC[0x708 - 0x5FC];
	Vec8008F77C position; // 0x708
	u8 pad714[0x9B8 - 0x714];
	Team8008F77C* team; // 0x9B8
};

struct Team8008F77C {
	u8 pad0[0x12C];
	Player8008F77C* formationA; // 0x12C
	Player8008F77C* formationB; // 0x130
	Player8008F77C* front;      // 0x134
	Player8008F77C* middle;     // 0x138
	Player8008F77C* back;       // 0x13C
};

static inline s32 GetFormationIndex(Team8008F77C* team, Player8008F77C* player)
{
	if (team->formationA == player) {
		if (team->middle == player) {
			return 1;
		}
		if (team->front == player) {
			return 0;
		}
		if (team->front) {
			return 1;
		}
		return 0;
	}
	if (team->formationB == player) {
		if (team->back == player) {
			return 2;
		}
		if (team->middle == player) {
			return 1;
		}
		if (team->front == player) {
			return 0;
		}
		if (team->middle) {
			return 2;
		}
		return 1;
	}
	return -1;
}

extern "C" {
s32 fn_8008F77C(Player8008F77C* player)
{
	Team8008F77C* team = player->team;
	s32 index          = GetFormationIndex(team, player);

	if (index <= 0) {
		Player8008F77C* front = team->front;
		if (front) {
			player->formationPosition.x = front->position.x;
			player->formationPosition.y = front->position.y;
			player->formationPosition.z = front->position.z;
		} else {
			player->formationPosition.x = player->position.x;
			player->formationPosition.y = player->position.y;
			player->formationPosition.z = player->position.z;
		}
	}
	return index;
}
}
