#include "types.h"

// Two of TObjWeight's area checks (weightCheckActivePlayerUnder and
// weightCheckPlayerUnder here): the inline area check of weight.inc counting
// only the players in the active state, and counting every player. Only a body
// inlined into the function gives the retail's registers and stack slots.

#include "src/rel/weight.inc"

extern "C" s32 weightCheckActivePlayerUnder(Weight* object)
{
	return PlayerUnderWeight(object, 1);
}

extern "C" s32 weightCheckPlayerUnder(Weight* object)
{
	return PlayerUnderWeight(object, 0);
}
