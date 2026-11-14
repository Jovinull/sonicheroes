// Issues a libpng warning (HYPOTHESIS: png_warning): skips an optional "#nnnn " error-number prefix
// (up to 14 characters) and passes the rest to the user warning handler at +0x4, or to
// fn_8017CA08 (png_default_warning) when none is installed.
#include "types.h"

struct Png8017C5FC {
	void* errorFn;                                            // 0x0
	void (*warningFn)(Png8017C5FC* png, const char* message); // 0x4
};

extern "C" {
void fn_8017CA08(Png8017C5FC* png, const char* message);

void fn_8017C5FC(Png8017C5FC* png, const char* message)
{
	int offset = 0;
	if (*message == '#') {
		for (offset = 1; offset < 15; offset++) {
			if (*(message + offset) == ' ') {
				break;
			}
		}
	}
	if (png->warningFn != 0) {
		png->warningFn(png, message + offset);
	} else {
		fn_8017CA08(png, message + offset);
	}
}
}
