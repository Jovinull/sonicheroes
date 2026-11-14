#ifndef GAME_RW_FRAME_H
#define GAME_RW_FRAME_H

#include "game/object.h"

// RenderWare frame-hierarchy helpers shared by the frame units around 0x8019E000.
// Function names in comments are HYPOTHESIS (RenderWare API shape); symbols stay fn_ addresses.

struct RwFreeList;

// Engine globals block (HYPOTHESIS: RwEngineInstance). Only the fields used by the frame units are
// known; modules keep their own globals at a registered offset inside it.
struct RwEngineGlobals {
	u8 pad0[0xBC];
	RwLinkList dirtyFrameList; // 0xBC
	u8 padC4[0x148 - 0xC4];
	// HYPOTHESIS: memory-function table entry that releases an entry to a free list.
	void (*freeListFree)(RwFreeList* freeList, void* entry); // 0x148
};

// Frame module bookkeeping (HYPOTHESIS: frameModule): offset of the frame globals inside the
// engine block and the number of open engine instances.
struct RwFrameModuleInfo {
	s32 globalsOffset;
	s32 numInstances;
};

extern "C" {
extern RwEngineGlobals* lbl_8042C9A4;
extern RwFrameModuleInfo lbl_8042C9A8;
// HYPOTHESIS: _rwSetHierarchyRoot.
void fn_8019DFDC(RwFrame* frame, RwFrame* root);
}

// Frame free list of the current engine instance (first field of the frame module globals).
#define RW_FRAME_FREE_LIST (*(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C9A8.globalsOffset))

// Frame private flags: hierarchy sync (root, bits 0-1) and subtree sync (bits 2-3).
#define RW_FRAME_HIERARCHY_SYNC 0x3
#define RW_FRAME_SUBTREE_SYNC   0xC

// Unlinks a node from its doubly linked list (HYPOTHESIS: rwLinkListRemoveLLLink).
static inline void RwLLLinkRemove(RwLLLink* link)
{
	link->prev->next = link->next;
	link->next->prev = link->prev;
}

// Puts the frame's root on the engine dirty-frame list the first time the hierarchy is flagged,
// then flags the root hierarchy and the frame subtree for resynchronization
// (HYPOTHESIS: RwFrameUpdateObjects, inlined).
static inline void RwFrameMarkDirty(RwFrame* frame)
{
	u8 oldState = frame->root->object.privateFlags;
	if (!(oldState & RW_FRAME_HIERARCHY_SYNC)) {
		frame->root->inDirtyListLink.next            = lbl_8042C9A4->dirtyFrameList.link.next;
		frame->root->inDirtyListLink.prev            = &lbl_8042C9A4->dirtyFrameList.link;
		lbl_8042C9A4->dirtyFrameList.link.next->prev = &frame->root->inDirtyListLink;
		lbl_8042C9A4->dirtyFrameList.link.next       = &frame->root->inDirtyListLink;
	}
	frame->root->object.privateFlags = oldState | RW_FRAME_HIERARCHY_SYNC;
	frame->object.privateFlags |= RW_FRAME_SUBTREE_SYNC;
}

#endif
