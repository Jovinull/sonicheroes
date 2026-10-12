#include "types.h"

struct TFn800898F0 {
	u8 mPadding0[0x630];
	s32 mValue;
};

extern "C" void fn_800898F0(TFn800898F0* arg0, s32 arg1)
{
	arg0->mValue = arg1;
}
