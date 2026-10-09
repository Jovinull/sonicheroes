// fn_3_9FC0C, the factory for TObjS02Rolling_CL in stage01D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// In the editor a zero size in the placement's parameter block becomes 50, the
// module's constants 0 and 50. The kind byte at 4 then picks the two bytes at
// 0xB8: a bit (1, 2, 4 or 8) and whether it is one of the upper two kinds. The
// parameter block pointer is read first, before the class name.

#define S02_ROLLING_CL_CTOR inline
#include "src/rel/s02_rolling_cl_class.inc"

extern "C" void fn_3_9FC0C(void)
{
	new TObjS02Rolling_CL(lbl_8042C110);
}
