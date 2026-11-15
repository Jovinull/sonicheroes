// Empties the resource arena (HYPOTHESIS: RwResourcesEmptyArena): joins the two resource lists,
// frees every entry as fn_80197384 does (destroy notification, owner reference cleared, heap or
// engine free), then leaves both lists empty and clears the reusage size. Returns 1.
#include "game/rw_resources.h"

extern "C" {
s32 fn_80197770(void)
{
	RwLLLink* cur;
	RwLLLink* end;

	RW_RESOURCES_GLOBALS->entriesA.link.prev->next = RW_RESOURCES_GLOBALS->entriesB.link.next;
	cur                                            = RW_RESOURCES_GLOBALS->entriesA.link.next;
	end                                            = &RW_RESOURCES_GLOBALS->entriesB.link;
	while (cur != end) {
		RwResEntry* entry = (RwResEntry*)cur;
		cur               = cur->next;
		if (entry->destroyNotify != 0) {
			entry->destroyNotify(entry);
		}
		if (entry->ownerRef != 0) {
			*entry->ownerRef = 0;
		}
		if (entry->link.next != 0) {
			RwLLLinkRemove(&entry->link);
			RW_RESOURCES_GLOBALS->currentSize -= entry->size;
			fn_8019998C(entry);
		} else {
			lbl_8042C9A4->rwfree(entry);
		}
	}
	RW_RESOURCES_GLOBALS->entriesA.link.next = &RW_RESOURCES_GLOBALS->entriesA.link;
	RW_RESOURCES_GLOBALS->entriesA.link.prev = &RW_RESOURCES_GLOBALS->entriesA.link;
	RW_RESOURCES_GLOBALS->entriesB.link.next = &RW_RESOURCES_GLOBALS->entriesB.link;
	RW_RESOURCES_GLOBALS->entriesB.link.prev = &RW_RESOURCES_GLOBALS->entriesB.link;
	RW_RESOURCES_GLOBALS->reusageSize        = 0;
	return 1;
}
}
