#include "types.h"

// TEnemySearcher_StrategyLaser's strategy modes (the PS2 build's names): the
// laser searcher only turns its laser on when it starts to wait, walk or
// wander.

#include "src/rel/searcher_strategy.inc"

void TEnemySearcher_StrategyLaser::StrategyMode_Wander(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::GADGET_MODE_2);
			}
			mReqEnemyMode = 0xA;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyLaser::StrategyMode_Walk(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::GADGET_MODE_2);
			}
			mReqEnemyMode = 2;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyLaser::StrategyMode_Wait(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::GADGET_MODE_2);
			}
			mReqEnemyMode = 1;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}
