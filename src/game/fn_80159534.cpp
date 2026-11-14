// Finds the entry whose key (+0x0) is key in the list at +0x4 of the module globals tracked by
// lbl_8042C910 (entries linked at +0x8), unlinks it and returns it to the module free list (first
// field of the globals). Names are UNKNOWN.
#include "game/rw_engine.h"

struct Entry80159534 {
	void* key; // 0x0
	s32 f4;
	RwLLLink link; // 0x8
};

extern "C" {
extern RwModuleInfo lbl_8042C910;

void fn_80159534(void* key)
{
	RwLinkList* list = (RwLinkList*)((u8*)lbl_8042C9A4 + lbl_8042C910.globalsOffset + 4);
	RwLLLink* cur    = list->link.next;
	while (cur != &list->link) {
		Entry80159534* entry = (Entry80159534*)((u8*)cur - 0x8);
		if (entry->key == key) {
			RwLLLinkRemove(&entry->link);
			lbl_8042C9A4->freeListFree(
			    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C910.globalsOffset), entry);
			return;
		}
		cur = cur->next;
	}
}
}
