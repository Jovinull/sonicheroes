// Updates the entries of an fn_802038AC object (HYPOTHESIS: an animation pass): for each 0x3C-byte
// entry of the list at 0x8, with the object's index at 0x44 naming it, an entry whose parent
// (index at 0x34, -1 for none) qualifies and whose target at 0x20 passes fn_801733E8 is flagged
// active (0x4) and its key-frame cursor applied (fn_80200CB0); other entries are flagged
// inactive. Stops with null when applying a cursor fails; otherwise resets the index and returns
// the object. The retail parent test ORs the flag in, so any existing parent qualifies.
// NonMatching: the entry count and the active flag swap r30/r31 (5 words differ).
#include "game/keyframe_cursor.h"
#include "game/object_802038AC.h"

struct Entry802041EC {
	s32 flags;             // 0x0: 0x4 = active
	KeyFrameCursor cursor; // 0x4
	void* target;          // 0x20
	u8 pad24[0x34 - 0x24];
	s32 parent; // 0x34
	u8 pad38[0x3C - 0x38];
};

extern "C" {
s32 fn_8019469C(RwSList* list);
void* fn_8019460C(RwSList* list);
void* fn_8019472C(RwSList* list, s32 index);
s32 fn_801733E8(void* target);
KeyFrameCursor* fn_80200CB0(KeyFrameCursor* cursor, void* arg);
}

static inline Object802038AC* ApplyEntry(Object802038AC* object, Entry802041EC* entry)
{
	entry->flags |= 0x4;
	return fn_80200CB0(&entry->cursor, &entry->target) == 0 ? 0 : object;
}

static inline Object802038AC* UpdateEntries(Object802038AC* object)
{
	s32 count;
	Entry802041EC* entry;
	s32 i;
	s32 active;

	count = fn_8019469C((RwSList*)object->part8);
	if (count > 0) {
		entry = (Entry802041EC*)fn_8019460C((RwSList*)object->part8);
		for (i = 0; i < count; i++) {
			active = 0;
			if (entry->parent == -1
			    || (((Entry802041EC*)fn_8019472C((RwSList*)object->part8, entry->parent))->flags
			           | 0x4)
			        != 0) {
				active = 1;
			}
			object->index = i;
			if (active && fn_801733E8(entry->target)) {
				if (ApplyEntry(object, entry) != object) {
					return 0;
				}
			} else {
				entry->flags &= ~0x4;
			}
			entry++;
		}
	}
	object->index = -1;
	return object;
}

extern "C" {
Object802038AC* fn_802041EC(Object802038AC* object)
{
	if (object->part8) {
		if (!UpdateEntries(object)) {
			return 0;
		}
	}
	return object;
}
}
