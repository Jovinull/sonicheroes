// TEnemyScoreMan's ParalyzeEnemy, TornadoEnemy, DestroyEnemy and AddScore in
// the stage modules that carry their own copy of the score manager (31D-33D),
// the same code as main's game/enemy/e_scoreman.cpp: the enemy counts and
// timers of the frame's bonus, and a player's points through the team's
// score parameters.
#include "game/enemy/e_scoreman.h"

struct ScorePlayerView {
	u8 unknown[0x254];
	s32 player_type;
	void* teamPtr;
	s8 teamNo;
};
struct ScoreTeamView {
	u8 unknown[0x23c];
	s32 field23c;
};

extern "C" {
extern ScorePlayerView* lbl_802AD0D0[8];
extern ScoreTeamView* lbl_80303DC8[4];
void addScore__11PARAM_SCOREFiii(PARAM_SCORE*, s32, s32, s32);
}

void TEnemyScoreMan::ParalyzeEnemy(s32 playernumber)
{
	if (mPlayerNumForParalyze != -1)
		return;
	if (mPlayerNumForParalyze == playernumber) {
		++mParalyzeEnemyNum;
		return;
	}
	mPlayerNumForParalyze = playernumber;
	++mParalyzeEnemyNum;
}
void TEnemyScoreMan::TornadoEnemy(s32 teamnumber)
{
	++mTornadoEnemyNum;
	mTeamNumForTornado = teamnumber;
	mTornadoEnemyTmr   = 120;
}
void TEnemyScoreMan::DestroyEnemy(s32 playernumber)
{
	++mDestroyEnemyNum;
	mPlayerNumForDestroy = playernumber;
	mDestroyEnemyTmr     = 240;
}
void TEnemyScoreMan::AddScore(s32 playernumber, s32 score)
{
	if (playernumber == -1)
		return;
	ScorePlayerView* pwk = lbl_802AD0D0[playernumber];
	if (!pwk)
		return;
	s32 teamNo = pwk->teamNo;
	if (!lbl_80303DC8[teamNo])
		return;
	addScore__11PARAM_SCOREFiii(&static_cast<PARAM_SCORE&>(*this), teamNo, pwk->player_type, score);
}
