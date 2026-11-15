// Formats a wide string into a buffer (HYPOTHESIS: a swprintf-style helper of the menus): clears
// the buffer and formats into it with wideFormatToBuffer. Does nothing without a buffer.
#include "types.h"
#include "Runtime.PPCEABI.H/__va_arg.h"

extern "C" {
s32 wideFormatToBuffer(u16* buffer, const u16* format, void* args);

void fn_8012EC18(u16* buffer, const u16* format, ...)
{
	if (buffer != 0) {
		__va_list args;
		__builtin_va_info(args);
		*buffer = 0;
		wideFormatToBuffer(buffer, format, args);
	}
}
}
