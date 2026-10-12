#include "types.h"

struct TFn8004D99C {
	s32 mValue;
	u8 mPadding[8];
};

extern "C" s32 lbl_8042C1FC;
extern "C" TFn8004D99C lbl_802D5AF0[4];

extern "C" void fn_8004D99C()
{
	s32 value                  = 0;
	s32 index                  = lbl_8042C1FC;
	lbl_802D5AF0[index].mValue = value;
}
