#include "types.h"

extern "C" {
s32 CheckRangeOut__10TObjSetObjFv(void* setobj);
s32 CheckMustKill__10TObjSetObjFv(void* setobj);
void markSampleForDeletion(void* o);
void fn_16_48398(void* o);
void fn_16_1180(void* a, void* b, void* c);
}

extern "C" void fn_16_4845C(register char* obj)
{
	if (CheckRangeOut__10TObjSetObjFv(obj + 0x28) || CheckMustKill__10TObjSetObjFv(obj + 0x28)) {
		markSampleForDeletion(obj);
		return;
	}
	fn_16_48398(obj);
	fn_16_1180(obj + 0x30, *(void**)(obj + 0x28), *(char**)(obj + 0x28) + 0xC);
}
