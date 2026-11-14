// Clears size bytes at dst to value after the size-overflow check (HYPOTHESIS: libpng
// png_memset_check; the check compares the size with itself converted to the size type, which
// cannot fail here, and would report the message lbl_8028ECE8 through fn_8017C5A8, png_error).
#include "types.h"
#include "MSL_C/string.h"

extern "C" {
extern char lbl_8028ECE8[];
void fn_8017C5A8(void* png, const char* message);

void* fn_8017CF5C(void* png, void* dst, s32 value, unsigned int size)
{
	unsigned long total = size;
	if (total != size) {
		fn_8017C5A8(png, lbl_8028ECE8);
	}
	return memset(dst, value, total);
}
}
