// Opens the resources module (HYPOTHESIS: _rwResourcesOpen): records the globals offset, allocates
// the resource arena of the engine's configured size and initialises the resource heap in it
// (fn_80199934), sets up the two resource lists and clears the size counters. Returns the instance,
// or null when the arena cannot be allocated (error 0x80000013 of plugin 1) or the heap cannot be
// initialised (error 0xC of plugin 1).
// NonMatching: retail re-reads lbl_8042C970.globalsOffset right after storing it, while this source
// reuses the stored register, so the stream is one instruction shorter. Reading the offset through
// a volatile access makes the function exact, so that re-read is the only difference; its source
// form is UNKNOWN (the same re-read appears in fn_801A1B84). Not reproduced by compiling as C,
// compilers 1.3 to 2.0p1 or optimizer flag changes.
#include "game/rw_engine.h"

// Resources module globals (HYPOTHESIS: rwResourcesGlobals; +0x4 and +0xC are also used by
// fn_80197384 and fn_80197300).
struct RwResourcesGlobals801971B0 {
	u32 maxSize;         // 0x0
	u32 currentSize;     // 0x4
	u32 reusageSize;     // 0x8
	void* memHeap;       // 0xC
	RwLinkList entriesA; // 0x10
	RwLinkList entriesB; // 0x18
	RwLinkList* listB;   // 0x20: points at entriesB
	RwLinkList* listA;   // 0x24: points at entriesA
};

#define RW_ERROR_RES_HEAP_INIT_801971B0 0xC

extern "C" {
extern RwModuleInfo lbl_8042C970;
// HYPOTHESIS: _rwResHeapInit; returns nonzero on success.
s32 fn_80199934(void* heap, u32 size);
}

static inline RwResourcesGlobals801971B0* ResourcesInit801971B0(
    RwResourcesGlobals801971B0* res, u32 size)
{
	if (size != 0) {
		res->memHeap = lbl_8042C9A4->rwmalloc(size);
		if (res->memHeap == 0) {
			RwError error;
			error.pluginID  = 1;
			error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
			fn_80193FE8(&error);
			return 0;
		}
		if (!fn_80199934(res->memHeap, size)) {
			lbl_8042C9A4->rwfree(res->memHeap);
			RwError error;
			error.pluginID  = 1;
			error.errorCode = fn_8019408C(RW_ERROR_RES_HEAP_INIT_801971B0, 0);
			fn_80193FE8(&error);
			return 0;
		}
	} else {
		res->memHeap = 0;
	}
	res->entriesA.link.next = &res->entriesA.link;
	res->entriesA.link.prev = &res->entriesA.link;
	res->entriesB.link.next = &res->entriesB.link;
	res->entriesB.link.prev = &res->entriesB.link;
	res->listA              = &res->entriesA;
	res->listB              = &res->entriesB;
	res->maxSize            = size;
	res->currentSize        = 0;
	res->reusageSize        = 0;
	return res;
}

extern "C" {
void* fn_801971B0(void* instance, s32 offset, s32 size)
{
	lbl_8042C970.globalsOffset = offset;
	if (ResourcesInit801971B0(
	        (RwResourcesGlobals801971B0*)((u8*)lbl_8042C9A4 + lbl_8042C970.globalsOffset),
	        lbl_8042C9A4->resArenaInitSize)
	    == 0) {
		return 0;
	}
	lbl_8042C970.numInstances++;
	return instance;
}
}
