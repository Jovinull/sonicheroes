#include "types.h"

extern "C" {
void* __nw__10TObjSampleFUl(u32 size);
void* fn_16_113CC(void* p, s32 v);
extern s32 lbl_8042C110;

void fn_16_11564(void)
{
	void* p = __nw__10TObjSampleFUl(0xF8);
	if (p != 0)
		p = fn_16_113CC(p, lbl_8042C110);
}
}
