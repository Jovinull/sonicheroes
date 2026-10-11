// The three RenderWare helpers the flower object's translation unit keeps right
// after its constructor, the same bodies as rel/chao_ctor.cpp's (and main's
// nHierarchy): SetHierarchyForSkinAtomic, GetHierarchy and
// GetChildFrameHierarchy. Retail's copies are file-static; here they get names
// of their own.

#include "game/object.h"

extern "C" {
RpHAnimHierarchy* fn_8013F484(RwFrame* frame);
void fn_8019EB10(RwFrame* frame, RwFrame* (*callback)(RwFrame*, void*), void* data);
void* fn_80226468(void* geometry);
void fn_80226440(RpAtomic* atomic, void* hierarchy);
}

RwFrame* flowerGetChildFrameHierarchy(RwFrame* frame, void* data);

RpAtomic* flowerSetHierarchyForSkinAtomic(RpAtomic* atomic, void* data)
{
	if (fn_80226468(*(void**)((u8*)atomic + 0x18)) != NULL)
		fn_80226440(atomic, data);
	return atomic;
}

RpHAnimHierarchy* flowerGetHierarchy(RpClump* clump)
{
	RpHAnimHierarchy* hierarchy = NULL;
	hierarchy                   = fn_8013F484((RwFrame*)((RwObject*)clump)->parent);
	if (hierarchy == NULL)
		fn_8019EB10((RwFrame*)((RwObject*)clump)->parent, flowerGetChildFrameHierarchy, &hierarchy);
	return hierarchy;
}

RwFrame* flowerGetChildFrameHierarchy(RwFrame* frame, void* data)
{
	RpHAnimHierarchy* hierarchy = fn_8013F484(frame);
	if (hierarchy == NULL) {
		fn_8019EB10(frame, flowerGetChildFrameHierarchy, data);
		return frame;
	} else {
		*(RpHAnimHierarchy**)data = hierarchy;
		return NULL;
	}
}
