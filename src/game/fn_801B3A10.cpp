// Destroys a 0x34-byte object of the module tracked by lbl_8042CA80 (the counterpart of
// fn_801B3984): runs fn_801B3568 on each of its 0x28-byte items, forgets the item array, frees the
// buffer at +0x20 with the engine memory function and returns the object to the module free list.
// Field and type names are UNKNOWN; a null object is ignored.
#include "game/rw_engine.h"

struct Item801B3A10 {
	u8 pad0[0x28];
};

struct Object801B3A10 {
	s32 f0;
	u32 numItems;        // 0x4
	Item801B3A10* items; // 0x8
	u8 padC[0x20 - 0xC];
	void* buffer; // 0x20
	s32 f24;
	u8 pad28[0x34 - 0x28];
};

extern "C" {
extern RwModuleInfo lbl_8042CA80;
void fn_801B3568(Item801B3A10* item, Object801B3A10* object);

void fn_801B3A10(Object801B3A10* object)
{
	if (object != 0) {
		u32 count;
		u32 i;
		Item801B3A10* item;
		item  = object->items;
		i     = 0;
		count = object->numItems;
		for (; i < count; i++) {
			fn_801B3568(item, object);
			item++;
		}
		object->items = 0;
		if (object->buffer != 0) {
			lbl_8042C9A4->rwfree(object->buffer);
			object->buffer = 0;
			object->f24    = 0;
		}
		lbl_8042C9A4->freeListFree(
		    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042CA80.globalsOffset), object);
	}
}
}
