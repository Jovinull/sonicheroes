// Calls a callback for every 0x3C-byte entry of the list at 0x8 of an fn_802038AC object
// (HYPOTHESIS: a "for all" iterator): the object's index at 0x44 holds the entry index during
// the call, and the callback receives the entry's blocks at 0x4 and 0x20 and the user data. Stops
// and returns null when the callback does not return the object; otherwise resets the index to
// -1 and returns the object.
#include "game/object_802038AC.h"

// Entry of the list at 0x8 (only the callback arguments are known).
struct Entry80204144 {
	u8 pad0[0x4];
	u8 first[0x1C];  // 0x4
	u8 second[0x1C]; // 0x20
};

typedef Object802038AC* (*Callback80204144)(
    Object802038AC* object, void* first, void* second, void* data);

extern "C" {
s32 fn_8019469C(RwSList* list);
void* fn_8019460C(RwSList* list);

Object802038AC* fn_80204144(Object802038AC* object, Callback80204144 callback, void* data)
{
	s32 count = fn_8019469C((RwSList*)object->part8);

	if (count > 0) {
		Entry80204144* entry = (Entry80204144*)fn_8019460C((RwSList*)object->part8);
		s32 i;
		for (i = 0; i < count; i++) {
			object->index = i;
			if (callback(object, entry->first, entry->second, data) != object) {
				return 0;
			}
			entry++;
		}
	}
	object->index = -1;
	return object;
}
}
