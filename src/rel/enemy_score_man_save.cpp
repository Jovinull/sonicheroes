// TEnemyScoreMan's SaveDestroyEnemyTotalGoal and SaveDestroyEnemyTotal in the
// stage modules that carry their own copy of the score manager (31D-33D),
// the same code as main's game/enemy/e_scoreman.cpp: the destroyed enemy total
// is kept, at the goal with the goal flag.
#include "game/enemy/e_scoreman.h"

void TEnemyScoreMan::SaveDestroyEnemyTotalGoal()
{
	mSaveDestroyEnemyTotal = mDestroyEnemyTotal;
	mScoreManFlag.Flag |= 1;
}
void TEnemyScoreMan::SaveDestroyEnemyTotal()
{
	mSaveDestroyEnemyTotal = mDestroyEnemyTotal;
}
