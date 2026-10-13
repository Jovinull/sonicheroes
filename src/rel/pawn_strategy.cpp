#include "types.h"

// TEnemyPawn_Strategy (the PS2 build's names), all but the strategy modes
// (rel/pawn_strategy_modes.cpp):
// - FuncTbl: the strategy modes by mode number, filled at startup from one
//   constant per member pointer;
// - SetUpFirst: takes its pawn and starts the strategy in the mode for the
//   pawn's start kind (the retail has the case for kind 3 before kind 2's);
// - IsReqChangeMode: updates the pawn's hit points and switches the strategy
//   when the pawn is destroyed (0xF), when the pawn asks for a mode (each enemy
//   mode request maps to a strategy mode; the request is then cleared), or when
//   it is stirred up or blown (0x1000 and 0x2000 state bits) outside the modes
//   that ignore that; returns whether the strategy changed;
// - ExecStrategyMode: runs a mode's member from FuncTbl for the sub-step;
// - the destructor and constructor; the strategy base's destructor and vtable
//   come out of this unit as template instances.
// IsReqChangeMode is the key function, so this unit also holds the strategy's
// vtable. It is built with deferred inlining, which puts the vtable before the
// jump tables as in the retail and emits the functions in reverse definition
// order: they are defined last to first.

#include "src/rel/pawn_strategy.inc"

// the startup copy of FuncTbl loads each member pointer constant by its own
// address
#pragma pool_data off

void (TEnemyPawn_Strategy::* TEnemyPawn_Strategy::FuncTbl[27])(TEnemyPawn_Strategy::eStrategy sub)
    = {
	      &TEnemyPawn_Strategy::StrategyMode_Crouch,       // 0x0
	      &TEnemyPawn_Strategy::StrategyMode_CrouchStand,  // 0x1
	      &TEnemyPawn_Strategy::StrategyMode_Wait,         // 0x2
	      &TEnemyPawn_Strategy::StrategyMode_Turn,         // 0x3
	      &TEnemyPawn_Strategy::StrategyMode_Wander,       // 0x4
	      &TEnemyPawn_Strategy::StrategyMode_WanderTurn,   // 0x5
	      &TEnemyPawn_Strategy::StrategyMode_WanderWalk,   // 0x6
	      &TEnemyPawn_Strategy::StrategyMode_FallHide,     // 0x7
	      &TEnemyPawn_Strategy::StrategyMode_FallDown,     // 0x8
	      &TEnemyPawn_Strategy::StrategyMode_FallLand,     // 0x9
	      &TEnemyPawn_Strategy::StrategyMode_Hide,         // 0xa
	      &TEnemyPawn_Strategy::StrategyMode_HideComeOut,  // 0xb
	      &TEnemyPawn_Strategy::StrategyMode_WarpHide,     // 0xc
	      &TEnemyPawn_Strategy::StrategyMode_WarpOut,      // 0xd
	      &TEnemyPawn_Strategy::StrategyMode_Ctrl,         // 0xe
	      &TEnemyPawn_Strategy::StrategyMode_Destroy,      // 0xf
	      &TEnemyPawn_Strategy::StrategyMode_Tornado,      // 0x10
	      &TEnemyPawn_Strategy::StrategyMode_ThunderShoot, // 0x11
	      &TEnemyPawn_Strategy::StrategyMode_ShotReady,    // 0x12
	      &TEnemyPawn_Strategy::StrategyMode_ShotFire,     // 0x13
	      &TEnemyPawn_Strategy::StrategyMode_MgunReady,    // 0x14
	      &TEnemyPawn_Strategy::StrategyMode_MgunFire,     // 0x15
	      &TEnemyPawn_Strategy::StrategyMode_Run,          // 0x16
	      &TEnemyPawn_Strategy::StrategyMode_BlowShield,   // 0x17
	      &TEnemyPawn_Strategy::StrategyMode_Dropped,      // 0x18
	      &TEnemyPawn_Strategy::StrategyMode_BiteNail,     // 0x19
	      &TEnemyPawn_Strategy::StrategyMode_Idle,         // 0x1a
      };

TEnemyPawn_Strategy::TEnemyPawn_Strategy() { }

TEnemyPawn_Strategy::~TEnemyPawn_Strategy() { }

void TEnemyPawn_Strategy::ExecStrategyMode(int mode, eStrategy sub)
{
	(this->*FuncTbl[mode])(sub);
}

int TEnemyPawn_Strategy::IsReqChangeMode()
{
	int mode = mpOwner->mode;

	mpOwner->CheckHitPoint();
	if (fn_800A3ED4(mpOwner) && mode != 0x1D) {
		InitStrategyMode(0xF);
		return 1;
	}
	if (mpOwner->request != 0) {
		int changed = 0;

		switch (mpOwner->request) {
			case 0x1:
				InitStrategyMode(0x2);
				changed = 1;
				break;
			case 0x16:
				InitStrategyMode(0x12);
				changed = 1;
				break;
			case 0x17:
				InitStrategyMode(0x13);
				changed = 1;
				break;
			case 0x18:
				InitStrategyMode(0x14);
				changed = 1;
				break;
			case 0x3:
				InitStrategyMode(0x16);
				changed = 1;
				break;
			case 0xa:
				InitStrategyMode(0x4);
				changed = 1;
				break;
			case 0xb:
				InitStrategyMode(0x5);
				changed = 1;
				break;
			case 0xc:
				InitStrategyMode(0x6);
				changed = 1;
				break;
			case 0x1c:
				InitStrategyMode(0x18);
				changed = 1;
				break;
			case 0x9:
				InitStrategyMode(0x19);
				changed = 1;
				break;
			case 0x13:
				InitStrategyMode(0x9);
				changed = 1;
				break;
			case 0x12:
				InitStrategyMode(0x8);
				changed = 1;
				break;
			case 0x4:
				InitStrategyMode(0x3);
				changed = 1;
				break;
			case 0x5e:
				InitStrategyMode(0x1a);
				changed = 1;
				break;
			case 0x1d:
				InitStrategyMode(0xf);
				changed = 1;
				break;
		}
		mpOwner->request = 0;
		return changed;
	}
	if (mpOwner->state & 0x1000) {
		switch (mode) {
			case 0x11:
			case 0x14:
			case 0x1A:
			case 0x1B:
			case 0x1C:
			case 0x1D:
			case 0x24:
				return 0;
		}
		if (mpOwner->shielded == 0) {
			InitStrategyMode(0x10);
		} else {
			InitStrategyMode(0x17);
		}
		return 1;
	}
	if (mpOwner->state & 0x2000) {
		switch (mode) {
			case 0x11:
			case 0x14:
			case 0x1A:
			case 0x1B:
			case 0x1C:
			case 0x1D:
			case 0x24:
				return 0;
		}
		if (mpOwner->shielded == 0) {
			InitStrategyMode(0x11);
		}
		return 1;
	}
	return 0;
}

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
