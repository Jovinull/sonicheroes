#include "types.h"

// Team-wide helpers of the stage modules that carry the sled stages' objects
// (01D, 05D, 07D, 11D): teamSetModeF and teamSetMode9 put the three members of
// a team, in the module's member order, in mode 0xF or 9; teamFlagLeaders
// sets the game's flag for each team's leader.

typedef struct TeamInfo {
	u8 unk000[0x110];
	s8 members[3]; // 0x110
	u8 unk113[0x39];
	s8 leader; // 0x14C
} TeamInfo;

typedef struct GameState {
	u8 unk00[0x30];
	s32 leaderFlags[8]; // 0x30
} GameState;

extern "C" TeamInfo* lbl_80303DC8[];
extern "C" GameState lbl_8029BBD0;
extern "C" s32 teamMemberOrder[];

extern "C" s32 fn_800927D0(TeamInfo* team, s32 member);
extern "C" void fn_800E1208(s32 player, s32 mode, s32 arg);

extern "C" void teamSetModeF(s32 no)
{
	TeamInfo* team = lbl_80303DC8[no];

	if (team != NULL) {
		s32 i;

		for (i = 0; i < 3; i++) {
			s32 member = fn_800927D0(team, teamMemberOrder[i]);

			fn_800E1208(team->members[member], 0xF, 0);
		}
	}
}

extern "C" void teamSetMode9(s32 no)
{
	TeamInfo* team = lbl_80303DC8[no];

	if (team != NULL) {
		s32 i;

		for (i = 0; i < 3; i++) {
			s32 member = fn_800927D0(team, teamMemberOrder[i]);

			fn_800E1208(team->members[member], 9, 0);
		}
	}
}

extern "C" void teamFlagLeaders(void)
{
	u8 i;

	for (i = 0; i < 4; i++) {
		TeamInfo* team = lbl_80303DC8[i];

		if (team != NULL) {
			lbl_8029BBD0.leaderFlags[team->leader] = 1;
		}
	}
}
