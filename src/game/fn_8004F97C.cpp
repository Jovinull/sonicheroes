#include "types.h"

// A static initializer: lbl_8042C230 gets the offset of the 39th word of the
// buffer at lbl_802C21E0 (0x9C).

extern "C" u8 lbl_802C21E0[0xE7F5];
extern "C" s32 lbl_8042C230;

extern "C" void fn_8004F97C(void)
{
	lbl_8042C230 = (u8*)((u32*)lbl_802C21E0 + 0x27) - (u8*)lbl_802C21E0;
}

__declspec(section ".ctors") void (*const fn8004F97CCtorEntry)(void) = fn_8004F97C;
