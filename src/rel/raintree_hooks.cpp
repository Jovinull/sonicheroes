#include "types.h"

// The raintree family's Reset and Unload hooks (raintreeReset and
// raintreeUnload here): nothing to reset; the resource is released. Its Load
// does more and is not here.

extern "C" void* raintreeResource;

extern "C" void fn_8013BD74(void* object);

extern "C" void raintreeReset(void) { }

extern "C" void raintreeUnload(void)
{
	fn_8013BD74(raintreeResource);
}
