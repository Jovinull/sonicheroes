// Default zlib deallocator (HYPOTHESIS: zlib zcfree): frees ptr with free. The opaque pointer is
// only tested to keep it used, as zlib does.
#include "types.h"

extern "C" {
void free(void* ptr);

void fn_801788FC(void* opaque, void* ptr)
{
	free(ptr);
	if (opaque) {
		return;
	}
}
}
