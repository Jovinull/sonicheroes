#include "game/game2pTable.h"
#include "game/pathctrl.h"

// Complete C++ game2pTable unit, identified by symbolic metadata and GameCube
// table/caller relationships. Views below describe only accessed GC fields;
// their names are local reconstruction labels, not asserted original types.
struct Game2pModeView {
	u8 unk_0x00[0x1e];
	s8 field1e;
	u8 unk_0x1f[5];
	s8 field24;
};
struct Game2pPlayerView {
	u8 unk_0x00[0x760];
	s8 field760, field761;
};
struct Game2pTeamView {
	u8 unk_0x00[0x34];
	s32 field34;
	u8 unk_0x38[0x110 - 0x38];
	s8 memberNo[3];
	u8 unk_0x113;
	Game2pPlayerView* player[3];
};
struct Game2pActionView {
	u8 unk_0x00[0x2c];
	s32 stage;
};
struct GAME2PTABLE_TIME {
	s32 stage; // Metadata stage enum occupies four bytes.
	s8 minute, second;
};
struct GAME2PTABLE_POSITION {
	s32 stage;
	RwV3d pos;
};

// Only position prefixes are accessed; the remaining known-size locator
// records are opaque here and never allocated through these views.
struct GOAL_LOCATE {
	RwV3d pos;
	u8 unk_0x0c[8];
};
struct START_LOCATE {
	RwV3d pos;
	u8 unk_0x0c[16];
};

extern "C" {
extern Game2pModeView* lbl_8042C180;
extern Game2pTeamView* lbl_80303DC8[4];
extern Game2pActionView lbl_8029C310;
s32 fn_800663D0(s32 team);
s32 fn_80018C0C();
void fn_80137D0C(s32 voice, s32 character, s32 player);
GOAL_LOCATE* fn_800A2234(s32 team);
START_LOCATE* fn_800A2294(s32 locator);
}

static GAME2PTABLE_TIME timelimit_table[] = {
	{ 26, 5, 0 },
	{ 27, 5, 0 },
	{ 28, 5, 0 },
	{ 37, 10, 0 },
	{ 38, 10, 0 },
	{ 39, 10, 0 },
	{ 40, 10, 0 },
	{ 41, 10, 0 },
	{ 42, 10, 0 },
	{ 43, 1, 0 },
	{ 44, 2, 0 },
	{ 45, 1, 0 },
	{ 46, 10, 0 },
	{ 47, 10, 0 },
	{ 48, 10, 0 },
	{ 49, 10, 0 },
	{ 50, 10, 0 },
	{ 51, 10, 0 },
};
static GAME2PTABLE_POSITION start2pposition_table[] = {
	{ 37, { 0.0f, 140.0f, 850.0f } },
};
static GAME2PTABLE_POSITION goal2pposition_table[] = {
	{ 37, { -4509.0f, 100.0f, -13034.0f } },
	{ 38, { -355.0f, -4700.0f, -20400.0f } },
	{ 37, { 13018.0f, -25695.0f, -24650.0f } },
	{ 46, { 0.0f, 0.0f, 0.0f } },
	{ 47, { 0.0f, 30.0f, -4750.0f } },
	{ 48, { 0.0f, 453.0f, -1890.0f } },
	{ 49, { -39000.0f, 16717.0f, -20060.0f } },
	{ 50, { -870.0f, -720.0f, -19410.0f } },
	{ 51, { -6000.0f, 3413.0f, -13480.0f } },
};
static s32 introvoice_table[] = { 10, 11, 12, 13, 14 };

s32 game2pSetStartPosition(RwV3d* pPosition, s32 team)
{
	s32 i             = 0;
	s32 Stage_Current = lbl_8029C310.stage;
	for (; i < 1; i++) {
		if (Stage_Current == start2pposition_table[i].stage) {
			if (pPosition != NULL) {
				pPosition->x = start2pposition_table[i].pos.x;
				pPosition->y = start2pposition_table[i].pos.y;
				pPosition->z = start2pposition_table[i].pos.z;
			}
			return 1;
		}
	}
	if (lbl_80303DC8[team] == NULL)
		return 0;
	START_LOCATE* pos = fn_800A2294(lbl_80303DC8[team]->field34);
	if (pos != NULL) {
		if (pPosition != NULL) {
			pPosition->x = pos->pos.x;
			pPosition->y = pos->pos.y;
			pPosition->z = pos->pos.z;
		}
		return 1;
	}
	return 0;
}

s32 game2pSetGoalPosition(RwV3d* pPosition, s32 team)
{
	s32 i             = 0;
	s32 Stage_Current = lbl_8029C310.stage;
	for (; i < 9; i++) {
		if (Stage_Current == goal2pposition_table[i].stage) {
			if (pPosition != NULL) {
				pPosition->x = goal2pposition_table[i].pos.x;
				pPosition->y = goal2pposition_table[i].pos.y;
				pPosition->z = goal2pposition_table[i].pos.z;
			}
			return 1;
		}
	}
	GOAL_LOCATE* pos = fn_800A2234(team);
	if (pos != NULL) {
		if (pPosition != NULL) {
			pPosition->x = pos->pos.x;
			pPosition->y = pos->pos.y;
			pPosition->z = pos->pos.z;
		}
		return 1;
	}
	return 0;
}

s32 game2pSetLimitTime(s8* pMinute, s8* pSecond)
{
	s32 i             = 0;
	s32 Stage_Current = lbl_8029C310.stage;
	for (; i < 18; i++) {
		if (Stage_Current == timelimit_table[i].stage) {
			if (pMinute != NULL)
				*pMinute = timelimit_table[i].minute;
			if (pSecond != NULL)
				*pSecond = timelimit_table[i].second;
			return 1;
		}
	}
	if (pMinute != NULL)
		*pMinute = 1;
	if (pSecond != NULL)
		*pSecond = 0;
	return 0;
}

s32 game2pGetMainMemberNo(s32 team)
{
	s32 previous;
	if (lbl_8042C180->field1e != 2)
		return 0;
	switch (fn_800663D0(team)) {
		default:
			break;
		case 0:
			if (fn_800663D0((~team) & 1) > 0)
				return 2;
			return 0;
	}
	previous = fn_80018C0C();
	if (previous == -1 || fn_800663D0((~team) & 1) == 0
	    || previous == lbl_80303DC8[team]->memberNo[0]
	    || previous == lbl_80303DC8[team]->memberNo[1]
	    || previous == lbl_80303DC8[team]->memberNo[2])
		return 1;
	return 2;
}

void game2pCallIntroVoice(s32 team)
{
	// Supported modes initialize voice; retail has no default for other modes.
	s32 voice;
	s32 member                 = game2pGetMainMemberNo(team);
	Game2pTeamView* teamObject = lbl_80303DC8[team];
	if (teamObject != NULL) {
		Game2pPlayerView* player = teamObject->player[member];
		s32 character            = player->field761;
		switch (lbl_8042C180->field24) {
			case 0:
				voice = 0;
				break;
			case 6:
				voice = 1;
				break;
			case 3:
				voice = 2;
				break;
			case 1:
				voice = 3;
				break;
			case 2:
				voice = 4;
				break;
		}
		fn_80137D0C(introvoice_table[voice], character, player->field760);
	}
}
