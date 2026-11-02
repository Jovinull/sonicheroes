#include "types.h"

// BMODEL's atomic and frame searches and its hierarchy attach and detach (the
// PS2 build's names, from STAGE.BIN, where it has them), the same in the four
// stage modules that carry BMODEL. SearchAtomicFromFrame (GC only) finds the
// atomic hanging from a frame; SearchAtomicFromNodeID finds the one under a
// hierarchy node (with SearchFrameFromNodeID inlined). SearchClump and
// GetLightNumber read an entry of a BMODEL_DATA table. The PS2 build calls the
// search callback SearchAtomicFromFrameCallBack, a name TObjBobsleigh already
// takes here.

struct RpClump;
struct RwFrame;

struct RpAtomic {
	u8 unk00[0x4];
	RwFrame* frame; // 0x04
};

struct RpHAnimNodeInfo {
	u8 unk00[0xC];
	RwFrame* frame; // 0x0C
}; // 0x10

struct RpHAnimHierarchy {
	u8 unk00[0x10];
	RpHAnimNodeInfo* nodes; // 0x10
};

struct BMODEL_DATA {
	u8 unk00[0x2];
	s8 light; // 0x02
	u8 unk03[0x5];
	RpClump* clump; // 0x08
	u8 unk0C[0x1C];
}; // 0x28

class HAnimClass
{
public:
	RpHAnimHierarchy* GetHierarchy(RpClump* clump);
	void SetHierarchyForAtomic(RpClump* clump, RpHAnimHierarchy* hierarchy);
};

class BMODEL
{
public:
	static RpAtomic* SearchAtomicFromFrame(RpClump* clump, RwFrame* frame);
	static RpAtomic* SearchAtomicFromNodeID(RpClump* clump, s32 node);
	static RwFrame* SearchFrameFromNodeID(RpHAnimHierarchy* hierarchy, s32 node);
	static void DetachHierarchy(RpClump* clump);
	static RpHAnimHierarchy* AttachHierarchy(RpClump* clump);
	static RpClump* SearchClump(BMODEL_DATA* data, s16 no);
	static s8 GetLightNumber(BMODEL_DATA* data, s16 no);
};

extern HAnimClass HAnim;

s32 objRpHAnimHierarchyFindFrameFromBoneID(RpHAnimHierarchy* hierarchy, s32 bone);

extern "C" {
extern RpAtomic* bmodelFoundAtomic;
void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
void fn_8013F448(RpHAnimHierarchy* hierarchy);
void fn_8013F3A4(RpHAnimHierarchy* hierarchy);
}

RpAtomic* bmodelSearchAtomicFromFrameCallBack(RpAtomic* atomic, void* data);

static inline RpAtomic* bmodelSearchAtomic(RpClump* clump, RwFrame* frame)
{
	bmodelFoundAtomic = NULL;
	fn_8014FFBC(clump, bmodelSearchAtomicFromFrameCallBack, frame);
	return bmodelFoundAtomic;
}

static inline RwFrame* bmodelSearchFrame(RpHAnimHierarchy* hierarchy, s32 node)
{
	s32 index;

	if (hierarchy == NULL) {
		return NULL;
	}
	index = objRpHAnimHierarchyFindFrameFromBoneID(hierarchy, node);
	if (index >= 0) {
		return hierarchy->nodes[index].frame;
	}
	return NULL;
}

RpAtomic* BMODEL::SearchAtomicFromFrame(RpClump* clump, RwFrame* frame)
{
	return bmodelSearchAtomic(clump, frame);
}

RpAtomic* BMODEL::SearchAtomicFromNodeID(RpClump* clump, s32 node)
{
	RpHAnimHierarchy* hierarchy = HAnim.GetHierarchy(clump);
	RwFrame* frame;

	if (hierarchy == NULL) {
		return NULL;
	}
	frame = bmodelSearchFrame(hierarchy, node);
	if (frame == NULL) {
		return NULL;
	}
	return bmodelSearchAtomic(clump, frame);
}

RpAtomic* bmodelSearchAtomicFromFrameCallBack(RpAtomic* atomic, void* data)
{
	if (atomic->frame == data) {
		bmodelFoundAtomic = atomic;
		return NULL;
	}
	return atomic;
}

RwFrame* BMODEL::SearchFrameFromNodeID(RpHAnimHierarchy* hierarchy, s32 node)
{
	return bmodelSearchFrame(hierarchy, node);
}

void BMODEL::DetachHierarchy(RpClump* clump)
{
	RpHAnimHierarchy* hierarchy;

	if (clump != NULL && (hierarchy = HAnim.GetHierarchy(clump)) != NULL) {
		fn_8013F448(hierarchy);
	}
}

RpHAnimHierarchy* BMODEL::AttachHierarchy(RpClump* clump)
{
	RpHAnimHierarchy* hierarchy;

	if (clump == NULL) {
		return NULL;
	}
	hierarchy = HAnim.GetHierarchy(clump);
	if (hierarchy == NULL) {
		return NULL;
	}
	fn_8013F3A4(hierarchy);
	HAnim.SetHierarchyForAtomic(clump, hierarchy);
	return hierarchy;
}

RpClump* BMODEL::SearchClump(BMODEL_DATA* data, s16 no)
{
	BMODEL_DATA* entry = &data[no];

	return entry->clump;
}

s8 BMODEL::GetLightNumber(BMODEL_DATA* data, s16 no)
{
	BMODEL_DATA* entry = &data[no];

	return entry->light;
}
