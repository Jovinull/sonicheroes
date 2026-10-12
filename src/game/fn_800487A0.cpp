#include "types.h"

struct TFn800487A0 {
	u8 mPadding0[0x678];
	s32 mValues[4];
};

extern "C" void fn_800487A0(TFn800487A0* arg0)
{
	arg0->mValues[0] = 0;
	arg0->mValues[1] = 0;
	arg0->mValues[2] = 0;
	arg0->mValues[3] = 0;
}
