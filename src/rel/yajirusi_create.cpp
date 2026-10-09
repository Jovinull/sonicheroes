// yajirusiCreate, the factory rel/yajirusi_register.cpp puts in the editor
// record for TObjYajirusi, in stage05D.
//
// The allocation is a real new-expression of the C++ class, which is what gives
// the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp has
// the long form. The class has the collision block as its third base, as in
// rel/warp_create.cpp.
//
// It is rel/rail_cap_ex_create.cpp for 2 models, starting with
// "stg05_on_ya01.dff": each is cloned into its own part and added once to the
// world slot its file names. The collision base then takes 1 of the module's
// shapes through InitShare, as rel/key_object_create.cpp does.

#define YAJIRUSI_CTOR inline
#include "src/rel/yajirusi_class.inc"

extern "C" void yajirusiCreate(void)
{
	new TObjYajirusi(lbl_8042C110);
}
