#include "types.h"

// Copies the pointed-to word into lbl_8042C77C.

extern "C" s32 lbl_8042C77C;

extern "C" void fn_80130478(s32* value)
{
	lbl_8042C77C = *value;
}
