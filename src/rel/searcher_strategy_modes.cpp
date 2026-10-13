#include "types.h"

// TEnemySearcher_Strategy's strategy modes (the PS2 build's names): most only
// ask the searcher for their enemy mode; the thunder shoot lasts 240 frames,
// the attack runs while the player stays in reach, and a search that finds
// nobody in 300 frames aims somewhere new and wanders. Walking with an attack
// does nothing.

#include "src/rel/searcher_strategy.inc"

void TEnemySearcher_Strategy::StrategyMode_Idle(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x5E;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_Strategy::StrategyMode_ThunderShootReturn(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x25;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_Strategy::StrategyMode_ThunderShoot(eStrategy sub)
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
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_Strategy::StrategyMode_Siren(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x23;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_Strategy::StrategyMode_Ready(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x1F;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_Strategy::StrategyMode_Destroy(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x1D;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_Strategy::StrategyMode_Attack(eStrategy sub)
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
						mpOwner->ReqChangeGadgetMode(TEnemyGadget::GADGET_MODE_2);
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

void TEnemySearcher_Strategy::StrategyMode_Tornado(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x1A;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_Strategy::StrategyMode_WanderWithAttack(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x22;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_Strategy::StrategyMode_WalkWithAttack(eStrategy sub) { }

void TEnemySearcher_Strategy::StrategyMode_Search(eStrategy sub)
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
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_Strategy::StrategyMode_Wander(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0xA;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_Strategy::StrategyMode_Walk(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 2;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemySearcher_Strategy::StrategyMode_Wait(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 1;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}
