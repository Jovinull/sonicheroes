#include "types.h"

extern "C" void fn_16_9FC4(u32* p, s8 bit)
{
	p[(bit & 0x60) >> 5] |= 1 << (bit & 0x1F);
}
