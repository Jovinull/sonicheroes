// Allocates a resource entry (HYPOTHESIS: RenderWare RwResourcesAllocateResEntry): takes a block
// of the requested size plus the entry header from the resource heap (fn_80199A44), links it at
// the head of the first entry list, records the owner, size, owner reference and destroy
// notification and adds the size to the used total. While the heap is full, frees the oldest entry
// of the second list, then of the first one (counting its size as reused), and gives up with
// error 0xC when both are empty, clearing the owner reference. Returns the entry or null.
// NonMatching: the first freed entry is loaded straight into its saved register instead of being
// copied there after the destroy-callback load, and the globals pointer takes r4 instead of r5 (11
// words, same instructions). Tried call-argument and victim-local forms, hoisted and permuted
// declarations.
#include "game/rw_resources.h"

extern "C" {
// HYPOTHESIS: _rwResHeapAlloc.
RwResEntry* fn_80199A44(void* heap, s32 size);

// Copy of fn_80197384 (RwResourcesFreeResEntry). Retail inlines it twice here, so the original
// shares one unit with it (and fn_80197434); this unit cannot call the separate object.
static inline s32 FreeResEntry801974E0(RwResEntry* entry)
{
	if (entry->destroyNotify != 0) {
		entry->destroyNotify(entry);
	}
	if (entry->ownerRef != 0) {
		*entry->ownerRef = 0;
	}
	if (entry->link.next != 0) {
		RW_LL_LINK_REMOVE(&entry->link);
		RW_RESOURCES_GLOBALS->currentSize -= entry->size;
		fn_8019998C(entry);
	} else {
		lbl_8042C9A4->rwfree(entry);
	}
	return 1;
}

RwResEntry* fn_801974E0(
    void* owner, RwResEntry** ownerRef, s32 size, void (*destroyNotify)(RwResEntry* resEntry))
{
	s32 exhausted = 0;

	while (!exhausted) {
		RwResEntry* entry = fn_80199A44(RW_RESOURCES_GLOBALS->memHeap, size + sizeof(RwResEntry));
		if (entry != 0) {
			entry->link.next                             = RW_RESOURCES_GLOBALS->listA->link.next;
			entry->link.prev                             = &RW_RESOURCES_GLOBALS->listA->link;
			RW_RESOURCES_GLOBALS->listA->link.next->prev = &entry->link;
			RW_RESOURCES_GLOBALS->listA->link.next       = &entry->link;
			entry->owner                                 = owner;
			entry->size                                  = size;
			entry->ownerRef                              = ownerRef;
			entry->destroyNotify                         = destroyNotify;
			RW_RESOURCES_GLOBALS->currentSize += size;
			if (ownerRef != 0) {
				*ownerRef = entry;
			}
			return entry;
		}

		{
			RwResourcesGlobals* globals = RW_RESOURCES_GLOBALS;
			RwResEntry* victim          = (RwResEntry*)globals->listB->link.prev;
			if (victim != (RwResEntry*)globals->listB) {
				FreeResEntry801974E0(victim);
			} else {
				victim = (RwResEntry*)globals->listA->link.prev;
				if (victim != (RwResEntry*)globals->listA) {
					globals->reusageSize += victim->size;
					FreeResEntry801974E0(victim);
				} else {
					exhausted = 1;
				}
			}
		}
	}

	if (ownerRef != 0) {
		*ownerRef = 0;
	}
	{
		RwError error;
		error.pluginID  = RW_ID_CORE_PLUGIN;
		error.errorCode = fn_8019408C(0xC, size);
		fn_80193FE8(&error);
	}
	return 0;
}
}
