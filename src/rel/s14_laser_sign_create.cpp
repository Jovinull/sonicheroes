// s14LaserSignCreate, the factory rel/s14_laser_sign_register.cpp puts in
// the editor record for TObjS14LaserSignSet, in stage13D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// The first set object of a placement leaves an eight byte record on it, built
// with the global operator new; the record's constructor clears its count, and
// the set clears it again once the record is attached.

#define S14_LASER_SIGN_CTOR inline
#include "src/rel/s14_laser_sign_class.inc"

extern "C" void s14LaserSignCreate(void)
{
	new TObjS14LaserSignSet(lbl_8042C110);
}
