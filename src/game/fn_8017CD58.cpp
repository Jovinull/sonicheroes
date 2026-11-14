// Frees a libpng structure (HYPOTHESIS: png_destroy_struct_2): through freeFn with a stack
// png_struct carrying mem_ptr as its context when given, otherwise through free. A null pointer is
// ignored.
#include "types.h"

// png_struct (HYPOTHESIS: 0x1B4 bytes; only the allocator context is used here).
struct Png8017CD58 {
	unsigned char pad0[0x1A8];
	void* memPtr; // 0x1A8
	unsigned char pad1AC[0x1B4 - 0x1AC];
};

typedef void (*PngFree8017CD58)(Png8017CD58* png, void* ptr);

extern "C" {
void free(void* ptr);

void fn_8017CD58(void* ptr, PngFree8017CD58 freeFn, void* memPtr)
{
	if (ptr != 0) {
		if (freeFn != 0) {
			Png8017CD58 dummy;
			dummy.memPtr = memPtr;
			freeFn(&dummy, ptr);
		} else {
			free(ptr);
		}
	}
}
}
