#include "types.h"

extern "C" {
extern void* lbl_80303DC8[];
s32 fn_8009278C(void* team, s32 type);
void fn_16_D70(void* team, s32 member);
}

extern "C" void fn_16_4CC9C(s32 arg0, s32 arg1)
{
	fn_16_D70(lbl_80303DC8[arg0], fn_8009278C(lbl_80303DC8[arg0], arg1));
}
