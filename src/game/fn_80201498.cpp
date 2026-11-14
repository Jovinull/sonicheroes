// Destroys an object of the unit around 0x802013C4 (HYPOTHESIS): releases its storage at 0x8,
// either as a growable array (fn_80194628, HYPOTHESIS: _rwSListDestroy) when the flag at 0x4 is
// set or as a plain engine heap block, then returns the object to free list 7 of the table
// lbl_8040EB50. Returns whether an object was given. Field names are inferred from this
// function only.
#include "game/rw_engine.h"

struct Object80201498 {
	u8 pad0[0x4];
	s32 isList;    // 0x4
	void* storage; // 0x8
};

// Free lists of the module (only the one used here is named).
struct FreeLists80201498 {
	u8 pad0[0x1C];
	RwFreeList* objects; // 0x1C
	u8 pad20[0x30 - 0x20];
};

extern "C" {
extern FreeLists80201498 lbl_8040EB50;

s32 fn_80194628(RwSList* list);

s32 fn_80201498(Object80201498* object)
{
	s32 given = (object != 0) ? 1 : 0;

	if (given) {
		if (object->isList) {
			fn_80194628((RwSList*)object->storage);
		} else {
			lbl_8042C9A4->rwfree(object->storage);
		}
		lbl_8042C9A4->freeListFree(lbl_8040EB50.objects, object);
	}
	return given;
}
}
