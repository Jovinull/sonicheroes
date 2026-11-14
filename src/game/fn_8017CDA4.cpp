// Allocates size bytes for png (HYPOTHESIS: libpng png_malloc): through the user allocator at +0x1AC
// when one is installed, reporting a failure through fn_8017C5A8 (png_error) with lbl_8028ECA8,
// otherwise through fn_8017CE20 (png_malloc_default). Returns null for a null png or a zero size.
#include "types.h"

struct Png8017CDA4 {
	unsigned char pad0[0x1AC];
	void* (*mallocFn)(Png8017CDA4* png, unsigned int size); // 0x1AC
};

extern "C" {
extern char lbl_8028ECA8[];
void fn_8017C5A8(Png8017CDA4* png, const char* message);
void* fn_8017CE20(Png8017CDA4* png, unsigned int size);

void* fn_8017CDA4(Png8017CDA4* png, unsigned int size)
{
	void* ret;
	if (png == 0 || size == 0) {
		return 0;
	}
	if (png->mallocFn != 0) {
		ret = png->mallocFn(png, size);
		if (ret == 0) {
			fn_8017C5A8(png, lbl_8028ECA8);
		}
		return ret;
	}
	return fn_8017CE20(png, size);
}
}
