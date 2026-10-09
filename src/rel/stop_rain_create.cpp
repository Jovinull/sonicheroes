// stoprainCreate, the factory the editor record for TObjStopRain points at, in
// stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The placement's parameter block holds the box's three extents; the module's
// shape takes each halved, by the module's constant 0.5, before it goes to the
// collision base. The parameter block pointer is read first, before the class
// name, and the constant once.

#define STOP_RAIN_CTOR inline
#include "src/rel/stop_rain_class.inc"

extern "C" void stoprainCreate(void)
{
	new TObjStopRain(lbl_8042C110);
}
