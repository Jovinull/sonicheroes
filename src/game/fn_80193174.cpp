#include "types.h"

extern "C" {

void* fn_80193174(void* mem, u32 size)
{
	u32 v;
	u32* p = (u32*)mem;
	u32 n  = size >> 2;

	while (n) {
		v  = *p;
		*p = (v << 24) | ((v & 0xFF00) << 8) | ((v >> 8) & 0xFF00) | (v >> 24);
		p++;
		n--;
	}
	return mem;
}
}
