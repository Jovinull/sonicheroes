// Reads the word at base plus lbl_8042C828 and 4.
#include "types.h"

extern "C" {
extern s32 lbl_8042C828;

s32 fn_8013F484(void* base)
{
	return *(s32*)((u8*)base + lbl_8042C828 + 4);
}
}
