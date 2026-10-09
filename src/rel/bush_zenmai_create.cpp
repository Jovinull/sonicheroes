// bushzenmaiCreate, the factory rel/bushzenmai_register.cpp puts in the editor
// record for TObjBushZenmai, in stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what gives
// the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp has
// the long form. The class has the collision block as its third base, as in
// rel/warp_create.cpp, and it takes the module's shape through InitShare, as
// rel/key_object_create.cpp does.
//
// It is rel/tenkyu_create.cpp for "obj10_zenmai.dff": clone the module's model
// and, unless it is already in, add it to the world slot the model file names,
// reading the model file's global each time, which the original does too.

#define BUSH_ZENMAI_CTOR inline
#include "src/rel/bush_zenmai_class.inc"

extern "C" void bushzenmaiCreate(void)
{
	new TObjBushZenmai(lbl_8042C110);
}
