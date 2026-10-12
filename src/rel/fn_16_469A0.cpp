#include "types.h"

extern "C" void fn_16_469A0(s32 arg0, s32* arg1, u8 arg2)
{
	*arg1 = (arg2 << 24) | (*arg1 & 0x00FFFFFF);
}
