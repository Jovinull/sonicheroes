#include "types.h"

extern "C" {
s32 fn_80239724(s32 arg0);
s32 fn_16_51BF4(s32 arg0);
void fn_16_50398(s32 arg0, s32 arg1);
}

extern "C" s32 fn_16_50320(s32 arg0, s32 arg1)
{
	s32 temp_r31;
	s32 temp_r30;
	s32 temp_r29;

	temp_r31 = fn_80239724(arg0);
	temp_r30 = fn_16_51BF4(arg1);
	temp_r29 = fn_80239724(temp_r30);
	fn_16_50398(temp_r31, temp_r29);
	return arg0;
}
