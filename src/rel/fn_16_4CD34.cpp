#include "types.h"

extern "C" void* lbl_80303DC8[];
extern "C" s32 fn_8009278C(void* team, int type);

extern "C" void fn_16_4CD34(int idx, s8* out)
{
	out[0] = fn_8009278C(lbl_80303DC8[idx], 0);
	out[1] = fn_8009278C(lbl_80303DC8[idx], 2);
	out[2] = fn_8009278C(lbl_80303DC8[idx], 1);
}
