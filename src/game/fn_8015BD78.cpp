#include "types.h"

// Loads the word at the supplied base plus lbl_8042C920.
extern "C" {
extern s32 lbl_8042C920;

void* fn_8015BD78(void* base)
{
	return *(void**)((u8*)base + lbl_8042C920);
}
}
