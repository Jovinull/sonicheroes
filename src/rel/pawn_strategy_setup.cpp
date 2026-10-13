#include "types.h"

// Two TEnemyPawn_Strategy members (the PS2 build's names):
// - IsReqChangeMode: updates the pawn's hit points and switches the strategy
//   when the pawn is destroyed (0xF), when the pawn asks for a mode (each enemy
//   mode request maps to a strategy mode; the request is then cleared), or when
//   it is stirred up or blown (0x1000 and 0x2000 state bits) outside the modes
//   that ignore that; returns whether the strategy changed;
// - SetUpFirst: takes its pawn and starts the strategy in the mode for the
//   pawn's start kind (the retail has the case for kind 3 before kind 2's).
// This unit holds the strategy's own vtable (IsReqChangeMode is its key
// function). It is built with deferred inlining, so the vtable comes out
// before the jump tables as in the retail; that mode emits the functions in
// reverse order, so IsReqChangeMode is defined first.

#include "src/rel/pawn_strategy.inc"

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
