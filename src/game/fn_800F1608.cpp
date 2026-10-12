#include "types.h"

struct TFn800F1608 {
	u8 mPadding0[0x10];
	s16 mValue;
	u8 mPadding12[0x12];
	f32 mFloat;
};

extern "C" void fn_800F1608(TFn800F1608* arg0, s32 arg1, f32 arg2)
{
	arg0->mValue = arg1;
	arg0->mFloat = arg2;
}
