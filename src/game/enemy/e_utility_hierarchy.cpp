// Complete C++ enemy/e_utility_hierarchy.cpp, identified by namespace
// metadata, callback references and GameCube motion-manager callers.
#include "game/enemy/e_utility_hierarchy.h"
#include "types.h"

// Only these RenderWare prefixes are accessed; no full objects are allocated.
struct RwObject {
	u8 type, subType, flags, privateFlags;
	void* parent;
};
struct RwLLLink {
	RwLLLink* next;
	RwLLLink* prev;
};
struct RwObjectHasFrame {
	RwObject object;
	RwLLLink lFrame;
	RwObjectHasFrame* (*sync)(RwObjectHasFrame*);
};
struct RpGeometry;
struct RpSkin;
struct RwResEntry;
struct RpAtomic {
	RwObjectHasFrame object;
	RwResEntry* repEntry;
	RpGeometry* geometry;
};
struct RpClump {
	RwObject object;
};

extern "C" {
RpSkin* fn_80226468(RpGeometry*);
RpAtomic* fn_80226440(RpAtomic*, RpHAnimHierarchy*);
RpHAnimHierarchy* fn_8013F484(RwFrame*);
RwFrame* fn_8019EB10(RwFrame*, RwFrame* (*)(RwFrame*, void*), void*);
}

namespace nHierarchy
{
RpAtomic* SetHierarchyForSkinAtomic(RpAtomic* atomic, void* data)
{
	if (fn_80226468(atomic->geometry) != NULL)
		fn_80226440(atomic, (RpHAnimHierarchy*)data);
	return atomic;
}

RpHAnimHierarchy* GetHierarchy(RpClump* clump)
{
	RpHAnimHierarchy* hierarchy = NULL;
	hierarchy                   = fn_8013F484((RwFrame*)clump->object.parent);
	if (hierarchy == NULL)
		fn_8019EB10((RwFrame*)clump->object.parent, GetChildFrameHierarchy, &hierarchy);
	return hierarchy;
}

RwFrame* GetChildFrameHierarchy(RwFrame* frame, void* data)
{
	RpHAnimHierarchy* hierarchy = fn_8013F484(frame);
	if (hierarchy == NULL) {
		fn_8019EB10(frame, GetChildFrameHierarchy, data);
		return frame;
	} else {
		*(RpHAnimHierarchy**)data = hierarchy;
		return NULL;
	}
}
}
