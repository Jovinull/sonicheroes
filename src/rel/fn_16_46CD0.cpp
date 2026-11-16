#include "types.h"

extern "C" {
extern void* lbl_8042C180;
s32 fn_16_F20(void*, s32);
void fn_8014FF2C(void*);
}

extern "C" void fn_16_46CD0(register u8* obj)
{
	if (fn_16_F20(lbl_8042C180, 0x20) == 0) {
		if (*(void**)(obj + 0xE4) != 0) {
			fn_8014FF2C(*(void**)(obj + 0xE4));
		}
	}
}
