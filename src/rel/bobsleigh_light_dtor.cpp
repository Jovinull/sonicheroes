#include "types.h"

// TObjBobsleighLight's destructor (the PS2 build's TObjBobsleighLight::__dt):
// it frees the models and their materials (DestroyClump, inlined).

#include "src/rel/bobsleigh_light_class.inc"

TObjBobsleighLight::~TObjBobsleighLight()
{
	DestroyClump();
}
