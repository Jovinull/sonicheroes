#include "game/rankTable.h"

// Symbolic rankTable.cpp metadata establishes C++; retail supplies table values
// and the larger final-release row counts. External views expose only accessed fields.
struct ACTION {
	u8 prefix[0x2C];
	s32 currentStageNo;
};
struct TObjTeam {
	u8 prefix[0x34];
	s32 teamKind;
};
struct MODESWITCH {
	s8 modeswitchflags[0x2C];
};
extern "C" {
extern ACTION lbl_8029C310;
extern TObjTeam* lbl_80303DC8[4];
extern MODESWITCH* lbl_8042C180;
}

struct SCORE_RANK_TABLE {
	s32 stage;
	s16 qualification[4][4];
};
struct SCORE_RANK_TABLE2 {
	s32 stage;
	s16 qualification[2][4];
};
struct TIME_RANK_TABLE {
	s32 stage;
	s8 qualification[4][4][2];
};
struct TIME_RANK_TABLE2 {
	s32 stage;
	s8 qualification[2][4][2];
};

static SCORE_RANK_TABLE score_rank_table[15] = {
	{ 2,
	    { { 450, 500, 550, 600 }, { 450, 550, 650, 700 }, { 280, 350, 420, 480 },
	        { 280, 350, 400, 450 } } },
	{ 3,
	    { { 320, 400, 450, 500 }, { 550, 700, 850, 900 }, { 250, 300, 350, 400 },
	        { 320, 370, 450, 500 } } },
	{ 4,
	    { { 350, 450, 550, 600 }, { 400, 500, 600, 650 }, { 280, 380, 450, 500 },
	        { 400, 500, 600, 650 } } },
	{ 5,
	    { { 300, 350, 400, 450 }, { 420, 520, 620, 720 }, { 300, 350, 400, 450 },
	        { 300, 350, 400, 450 } } },
	{ 6,
	    { { 280, 320, 360, 400 }, { 300, 400, 450, 500 }, { 200, 250, 300, 350 },
	        { 220, 260, 300, 320 } } },
	{ 7,
	    { { 200, 240, 280, 320 }, { 200, 280, 350, 420 }, { 150, 250, 300, 350 },
	        { 200, 240, 280, 320 } } },
	{ 8,
	    { { 200, 250, 300, 350 }, { 300, 350, 400, 450 }, { 280, 320, 360, 380 },
	        { 200, 240, 280, 320 } } },
	{ 36,
	    { { 200, 250, 300, 350 }, { 300, 350, 400, 450 }, { 280, 320, 360, 380 },
	        { 200, 240, 280, 320 } } },
	{ 9,
	    { { 200, 300, 350, 400 }, { 250, 350, 450, 550 }, { 280, 320, 360, 380 },
	        { 200, 240, 280, 320 } } },
	{ 10,
	    { { 250, 280, 320, 350 }, { 300, 350, 400, 450 }, { 300, 340, 380, 400 },
	        { 300, 340, 380, 400 } } },
	{ 11,
	    { { 200, 240, 280, 320 }, { 250, 300, 350, 400 }, { 280, 320, 380, 420 },
	        { 280, 320, 360, 400 } } },
	{ 12,
	    { { 300, 350, 400, 450 }, { 450, 550, 600, 650 }, { 300, 350, 400, 450 },
	        { 200, 250, 300, 350 } } },
	{ 13,
	    { { 200, 280, 320, 360 }, { 250, 400, 500, 580 }, { 250, 350, 400, 450 },
	        { 100, 150, 200, 250 } } },
	{ 14,
	    { { 100, 150, 180, 200 }, { 180, 230, 280, 300 }, { 230, 300, 350, 400 },
	        { 150, 250, 300, 330 } } },
	{ 15,
	    { { 350, 470, 570, 620 }, { 350, 470, 570, 620 }, { 200, 250, 330, 360 },
	        { 400, 500, 600, 650 } } },
};

static SCORE_RANK_TABLE2 score_rank_table2[15] = {
	{ 2, { { 320, 400, 450, 500 }, { 180, 250, 300, 350 } } },
	{ 3, { { 300, 350, 400, 450 }, { 250, 300, 400, 430 } } },
	{ 4, { { 320, 420, 520, 580 }, { 350, 400, 550, 600 } } },
	{ 5, { { 250, 300, 350, 400 }, { 250, 300, 350, 400 } } },
	{ 6, { { 300, 350, 400, 450 }, { 80, 100, 120, 140 } } },
	{ 7, { { 260, 280, 300, 320 }, { 120, 150, 180, 200 } } },
	{ 8, { { 200, 250, 300, 350 }, { 250, 300, 320, 340 } } },
	{ 36, { { 200, 250, 300, 350 }, { 250, 300, 320, 340 } } },
	{ 9, { { 300, 350, 380, 400 }, { 150, 200, 240, 260 } } },
	{ 10, { { 280, 300, 350, 380 }, { 320, 360, 400, 420 } } },
	{ 11, { { 240, 260, 280, 300 }, { 180, 240, 280, 320 } } },
	{ 12, { { 380, 400, 430, 450 }, { 150, 180, 200, 230 } } },
	{ 13, { { 240, 280, 320, 360 }, { 100, 150, 180, 200 } } },
	{ 14, { { 100, 180, 250, 300 }, { 150, 220, 270, 300 } } },
	{ 15, { { 200, 270, 370, 400 }, { 300, 400, 500, 550 } } },
};

static TIME_RANK_TABLE time_rank_table[9] = {
	{ 16,
	    { { { 4, 0 }, { 3, 0 }, { 2, 0 }, { 1, 0 } }, { { 4, 0 }, { 3, 0 }, { 2, 0 }, { 1, 0 } },
	        { { 4, 0 }, { 3, 0 }, { 2, 0 }, { 1, 0 } },
	        { { 4, 0 }, { 3, 0 }, { 2, 0 }, { 1, 0 } } } },
	{ 17,
	    { { { 2, 30 }, { 1, 30 }, { 1, 0 }, { 0, 30 } },
	        { { 2, 30 }, { 1, 30 }, { 1, 0 }, { 0, 30 } },
	        { { 2, 30 }, { 1, 30 }, { 1, 0 }, { 0, 30 } },
	        { { 2, 30 }, { 1, 30 }, { 1, 0 }, { 0, 30 } } } },
	{ 18,
	    { { { 5, 30 }, { 4, 30 }, { 3, 30 }, { 2, 30 } },
	        { { 6, 0 }, { 5, 0 }, { 4, 0 }, { 3, 0 } },
	        { { 4, 30 }, { 3, 30 }, { 2, 30 }, { 1, 30 } },
	        { { 6, 0 }, { 5, 0 }, { 4, 0 }, { 3, 0 } } } },
	{ 19,
	    { { { 5, 0 }, { 4, 0 }, { 3, 0 }, { 2, 0 } }, { { 5, 0 }, { 4, 0 }, { 3, 0 }, { 2, 0 } },
	        { { 5, 0 }, { 4, 0 }, { 3, 0 }, { 2, 0 } },
	        { { 5, 0 }, { 4, 0 }, { 3, 0 }, { 2, 0 } } } },
	{ 20,
	    { { { 2, 30 }, { 1, 30 }, { 1, 0 }, { 0, 30 } },
	        { { 2, 30 }, { 1, 30 }, { 1, 0 }, { 0, 30 } },
	        { { 2, 30 }, { 1, 30 }, { 1, 0 }, { 0, 30 } },
	        { { 2, 30 }, { 1, 30 }, { 1, 0 }, { 0, 30 } } } },
	{ 21,
	    { { { 7, 0 }, { 6, 0 }, { 5, 0 }, { 4, 0 } }, { { 9, 0 }, { 8, 0 }, { 7, 0 }, { 6, 0 } },
	        { { 5, 0 }, { 4, 0 }, { 3, 0 }, { 2, 0 } },
	        { { 7, 0 }, { 6, 0 }, { 5, 0 }, { 4, 0 } } } },
	{ 22,
	    { { { 6, 30 }, { 5, 30 }, { 4, 30 }, { 3, 30 } },
	        { { 6, 30 }, { 5, 30 }, { 4, 30 }, { 3, 30 } },
	        { { 6, 30 }, { 5, 30 }, { 4, 30 }, { 3, 30 } },
	        { { 6, 30 }, { 5, 30 }, { 4, 30 }, { 3, 30 } } } },
	{ 23,
	    { { { 10, 0 }, { 9, 0 }, { 8, 0 }, { 7, 0 } }, { { 10, 0 }, { 9, 0 }, { 8, 0 }, { 7, 0 } },
	        { { 10, 0 }, { 9, 0 }, { 8, 0 }, { 7, 0 } },
	        { { 10, 0 }, { 9, 0 }, { 8, 0 }, { 7, 0 } } } },
	{ 24,
	    { { { 10, 0 }, { 9, 0 }, { 8, 0 }, { 7, 0 } }, { { 10, 0 }, { 9, 0 }, { 8, 0 }, { 7, 0 } },
	        { { 10, 0 }, { 9, 0 }, { 8, 0 }, { 7, 0 } },
	        { { 10, 0 }, { 9, 0 }, { 8, 0 }, { 7, 0 } } } },
};

static TIME_RANK_TABLE2 time_rank_table2[14] = {
	{ 2,
	    { { { 11, 0 }, { 9, 0 }, { 7, 30 }, { 7, 0 } },
	        { { 6, 0 }, { 4, 0 }, { 3, 0 }, { 2, 30 } } } },
	{ 3,
	    { { { 9, 0 }, { 7, 0 }, { 5, 30 }, { 5, 0 } },
	        { { 9, 0 }, { 7, 0 }, { 6, 0 }, { 5, 30 } } } },
	{ 4,
	    { { { 11, 0 }, { 9, 30 }, { 8, 30 }, { 8, 0 } },
	        { { 7, 0 }, { 5, 0 }, { 4, 30 }, { 3, 45 } } } },
	{ 5,
	    { { { 10, 0 }, { 9, 0 }, { 8, 0 }, { 7, 0 } },
	        { { 5, 0 }, { 4, 30 }, { 4, 0 }, { 3, 30 } } } },
	{ 6,
	    { { { 12, 0 }, { 11, 0 }, { 10, 30 }, { 10, 0 } },
	        { { 10, 0 }, { 8, 0 }, { 6, 0 }, { 4, 0 } } } },
	{ 7,
	    { { { 14, 0 }, { 13, 0 }, { 12, 30 }, { 12, 0 } },
	        { { 5, 0 }, { 4, 30 }, { 4, 0 }, { 3, 30 } } } },
	{ 8,
	    { { { 12, 30 }, { 11, 30 }, { 11, 0 }, { 10, 30 } },
	        { { 5, 30 }, { 5, 0 }, { 4, 30 }, { 4, 0 } } } },
	{ 9,
	    { { { 13, 30 }, { 12, 30 }, { 12, 0 }, { 11, 30 } },
	        { { 5, 30 }, { 5, 0 }, { 4, 30 }, { 4, 0 } } } },
	{ 10,
	    { { { 16, 0 }, { 15, 0 }, { 14, 30 }, { 14, 0 } },
	        { { 5, 0 }, { 4, 30 }, { 4, 0 }, { 3, 30 } } } },
	{ 11,
	    { { { 16, 0 }, { 15, 0 }, { 14, 30 }, { 14, 0 } },
	        { { 5, 30 }, { 5, 0 }, { 4, 30 }, { 4, 0 } } } },
	{ 12,
	    { { { 13, 0 }, { 12, 0 }, { 11, 30 }, { 11, 0 } },
	        { { 5, 0 }, { 4, 30 }, { 4, 0 }, { 3, 30 } } } },
	{ 13,
	    { { { 13, 0 }, { 12, 0 }, { 11, 30 }, { 11, 0 } },
	        { { 5, 0 }, { 4, 30 }, { 4, 0 }, { 3, 30 } } } },
	{ 14,
	    { { { 16, 30 }, { 15, 30 }, { 14, 30 }, { 13, 30 } },
	        { { 9, 0 }, { 7, 0 }, { 5, 30 }, { 5, 0 } } } },
	{ 15,
	    { { { 15, 0 }, { 14, 0 }, { 13, 0 }, { 12, 0 } },
	        { { 8, 0 }, { 6, 0 }, { 5, 0 }, { 4, 30 } } } },
};

static ENUM_PLAYER_VOICE adx_rank_table[5] = { ENUM_PLAYER_VOICE_RANK_A, ENUM_PLAYER_VOICE_RANK_B,
	ENUM_PLAYER_VOICE_RANK_C, ENUM_PLAYER_VOICE_RANK_D, ENUM_PLAYER_VOICE_RANK_E };
ENUM_PLAYER_VOICE GetADXForRank(s32 rank)
{
	switch (lbl_8029C310.currentStageNo) {
		case 16:
			return ENUM_PLAYER_VOICE_CLEAR_EGGHAWK;
		case 17:
			return ENUM_PLAYER_VOICE_CLEAR_TEAM_1;
		case 18:
			return ENUM_PLAYER_VOICE_CLEAR_ZAKO_1;
		case 19:
			return ENUM_PLAYER_VOICE_CLEAR_EGGALBATROSS;
		case 20:
			return ENUM_PLAYER_VOICE_CLEAR_TEAM_2;
		case 21:
			return ENUM_PLAYER_VOICE_CLEAR_ZAKO_2;
		case 22:
			return ENUM_PLAYER_VOICE_CLEAR_KINGPAWN;
		case 23:
		case 24:
			return static_cast<ENUM_PLAYER_VOICE>(-1);
		default:
			return adx_rank_table[rank];
	}
}

s32 CheckTimeRank(s32 teamNo, s32 min, s32 sec)
{
	s32 i             = 0;
	s32 Stage_Current = lbl_8029C310.currentStageNo;
	s32 teamKind      = lbl_80303DC8[teamNo]->teamKind;
	if (lbl_8042C180->modeswitchflags[0x28] == 0) {
		for (; i < 9; ++i) {
			if (Stage_Current == time_rank_table[i].stage) {
				for (s32 j = 0; j < 4; ++j) {
					if (time_rank_table[i].qualification[teamKind][j][0] <= min
					    && (min != time_rank_table[i].qualification[teamKind][j][0]
					        || time_rank_table[i].qualification[teamKind][j][1] <= sec))
						return 4 - j;
				}
				return 0;
			}
		}
	} else {
		switch (teamKind) {
			case 1:
				teamKind = 0;
				break;
			case 2:
				teamKind = 1;
				break;
			default:
				return -1;
		}
		for (; i < 14; ++i) {
			if (Stage_Current == time_rank_table2[i].stage) {
				for (s32 j = 0; j < 4; ++j) {
					if (time_rank_table2[i].qualification[teamKind][j][0] <= min
					    && (min != time_rank_table2[i].qualification[teamKind][j][0]
					        || time_rank_table2[i].qualification[teamKind][j][1] <= sec))
						return 4 - j;
				}
				return 0;
			}
		}
	}
	return -1;
}

s32 CheckScoreRank(s32 teamNo, s32 total_score)
{
	s32 i             = 0;
	s32 Stage_Current = lbl_8029C310.currentStageNo;
	s32 teamKind      = lbl_80303DC8[teamNo]->teamKind;
	if (lbl_8042C180->modeswitchflags[0x28] == 0) {
		for (; i < 15; ++i) {
			if (Stage_Current == score_rank_table[i].stage) {
				for (s32 j = 0; j < 4; ++j) {
					if (score_rank_table[i].qualification[teamKind][j] * 100 > total_score)
						return 4 - j;
				}
				return 0;
			}
		}
	} else {
		switch (teamKind) {
			case 0:
				teamKind = 0;
				break;
			case 3:
				teamKind = 1;
				break;
			default:
				return -1;
		}
		for (; i < 15; ++i) {
			if (Stage_Current == score_rank_table2[i].stage) {
				for (s32 j = 0; j < 4; ++j) {
					if (score_rank_table2[i].qualification[teamKind][j] * 100 > total_score)
						return 4 - j;
				}
				return 0;
			}
		}
	}
	return -1;
}
