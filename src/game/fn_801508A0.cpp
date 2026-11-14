// Creates an empty clump (HYPOTHESIS: RpClumpCreate): takes one from the clump free list (+0x4 of the
// clump module globals), initializes its object header (type 2) with no parent, empties its atomic,
// light and camera lists, clears the two words at +0x20/+0x24 and installs the default render
// callback fn_8014F524, then runs the clump plugin constructors. Returns the clump, or null when
// allocation fails.
#include "game/rw_engine.h"

#define RP_CLUMP_TYPE 2

// Clump fields used here (HYPOTHESIS: RpClump layout).
struct RpClump801508A0 {
	RwObject object;                                       // 0x0
	RwLinkList atomicList;                                 // 0x8
	RwLinkList lightList;                                  // 0x10
	RwLinkList cameraList;                                 // 0x18
	void* f20;                                             // 0x20
	void* f24;                                             // 0x24
	void* (*callback)(RpClump801508A0* clump, void* data); // 0x28
};

extern "C" {
// Clump module bookkeeping (HYPOTHESIS: clumpModule) and plugin registry (clumpTKList).
extern RwModuleInfo lbl_8042C8D8;
extern RwPluginRegistry lbl_8028D248;
// HYPOTHESIS: the default clump render callback.
void* fn_8014F524(RpClump801508A0* clump, void* data);

RpClump801508A0* fn_801508A0(void)
{
	RpClump801508A0* clump = (RpClump801508A0*)lbl_8042C9A4->freeListAlloc(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C8D8.globalsOffset + 4));
	if (clump == 0) {
		return clump;
	}
	clump->object.type          = RP_CLUMP_TYPE;
	clump->object.subType       = 0;
	clump->object.flags         = 0;
	clump->object.privateFlags  = 0;
	clump->object.parent        = 0;
	clump->object.parent        = 0;
	clump->atomicList.link.next = &clump->atomicList.link;
	clump->atomicList.link.prev = &clump->atomicList.link;
	clump->lightList.link.next  = &clump->lightList.link;
	clump->lightList.link.prev  = &clump->lightList.link;
	clump->cameraList.link.next = &clump->cameraList.link;
	clump->cameraList.link.prev = &clump->cameraList.link;
	clump->f24                  = 0;
	clump->f20                  = 0;
	clump->callback             = fn_8014F524;
	fn_80198D5C(&lbl_8028D248, clump);
	return clump;
}
}
