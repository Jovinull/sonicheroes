// Recursively clones a frame hierarchy (HYPOTHESIS: the recursive step of RwFrameCloneHierarchy).
// The clone copies the object header and modelling matrix, gets an empty object list and root as
// its hierarchy root (itself at the top level), and src->root temporarily records the clone so the
// caller can remap attached objects. Children are cloned and linked at the head of the clone's child
// list; on failure the partial clone is destroyed. Plugin data is initialized and copied last.
#include "game/rw_frame.h"

// The retail copy moves the matrix as sixteen plain words; a struct copy of RwMatrix through its
// RwV3d members allocates the transfer registers differently.
struct RwMatrixWords {
	u32 w[16];
};

static inline void RwMatrixCopyWords(RwMatrix* dst, const RwMatrix* src)
{
	*(RwMatrixWords*)dst = *(const RwMatrixWords*)src;
}

extern "C" {
// HYPOTHESIS: RwFrameDestroyHierarchy.
void fn_8019E85C(RwFrame* frame);

RwFrame* fn_8019E0F0(RwFrame* src, RwFrame* root)
{
	RwFrame* dst;
	RwFrame* child;
	dst = (RwFrame*)lbl_8042C9A4->freeListAlloc(RW_FRAME_FREE_LIST);
	if (dst == 0) {
		return 0;
	}
	if (root == 0) {
		root = dst;
	}
	dst->object.type          = src->object.type;
	dst->object.subType       = src->object.subType;
	dst->object.flags         = src->object.flags;
	dst->object.privateFlags  = src->object.privateFlags;
	dst->object.parent        = 0;
	dst->objectList.link.next = &dst->objectList.link;
	dst->objectList.link.prev = &dst->objectList.link;
	dst->object.parent        = 0;
	RwMatrixCopyWords(&dst->modelling, &src->modelling);
	dst->child = 0;
	dst->next  = 0;
	dst->root  = root;
	src->root  = dst;
	for (child = src->child; child != 0; child = child->next) {
		RwFrame* clone = fn_8019E0F0(child, root);
		if (clone == 0) {
			fn_8019E85C(dst);
			return 0;
		}
		clone->next          = dst->child;
		dst->child           = clone;
		clone->object.parent = dst;
	}
	fn_80198D5C(&lbl_802905F8, dst);
	fn_80198E70(&lbl_802905F8, dst, src);
	return dst;
}
}
