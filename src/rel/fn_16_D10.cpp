#include "types.h"

extern "C" s32 fn_800211A8(s32 arg0);
extern "C" void fn_16_D4C(s32 arg0, s32 arg1);

extern "C" void fn_16_D10(s32 arg0)
{
	fn_16_D4C(arg0, fn_800211A8(arg0));
}
