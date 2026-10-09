// s14keyObjectCreate, the factory the editor record for TObjS14Key points at,
// in stage13D. It is rel/s06_chip_create.cpp under another class name.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp, and
// it takes the module's shape through InitShare, as rel/key_object_create.cpp
// does.
//
// The key clones the module's model, lights it from the placement and wraps
// it in a DealMaterial, a real new-expression too. Outside the editor it takes
// its shape and runs SearchCage, the key's search for a cage (type 0x24) within
// the module's range constant; see rel/key_object_create.cpp. In game mode 8
// the placement is flagged with bit 0x10000000. The floats are the module's
// constants, read as externals.

#define S14_KEY_CTOR inline
#include "src/rel/s14_key_class.inc"

extern "C" void s14keyObjectCreate(void)
{
	new TObjS14Key(lbl_8042C110);
}
