// TEnemyScoreMan's technical point helpers in the stage modules that carry
// their own copy of the score manager (31D-33D), the same code as main's
// game/enemy/e_scoreman.cpp, where they are inlined: the more enemies at once,
// the higher the level of the points the team (or the player's team) gets.
// Here they take the manager (main declares them static), so they are plain
// functions under the members' names.
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
extern "C" void AddTechnicPointForParalyzeEnemy__14TEnemyScoreManFii(
    TEnemyScoreMan* self, s32 playernumber, s32 num)
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
extern "C" void AddTechnicPointForTornadoEnemy__14TEnemyScoreManFii(
    TEnemyScoreMan* self, s32 teamnumber, s32 num)
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
extern "C" void AddTechnicPointForDestroyEnemy__14TEnemyScoreManFii(
    TEnemyScoreMan* self, s32 playernumber, s32 num)
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
