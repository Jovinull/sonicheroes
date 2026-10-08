// Complete C++ enemy/e_scoreman.cpp; metadata names and GC behavior/layout.
#include "game/enemy/e_scoreman.h"

char* CL_TEnemyScoreMan = "TEnemyScoreMan";
TEnemyScoreMan* TEnemyScoreMan::EnemyScoreMan;
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
void TEnemyScoreMan::SaveDestroyEnemyTotalGoal()
{
	mSaveDestroyEnemyTotal = mDestroyEnemyTotal;
	mScoreManFlag.Flag |= 1;
}
void TEnemyScoreMan::SaveDestroyEnemyTotal()
{
	mSaveDestroyEnemyTotal = mDestroyEnemyTotal;
}
// GC-only methods retain address-based ABI names.
extern "C" void fn_8011C0E8(TEnemyScoreMan* self)
{
	++self->mDestroyEnemyTotal;
	if (lbl_8042C180->flag24 == 4 || lbl_8042C180->flag24 == 8) {
		self->mSaveDestroyEnemyTotal = self->mDestroyEnemyTotal;
		saveTime__18PARAM_SAVEPOSITIONFv(&static_cast<ScoreSavedStateBase&>(*self));
	}
}
extern "C" void fn_8011C13C(TEnemyScoreMan* self)
{
	++self->counter58;
	if (lbl_8042C180->flag24 == 4 || lbl_8042C180->flag24 == 8)
		saveTime__18PARAM_SAVEPOSITIONFv(&static_cast<ScoreSavedStateBase&>(*self));
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
void TEnemyScoreMan::Exec()
{
	if (lbl_8042C180->flag24 == 5 || lbl_8042C180->flag24 == 4 || lbl_8042C180->flag24 == 8) {
		if (lbl_8029C310.restartFlag == ACTIONMODE_TURN_RESTART) {
			if (mScoreManFlag.Flag & 1)
				mDestroyEnemyTotal = mSaveDestroyEnemyTotal;
			else {
				mDestroyEnemyTotal     = 0;
				mSaveDestroyEnemyTotal = 0;
				counter58              = 0;
			}
		}
		if (lbl_8029C310.restartFlag == ACTIONMODE_TURN_CONTINUE)
			mDestroyEnemyTotal = mSaveDestroyEnemyTotal;
	}
	if (ScoreIsRestarting()) {
		ResetVariable();
		return;
	}
	if (lbl_8042C180->flag24 == 5 || lbl_8042C180->flag24 == 4) {
		ScoreTeamView* pteam = lbl_80303DC8[0];
		if (pteam)
			pteam->field23c = mDestroyEnemyTotal;
	}
	if (lbl_8042C180->flag24 == 8 && lbl_8029C310.currentStageNo == 5) {
		ScoreTeamView* pteam = lbl_80303DC8[0];
		if (pteam)
			pteam->field23c = counter58;
	}
	if (lbl_8042C180->flag22 == 1) {
		mDestroyEnemyTmr = -1;
		mTornadoEnemyTmr = -1;
	}
	if (mDestroyEnemyTmr < 0) {
		if (mDestroyEnemyNum > 0) {
			AddTechnicPointForDestroyEnemy(mPlayerNumForDestroy, mDestroyEnemyNum);
			mDestroyEnemyNum = 0;
		}
	} else
		--mDestroyEnemyTmr;
	if (mTornadoEnemyTmr < 0) {
		if (mTornadoEnemyNum > 0) {
			AddTechnicPointForTornadoEnemy(mTeamNumForTornado, mTornadoEnemyNum);
			mTornadoEnemyNum = 0;
		}
	} else
		--mTornadoEnemyTmr;
	if (mPlayerNumForParalyze != -1) {
		ScoreTaskView* twk = lbl_802AD090[mPlayerNumForParalyze];
		if (twk) {
			if (twk->mode != 0x3b) {
				AddTechnicPointForParalyzeEnemy(mPlayerNumForParalyze, mParalyzeEnemyNum);
				mPlayerNumForParalyze = -1;
				mParalyzeEnemyNum     = 0;
			}
		} else {
			mPlayerNumForParalyze = -1;
			mParalyzeEnemyNum     = 0;
		}
	}
}
TEnemyScoreMan::~TEnemyScoreMan() { }
inline TEnemyScoreMan::TEnemyScoreMan(TObject* ptp)
    : TObject(ptp)
{
	mScoreManFlag.Flag     = 0;
	ClassName              = CL_TEnemyScoreMan;
	DispTime               = sizeof(TEnemyScoreMan);
	mDestroyEnemyTotal     = 0;
	mSaveDestroyEnemyTotal = 0;
	counter58              = 0;
	ResetVariable();
}
void TEnemyScoreMan::DeleteInstance()
{
	if (EnemyScoreMan) {
		EnemyScoreMan->Signal |= 1;
		EnemyScoreMan = 0;
	}
}
void TEnemyScoreMan::CreateInstance()
{
	if (!EnemyScoreMan)
		EnemyScoreMan = new TEnemyScoreMan(lbl_8042C0FC);
}
