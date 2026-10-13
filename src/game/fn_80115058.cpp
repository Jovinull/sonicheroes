#include "types.h"

// Clears the four words at lbl_8042C678 to lbl_8042C684.

extern s32 lbl_8042C678;
extern s32 lbl_8042C67C;
extern s32 lbl_8042C680;
extern s32 lbl_8042C684;

extern "C" void fn_80115058(void)
{
	lbl_8042C678 = 0;
	lbl_8042C67C = 0;
	lbl_8042C680 = 0;
	lbl_8042C684 = 0;
}
