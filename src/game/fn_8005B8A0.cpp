#include "types.h"

struct TFn8005B8A0 {
	u8 mPadding0[0x18];
	s32 mValues[4];
};

extern "C" void fn_8005B8A0(TFn8005B8A0* arg0)
{
	arg0->mValues[0] = 0;
	arg0->mValues[1] = 0;
	arg0->mValues[2] = 0;
	arg0->mValues[3] = 0;
}
