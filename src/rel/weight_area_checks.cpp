#include "types.h"

// TObjWeight's Check_Shadow and Check_Laser (the PS2 build's names;
// weightCheckShadow and weightCheckLaser here): CheckPlayerTrespassArea of
// weight.inc, inlined, counting only the players in the active state and
// counting every player.

#include "src/rel/weight.inc"

extern "C" s32 weightCheckShadow(Weight* object)
{
	return CheckPlayerTrespassArea(object, 1);
}

extern "C" s32 weightCheckLaser(Weight* object)
{
	return CheckPlayerTrespassArea(object, 0);
}
