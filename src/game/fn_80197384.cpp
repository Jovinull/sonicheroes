// Frees a resource entry (HYPOTHESIS: RwResourcesFreeResEntry): runs its destroy notification
// (+0x14), clears the owner's reference (+0x10) and either unlinks it from the resource list,
// subtracts its size from the used total (+0x4 of the resources module globals tracked by
// lbl_8042C970) and returns it to the resource heap through fn_80199984 (_rwResHeapFree), or, when
// it is not linked, frees it with the engine memory function. Always returns 1.
#include "game/rw_engine.h"

// Resource entry (HYPOTHESIS: RwResEntry layout).
struct RwResEntry80197384 {
	RwLLLink link;                                       // 0x0
	s32 size;                                            // 0x8
	void* owner;                                         // 0xC
	RwResEntry80197384** ownerRef;                       // 0x10
	void (*destroyNotify)(RwResEntry80197384* resEntry); // 0x14
};

extern "C" {
extern RwModuleInfo lbl_8042C970;
void fn_8019998C(RwResEntry80197384* resEntry);

s32 fn_80197384(RwResEntry80197384* entry)
{
	if (entry->destroyNotify != 0) {
		entry->destroyNotify(entry);
	}
	if (entry->ownerRef != 0) {
		*entry->ownerRef = 0;
	}
	if (entry->link.next != 0) {
		RwLLLinkRemove(&entry->link);
		*(s32*)((u8*)lbl_8042C9A4 + lbl_8042C970.globalsOffset + 4) -= entry->size;
		fn_8019998C(entry);
	} else {
		lbl_8042C9A4->rwfree(entry);
	}
	return 1;
}
}
