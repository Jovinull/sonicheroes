// Default libpng deallocator (HYPOTHESIS: png_free_default): frees ptr with free; nothing happens
// for a null png or pointer.
#include "types.h"

extern "C" {
void free(void* ptr);

void fn_8017CEC0(void* png, void* ptr)
{
	if (png == 0 || ptr == 0) {
		return;
	}
	free(ptr);
}
}
