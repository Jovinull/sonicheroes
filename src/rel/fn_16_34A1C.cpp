#include "types.h"

extern "C" {
void* __nw__10TObjSampleFUl(u32);
void* fn_16_34440(void*, void*);
extern void* lbl_8042C110;

void fn_16_34A1C(void)
{
	void* p = __nw__10TObjSampleFUl(0xFC);

	if (p) {
		p = fn_16_34440(p, lbl_8042C110);
	}
}
}
