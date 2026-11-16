#include "types.h"

extern "C" s32 fn_16_F20(signed char* o, s32 i)
{
	if (i < 0) {
		return -1;
	}
	if (i < 0x2c) {
		return o[i];
	}
	if (i < 0x33) {
		return *(s32*)((u8*)o + 0x2c + (i - 0x2d) * 4);
	}
	return -1;
}
