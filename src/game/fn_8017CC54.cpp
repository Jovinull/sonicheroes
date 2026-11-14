// Allocates a cleared libpng structure (HYPOTHESIS: png_create_struct_2): 0x1B4 bytes for a
// png_struct (type 1) or 0x120 for a png_info (type 2), through malloc_fn when given (with a stack
// png_struct carrying mem_ptr as its context, or none when mem_ptr is null) or through malloc.
// Returns null for an unknown type or a failed allocation.
#include "types.h"
#include "MSL_C/string.h"

#define PNG_STRUCT_PNG  1
#define PNG_STRUCT_INFO 2

// png_struct (HYPOTHESIS: 0x1B4 bytes; only the allocator context is used here).
struct Png8017CC54 {
	unsigned char pad0[0x1A8];
	void* memPtr; // 0x1A8
	unsigned char pad1AC[0x1B4 - 0x1AC];
};

typedef void* (*PngMalloc8017CC54)(Png8017CC54* png, unsigned int size);

extern "C" {
void* malloc(unsigned int size);

void* fn_8017CC54(int type, PngMalloc8017CC54 mallocFn, void* memPtr)
{
	unsigned int size;
	void* ptr;
	if (type == PNG_STRUCT_INFO) {
		size = 0x120;
	} else if (type == PNG_STRUCT_PNG) {
		size = sizeof(Png8017CC54);
	} else {
		return 0;
	}
	if (mallocFn != 0) {
		if (memPtr != 0) {
			Png8017CC54 dummy;
			dummy.memPtr = memPtr;
			ptr          = mallocFn(&dummy, size);
		} else {
			ptr = mallocFn(0, size);
		}
		if (ptr != 0) {
			memset(ptr, 0, size);
		}
		return ptr;
	}
	ptr = malloc(size);
	if (ptr != 0) {
		memset(ptr, 0, size);
	}
	return ptr;
}
}
