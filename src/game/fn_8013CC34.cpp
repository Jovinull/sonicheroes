// Returns the first pointer in the object at the registered plugin offset, or
// null.
#include "types.h"

extern "C" {
extern s32 lbl_8042C818;

void* fn_8013CC34(void* object)
{
	void* entry = *(void**)((u8*)object + lbl_8042C818);
	if (entry != NULL) {
		return *(void**)entry;
	}
	return NULL;
}
}
