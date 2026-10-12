#include "types.h"

// This unique main region contains three short field getters.
struct TFn80128224Data {
	u8 mPadding0[8];
	s32 mValue8;
	u8 mPaddingC[8];
	s32 mValue14;
	u8 mPadding18[4];
	s32 mValue1C;
};

extern "C" s32 fn_80128224(TFn80128224Data* arg0)
{
	return arg0->mValue1C;
}

extern "C" s32 fn_8012822C(TFn80128224Data* arg0)
{
	return arg0->mValue14;
}

extern "C" s32 fn_80128234(TFn80128224Data* arg0)
{
	return arg0->mValue8;
}
