#include "types.h"

extern "C" void* __nw__10TObjSampleFUl(u32 size);
extern "C" void* fn_16_612C(void* object, void* owner);
extern "C" void* lbl_8042C110;

extern "C" void fn_16_6460(void)
{
	void* object = __nw__10TObjSampleFUl(0xF4);
	if (object != NULL) {
		object = fn_16_612C(object, lbl_8042C110);
	}
}
