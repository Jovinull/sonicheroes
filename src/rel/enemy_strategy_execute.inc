// TEnemyStrategy::Execute (the PS2 build's name), for the units that emit an
// instance of it: takes the owner, clears the enemy mode request, pauses the
// current mode when the strategy wants to switch, runs the mode and passes on
// the enemy mode it asks for. Kept out of rel/enemy_strategy.inc so that the
// units emitting a strategy's vtable do not instantiate it too.

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
