#include "types.h"

// TEnemyPawn_Strategy's strategy modes (the PS2 build's names, in its order):
// each asks the pawn for an enemy mode when it starts; the timed ones switch
// to the next strategy mode when their count runs out, the watching ones when
// the pawn finds a player (or, crouching, when it is hit).

#include "src/rel/pawn_strategy.inc"

extern "C" s8* lbl_8042C180;

void TEnemyPawn_Strategy::StrategyMode_Idle(eStrategy sub)
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

void TEnemyPawn_Strategy::StrategyMode_BiteNail(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 9;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_BlowShield(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x1B;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_Run(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 3;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_MgunFire(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mTimer        = mpOwner->shotWait;
			mReqEnemyMode = 0x19;
			break;
		case STRATEGY_EXEC:
			nSystem::DecreaseTimer(mTimer);
			if (mTimer < 0) {
				InitStrategyMode(4);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_MgunReady(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mTimer        = 0xB4;
			mReqEnemyMode = 0x18;
			break;
		case STRATEGY_EXEC:
			nSystem::DecreaseTimer(mTimer);
			if (mTimer < 0) {
				InitStrategyMode(0x15);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_ShotFire(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x17;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_ShotReady(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x16;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_ThunderShoot(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x24;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_Dropped(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mTimer        = 0xF0;
			mReqEnemyMode = 0x1C;
			break;
		case STRATEGY_EXEC:
			nSystem::DecreaseTimer(mTimer);
			if (mTimer < 0) {
				if (mpOwner->start == 6) {
					InitStrategyMode(0x1A);
				} else {
					InitStrategyMode(4);
				}
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_Tornado(eStrategy sub)
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

void TEnemyPawn_Strategy::StrategyMode_Destroy(eStrategy sub)
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

void TEnemyPawn_Strategy::StrategyMode_Ctrl(eStrategy sub) { }

void TEnemyPawn_Strategy::StrategyMode_WarpOut(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x15;
			mTimer        = 0x3C;
			break;
		case STRATEGY_EXEC:
			nSystem::DecreaseTimer(mTimer);
			if (mTimer < 0) {
				InitStrategyMode(8);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_WarpHide(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x14;
			break;
		case STRATEGY_EXEC:
			if (lbl_8042C180[0x1F] == 0 && mpOwner->SearchPlayerForPawn(0)) {
				InitStrategyMode(0xD);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_HideComeOut(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x10;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_Hide(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0xF;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerForPawn(1)) {
				InitStrategyMode(0xB);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_FallLand(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x13;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_FallDown(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x12;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_FallHide(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0x11;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerForPawn(0)) {
				InitStrategyMode(8);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_WanderWalk(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0xC;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_WanderTurn(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0xB;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_Wander(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0xA;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerForPawn(1)) {
				InitStrategyMode(3);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_Turn(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 4;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_Wait(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 1;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerForPawn(0)) {
				InitStrategyMode(3);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_CrouchStand(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0xE;
			break;
		case STRATEGY_EXEC:
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}

void TEnemyPawn_Strategy::StrategyMode_Crouch(eStrategy sub)
{
	switch (sub) {
		case STRATEGY_INIT:
			mReqEnemyMode = 0xD;
			break;
		case STRATEGY_EXEC:
			if (mpOwner->SearchPlayerForPawn(1)) {
				InitStrategyMode(1);
			} else if (mpOwner->CheckDamage()) {
				InitStrategyMode(0x19);
			}
			break;
		case STRATEGY_PAUSE:
		case STRATEGY_EXIT:
			break;
	}
}
