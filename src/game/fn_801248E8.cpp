#include "types.h"

struct TFn801248E8 {
	u8 mPadding0[0xD8];
	s32 mValues[1];
};

extern "C" s32 fn_801248E8(TFn801248E8* arg0, s32 arg1)
{
	return arg0->mValues[arg1];
}
