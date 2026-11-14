#ifndef GAME_RW_FRAME_H
#define GAME_RW_FRAME_H

#include "game/object.h"

// RenderWare frame-hierarchy helpers shared by the frame units around 0x8019E000.
// Function names in comments are HYPOTHESIS (RenderWare API shape); symbols stay fn_ addresses.

// Engine globals block (HYPOTHESIS: RwEngineInstance). Only the dirty-frame list is known.
struct RwFrameGlobals {
	u8 pad0[0xBC];
	RwLinkList dirtyFrameList; // 0xBC
};

extern "C" {
extern RwFrameGlobals* lbl_8042C9A4;
// HYPOTHESIS: _rwSetHierarchyRoot.
void fn_8019DFDC(RwFrame* frame, RwFrame* root);
}

// Frame private flags: hierarchy sync (root, bits 0-1) and subtree sync (bits 2-3).
#define RW_FRAME_HIERARCHY_SYNC 0x3
#define RW_FRAME_SUBTREE_SYNC   0xC

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
