#include "types.h"

// Keeps the first non-zero value it is given in lbl_8042C1C8; later calls do
// nothing while one is set. The first argument is unused.

extern u32 lbl_8042C1C8;

extern "C" void fn_800421B4(void* self, u32 value)
{
	if (lbl_8042C1C8 == 0) {
		lbl_8042C1C8 = value;
	}
}
