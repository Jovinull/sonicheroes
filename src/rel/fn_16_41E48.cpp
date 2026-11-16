#include "types.h"

extern "C" {
void* __nw__10TObjSampleFUl(unsigned long size);
void* fn_16_41A20(void* object, void* owner);
extern void* lbl_8042C110;

void fn_16_41E48(void)
{
	void* p;
	p = __nw__10TObjSampleFUl(0x84);
	if (p) {
		p = fn_16_41A20(p, lbl_8042C110);
	}
}
}
