#include "types.h"

// TEnemySearcher_StrategySearchLight's strategy modes (the PS2 build's names):
// the search light searcher stows its light and watches while it waits, walks
// or wanders, sounds the siren when it finds a player, and attacks while the
// player stays in reach, going back to the mode it came from when the time
// runs out.

#include "src/rel/searcher_strategy.inc"

void TEnemySearcher_StrategySearchLight::StrategyMode_Siren(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mTimer2 = mpOwner->attackWait;
			}
			mReqEnemyMode = 0x23;
			break;
		case STRATEGY_EXEC:
			nSystem::DecreaseTimer(mTimer2);
			if (mTimer2 < 0) {
				if (mpOwner != NULL) {
					mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_NOACTION);
				}
				InitStrategyMode(mFirstMode);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategySearchLight::StrategyMode_Attack(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mTimer2 = mpOwner->readyWait;
			}
			mReqEnemyMode = 0x20;
			break;
		case STRATEGY_EXEC:
			if (fn_800A6334(mpOwner) == 0) {
				InitStrategyMode(mFirstMode);
			} else {
				nSystem::DecreaseTimer(mTimer2);
				if (mTimer2 < 0) {
					if (mpOwner != NULL) {
						mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_NOACTION);
					}
					InitStrategyMode(mPrevMode);
				}
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategySearchLight::StrategyMode_Wander(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_NOACTION);
			}
			mReqEnemyMode = 0xA;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerFirst()) {
				InitStrategyMode(0xA);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategySearchLight::StrategyMode_Walk(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_NOACTION);
			}
			mReqEnemyMode = 2;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerFirst()) {
				InitStrategyMode(0xA);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategySearchLight::StrategyMode_Wait(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_NOACTION);
			}
			mReqEnemyMode = 1;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerFirst()) {
				InitStrategyMode(0xA);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}
