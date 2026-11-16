#include "types.h"

extern "C" void* lbl_8042C110;
extern "C" void* __nw__10TObjSampleFUl(u32 size);
extern "C" void* fn_16_17DBC(void* p, void* o);

extern "C" void fn_16_18048(void)
{
	void* p = __nw__10TObjSampleFUl(0x6C);
	if (p) {
		p = fn_16_17DBC(p, lbl_8042C110);
	}
}
