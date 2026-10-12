#include "types.h"

struct TFn8004FC9CData {
	u8 mPadding0[5];
	volatile s8 mField5;
	u8 mPadding6[0x16];
	volatile s8 mField1C;
};

extern TFn8004FC9CData* lbl_8042C180;

extern "C" void fn_8004FC9C(void)
{
	TFn8004FC9CData* data = lbl_8042C180;
	if (data->mField1C != 0 || data->mField5 == 0) {
		return;
	}
}
