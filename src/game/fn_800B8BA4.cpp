#include "types.h"

// HYPOTHESIS: If the object passes the code-6 predicate, run the code-6 operation; always return the object.

extern "C" {
u32 fn_80146BC8(void*, s32);
void fn_80146B08(void*, s32);
void* fn_800B8BA4(void* object)
{
	if (fn_80146BC8(object, 6) != 0) {
		fn_80146B08(object, 6);
	}
	return object;
}
}
