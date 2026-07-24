#include "types.h"

struct AutosaveWindow;

extern "C" AutosaveWindow* fn_2_1424(u32 size);
extern "C" AutosaveWindow* fn_2_3AE8(AutosaveWindow* window, void* parent, void* config);

extern "C" AutosaveWindow* fn_2_3DF0(void* parent, void* config)
{
	AutosaveWindow* window;

	window = fn_2_1424(0x838);
	if (window != NULL) {
		window = fn_2_3AE8(window, parent, config);
	}
	return window;
}
