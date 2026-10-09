// sidaCreate, the factory rel/sida_register.cpp puts in the editor record for
// TObjSida, in stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what gives
// the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp has
// the long form. The class has the collision block as its third base, as in
// rel/warp_create.cpp, though nothing here gives it a shape.
//
// It is rel/tenkyu_create.cpp for "obj09_fern.dff": clone the module's model
// and, unless it is already in, add it to the world slot the model file names,
// reaching the model file through a local pointer.

#define SIDA_CTOR inline
#include "src/rel/sida_class.inc"

extern "C" void sidaCreate(void)
{
	new TObjSida(lbl_8042C110);
}
