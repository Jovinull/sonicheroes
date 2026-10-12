#include "types.h"

extern "C" u8 lbl_802B908C[];
extern "C" s32 lbl_8042C1FC;
extern "C" void* lbl_8042C208;

extern "C" void fn_8004EC9C(void* arg0, s32 arg1)
{
	lbl_8042C1FC = arg1;
	lbl_8042C208 = lbl_802B908C + arg1 * 0x2324 + 0x40;
}
