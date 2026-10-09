// s13TsuitateCreate, the factory the editor record for TObjS13Partition
// points at, in stage13D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The module's loader (fn_9_75A80) builds the clump from the class's model
// description and the collision base takes two of the module's shapes. The
// clump's frame is then turned about Y by the placement's angle and moved to
// the placement, as in rel/s14d_crush_create.cpp. The 1 is the module's
// constant, read as an external.

#define S13_PARTITION_CTOR inline
#include "src/rel/s13_partition_class.inc"

extern "C" void s13TsuitateCreate(void)
{
	new TObjS13Partition(lbl_8042C110);
}
