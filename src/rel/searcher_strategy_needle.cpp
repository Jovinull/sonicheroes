#include "types.h"

// TEnemySearcher_StrategyNeedle's strategy modes (the PS2 build's names): the
// needle searcher fires its needles for the attack time, then rests for the
// ready time, over and over while it waits, walks, wanders or searches; it
// gives up a long search by aiming somewhere new, and stops firing when it
// leaves a search or a wander.

#include "src/rel/searcher_strategy.inc"

void TEnemySearcher_StrategyNeedle::StrategyMode_Search(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mTimer2    = mpOwner->readyWait;
				mFireTimer = mpOwner->attackWait;
				mFiring    = 0;
			}
			mReqEnemyMode = 0x1E;
			mTimer        = 300;
			break;
		case STRATEGY_EXEC:
			if (mFiring) {
				nSystem::DecreaseTimer(mFireTimer);
				if (mFireTimer < 0) {
					mFiring = 0;
					mTimer2 = mpOwner->readyWait;
					mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_POSTATTACK);
				}
			} else {
				nSystem::DecreaseTimer(mTimer2);
				if (mTimer2 < 0) {
					mFiring    = 1;
					mFireTimer = mpOwner->attackWait;
					mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_PREATTACK);
				}
			}
			nSystem::DecreaseTimer(mTimer);
			if (mTimer < 0) {
				mpOwner->SetUpAimPosition();
				InitStrategyMode(2);
			}
			break;
		case STRATEGY_PAUSE:
			break;
		case STRATEGY_EXIT:
			mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_POSTATTACK);
			break;
	}
}

void TEnemySearcher_StrategyNeedle::StrategyMode_Wander(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mTimer2    = mpOwner->readyWait;
				mFireTimer = mpOwner->attackWait;
				mFiring    = 0;
			}
			mReqEnemyMode = 0xA;
			break;
		case STRATEGY_EXEC:
			if (mFiring) {
				nSystem::DecreaseTimer(mFireTimer);
				if (mFireTimer < 0) {
					mFiring = 0;
					mTimer2 = mpOwner->readyWait;
					mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_POSTATTACK);
				}
			} else {
				nSystem::DecreaseTimer(mTimer2);
				if (mTimer2 < 0) {
					mFiring    = 1;
					mFireTimer = mpOwner->attackWait;
					mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_PREATTACK);
				}
			}
			break;
		case STRATEGY_PAUSE:
			break;
		case STRATEGY_EXIT:
			mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_POSTATTACK);
			break;
	}
}

void TEnemySearcher_StrategyNeedle::StrategyMode_Walk(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mTimer2    = mpOwner->readyWait;
				mFireTimer = mpOwner->attackWait;
				mFiring    = 0;
			}
			mReqEnemyMode = 2;
			break;
		case STRATEGY_EXEC:
			if (mFiring) {
				nSystem::DecreaseTimer(mFireTimer);
				if (mFireTimer < 0) {
					mFiring = 0;
					mTimer2 = mpOwner->readyWait;
					mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_POSTATTACK);
				}
			} else {
				nSystem::DecreaseTimer(mTimer2);
				if (mTimer2 < 0) {
					mFiring    = 1;
					mFireTimer = mpOwner->attackWait;
					mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_PREATTACK);
				}
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_StrategyNeedle::StrategyMode_Wait(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			if (mpOwner != NULL) {
				mTimer2    = mpOwner->readyWait;
				mFireTimer = mpOwner->attackWait;
				mFiring    = 0;
			}
			mReqEnemyMode = 1;
			break;
		case STRATEGY_EXEC:
			if (mFiring) {
				nSystem::DecreaseTimer(mFireTimer);
				if (mFireTimer < 0) {
					mFiring = 0;
					mTimer2 = mpOwner->readyWait;
					mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_POSTATTACK);
				}
			} else {
				nSystem::DecreaseTimer(mTimer2);
				if (mTimer2 < 0) {
					mFiring    = 1;
					mFireTimer = mpOwner->attackWait;
					mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_PREATTACK);
				}
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}
