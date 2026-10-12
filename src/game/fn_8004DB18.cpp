#include "types.h"

struct TFn8004DB18Entry {
	s32 mValue;
	u8 mPadding[0x110];
};

extern "C" TFn8004DB18Entry lbl_802C1D1C[4];
extern "C" s32 lbl_8042C1FC;

extern "C" s32 fn_8004DB18(void)
{
	// Keep the index first so MWCC scales it before materializing the base.
	return lbl_8042C1FC[lbl_802C1D1C].mValue != 0;
}
