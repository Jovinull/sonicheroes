// waterplantCreate, the factory the editor record for TObjWaterPlant points
// at, in stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// The plant clones the model the module loaded for "obj10_WaterPlant.dff" and,
// unless it is already in, adds it to the world the model file names: one of
// the world slots from 0x7250 in the stage block. The flag is written and read
// back before the test, as the original does. The slot's address is written
// as the base plus 0x7250 plus the index scaled, which is the order the
// original adds them in; indexing an array member scales and adds the base
// first.

#define WATER_PLANT_CTOR inline
#include "src/rel/water_plant_class.inc"

extern "C" void waterplantCreate(void)
{
	new TObjWaterPlant(lbl_8042C110);
}
