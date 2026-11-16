#include "types.h"
extern "C" {
void* __nw__10TObjSampleFUl(u32);
void* fn_16_427B0(void*, s32);
extern s32 lbl_8042C110;
void fn_16_429C8(void)
{
	void* p = __nw__10TObjSampleFUl(0xD0);
	if (p)
		p = fn_16_427B0(p, lbl_8042C110);
}
}
