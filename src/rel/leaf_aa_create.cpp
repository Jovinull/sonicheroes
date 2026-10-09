// leafaaCreate, the factory the editor record for TObjLeafAA points at, in
// stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// It is rel/water_plant_create.cpp for "dobj_leafAA.dff", with one more word
// in front of the position that the constructor clears last.

#define LEAF_AA_CTOR inline
#include "src/rel/leaf_aa_class.inc"

extern "C" void leafaaCreate(void)
{
	new TObjLeafAA(lbl_8042C110);
}
