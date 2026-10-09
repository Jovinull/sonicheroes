// s14ThunderCreate, the factory the editor record for TObjS14ThunderSet points
// at, in stage13D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// In the editor an all-zero parameter block gets the defaults 100, 10 and 100,
// and a zero float at 0x8 becomes 1 with the next one cleared; the 0 and 1 are
// the module's constants, read as externals. The set keeps pointers to its
// placement and to the placement's angle, and finishes in fn_9_A215C, a
// function of the class the PS2 build's names do not settle. The parameter
// block pointer is read first, before the class name.

#define S14_THUNDER_CTOR inline
#include "src/rel/s14_thunder_class.inc"

extern "C" void s14ThunderCreate(void)
{
	new TObjS14ThunderSet(lbl_8042C110);
}
