// Adds a named entry to the record lbl_803EC968 (the counterpart of fn_8016DE10): takes one from the
// entry free list (+0x1CC), stores value, a heap copy of name (engine string and memory functions)
// and links it at the head of the list (+0x1D0). Names are UNKNOWN. Returns the stored value.
#include "game/rw_engine.h"

struct Entry8016E868 {
	char* name;          // 0x0
	void* value;         // 0x4
	Entry8016E868* next; // 0x8
};

struct Rec8016E868 {
	u8 pad0[0x1CC];
	RwFreeList* entryFreeList; // 0x1CC
	Entry8016E868* entries;    // 0x1D0
};

extern "C" {
extern Rec8016E868 lbl_803EC968;

void* fn_8016E868(void* value, const char* name)
{
	Entry8016E868* entry = (Entry8016E868*)lbl_8042C9A4->freeListAlloc(lbl_803EC968.entryFreeList);
	entry->value         = value;
	entry->name          = (char*)lbl_8042C9A4->rwmalloc(lbl_8042C9A4->rwstrlen(name) + 1);
	lbl_8042C9A4->rwstrcpy(entry->name, name);
	entry->next          = lbl_803EC968.entries;
	lbl_803EC968.entries = entry;
	return entry->value;
}
}
