#include "types.h"

// Stores 0x01000000 at the address lbl_8042CA60 + 0x20 from the object.
extern "C" {
extern s32 lbl_8042CA60;

void fn_801B1BF8(void* object)
{
	*(u32*)((u8*)object + lbl_8042CA60 + 0x20) = 0x01000000;
}
}
