// Calls the one-shot callback stored at +0x54, if any, then clears it.

#include "types.h"

extern "C" void fn_8004EC58(void* self)
{
	void (*callback)() = *(void (**)())((u8*)self + 0x54);

	if (callback != NULL) {
		callback();
		*(void**)((u8*)self + 0x54) = NULL;
	}
}
