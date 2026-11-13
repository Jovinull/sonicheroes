#include "types.h"

// HYPOTHESIS: Tests the word at the computed address plus 0x3C, clears 0x3C bytes at +0x38 when set, and returns the result.

extern "C" {
extern s32 lbl_8042C9A4;
extern s32 lbl_8042CA74;
void* memset(void*, s32, u32);
struct Object801B2A14 {
	u8 pad[0x3C];
	u32 state;
};
s32 fn_801B2A14()
{
	Object801B2A14* object = (Object801B2A14*)(lbl_8042C9A4 + lbl_8042CA74);
	if (object->state == 0) {
		return 0;
	}
	memset((u8*)object + 0x38, 0, 0x3C);
	return 1;
}
}
