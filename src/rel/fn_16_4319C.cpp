#include "types.h"

extern "C" {
void* __nw__10TObjSampleFUl(u32 size);
void* fn_16_42F60(void* p, void* a);
extern void* lbl_8042C110;

void fn_16_4319C(void)
{
	void* p;
	p = __nw__10TObjSampleFUl(0x34);
	if (p) {
		p = fn_16_42F60(p, lbl_8042C110);
	}
}
}
