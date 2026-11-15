#include "types.h"

extern "C" {

s32 fn_801645E4(void*); /* extern */

s32 fn_801649BC(void* arg1, s32 arg2, s32 arg3)
{
	s32 t = arg3 * fn_801645E4(arg1);
	s32 x = arg2 * 3;
	x += t;
	x = (x + 0x1F) & 0xFFFFFFE0;
	return x;
}
}
