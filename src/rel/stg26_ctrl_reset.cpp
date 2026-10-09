#include "game/obj_stg26_ctrl.h"

// fn_10_6CBB4, stage26D's reset of its stage controller, TStg26Ctrl
// (game/obj_stg26_ctrl.h): delete the one in the module's instance slot, if
// any, through its virtual destructor, and create a fresh one in its place.
//
// The explicit test in front of the delete is the original's: it is why there
// are two branches on the one compare, the second from delete's own null test.
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.

extern "C" TObject* lbl_8042C110;

extern "C" void fn_10_6CBB4(void)
{
	if (stg26CtrlInstance != NULL) {
		delete stg26CtrlInstance;
	}
	stg26CtrlInstance = new TStg26Ctrl(lbl_8042C110);
}
