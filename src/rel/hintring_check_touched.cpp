#include "types.h"

// TObjHintRing::CheckTouchedByLeader (the PS2 build's name), the same in the
// thirteen stage modules that share the engine core: the ring answers the team
// (0 to 3) whose player is nearest the ring's centre (lifted by
// hintringInsideLift) within the touch range, or -1. A team in mode 2 or 3
// counts its first player that is in range, looking from its last; any other
// team counts only its leader. The distances are squared.

typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;

typedef struct HintRingPlayer {
	u8 unk000[0x760];
	s8 character; // 0x760
} HintRingPlayer;

typedef struct HintRingTeam {
	u8 unk000[0x3B];
	s8 leader; // 0x3B
	u8 unk03C[0xD4];
	s8 members[3]; // 0x110
	u8 unk113[0xE];
	s8 count; // 0x121
	u8 unk122[0x12];
	HintRingPlayer* players[3]; // 0x134
	s32 mode;                   // 0x140
} HintRingTeam;

typedef struct HintRing {
	u8 unk00[0x30];
	RwV3d pos; // 0x30
} HintRing;

extern "C" HintRingTeam* lbl_80303DC8[4];
extern "C" const f32 hintringFarthest;
extern "C" const f32 hintringInsideLift;
extern "C" const f32 hintringTouchRange;
extern "C" s32 fn_8003E2E4(s32 player, s32 kind, RwV3d* position, s32 arg3);

extern "C" s32 CheckTouchedByLeader__12TObjHintRingFv(HintRing* ring)
{
	f32 best = hintringFarthest;
	s32 i;
	s32 found;
	f32 dist;

	found = -1;

	for (i = 0; i < 4; i++) {
		HintRingTeam* team = lbl_80303DC8[i];

		if (team == NULL) {
			continue;
		}
		switch (team->mode) {
			case 2:
			case 3: {
				s32 j;

				j = team->count;
				for (j--; j >= 0; j--) {
					RwV3d pos;

					if (fn_8003E2E4(team->players[j]->character, 0, &pos, 0) == 0) {
						continue;
					}
					{
						RwV3d center = ring->pos;

						center.y += hintringInsideLift;
						pos.x -= center.x;
						pos.y -= center.y;
						pos.z -= center.z;
						dist = pos.z * pos.z + (pos.x * pos.x + pos.y * pos.y);
					}
					if (dist <= hintringTouchRange) {
						break;
					}
				}
				if (j < 0) {
					continue;
				}
				break;
			}
			default: {
				RwV3d pos;

				if (fn_8003E2E4(team->members[team->leader], 0, &pos, 0) == 0) {
					continue;
				}
				{
					RwV3d center = ring->pos;

					center.y += hintringInsideLift;
					pos.x -= center.x;
					pos.y -= center.y;
					pos.z -= center.z;
					dist = pos.z * pos.z + (pos.x * pos.x + pos.y * pos.y);
				}
				if (dist > hintringTouchRange) {
					continue;
				}
				break;
			}
		}
		if (!(best < dist)) {
			best  = dist;
			found = i;
		}
	}
	return found;
}
