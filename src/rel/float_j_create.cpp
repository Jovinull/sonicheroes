// floatjCreate, the factory the editor record for TObjFloatJ points at, in
// stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The object clones the module's model into the world at 0x725C of the stage
// block, then sizes the module's shape: its radius is the first word of the
// placement's parameter block times the module's constant 20. The parameter
// block pointer is read first, before the class name.

#define FLOAT_J_CTOR inline
#include "src/rel/float_j_class.inc"

extern "C" void floatjCreate(void)
{
	new TObjFloatJ(lbl_8042C110);
}
