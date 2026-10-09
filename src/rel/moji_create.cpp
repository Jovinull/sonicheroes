// mojiCreate, the factory the editor record for TObjMoji points at, in
// stage05D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp, and
// it takes the module's shapes through InitShare, as rel/key_object_create.cpp
// does.
//
// It is rel/big_dice_create.cpp for eight models, starting with
// "stg05_on_moji01.dff": clone each into its own part, apply the placement
// through the class's own EditOnChange, and then take two of the module's four
// shapes, the second pair when the first word of the parameter block is 1. The
// parameter block pointer is read with the position, and the loop counter is
// declared before it, which is the order the original gives them registers.

#define MOJI_CTOR inline
#include "src/rel/moji_class.inc"

extern "C" void mojiCreate(void)
{
	new TObjMoji(lbl_8042C110);
}
