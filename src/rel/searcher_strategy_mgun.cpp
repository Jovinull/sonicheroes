#include "types.h"

// TEnemySearcher_StrategyMGun's strategy modes (the PS2 build's names): the
// machine gun searcher stows its gun and watches while it waits, walks or
// wanders, readies the gun when it finds a player, fires while the attack time
// runs, and gives up a long search by aiming somewhere new.

#include "src/rel/searcher_strategy.inc"

void TEnemySearcher_StrategyMGun::StrategyMode_Ready(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mTimer2 = mpOwner->readyWait;
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::GADGET_MODE_READY);
			}
			mReqEnemyMode = 0x1F;
			break;
		case STRATEGY_EXEC:
			if (fn_800A6334(mpOwner) == 0) {
				InitStrategyMode(mFirstMode);
			} else {
				nSystem::DecreaseTimer(mTimer2);
				if (mTimer2 < 0) {
					InitStrategyMode(4);
				}
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyMGun::StrategyMode_Attack(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mTimer2       = mpOwner->attackWait;
			mReqEnemyMode = 0x20;
			break;
		case STRATEGY_EXEC:
			nSystem::DecreaseTimer(mTimer2);
			if (mTimer2 < 0) {
				InitStrategyMode(mFirstMode);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyMGun::StrategyMode_Search(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mTimer        = 0;
			mReqEnemyMode = 0x1E;
			break;
		case STRATEGY_EXEC:
			nSystem::IncreaseTimer(mTimer);
			if (mTimer > 300) {
				mpOwner->SetUpAimPosition();
				InitStrategyMode(2);
			}
			if (mpOwner->SearchPlayerForSearcher()) {
				InitStrategyMode(9);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyMGun::StrategyMode_Wander(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::GADGET_MODE_STOW);
			}
			mReqEnemyMode = 0xA;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerForSearcher()) {
				InitStrategyMode(9);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyMGun::StrategyMode_Walk(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::GADGET_MODE_STOW);
			}
			mReqEnemyMode = 2;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerForSearcher()) {
				InitStrategyMode(9);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyMGun::StrategyMode_Wait(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::GADGET_MODE_STOW);
			}
			mReqEnemyMode = 1;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerForSearcher()) {
				InitStrategyMode(9);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}
