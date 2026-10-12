#include "types.h"

extern s8 lbl_8042C470;
extern s8 lbl_8042C471;

extern "C" void fn_800CAF14(s8 arg0)
{
	if (lbl_8042C470 == 1) {
		lbl_8042C471 = arg0;
	}
}
