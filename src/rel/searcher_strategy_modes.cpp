#include "types.h"

// TEnemySearcher_Strategy (the PS2 build's names), from SetUpFirst to the
// strategy modes:
// - SetUpFirst: takes its searcher and starts the strategy in the mode for the
//   searcher's move type (waiting, walking, wandering; 3 idles);
// - IsReqChangeMode: updates the searcher's hit points and switches the
//   strategy when the searcher is destroyed (Destroy), stirred up by a tornado
//   (0x1000 state bit: Tornado) or hit by a thunder shoot (0x2000: ThunderShoot)
//   outside the modes that ignore that, when its tornado mode ends (back to the
//   previous strategy mode), or when it asks for a mode (the request is then
//   cleared); returns whether the strategy changed (for a request, only a
//   search counts);
// - the strategy modes: most only ask the searcher for their enemy mode; the
//   thunder shoot lasts 240 frames, the attack runs while the player stays in
//   reach, and a search that finds nobody in 300 frames aims somewhere new and
//   wanders. Walking with an attack does nothing.
// The strategy mode numbers follow the vtable: 0 Wait, 1 Walk, 2 Wander,
// 3 Search, 4 Attack, 5 WalkWithAttack, 6 WanderWithAttack, 7 Tornado,
// 8 Destroy, 9 Ready, 0xA Siren, 0xB ThunderShoot, 0xC ThunderShootReturn,
// 0xD Idle.

#include "src/rel/searcher_strategy.inc"

void TEnemySearcher_Strategy::SetUpFirst(TObjEnemySearcher* owner)
{
	mpOwner = owner;
	if (mpOwner != NULL) {
		switch (mpOwner->GetMoveType()) {
			case 0:
				StartStrategyMode(0);
				break;
			case 1:
				StartStrategyMode(1);
				break;
			case 2:
				StartStrategyMode(2);
				break;
			case 3:
				StartStrategyMode(0xD);
				break;
		}
	}
}

int TEnemySearcher_Strategy::IsReqChangeMode()
{
	if (mpOwner != NULL) {
		mpOwner->CheckHitPoint();
	}
	if (fn_800A3ED4(mpOwner) && mpOwner->mode != 0x1D) {
		InitStrategyMode(8);
		return 1;
	}
	if (mpOwner->state & 0x1000) {
		switch (mpOwner->mode) {
			case 0x1A:
			case 0x1D:
			case 0x24:
			case 0x25:
				return 0;
		}
		InitStrategyMode(7);
		return 1;
	}
	switch (mpOwner->mode) {
		case 0x1A:
			InitStrategyMode(mPrevMode);
			return 1;
	}
	if (mpOwner->state & 0x2000) {
		switch (mpOwner->mode) {
			case 0x1A:
			case 0x1D:
			case 0x24:
			case 0x25:
				return 0;
		}
		InitStrategyMode(0xB);
		return 1;
	}
	if (mpOwner->request != 0) {
		int changed = 0;

		switch (mpOwner->request) {
			case 0x1E:
				InitStrategyMode(3);
				changed = 1;
				break;
			case 1:
				InitStrategyMode(0);
				break;
			case 2:
				InitStrategyMode(1);
				break;
			case 0xA:
				InitStrategyMode(2);
				break;
		}
		mpOwner->request = 0;
		return changed;
	}
	return 0;
}

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
						mpOwner->ReqChangeGadgetMode(TEnemyGadget::E_GM_PREATTACK);
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
