#include "game/obj_stg26_ctrl.h"

// fn_10_6CDEC, stage26D's start hook for its stage controller, TStg26Ctrl
// (game/obj_stg26_ctrl.h).
//
// It sets two of the engine's distances to the module's constants 400000 and
// 320000, calls fn_80110C38, and creates the controller once, keeping it in
// the module's instance slot. The allocation is a real new-expression of the
// C++ class, which is what gives the original's `mr r0, r3` and then
// `mr r31, r0`; rel/sample1_create.cpp has the long form.

extern "C" const f32 stg26CtrlFarDistance[1];
extern "C" const f32 stg26CtrlNearDistance[1];
extern "C" f32 lbl_8042C20C;
extern "C" f32 lbl_802C216C;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_80110C38(void);

extern "C" void fn_10_6CDEC(void)
{
	lbl_8042C20C = stg26CtrlFarDistance[0];
	lbl_802C216C = stg26CtrlNearDistance[0];
	fn_80110C38();
	if (stg26CtrlInstance == NULL) {
		stg26CtrlInstance = new TStg26Ctrl(lbl_8042C110);
	}
}
