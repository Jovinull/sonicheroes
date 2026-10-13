#include "types.h"

// TEnemyPawn_Strategy::ExecStrategyMode (the PS2 build's name): runs the given
// strategy mode's member from the mode table (FuncTbl) for the sub-step.

#include "src/rel/pawn_strategy.inc"

void TEnemyPawn_Strategy::ExecStrategyMode(int mode, eStrategy sub)
{
	(this->*FuncTbl[mode])(sub);
}
