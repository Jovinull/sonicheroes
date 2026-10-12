#include "types.h"

struct TFn8010F5D8Child {
	u8 mPadding[4];
	s32 mFlags;
};

struct TFn8010F5D8 {
	u8 mPadding0[0x70];
	TFn8010F5D8Child* mpChild;
	u8 mPadding1[0x134];
	s32 mValue1A8;
};

extern "C" void fn_8010F5D8(TFn8010F5D8* arg0)
{
	TFn8010F5D8Child* child = arg0->mpChild;
	if (child != NULL) {
		child->mFlags |= 0x10;
	}
	arg0->mValue1A8 = 0;
}
