// TEnemyScoreMan::ResetVariable in the stage modules that carry their own copy
// of the score manager (31D-33D), the same code as main's
// game/enemy/e_scoreman.cpp, where it is inlined.
#include "game/enemy/e_scoreman.h"

void TEnemyScoreMan::ResetVariable()
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
