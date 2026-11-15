// Finds or loads a named entry of the record lbl_803EC968: returns the entry of the list at +0x1D0
// whose name matches; otherwise loads the value through the loader callback at +0x8B0 with the
// image search path saved around the call (fn_8019FE1C/fn_8019FD34, HYPOTHESIS: RwImageGetPath
// and RwImageSetPath) and, when that succeeds, adds an entry for it as fn_8016E868 does. Returns
// the entry, or null when the loader fails. Names are UNKNOWN.
#include "game/rw_engine.h"

struct Entry8016E924 {
	char* name;          // 0x0
	void* value;         // 0x4
	Entry8016E924* next; // 0x8
};

struct Rec8016E924 {
	u8 pad0[0x1CC];
	RwFreeList* entryFreeList; // 0x1CC
	Entry8016E924* entries;    // 0x1D0
	u8 pad1D4[0x8B0 - 0x1D4];
	void* (*load)(const char* name); // 0x8B0
};

extern "C" {
extern Rec8016E924 lbl_803EC968;
const char* fn_8019FE1C(void);
const char* fn_8019FD34(const char* path);
}

static inline Entry8016E924* FindEntry8016E924(const char* name)
{
	Entry8016E924* entry;
	for (entry = lbl_803EC968.entries; entry != 0; entry = entry->next) {
		if (lbl_8042C9A4->rwstrcmp(name, entry->name) == 0) {
			return entry;
		}
	}
	return 0;
}

// Links a new entry for value under a heap copy of name at the head of the list (as fn_8016E868).
static inline Entry8016E924* AddEntry8016E924(void* value, const char* name)
{
	Entry8016E924* entry = (Entry8016E924*)lbl_8042C9A4->freeListAlloc(lbl_803EC968.entryFreeList);
	entry->value         = value;
	entry->name          = (char*)lbl_8042C9A4->rwmalloc(lbl_8042C9A4->rwstrlen(name) + 1);
	lbl_8042C9A4->rwstrcpy(entry->name, name);
	entry->next          = lbl_803EC968.entries;
	lbl_803EC968.entries = entry;
	return entry;
}

extern "C" {
Entry8016E924* fn_8016E924(const char* name)
{
	Entry8016E924* entry = FindEntry8016E924(name);
	if (entry == 0) {
		char path[128];
		void* value;

		lbl_8042C9A4->rwstrcpy(path, fn_8019FE1C());
		value = lbl_803EC968.load(name);
		if (value != 0) {
			entry = AddEntry8016E924(value, name);
		} else {
			entry = 0;
		}
		fn_8019FD34(path);
	}
	return entry;
}
}
