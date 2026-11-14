// Finds the next entry with the given key in a record list, resuming from the shared search
// cache lbl_802AD060 (HYPOTHESIS: one of the cached record iterators around 0x80020000; this one
// uses tag 0x2A10). Changing the list, tag or key restarts the search; the start index is
// clamped to 8. The retail loop compares the key of the list's first entry on every step and
// returns that entry (it never advances the entry pointer). Returns null when no step matches.
// Field names are inferred from these iterators only.
#include "types.h"

// Search cache shared by the iterators.
struct SearchCache8001F9F8 {
	void* list; // 0x0
	s32 tag;    // 0x4
	s32 index;  // 0x8
	s32 key;    // 0xC
};

struct Entry8001F9F8 {
	u8 key; // 0x0
};

struct List8001F9F8 {
	u8 pad0[0xA];
	u16 count; // 0xA
	u8 padC[0x4];
	Entry8001F9F8* entries; // 0x10
};

extern "C" {
extern SearchCache8001F9F8 lbl_802AD060;

Entry8001F9F8* fn_8001F9F8(List8001F9F8* list, u8 key)
{
	s32 i;
	Entry8001F9F8* entry;

	if (lbl_802AD060.list != list) {
		lbl_802AD060.list  = list;
		lbl_802AD060.tag   = -1;
		lbl_802AD060.key   = -1;
		lbl_802AD060.index = -1;
	}
	if (lbl_802AD060.tag != 0x2A10) {
		lbl_802AD060.tag   = 0x2A10;
		lbl_802AD060.key   = -1;
		lbl_802AD060.index = -1;
	}
	if (key != -1 && lbl_802AD060.key != key) {
		lbl_802AD060.key   = key;
		lbl_802AD060.index = -1;
	}
	if (++lbl_802AD060.index > 8) {
		lbl_802AD060.index = 8;
	}
	i     = lbl_802AD060.index;
	entry = list->entries;
	for (; i < list->count; i++) {
		if (key == entry->key) {
			lbl_802AD060.index = i;
			return entry;
		}
	}
	return 0;
}
}
