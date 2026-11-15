// Resynchronizes a dirty frame hierarchy from its root (HYPOTHESIS: the per-root step of
// _rwFrameSyncDirty). When the root hierarchy needs its matrices rebuilt, the root LTM is copied
// from its modelling matrix if the root subtree is dirty, the root's objects are synced and the
// children are walked by fn_801A2980; otherwise the objects are synced and the children are walked
// by fn_801A2B90. The four sync bits are cleared afterwards.
// NonMatching: retail loads each list head into r0 and copies it into the loop register (one extra
// mr per object loop, also seen in the outer loop of fn_801A2B90), keeps the flags in r30 and the
// subtree bit in r31 (swapped here), and pairs the matrix word copies through r3/r0. Tried while,
// for, do-while and guarded loops, an inline helper taking the head as a parameter and declaration
// orders.
#include "game/rw_frame.h"

// Root and subtree "LTM" sync bits (HYPOTHESIS: rwFRAMEPRIVATEHIERARCHYSYNCLTM and
// rwFRAMEPRIVATESUBTREESYNCLTM).
#define RW_FRAME_HIERARCHY_SYNC_LTM 0x1
#define RW_FRAME_SUBTREE_SYNC_LTM   0x4

typedef RwObjectHasFrame* (*RwObjectHasFrameSync801A2DA8)(RwObjectHasFrame* object);

extern "C" {
// HYPOTHESIS: the child walks with and without matrix rebuilding.
void fn_801A2980(RwFrame* child, s32 dirtyLTM);
void fn_801A2B90(RwFrame* child);
}

// Calls the sync callback of every object attached to the frame.
static inline void SyncFrameObjects(RwFrame* frame)
{
	RwLLLink* cur = frame->objectList.link.next;
	RwLLLink* end = &frame->objectList.link;
	if (cur != end) {
		while (cur != end) {
			RwObjectHasFrame* object = (RwObjectHasFrame*)((u8*)cur - 8);
			((RwObjectHasFrameSync801A2DA8)object->sync)(object);
			cur = cur->next;
		}
	}
}

extern "C" {
void fn_801A2DA8(RwFrame* frame)
{
	u8 flags = frame->object.privateFlags;
	if (flags & RW_FRAME_HIERARCHY_SYNC_LTM) {
		s32 dirtyLTM = flags & RW_FRAME_SUBTREE_SYNC_LTM;
		if (dirtyLTM) {
			frame->ltm = frame->modelling;
		}
		SyncFrameObjects(frame);
		fn_801A2980(frame->child, dirtyLTM);
	} else {
		SyncFrameObjects(frame);
		fn_801A2B90(frame->child);
	}
	frame->object.privateFlags = flags & 0xF0;
}
}
