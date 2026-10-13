#include "types.h"

// TObjBobsleigh's two lookups (the PS2 build's names): the atomic of a clump
// hanging from a given frame (through RpClumpForAllAtomics and a callback that
// keeps the match) and the frame of a skeleton node from its ID.

typedef struct RwFrame RwFrame;
typedef struct RpClump RpClump;

typedef struct RpAtomic {
	u8 type[4];      // 0x00
	RwFrame* parent; // 0x04
} RpAtomic;

typedef struct RpHAnimNodeInfo {
	s32 nodeID;     // 0x00
	s32 nodeIndex;  // 0x04
	s32 flags;      // 0x08
	RwFrame* frame; // 0x0C
} RpHAnimNodeInfo;

typedef struct RpHAnimHierarchy {
	u8 unk00[0x10];
	RpHAnimNodeInfo* nodeInfo; // 0x10
} RpHAnimHierarchy;

class TObjBobsleigh
{
public:
	RpAtomic* SearchAtomicFromFrame(RpClump* clump, RwFrame* frame);
	RwFrame* SearchNodeFrameFromNodeID(RpHAnimHierarchy* hierarchy, int id);
};

extern "C" RpAtomic* bobsleighFoundAtomic;

// RpClumpForAllAtomics
extern "C" RpClump* fn_8014FFBC(
    RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
int objRpHAnimHierarchyFindFrameFromBoneID(RpHAnimHierarchy* hierarchy, int id);

RpAtomic* SearchAtomicFromFrameCallBack(RpAtomic* atomic, void* frame);

RpAtomic* TObjBobsleigh::SearchAtomicFromFrame(RpClump* clump, RwFrame* frame)
{
	bobsleighFoundAtomic = NULL;
	fn_8014FFBC(clump, SearchAtomicFromFrameCallBack, frame);
	return bobsleighFoundAtomic;
}

RpAtomic* SearchAtomicFromFrameCallBack(RpAtomic* atomic, void* frame)
{
	if (atomic->parent == frame) {
		bobsleighFoundAtomic = atomic;
		return NULL;
	}
	return atomic;
}

RwFrame* TObjBobsleigh::SearchNodeFrameFromNodeID(RpHAnimHierarchy* hierarchy, int id)
{
	int index = objRpHAnimHierarchyFindFrameFromBoneID(hierarchy, id);

	return hierarchy->nodeInfo[index].frame;
}
