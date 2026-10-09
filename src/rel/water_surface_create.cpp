// watersurfaceCreate, the factory the editor record for TObjWaterSurface points
// at, in stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// It is rel/water_plant_create.cpp for "obj10_waterSurface.dff": clone the
// module's model and, unless it is already in, add it to the world slot the
// model file names, with the slot's address written the way that file explains.

#define WATER_SURFACE_CTOR inline
#include "src/rel/water_surface_class.inc"

extern "C" void watersurfaceCreate(void)
{
	new TObjWaterSurface(lbl_8042C110);
}
