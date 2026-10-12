#include "types.h"

struct Fn800A26ECData {
	u8 pad[0x18];
	u32 field18;
};

extern s32 lbl_8042C320;

extern "C" s32 fn_800A26EC(Fn800A26ECData* arg0)
{
	return (u32)__cntlzw(arg0->field18 & lbl_8042C320) >> 5;
}
