// Copies size bytes from src to dst after the size-overflow check (HYPOTHESIS: libpng
// png_memcpy_check; the check compares the size with itself converted to the size type, which
// cannot fail here, and would report lbl_8028ECC8 through fn_8017C5A8, png_error).
#include "types.h"
#include "MSL_C/string.h"

extern "C" {
extern char lbl_8028ECC8[];
void fn_8017C5A8(void* png, const char* message);

void* fn_8017CEF8(void* png, void* dst, const void* src, unsigned int size)
{
	unsigned long total = size;
	if (total != size) {
		fn_8017C5A8(png, lbl_8028ECC8);
	}
	return memcpy(dst, src, total);
}
}
