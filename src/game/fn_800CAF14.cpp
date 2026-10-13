#include "types.h"

// Sets lbl_8042C471 to the given value while lbl_8042C470 is 1.

extern s8 lbl_8042C470;
extern s8 lbl_8042C471;

extern "C" void fn_800CAF14(s8 value)
{
	if (lbl_8042C470 == 1) {
		lbl_8042C471 = value;
	}
}
