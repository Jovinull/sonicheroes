// TEnemyScoreMan's constructor in the stage modules that carry their own copy
// of the score manager (31D-33D), the same code as main's
// game/enemy/e_scoreman.cpp, where it is inlined (ResetVariable too).
#include "game/enemy/e_scoreman.h"

extern char* CL_TEnemyScoreMan;

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
TEnemyScoreMan::TEnemyScoreMan(TObject* ptp)
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
