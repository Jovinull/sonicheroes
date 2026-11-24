#include "types.h"
extern "C" s32 CheckRangeOut__10TObjSetObjFv(void* setobj);
extern "C" s32 CheckMustKill__10TObjSetObjFv(void* setobj);
extern "C" s32 OnEdit__10TObjSetObjFv(void* setobj);
extern "C" void markSampleForDeletion(void* o);

extern "C" void fn_16_29B48(register char* object)
{
	if (CheckRangeOut__10TObjSetObjFv(object + 0x38)
	    || CheckMustKill__10TObjSetObjFv(object + 0x38)) {
		markSampleForDeletion(object);
		return;
	}
	if (OnEdit__10TObjSetObjFv(object + 0x38)) {
		return;
	}
}
