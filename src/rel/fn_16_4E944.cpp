#include "types.h"

extern "C" void __dl__FPv(void* memory);
extern "C" void fn_16_4E864(void* object);

extern "C" void* fn_16_4E944(void* object, s16 flags)
{
	if (object != NULL) {
		fn_16_4E864(object);
		if (flags > 0) {
			__dl__FPv(object);
		}
	}
	return object;
}
