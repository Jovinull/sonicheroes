#ifndef GAME_RW_RESOURCES_H
#define GAME_RW_RESOURCES_H

#include "game/rw_engine.h"

// RenderWare resources module (HYPOTHESIS: baresour.c). Layouts are inferred from the open
// (fn_801971B0), close (fn_80197300), entry free (fn_80197384) and empty-arena (fn_80197770)
// routines; names follow RenderWare.

// Resource entry (HYPOTHESIS: RwResEntry).
struct RwResEntry {
	RwLLLink link;                               // 0x0: null when the entry is not in a list
	s32 size;                                    // 0x8
	void* owner;                                 // 0xC
	RwResEntry** ownerRef;                       // 0x10
	void (*destroyNotify)(RwResEntry* resEntry); // 0x14
};

// Resources module globals (HYPOTHESIS: rwResourcesGlobals).
struct RwResourcesGlobals {
	u32 maxSize;         // 0x0
	u32 currentSize;     // 0x4
	u32 reusageSize;     // 0x8
	void* memHeap;       // 0xC
	RwLinkList entriesA; // 0x10
	RwLinkList entriesB; // 0x18
	RwLinkList* listB;   // 0x20: points at entriesB
	RwLinkList* listA;   // 0x24: points at entriesA
};

extern "C" {
// Resources module bookkeeping (HYPOTHESIS: resourcesModule).
extern RwModuleInfo lbl_8042C970;
// HYPOTHESIS: _rwResHeapFree.
void fn_8019998C(RwResEntry* resEntry);
}

#define RW_RESOURCES_GLOBALS ((RwResourcesGlobals*)((u8*)lbl_8042C9A4 + lbl_8042C970.globalsOffset))

#endif
