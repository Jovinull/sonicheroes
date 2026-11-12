// Reads a word from lbl_8042C9A4 + lbl_8042BCE0 + 8.
#include "types.h"

extern "C" {
extern s32 lbl_8042BCE0;
extern void* lbl_8042C9A4;

s32 fn_801471DC(void)
{
	return *(s32*)((u8*)lbl_8042C9A4 + lbl_8042BCE0 + 8);
}
}
