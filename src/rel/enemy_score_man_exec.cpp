// TEnemyScoreMan::Exec in the stage modules that carry their own copy of the
// score manager (31D-33D), the same code as main's game/enemy/e_scoreman.cpp
// (built here without exceptions): the destroyed enemy totals across
// restarts, the technical points for the frame's destroyed, blown away and
// paralysed enemies.
#include "game/enemy/e_scoreman.h"

// External accessed prefixes, not complete class definitions.
enum ACTIONMODE_TURN {
	ACTIONMODE_TURN_NONE,
	ACTIONMODE_TURN_CONTINUE,
	ACTIONMODE_TURN_RESTART,
	ACTIONMODE_TURN_GIVEUP,
	ACTIONMODE_TURN_MAX
};
struct ScoreActionView {
	u8 unknown[0x18];
	ACTIONMODE_TURN restartFlag;
	u8 unknown1c[0x10];
	s32 currentStageNo;
};
struct ScoreModeView {
	u8 unknown[0x22];
	s8 flag22, flag23, flag24;
};
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
struct ScoreTaskView {
	s16 mode;
};
extern "C" {
extern ScoreActionView lbl_8029C310;
extern ScoreModeView* lbl_8042C180;
extern ScorePlayerView* lbl_802AD0D0[8];
extern ScoreTaskView* lbl_802AD090[8];
extern ScoreTeamView* lbl_80303DC8[4];
extern TObject* lbl_8042C0FC;
void fn_800908C0(ScoreTeamView*, s32, s32);
void addScore__11PARAM_SCOREFiii(PARAM_SCORE*, s32, s32, s32);
void saveTime__18PARAM_SAVEPOSITIONFv(void*);
}
// Local predicate name reconstructed; enum and field are metadata-backed.
static inline s32 ScoreIsRestarting()
{
	ACTIONMODE_TURN flag = lbl_8029C310.restartFlag;
	return (flag == ACTIONMODE_TURN_CONTINUE || flag == ACTIONMODE_TURN_RESTART)
	    || flag == ACTIONMODE_TURN_GIVEUP;
}
inline void TEnemyScoreMan::AddTechnicPointForParalyzeEnemy(s32 playernumber, s32 num)
{
	ScorePlayerView* pwk = lbl_802AD0D0[playernumber];
	if (!pwk)
		return;
	ScoreTeamView* pteam = lbl_80303DC8[pwk->teamNo];
	if (!pteam)
		return;
	s32 score_level = 0;
	if (num >= 5)
		score_level = 4;
	else if (num >= 4)
		score_level = 3;
	else if (num >= 3)
		score_level = 2;
	else if (num >= 2)
		score_level = 1;
	if (score_level)
		fn_800908C0(pteam, 1, score_level);
}
inline void TEnemyScoreMan::AddTechnicPointForTornadoEnemy(s32 teamnumber, s32 num)
{
	if (teamnumber == -1)
		return;
	ScoreTeamView* pteam = lbl_80303DC8[teamnumber];
	if (!pteam)
		return;
	s32 score_level = 0;
	if (num >= 5)
		score_level = 4;
	else if (num >= 4)
		score_level = 3;
	else if (num >= 3)
		score_level = 2;
	else if (num >= 2)
		score_level = 1;
	if (score_level)
		fn_800908C0(pteam, 0, score_level);
}
inline void TEnemyScoreMan::AddTechnicPointForDestroyEnemy(s32 playernumber, s32 num)
{
	ScorePlayerView* const& pwk = lbl_802AD0D0[playernumber];
	if (!pwk)
		return;
	ScoreTeamView* pteam = lbl_80303DC8[pwk->teamNo];
	if (!pteam)
		return;
	s32 score_level = 0;
	if (num >= 5)
		score_level = 5;
	else if (num >= 4)
		score_level = 4;
	else if (num >= 3)
		score_level = 3;
	else if (num >= 2)
		score_level = 2;
	if (score_level)
		fn_800908C0(pteam, pwk->player_type, score_level);
}
inline void TEnemyScoreMan::ResetVariable()
{
	mDestroyEnemyNum      = 0;
	mTornadoEnemyNum      = 0;
	mParalyzeEnemyNum     = 0;
	mPlayerNumForDestroy  = 0;
	mTeamNumForTornado    = 0;
	mPlayerNumForParalyze = -1;
	mDestroyEnemyTmr      = 0;
	mTornadoEnemyTmr      = 0;
	mScoreManFlag.Flag    = 0;
}
// (a plain function under the member's name, so this unit does not emit the
// class's vtable, which stays in the module's data)
extern "C" void Exec__14TEnemyScoreManFv(TEnemyScoreMan* self)
{
	if (lbl_8042C180->flag24 == 5 || lbl_8042C180->flag24 == 4 || lbl_8042C180->flag24 == 8) {
		if (lbl_8029C310.restartFlag == ACTIONMODE_TURN_RESTART) {
			if (self->mScoreManFlag.Flag & 1)
				self->mDestroyEnemyTotal = self->mSaveDestroyEnemyTotal;
			else {
				self->mDestroyEnemyTotal     = 0;
				self->mSaveDestroyEnemyTotal = 0;
				self->counter58              = 0;
			}
		}
		if (lbl_8029C310.restartFlag == ACTIONMODE_TURN_CONTINUE)
			self->mDestroyEnemyTotal = self->mSaveDestroyEnemyTotal;
	}
	if (ScoreIsRestarting()) {
		self->ResetVariable();
		return;
	}
	if (lbl_8042C180->flag24 == 5 || lbl_8042C180->flag24 == 4) {
		ScoreTeamView* pteam = lbl_80303DC8[0];
		if (pteam)
			pteam->field23c = self->mDestroyEnemyTotal;
	}
	if (lbl_8042C180->flag24 == 8 && lbl_8029C310.currentStageNo == 5) {
		ScoreTeamView* pteam = lbl_80303DC8[0];
		if (pteam)
			pteam->field23c = self->counter58;
	}
	if (lbl_8042C180->flag22 == 1) {
		self->mDestroyEnemyTmr = -1;
		self->mTornadoEnemyTmr = -1;
	}
	if (self->mDestroyEnemyTmr < 0) {
		if (self->mDestroyEnemyNum > 0) {
			self->AddTechnicPointForDestroyEnemy(
			    self->mPlayerNumForDestroy, self->mDestroyEnemyNum);
			self->mDestroyEnemyNum = 0;
		}
	} else
		--self->mDestroyEnemyTmr;
	if (self->mTornadoEnemyTmr < 0) {
		if (self->mTornadoEnemyNum > 0) {
			self->AddTechnicPointForTornadoEnemy(self->mTeamNumForTornado, self->mTornadoEnemyNum);
			self->mTornadoEnemyNum = 0;
		}
	} else
		--self->mTornadoEnemyTmr;
	if (self->mPlayerNumForParalyze != -1) {
		ScoreTaskView* twk = lbl_802AD090[self->mPlayerNumForParalyze];
		if (twk) {
			if (twk->mode != 0x3b) {
				self->AddTechnicPointForParalyzeEnemy(
				    self->mPlayerNumForParalyze, self->mParalyzeEnemyNum);
				self->mPlayerNumForParalyze = -1;
				self->mParalyzeEnemyNum     = 0;
			}
		} else {
			self->mPlayerNumForParalyze = -1;
			self->mParalyzeEnemyNum     = 0;
		}
	}
}
