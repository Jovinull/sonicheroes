// Default libpng warning handler without console output (HYPOTHESIS: png_default_warning built with
// PNG_NO_CONSOLE_IO): does nothing; the null check only keeps the argument used.
#include "types.h"

extern "C" {
void fn_8017CA08(void* png, const char* message)
{
	if (png == 0) {
		return;
	}
}
}
