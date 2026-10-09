#include "game/effect/eff_bomb.h"

// fn_10_6CDEC, stage26D's start hook for its stage controller, TStg26Ctrl.
//
// It sets two of the engine's distances to the module's constants 400000 and
// 320000, calls fn_80110C38, and creates the controller once, keeping it in
// the module's instance slot. The allocation is a real new-expression of the
// C++ class, which is what gives the original's `mr r0, r3` and then
// `mr r31, r0`; rel/sample1_create.cpp has the long form. The class has a
// single base, and its constructor starts the mode at 0, sets the word at 0x2C,
// hangs a bare TObject under itself (a second new-expression, through
// TObject's own operator new) and starts the stage's music, "SNG_STG26.adx".

extern "C" char* CL_TStg26Ctrl;
extern "C" char stg26CtrlMusic[];
extern "C" const f32 stg26CtrlFarDistance[1];
extern "C" const f32 stg26CtrlNearDistance[1];
extern "C" f32 lbl_8042C20C;
extern "C" f32 lbl_802C216C;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_80110C38(void);
extern "C" void fn_800CCC6C(char* music);

class TStg26Ctrl;
extern "C" TStg26Ctrl* stg26CtrlInstance;

class TStg26Ctrl : public TObject
{
public:
	s32 mode;       // 0x28
	s32 unk2C;      // 0x2C
	TObject* child; // 0x30

	TStg26Ctrl(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TStg26Ctrl;
		DispTime  = 0x34;
		mode      = 0;
		unk2C     = 1;
		child     = new TObject(this);
		fn_800CCC6C(stg26CtrlMusic);
	}
	virtual ~TStg26Ctrl();
	virtual void Exec();
};

extern "C" void fn_10_6CDEC(void)
{
	lbl_8042C20C = stg26CtrlFarDistance[0];
	lbl_802C216C = stg26CtrlNearDistance[0];
	fn_80110C38();
	if (stg26CtrlInstance == NULL) {
		stg26CtrlInstance = new TStg26Ctrl(lbl_8042C110);
	}
}
