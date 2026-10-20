#include "types.h"

// TEnemyStrategy<TObjEnemyPawn>::Execute (the PS2 build's name), the pawn
// strategy's template instance: takes the owner, clears the enemy mode
// request, pauses the current mode when the strategy wants to switch, runs the
// mode and passes on the enemy mode it asks for.

#include "src/rel/enemy_strategy.inc"

class TObjEnemyPawn;

template <class T> void TEnemyStrategy<T>::Execute(T* owner)
{
	mpOwner       = owner;
	mReqEnemyMode = 0;
	if (IsReqChangeMode()) {
		ExecStrategyMode(mMode, STRATEGY_PAUSE);
	}
	ExecStrategyMode(mMode, STRATEGY_EXEC);
	if (mReqEnemyMode != 0) {
		fn_800A31B8(mpOwner, mReqEnemyMode);
	}
}

// the instance the pawn's unit emitted; explicit instantiation of the class
// emits only Execute (the inline members are unused, the pure ones only warn)
template class TEnemyStrategy<TObjEnemyPawn>;
