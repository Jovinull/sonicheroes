// powderCreate, the factory the editor record for TObjPowder points at, in
// stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The object carries a 4 KiB work area that the constructor clears with
// memset, and a word after it; the instance is 0x10D4 bytes.

#define POWDER_CTOR inline
#include "src/rel/powder_class.inc"

extern "C" void powderCreate(void)
{
	new TObjPowder(lbl_8042C110);
}
