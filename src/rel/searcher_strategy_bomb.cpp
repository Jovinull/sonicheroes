#include "types.h"

// TEnemySearcher_StrategyBomb's strategy modes (the PS2 build's names): the
// bomb searcher drops a bomb each time its wait runs out while it waits,
// walks, wanders or searches, gives up a long search by aiming somewhere new,
// and after an attack goes back to the mode of its move type.

#include "src/rel/searcher_strategy.inc"

void TEnemySearcher_StrategyBomb::StrategyMode_Attack(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x20;
			break;
		case STRATEGY_EXEC:
			switch (mpOwner->GetMoveType()) {
				case 0:
					InitStrategyMode(0);
					break;
				case 1:
					InitStrategyMode(1);
					break;
				case 2:
					InitStrategyMode(2);
					break;
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyBomb::StrategyMode_Search(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mTimer2 = mpOwner->readyWait;
			}
			mReqEnemyMode = 0x1E;
			mTimer        = 300;
			break;
		case STRATEGY_EXEC:
			nSystem::DecreaseTimer(mTimer2);
			if (mTimer2 < 0) {
				mTimer2 = mpOwner->readyWait;
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_PREATTACK);
			}
			nSystem::DecreaseTimer(mTimer);
			if (mTimer < 0) {
				mpOwner->SetUpAimPosition();
				InitStrategyMode(2);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyBomb::StrategyMode_Wander(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mTimer2 = mpOwner->readyWait;
			}
			mReqEnemyMode = 0xA;
			break;
		case STRATEGY_EXEC:
			nSystem::DecreaseTimer(mTimer2);
			if (mTimer2 < 0) {
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_PREATTACK);
				InitStrategyMode(2);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyBomb::StrategyMode_Walk(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mTimer2 = mpOwner->readyWait;
			}
			mReqEnemyMode = 2;
			break;
		case STRATEGY_EXEC:
			nSystem::DecreaseTimer(mTimer2);
			if (mTimer2 < 0) {
				if (mpOwner != NULL) {
					mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_PREATTACK);
				}
				InitStrategyMode(1);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyBomb::StrategyMode_Wait(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mTimer2 = mpOwner->readyWait;
			}
			mReqEnemyMode = 1;
			break;
		case STRATEGY_EXEC:
			nSystem::DecreaseTimer(mTimer2);
			if (mTimer2 < 0) {
				if (mpOwner != NULL) {
					mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_PREATTACK);
				}
				InitStrategyMode(0);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}
