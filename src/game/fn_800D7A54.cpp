#include "types.h"

extern "C" {
extern f32 lbl_803A7028[0x10000];
}

extern "C" u16 fn_800D7A54(u32 first, u32 second)
{
	u16 firstAngle  = (u16)first;
	u16 secondAngle = (u16)second;
	s16 difference  = (s16)(secondAngle - firstAngle);
	s16 result;
	if (difference < 0) {
		result = (s16)-difference;
	} else {
		result = difference;
	}
	return (u16)(s16)result;
}

extern "C" s16 fn_800D7A80(u32 first, u32 second)
{
	u16 firstAngle  = (u16)first;
	u16 secondAngle = (u16)second;
	return (s16)(secondAngle - firstAngle);
}

extern "C" u16 fn_800D7A94(u32 first, u32 second, s32 limit)
{
	u16 firstAngle = (u16)first;
	first          = (u16)second;
	s16 difference = (s16)(first - firstAngle);
	if (difference <= limit) {
		if (difference >= -limit)
			return (u16)first;
	}
	s16 result;
	if ((difference & 0x8000) != 0) {
		result = (s16)(firstAngle - limit);
	} else {
		result = (s16)(firstAngle + limit);
	}
	return (u16)(s16)result;
}

extern "C" f32 fn_800D7AE4(u16 angle)
{
	return lbl_803A7028[(u16)(angle + 0x4000)];
}

extern "C" f32 fn_800D7B00(u16 angle)
{
	return lbl_803A7028[angle];
}
