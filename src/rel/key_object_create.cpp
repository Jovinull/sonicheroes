// keyObjectCreate, the factory the editor record for TObjKey points at.
//
// It is the same 124 instructions in the thirteen stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp, and
// it takes its shape through InitShare, the PS2 name of fn_8003BF04; see the
// helper below.
//
// The constructor ends with SearchCage, which rel/e_s11_key_stage11.cpp already
// writes for stage 11's key: unless the placement already carries one, walk
// the placements of the key's group for a cage (type 0x24) closer than the
// module's range constant, and leave a tagged record with the key's position
// on the placement. Here the range is the module's own float, read once before
// the walk.
//
// The light bits are read through a volatile access for the reason written up
// in rel/itembaloon_create.cpp.

#define KEY_OBJECT_CTOR inline
#include "src/rel/key_object_class.inc"

extern "C" void keyObjectCreate(void)
{
	new TObjKey(lbl_8042C110);
}
