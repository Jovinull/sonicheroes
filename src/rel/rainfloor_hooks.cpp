#include "types.h"

// The rainfloor family's Reset and Unload hooks (rainfloorReset and
// rainfloorUnload here): nothing to reset; the resource is released. Its Load
// does more and is not here.

extern "C" void* rainfloorResource;

extern "C" void fn_8013BD74(void* object);

extern "C" void rainfloorReset(void) { }

extern "C" void rainfloorUnload(void)
{
	fn_8013BD74(rainfloorResource);
}
