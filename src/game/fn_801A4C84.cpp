#include "types.h"

// Stores the argument at lbl_8042C9A4 + lbl_8042C9C4 + 0x10.
extern "C" {
extern s32 lbl_8042C9A4;
extern s32 lbl_8042C9C4;

void fn_801A4C84(s32 value)
{
	s32 offset                    = lbl_8042C9C4;
	s32 base                      = lbl_8042C9A4;
	*(s32*)(base + offset + 0x10) = value;
}
}
