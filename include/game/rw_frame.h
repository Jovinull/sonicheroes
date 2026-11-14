#ifndef GAME_RW_FRAME_H
#define GAME_RW_FRAME_H

#include "game/rw_engine.h"

// RenderWare frame-hierarchy helpers shared by the frame units around 0x8019E000.
// Function names in comments are HYPOTHESIS (RenderWare API shape); symbols stay fn_ addresses.

extern "C" {
// Frame module bookkeeping (HYPOTHESIS: frameModule).
extern RwModuleInfo lbl_8042C9A8;
// Frame plugin registry (HYPOTHESIS: frameTKList).
extern RwPluginRegistry lbl_802905F8;
// HYPOTHESIS: _rwSetHierarchyRoot.
void fn_8019DFDC(RwFrame* frame, RwFrame* root);
// HYPOTHESIS: RwFrameUpdateObjects (out-of-line form of RwFrameMarkDirty).
RwFrame* fn_8019E880(RwFrame* frame);
// HYPOTHESIS: RwFrameRemoveChild.
RwFrame* fn_8019EA2C(RwFrame* child);
}

// .sdata2 constants 1.0f and 0.0f of the frame code. Declared non-const: the retail code
// reloads them after the matrix stores, treating them as ordinary memory rather than folded
// constants.
extern "C" {
extern f32 lbl_8042F6F8;
extern f32 lbl_8042F6FC;
}

// Frame free list of the current engine instance (first field of the frame module globals).
#define RW_FRAME_FREE_LIST (*(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C9A8.globalsOffset))

// Frame private flags: hierarchy sync (root, bits 0-1) and subtree sync (bits 2-3).
#define RW_FRAME_HIERARCHY_SYNC 0x3
#define RW_FRAME_SUBTREE_SYNC   0xC

// Loads the identity into the matrix and flags it as identity/orthonormal, using the frame code's
// .sdata2 constants.
static inline void RwMatrixSetIdentity(RwMatrix* m)
{
	RW_MATRIX_SET_IDENTITY(m, lbl_8042F6F8, lbl_8042F6FC);
}

// Links a node at the head of a list (HYPOTHESIS: rwLinkListAddLLLink).
static inline void RwLinkListAddLLLink(RwLinkList* list, RwLLLink* link)
{
	link->next            = list->link.next;
	link->prev            = &list->link;
	list->link.next->prev = link;
	list->link.next       = link;
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
