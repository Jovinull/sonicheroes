// Takes a 0x34-byte object from the free list of the module tracked by lbl_8042CA80 and clears it.
// On allocation failure records core error 0x80000013 (out of memory, 0x34 bytes) and returns
// null. The object's type is UNKNOWN.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

struct Object801B3984 {
	s32 f0;
	u8 pad4[0x34 - 0x4];
};

extern "C" {
extern RwModuleInfo lbl_8042CA80;

Object801B3984* fn_801B3984(void)
{
	Object801B3984* object = (Object801B3984*)lbl_8042C9A4->freeListAlloc(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042CA80.globalsOffset));
	if (object != 0) {
		memset(object, 0, sizeof(Object801B3984));
		object->f0 = 0;
		return object;
	}
	{
		RwError error;
		error.pluginID  = RW_ID_CORE_PLUGIN;
		error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, sizeof(Object801B3984));
		fn_80193FE8(&error);
	}
	return 0;
}
}
