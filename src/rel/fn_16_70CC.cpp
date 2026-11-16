#include "types.h"

extern "C" void* lbl_8042C110;
extern "C" void* __nw__10TObjSampleFUl(u32 size);
extern "C" void* fn_16_6D7C(void* object, void* owner);

extern "C" void fn_16_70CC(void)
{
	void* memory = __nw__10TObjSampleFUl(0x68);

	if (memory != NULL) {
		memory = fn_16_6D7C(memory, lbl_8042C110);
	}
}
