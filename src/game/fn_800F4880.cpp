#include "types.h"

extern "C" u32 fn_800F48A4(void);

extern "C" void fn_800F4880(void)
{
	if (fn_800F48A4() == 0) {
		return;
	}
}
