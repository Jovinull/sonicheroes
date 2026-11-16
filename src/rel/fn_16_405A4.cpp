#include "types.h"

extern "C" {
void* __nw__10TObjSampleFUl(u32 size);
void* fn_16_4025C(void* obj, void* owner);
extern void* lbl_8042C110;

void fn_16_405A4(void)
{
	void* p;

	p = __nw__10TObjSampleFUl(0xEC);
	if (p) {
		p = fn_16_4025C(p, lbl_8042C110);
	}
}
}
