// objSetparticleCreate, the factory the editor record for TObjSetParticle
// points at.
//
// It is the same 75 instructions in the thirteen stage modules that share the
// engine core, at a different address in each, so each module's splits.txt
// names its own range.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// The placement's parameter block holds the effect number in its first byte
// and a scale at 0x10. In the editor, an unset scale becomes 1 and an effect
// number outside 0 to 63 becomes 0. Numbers below 50 name one table of effects
// and the rest a second one, counted from 50; whichever starts the effect
// returns the handle kept at 0x30. Both get the placement's position and angle.
//
// The two floats are the module's own constants, 0 and 1, shared with the rest
// of the class's code, so they are read as externals rather than written as
// literals the compiler would place in this file.

#define OBJ_SET_PARTICLE_CTOR inline
#include "src/rel/obj_set_particle_class.inc"

extern "C" void objSetparticleCreate(void)
{
	new TObjSetParticle(lbl_8042C110);
}
