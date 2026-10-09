// noOttottoCollisionCreate, the factory the editor record for
// TObjSetNoOttottoCollision points at. The PS2 build keeps the class in
// o_setNoOttottoCollision.cpp; there the constructor is a function of its own,
// here it is inlined into the factory.
//
// It is the same 76 instructions in twelve of the stage modules that share the
// engine core, at a different address in each, so each module's splits.txt
// names its own range. stage11D has the whole class carved already, in
// rel/no_ottotto_collision_stage11.cpp, where a post-processor inserts the
// register copy this file gets from the compiler.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp,
// because the original builds it before the vtable stores.
//
// The placement's parameter block picks one of the module's two collision
// shapes and gives it its three extents; the shape is then handed to the
// collision base. The index is read again for every store because each store
// is a float the compiler cannot prove does not alias it.

#define NO_OTTOTTO_COLLISION_CTOR inline
#include "src/rel/no_ottotto_collision_class.inc"

extern "C" void noOttottoCollisionCreate(void)
{
	new TObjSetNoOttottoCollision(lbl_8042C110);
}
