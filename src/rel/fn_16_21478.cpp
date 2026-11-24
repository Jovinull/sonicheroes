#include "types.h"
extern "C" {
void* __nw__10TObjSampleFUl(u32);
void* fn_16_20E14(void*, s32, s32);
extern s32 lbl_8042C110;
void fn_16_21478(void)
{
	void* p;
	p = __nw__10TObjSampleFUl(0x134);
	if (p)
		p = fn_16_20E14(p, lbl_8042C110, 0);
}
}
