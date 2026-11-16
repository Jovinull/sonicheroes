#include "types.h"

extern "C" {
void* __nw__10TObjSampleFUl(u32);
void* fn_16_30CC0(void*, s32);
extern s32 lbl_8042C110;

void fn_16_31038(void)
{
	void* p;
	p = __nw__10TObjSampleFUl(0x100);
	if (p) {
		p = fn_16_30CC0(p, lbl_8042C110);
	}
}
}
