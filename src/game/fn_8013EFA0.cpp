// Creates a sub-hierarchy of an animation hierarchy (HYPOTHESIS:
// RpHAnimHierarchyCreateSubHierarchy): counts the nodes of the subtree rooted at startNode by following the push/pop node flags, takes a
// hierarchy from the HAnim free list, flags it as a sub-hierarchy, creates its sub-interpolator
// (fn_8020D120), finds the parent node index of the subtree root with a push/pop stack (-1 for
// the root), and shares the parent's frame, matrix array and node records from startNode on.
// Returns the sub-hierarchy.
#include "game/rw_engine.h"

#define RP_HANIM_POP_PARENT_MATRIX  0x1
#define RP_HANIM_PUSH_PARENT_MATRIX 0x2
#define RP_HANIM_SUB_HIERARCHY      0x1
#define RP_HANIM_STACK_SIZE         32

// HAnim plugin globals (HYPOTHESIS: RpHAnimAtomicGlobals; the hierarchy free list is at +0x4).
struct RpHAnimGlobals8013EFA0 {
	s32 engineOffset;          // 0x0
	RwFreeList* hierarchyList; // 0x4
};

extern "C" {
extern RpHAnimGlobals8013EFA0 lbl_8042C828;
// HYPOTHESIS: RtAnimInterpolatorCreateSubInterpolator.
void* fn_8020D120(void* parentInterpolator, s32 startNode, s32 numNodes, s32 maxInterpKeyFrameSize);

RpHAnimHierarchy* fn_8013EFA0(
    RpHAnimHierarchy* parent, s32 startNode, s32 flags, s32 maxInterpKeyFrameSize)
{
	RpHAnimHierarchy* hierarchy;
	s32 numNodes;
	s32 depth;
	RpHAnimNodeInfo* node;

	node     = &parent->pNodeInfo[startNode];
	numNodes = 1;
	depth    = 0;

	if (!(node->flags & RP_HANIM_POP_PARENT_MATRIX)) {
		depth = 1;
		node++;
	}
	while (depth != 0) {
		if (node->flags & RP_HANIM_PUSH_PARENT_MATRIX) {
			depth++;
		}
		if (node->flags & RP_HANIM_POP_PARENT_MATRIX) {
			depth--;
		}
		numNodes++;
		node++;
	}

	hierarchy        = (RpHAnimHierarchy*)lbl_8042C9A4->freeListAlloc(lbl_8042C828.hierarchyList);
	hierarchy->flags = flags | RP_HANIM_SUB_HIERARCHY;
	hierarchy->numNodes = numNodes;
	hierarchy->currentAnim
	    = fn_8020D120(parent->currentAnim, startNode, numNodes, maxInterpKeyFrameSize);
	if (startNode == 0) {
		hierarchy->rootParentOffset = -1;
	} else {
		s32 stack[RP_HANIM_STACK_SIZE];
		s32 i;
		s32* top;
		s32 parentIndex;

		top         = stack;
		parentIndex = -1;
		for (i = 0; i < startNode; i++) {
			if (parent->pNodeInfo[i].flags & RP_HANIM_PUSH_PARENT_MATRIX) {
				*top++ = parentIndex;
			}
			parentIndex = (parent->pNodeInfo[i].flags & RP_HANIM_POP_PARENT_MATRIX) ? *--top : i;
		}
		hierarchy->rootParentOffset = parentIndex;
	}
	hierarchy->parentFrame           = parent->pNodeInfo[startNode].pFrame;
	hierarchy->pMatrixArray          = parent->pMatrixArray + startNode;
	hierarchy->pMatrixArrayUnaligned = 0;
	hierarchy->pNodeInfo             = &parent->pNodeInfo[startNode];
	hierarchy->parentHierarchy       = parent;
	return hierarchy;
}
}
