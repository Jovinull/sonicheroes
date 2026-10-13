#include "types.h"

struct TFn80043E9CData {
	u8 mPadding0[0x6F0];
	s16 mField6F0;
	u8 mPadding6F2[2];
	s16 mField6F4;
	s16 mField6F6;
};

extern "C" void fn_800E12FC(u8* arg0, u8* arg1);

extern "C" s32 fn_80043E9C(TFn80043E9CData* arg0)
{
	u8* temp_r3 = (u8*)arg0 + 0x720;
	u8* temp_r4 = (u8*)arg0 + 0x760;
	if ((arg0->mField6F6 & 0x1000) != 0 && arg0->mField6F4 == 0x3F) {
		return 0;
	}

	s16 temp_r5             = *(s16*)(temp_r4 + 0x10);
	*(s16*)(temp_r4 + 0x10) = temp_r5 & ~0x4C00;
	arg0->mField6F0         = 0x27;
	fn_800E12FC(temp_r3, temp_r4);
	arg0->mField6F6 &= ~0x2500;
	return 1;
}
