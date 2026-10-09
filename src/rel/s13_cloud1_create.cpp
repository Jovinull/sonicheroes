// s13Cloud1Create, the factory the editor record for TObjS13Cloud1 points at,
// in stage13D, stage27D and stage28D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0` (here r30);
// rel/sample1_create.cpp has the long form. The third base is TObjS13Cloud,
// which the PS2 build names through SetTopPtcl and GetTopPtcl: it holds the
// first particle of the cloud and its inline constructor clears it, which is
// why that store comes before the vtable stores.
//
// In the editor two zero halfwords of the parameter block become 20 and 60.
// The parameter block pointer is read first, before the class name.

#define S13_CLOUD1_CTOR inline
#include "src/rel/s13_cloud1_class.inc"

extern "C" void s13Cloud1Create(void)
{
	new TObjS13Cloud1(lbl_8042C110);
}
