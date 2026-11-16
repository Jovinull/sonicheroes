#include "types.h"

extern "C" {
void* __nw__10TObjSampleFUl(u32 size);
void* fn_16_4FFE0(void* p);

void* fn_16_4F5F4(void)
{
	void* p = __nw__10TObjSampleFUl(0x74);
	if (p != 0)
		p = fn_16_4FFE0(p);
	return p;
}
}
