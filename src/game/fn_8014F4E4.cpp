// CORROBORATED: Clears three words relative to the object and returns it
// unchanged.
#include "types.h"

extern "C" {
extern s32 lbl_8042C8C8;

void* fn_8014F4E4(void* object, s32, s32)
{
	s32* record = (s32*)((u8*)object + lbl_8042C8C8);
	record[2]   = 0;
	record[1]   = 0;
	record[0]   = 0;
	return object;
}
}
