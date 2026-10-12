#include "types.h"

struct TFn800A31A0Inner {
	u8 mPadding0[0x18];
	u32 mValue;
};

struct TFn800A31A0 {
	u8 mPadding0[0xB0];
	TFn800A31A0Inner* mpInner;
};

extern "C" s32 fn_800A31A0(TFn800A31A0* arg0)
{
	return ((arg0->mpInner->mValue & 0x1C0000) >> 18) + 8;
}
