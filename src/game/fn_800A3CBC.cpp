#include "types.h"

struct TFn800A3CBC {
	u8 mPadding0[0x106];
	volatile u16 mFlags;
	u8 mPadding1[0x110];
	s32 mValue218;
	s32 mValue21C;
};

extern "C" void fn_800A3CBC(TFn800A3CBC* arg0)
{
	u32 flags;

	arg0->mValue21C = 0;
	arg0->mValue218 = 5;
	// Keep the explicit u16 narrowing after clearing the low four bits.
	flags = arg0->mFlags;
	flags &= 0xFFFFFFF0;
	arg0->mFlags = flags;
}
