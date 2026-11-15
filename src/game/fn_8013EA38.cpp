// Reads the hierarchy extension of a frame from a stream (HYPOTHESIS: RenderWare RpHAnim
// HAnimFrameStreamRead; names follow RpHAnimHierarchy). Reads the version (0x100), the node ID
// and node count; with nodes, reads the hierarchy flags and key-frame size, allocates a cleared
// hierarchy from the plugin free list with its interpolator (fn_8020C658), a 16-byte aligned
// matrix array unless the flags say there are none (0x2), and the node info array, whose node ID,
// index and flags are read per node. Returns the stream, or null when a read fails.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

#define RP_HANIM_STREAM_VERSION        0x100
#define RP_HANIM_HIERARCHY_NO_MATRICES 0x2

struct HAnimNodeInfo8013EA38 {
	s32 nodeID;    // 0x0
	s32 nodeIndex; // 0x4
	s32 flags;     // 0x8
	void* frame;   // 0xC
};

struct HAnimHierarchy8013EA38 {
	s32 flags;                       // 0x0
	s32 numNodes;                    // 0x4
	RwMatrix* matrices;              // 0x8: 16-byte aligned
	void* matricesUnaligned;         // 0xC
	HAnimNodeInfo8013EA38* nodeInfo; // 0x10
	void* parentFrame;               // 0x14
	HAnimHierarchy8013EA38* parent;  // 0x18
	s32 rootParentOffset;            // 0x1C
	void* interpolator;              // 0x20
};

struct HAnimFrameExt8013EA38 {
	s32 id;                            // 0x0
	HAnimHierarchy8013EA38* hierarchy; // 0x4
};

// Plugin globals: the frame extension offset and the hierarchy free list (HYPOTHESIS).
struct HAnimGlobals8013EA38 {
	s32 offset;           // 0x0
	RwFreeList* freeList; // 0x4
};

extern "C" {
extern HAnimGlobals8013EA38 lbl_8042C828;

// HYPOTHESIS: RwStreamReadInt32 and RtAnimInterpolatorCreate.
void* fn_80193884(void* stream, void* ints, u32 numBytes);
void* fn_8020C658(s32 numNodes, s32 keyFrameSize);

void* fn_8013EA38(void* stream, s32 length, void* frame)
{
	HAnimFrameExt8013EA38* ext = (HAnimFrameExt8013EA38*)((u8*)frame + lbl_8042C828.offset);
	s32 numNodes;
	s32 version;
	s32 flags;
	s32 keyFrameSize;

	if (fn_80193884(stream, &version, sizeof(version)) == 0) {
		return 0;
	}
	if (version != RP_HANIM_STREAM_VERSION) {
		return 0;
	}
	if (fn_80193884(stream, &ext->id, sizeof(ext->id)) == 0) {
		return 0;
	}
	if (fn_80193884(stream, &numNodes, sizeof(numNodes)) == 0) {
		return 0;
	}
	if (numNodes > 0) {
		HAnimHierarchy8013EA38* hierarchy;

		if (fn_80193884(stream, &flags, sizeof(flags)) == 0) {
			return 0;
		}
		if (fn_80193884(stream, &keyFrameSize, sizeof(keyFrameSize)) == 0) {
			return 0;
		}
		hierarchy = (HAnimHierarchy8013EA38*)lbl_8042C9A4->freeListAlloc(lbl_8042C828.freeList);
		memset(hierarchy, 0, sizeof(HAnimHierarchy8013EA38));
		if (hierarchy != 0) {
			s32 i;
			HAnimNodeInfo8013EA38* node;

			hierarchy->interpolator = fn_8020C658(numNodes, keyFrameSize);
			hierarchy->flags        = flags;
			hierarchy->parentFrame  = frame;
			hierarchy->numNodes     = numNodes;
			hierarchy->parent       = hierarchy;
			if (hierarchy->flags & RP_HANIM_HIERARCHY_NO_MATRICES) {
				hierarchy->matrices          = 0;
				hierarchy->matricesUnaligned = 0;
			} else {
				void* block         = lbl_8042C9A4->rwmalloc(numNodes * sizeof(RwMatrix) + 0xF);
				hierarchy->matrices = (RwMatrix*)(((u32)block + 0xF) & ~0xF);
				hierarchy->matricesUnaligned = block;
			}
			hierarchy->nodeInfo = (HAnimNodeInfo8013EA38*)lbl_8042C9A4->rwmalloc(
			    numNodes * sizeof(HAnimNodeInfo8013EA38));
			node = hierarchy->nodeInfo;
			for (i = 0; i < hierarchy->numNodes; i++) {
				if (fn_80193884(stream, &node->nodeID, sizeof(node->nodeID)) == 0) {
					return 0;
				}
				if (fn_80193884(stream, &node->nodeIndex, sizeof(node->nodeIndex)) == 0) {
					return 0;
				}
				if (fn_80193884(stream, &node->flags, sizeof(node->flags)) == 0) {
					return 0;
				}
				node->frame = 0;
				node++;
			}
		}
		ext->hierarchy = hierarchy;
	}
	return stream;
}
}
