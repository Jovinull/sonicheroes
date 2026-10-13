#include "types.h"

// TEnemySearcher_StrategyShot's strategy modes (the PS2 build's names): the
// shooting searcher works like the machine gun one, but watches with
// SearchPlayerFirst, fires for a fixed time, and cancels its shot when a mode
// is interrupted; its thunder shoot lasts 240 frames.

#include "src/rel/searcher_strategy.inc"

void TEnemySearcher_StrategyShot::StrategyMode_ThunderShoot(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mTimer2       = 240;
			mReqEnemyMode = 0x24;
			break;
		case STRATEGY_EXEC:
			nSystem::DecreaseTimer(mTimer2);
			if (mTimer2 < 0) {
				InitStrategyMode(0xC);
			}
			break;
		case STRATEGY_PAUSE:
			mpOwner->Cancel();
			break;
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyShot::StrategyMode_Ready(eStrategy sub)
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

void TEnemySearcher_StrategyShot::StrategyMode_Attack(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mTimer2       = 180;
			mReqEnemyMode = 0x20;
			break;
		case STRATEGY_EXEC:
			nSystem::DecreaseTimer(mTimer2);
			if (mTimer2 < 0) {
				InitStrategyMode(mFirstMode);
			}
			break;
		case STRATEGY_PAUSE:
			mpOwner->Cancel();
			break;
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyShot::StrategyMode_Search(eStrategy sub)
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

void TEnemySearcher_StrategyShot::StrategyMode_Wander(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::GADGET_MODE_STOW);
			}
			mReqEnemyMode = 0xA;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerFirst()) {
				InitStrategyMode(9);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyShot::StrategyMode_Walk(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::GADGET_MODE_STOW);
			}
			mReqEnemyMode = 2;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerFirst()) {
				InitStrategyMode(9);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyShot::StrategyMode_Wait(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mpOwner->ReqChangeGadgetMode(TEnemyGadget::GADGET_MODE_STOW);
			}
			mReqEnemyMode = 1;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerFirst()) {
				InitStrategyMode(9);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}
