#include "types.h"

// TEnemyPawn_Strategy::SetUpFirst (the PS2 build's name): takes its pawn and
// starts the strategy in the mode for the pawn's start kind (the retail has
// the case for kind 3 before the one for kind 2).

#include "src/rel/pawn_strategy.inc"

void TEnemyPawn_Strategy::SetUpFirst(TObjEnemyPawn* owner)
{
	mpOwner = owner;
	if (mpOwner != NULL) {
		switch (mpOwner->start) {
			case 0:
				StartStrategyMode(0);
				break;
			case 1:
				StartStrategyMode(4);
				break;
			case 3:
				StartStrategyMode(7);
				break;
			case 2:
				StartStrategyMode(0xA);
				break;
			case 4:
				StartStrategyMode(0xC);
				break;
			case 5:
				StartStrategyMode(0xE);
				break;
			case 6:
				StartStrategyMode(0x1A);
				break;
		}
	}
}
