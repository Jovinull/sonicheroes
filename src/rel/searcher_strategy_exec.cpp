#include "types.h"

// TEnemySearcher_Strategy::ExecStrategyMode (the PS2 build's name): runs a
// strategy mode's virtual for the sub-step, by mode number (the vtable's order,
// see rel/searcher_strategy_modes.cpp).

#include "src/rel/searcher_strategy.inc"

void TEnemySearcher_Strategy::ExecStrategyMode(int mode, eStrategy sub)
{
	switch (mode) {
		case 0x0:
			StrategyMode_Wait(sub);
			break;
		case 0x1:
			StrategyMode_Walk(sub);
			break;
		case 0x2:
			StrategyMode_Wander(sub);
			break;
		case 0x3:
			StrategyMode_Search(sub);
			break;
		case 0x4:
			StrategyMode_Attack(sub);
			break;
		case 0x5:
			StrategyMode_WalkWithAttack(sub);
			break;
		case 0x6:
			StrategyMode_WanderWithAttack(sub);
			break;
		case 0x7:
			StrategyMode_Tornado(sub);
			break;
		case 0x8:
			StrategyMode_Destroy(sub);
			break;
		case 0x9:
			StrategyMode_Ready(sub);
			break;
		case 0xA:
			StrategyMode_Siren(sub);
			break;
		case 0xB:
			StrategyMode_ThunderShoot(sub);
			break;
		case 0xC:
			StrategyMode_ThunderShootReturn(sub);
			break;
		case 0xD:
			StrategyMode_Idle(sub);
			break;
	}
}
