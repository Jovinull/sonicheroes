// Calls the one-shot callback stored at +0x58, if any, then clears it.

#include "types.h"

extern "C" void fn_8004E6AC(void* self)
{
	void (*callback)() = *(void (**)())((u8*)self + 0x58);

	if (callback != NULL) {
		callback();
		*(void**)((u8*)self + 0x58) = NULL;
	}
}
