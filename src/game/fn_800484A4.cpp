#include "types.h"

struct TFn800484A4Data {
	u8 mPadding0[0x6AC];
	s32 mField6AC;
	u8 mPadding6B0[0x46];
	s16 mField6F6;
	u8 mPadding6F8[0x68];
	s8 mField760;
	s8 mField761;
	u8 mPadding762[0x0E];
	s16 mField770;
	u8 mPadding772[0x246];
	s32 mField9B8;
	s8 mField9BC;
	s8 mField9BD;
};

extern "C" void fn_80090C70(s32 arg0, s32 arg1, s32 arg2);
extern "C" void fn_80137D0C(s32 voice, s32 character, s32 player);

extern "C" void fn_800484A4(TFn800484A4Data* arg0)
{
	s16 temp_r3;

	arg0->mField6F6 |= 4;
	temp_r3 = arg0->mField770;
	if ((temp_r3 & 0x800) == 0) {
		arg0->mField770 = temp_r3 | 0x800;
		arg0->mField6AC = 0x3C;
		fn_80090C70(arg0->mField9B8, arg0->mField9BD, 0x2F);
		fn_80137D0C(0x1B, arg0->mField761, arg0->mField760);
	}
}
