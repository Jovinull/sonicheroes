#include "types.h"

class TObjSample;
extern "C" void* lbl_8042C110;
extern "C" void* __nw__10TObjSampleFUl(u32 size);
extern "C" void* fn_16_1E33C(void* object, void* owner, int flag);

extern "C" void fn_16_1E900(void)
{
	void* p = __nw__10TObjSampleFUl(0x110);

	if (p) {
		p = fn_16_1E33C(p, lbl_8042C110, 0);
	}
}
