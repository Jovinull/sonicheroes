#include "types.h"

extern u32 lbl_8042C1C8;

extern "C" void fn_800421B4(void* arg0, u32 arg1)
{
	if (lbl_8042C1C8 == 0) {
		lbl_8042C1C8 = arg1;
	}
}
