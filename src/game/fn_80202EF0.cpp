// Releases the two growable arrays of an object (HYPOTHESIS): destroys the array at +0x18, then
// resets every 0x10-byte entry of the array at +0x14 (word 0 cleared, word 4 set to -1, the word at
// 8 cleared through both of its views) before destroying it, and clears both pointers. Returns
// the object. Names are inferred from this function only.
#include "game/rw_engine.h"

struct Entry80202EF0 {
	s32 f0; // 0x0
	s32 id; // 0x4: -1 when unused
	union {
		s32 value;
		void* data;
	} u;          // 0x8
	u8 padC[0x4]; // 0xC
};

struct Object80202EF0 {
	u8 pad0[0x14];
	RwSList* entries; // 0x14
	RwSList* list18;  // 0x18
};

extern "C" {
// HYPOTHESIS: _rwSListDestroy, _rwSListGetNumEntries and _rwSListGetArray.
s32 fn_80194628(RwSList* sList);
s32 fn_8019469C(RwSList* sList);
void* fn_8019460C(RwSList* sList);

Object80202EF0* fn_80202EF0(Object80202EF0* object)
{
	RwSList* entries;

	if (object->list18 != 0) {
		fn_80194628(object->list18);
	}
	object->list18 = 0;

	entries = object->entries;
	if (entries != 0) {
		s32 count = fn_8019469C(entries);
		if (count > 0) {
			Entry80202EF0* entry = (Entry80202EF0*)fn_8019460C(entries);
			s32 i;
			for (i = 0; i < count; i++) {
				entry->f0      = 0;
				entry->id      = -1;
				entry->u.value = 0;
				entry->u.data  = 0;
				entry++;
			}
		}
		fn_80194628(entries);
	}
	object->entries = 0;
	return object;
}
}
