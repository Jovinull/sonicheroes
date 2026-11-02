#include "types.h"

// The capture enemy's check on its held player (captureFreePlayerCheck here),
// the same in the seven stage modules that carry the capture: once the held
// player's team is in state 9 with a valid follower, the player is let go
// (mode 0xF) and the enemy holds nobody.

namespace nSearchPlayer
{
s32 GetTeamNoFromPlayerNum(s32 player);
}

typedef struct CaptureTeam {
	u8 unk000[0x14E];
	s16 follower; // 0x14E
	u8 unk150[0x4];
	s32 state; // 0x154
} CaptureTeam;

typedef struct Capture {
	u8 unk000[0x278];
	s32 player; // 0x278
} Capture;

extern "C" CaptureTeam* lbl_80303DC8[];

extern "C" void fn_800E1208(s32 player, s32 mode, s32 arg);

extern "C" void captureFreePlayerCheck(Capture* object)
{
	if (object->player != -1) {
		s32 team = nSearchPlayer::GetTeamNoFromPlayerNum(object->player);

		if (team != -1) {
			CaptureTeam* info = lbl_80303DC8[team];

			if (info != NULL) {
				s32 follower;

				if (info->state != 9) {
					follower = -1;
				} else {
					follower = info->follower;
				}
				if (follower != -1 && object->player != -1) {
					fn_800E1208(object->player, 0xF, 0);
					object->player = -1;
				}
			}
		}
	}
}
