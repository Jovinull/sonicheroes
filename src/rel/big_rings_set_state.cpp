#include "types.h"

// bigRingsSetState, the same in the twelve stage modules that share the engine
// core: it sets the word the big rings' hooks (rel/big_rings_hooks.cpp) clear.
// Nothing in the modules calls it.

extern "C" s32 bigRingsState;

extern "C" void bigRingsSetState(s32 state)
{
	bigRingsState = state;
}
