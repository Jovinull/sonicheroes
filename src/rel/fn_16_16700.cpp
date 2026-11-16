#include "types.h"

extern "C" void* lbl_8042C110;
extern "C" void* __nw__10TObjSampleFUl(u32 size);
extern "C" void* fn_16_16418(void* p, void* o);

extern "C" void fn_16_16700(void)
{
	void* p = __nw__10TObjSampleFUl(0xF8);
	if (p) {
		p = fn_16_16418(p, lbl_8042C110);
	}
}
