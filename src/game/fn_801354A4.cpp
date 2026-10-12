#include "types.h"

struct TFn801354A4 {
	u8 mPadding0[0x18];
	u32 mFlags;
};

extern "C" s32 fn_801354A4(TFn801354A4* arg0)
{
	return (u32)__cntlzw(arg0->mFlags & 0x8080) >> 5;
}
