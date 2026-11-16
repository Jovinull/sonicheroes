#include "types.h"

extern "C" void* lbl_8042C110;
extern "C" void* __nw__10TObjSampleFUl(u32 size);
extern "C" void* fn_16_28E60(void* object, void* owner);

extern "C" void fn_16_29254(void)
{
	void* p = __nw__10TObjSampleFUl(0xF4);

	if (p) {
		p = fn_16_28E60(p, lbl_8042C110);
	}
}
