#include "types.h"

// The breakable weight's Check_Shadow and Check_Laser (the PS2 build's
// TObjWeightExt names; breakableWeightCheckShadow and breakableWeightCheckLaser
// here; the weight's own are rel/weight_area_checks.cpp):
// CheckPlayerTrespassArea of breakable_weight.inc, inlined, counting only the
// players in the active state and counting every player.

#include "src/rel/breakable_weight.inc"

extern "C" s32 breakableWeightCheckShadow(BreakableWeight* object)
{
	return CheckPlayerTrespassArea(object, 1);
}

extern "C" s32 breakableWeightCheckLaser(BreakableWeight* object)
{
	return CheckPlayerTrespassArea(object, 0);
}
