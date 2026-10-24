#include "types.h"

// The rainleaf family's Reset and Unload hooks (rainleafReset and
// rainleafUnload here): nothing to reset; the resource is released. Its Load
// does more and is not here.

extern "C" void* rainleafResource;

extern "C" void fn_8013BD74(void* object);

extern "C" void rainleafReset(void) { }

extern "C" void rainleafUnload(void)
{
	fn_8013BD74(rainleafResource);
}
