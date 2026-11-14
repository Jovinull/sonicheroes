// Creates a 12-byte array header from the free list lbl_8042BD10 with storage for `count`
// 0x14-byte entries (HYPOTHESIS: the world sector data fn_801595B8 builds): an empty array gets no
// storage. An allocation failure records error 0x80000013 for plugin 2 (with the size, or 0xC for
// the header) and returns null, releasing the header again.
#include "game/rw_engine.h"

struct Array80155864 {
	u32 count;     // 0x0
	s32 word4;     // 0x4
	void* entries; // 0x8: count entries of 0x14 bytes
};

extern "C" {
extern RwFreeList* lbl_8042BD10;

Array80155864* fn_80155864(u32 count)
{
	Array80155864* array = (Array80155864*)lbl_8042C9A4->freeListAlloc(lbl_8042BD10);

	if (array) {
		array->word4 = 0;
		if (count) {
			u32 size       = count * 0x14;
			array->entries = lbl_8042C9A4->rwmalloc(size);
			if (!array->entries) {
				RwError error;
				lbl_8042C9A4->freeListFree(lbl_8042BD10, array);
				error.pluginID  = 2;
				error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
				fn_80193FE8(&error);
				return 0;
			}
			array->count = count;
		} else {
			array->entries = 0;
			array->count   = 0;
		}
		return array;
	}
	{
		RwError error;
		error.pluginID  = 2;
		error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, sizeof(Array80155864));
		fn_80193FE8(&error);
	}
	return 0;
}
}
