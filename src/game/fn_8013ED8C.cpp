// Creates an animation hierarchy (HYPOTHESIS: RpHAnimHierarchyCreate): takes the hierarchy from the
// HAnim free list, creates its interpolator (fn_8020C658), allocates the 16-byte aligned matrix
// array unless the no-matrices flag (0x2) is set, and fills one node record per node with the
// optional node ID and flag arrays. The hierarchy is its own parent. Returns the hierarchy.
// NonMatching: retail keeps maxInterpKeyFrameSize and then the hierarchy in r31 and the flags in
// r27 (five saved registers); this source gives them separate registers (six saved, 7 words
// differ). Declaration order, a temporary for the interpolator, an inline init helper and compilers
// 1.3 to 2.6 do not change it.
#include "game/rw_engine.h"

// HAnim plugin globals (HYPOTHESIS: RpHAnimAtomicGlobals; the hierarchy free list is at +0x4).
struct RpHAnimGlobals8013ED8C {
	s32 engineOffset;          // 0x0
	RwFreeList* hierarchyList; // 0x4
};

#define RP_HANIM_HIERARCHY_NO_MATRICES 0x2

extern "C" {
extern RpHAnimGlobals8013ED8C lbl_8042C828;
// HYPOTHESIS: RtAnimInterpolatorCreate(numNodes, maxInterpKeyFrameSize).
void* fn_8020C658(s32 numNodes, s32 maxInterpKeyFrameSize);

RpHAnimHierarchy* fn_8013ED8C(
    s32 numNodes, s32* nodeFlags, s32* nodeIDs, s32 flags, s32 maxInterpKeyFrameSize)
{
	RpHAnimHierarchy* hierarchy;
	s32 i;

	hierarchy = (RpHAnimHierarchy*)lbl_8042C9A4->freeListAlloc(lbl_8042C828.hierarchyList);
	hierarchy->currentAnim = fn_8020C658(numNodes, maxInterpKeyFrameSize);
	hierarchy->flags       = flags;
	hierarchy->numNodes    = numNodes;
	hierarchy->parentFrame = 0;
	if (!(flags & RP_HANIM_HIERARCHY_NO_MATRICES)) {
		void* matrices                   = lbl_8042C9A4->rwmalloc(sizeof(RwMatrix) * numNodes + 15);
		hierarchy->pMatrixArray          = (RwMatrix*)(((u32)matrices + 15) & ~15);
		hierarchy->pMatrixArrayUnaligned = matrices;
	} else {
		hierarchy->pMatrixArray          = 0;
		hierarchy->pMatrixArrayUnaligned = 0;
	}
	hierarchy->pNodeInfo
	    = (RpHAnimNodeInfo*)lbl_8042C9A4->rwmalloc(sizeof(RpHAnimNodeInfo) * numNodes);
	for (i = 0; i < numNodes; i++) {
		hierarchy->pNodeInfo[i].pFrame = 0;
		if (nodeIDs != 0) {
			hierarchy->pNodeInfo[i].nodeID = nodeIDs[i];
		}
		hierarchy->pNodeInfo[i].nodeIndex = i;
		if (nodeFlags != 0) {
			hierarchy->pNodeInfo[i].flags = nodeFlags[i];
		}
	}
	hierarchy->parentHierarchy = hierarchy;
	return hierarchy;
}
}
