// Resets a cursor over the entry list it holds (HYPOTHESIS: an animation key-frame cursor):
// clears its time to the .sdata2 constant lbl_8042FF6C and, when the list has entries, points it
// at the first and last entry and runs fn_80201B10 on the first entry's data with the argument;
// otherwise clears the position and both entry pointers. Returns the cursor. Field names are
// inferred from this function only.
#include "game/rw_engine.h"

struct Entry80200AC4 {
	u8 pad0[0x4];
	void* data; // 0x4
};

struct Cursor80200AC4 {
	RwSList* entries; // 0x0
	u8 pad4[0x4];
	f32 time; // 0x8
	u8 padC[0x4];
	s32 position;         // 0x10
	Entry80200AC4* first; // 0x14
	Entry80200AC4* last;  // 0x18
};

extern "C" {
extern f32 lbl_8042FF6C;

// HYPOTHESIS: RwSListGetNumEntries and RwSListGetEntry.
s32 fn_8019469C(RwSList* list);
void* fn_8019472C(RwSList* list, s32 index);
void fn_80201B10(void* data, void* arg);

Cursor80200AC4* fn_80200AC4(Cursor80200AC4* cursor, void* arg)
{
	s32 count = fn_8019469C(cursor->entries);

	cursor->time = lbl_8042FF6C;
	if (count >= 1) {
		cursor->position = 0;
		cursor->first    = (Entry80200AC4*)fn_8019472C(cursor->entries, 0);
		cursor->last     = (Entry80200AC4*)fn_8019472C(cursor->entries, count - 1);
		fn_80201B10(cursor->first->data, arg);
	} else {
		cursor->position = 0;
		cursor->first    = 0;
		cursor->last     = 0;
	}
	return cursor;
}
}
