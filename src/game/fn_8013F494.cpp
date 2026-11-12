// Returns the pointer stored at the table base plus lbl_8042C828.
#include "types.h"

extern "C" {
extern int lbl_8042C828;

void* fn_8013F494(void* base)
{
	return *(void**)((u8*)base + lbl_8042C828);
}
}
