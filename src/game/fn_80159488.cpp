// Records (key, value) in a new entry taken from the free list of the module tracked by
// lbl_8042C910 and links it at the head of the module's list at +0x4 (the counterpart of
// fn_80159534). Nothing happens when the free list is exhausted. Names are UNKNOWN.
#include "game/rw_engine.h"

struct Entry80159488 {
	void* key;     // 0x0
	void* value;   // 0x4
	RwLLLink link; // 0x8
};

extern "C" {
extern RwModuleInfo lbl_8042C910;
}

#define LIST80159488 (*(RwLinkList*)((u8*)lbl_8042C9A4 + lbl_8042C910.globalsOffset + 4))

extern "C" {
void fn_80159488(void* key, void* value)
{
	Entry80159488* entry = (Entry80159488*)lbl_8042C9A4->freeListAlloc(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C910.globalsOffset));
	if (entry != 0) {
		entry->key                   = key;
		entry->value                 = value;
		entry->link.next             = LIST80159488.link.next;
		entry->link.prev             = &LIST80159488.link;
		LIST80159488.link.next->prev = &entry->link;
		LIST80159488.link.next       = &entry->link;
	}
}
}
