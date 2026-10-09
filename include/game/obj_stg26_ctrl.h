#ifndef GAME_OBJ_STG26_CTRL_H
#define GAME_OBJ_STG26_CTRL_H
#include "game/effect/eff_bomb.h"

// TStg26Ctrl, stage26D's stage controller: a single-base object kept in the
// module's instance slot. Its constructor starts the mode at 0, sets the word
// at 0x2C, hangs a bare TObject under itself (a second new-expression, through
// TObject's own operator new) and starts the stage's music, "SNG_STG26.adx".
// It is inlined into rel/stg26_ctrl_start.cpp and rel/stg26_ctrl_reset.cpp.

extern "C" char* CL_TStg26Ctrl;
extern "C" char stg26CtrlMusic[];
extern "C" void fn_800CCC6C(char* music);

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

extern "C" TStg26Ctrl* stg26CtrlInstance;

#endif
