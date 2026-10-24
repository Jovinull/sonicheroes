// The three RenderWare helpers s02KameWave's translation unit keeps (the run
// they sit in ends with s02KameWaveCreate), the bodies of
// rel/flower_hierarchy.cpp: SetHierarchyForSkinAtomic, GetHierarchy and
// GetChildFrameHierarchy. Retail's copies are file-static; here they get names
// of their own. Only stage01D has them.

#include "game/object.h"

extern "C" {
RpHAnimHierarchy* fn_8013F484(RwFrame* frame);
void fn_8019EB10(RwFrame* frame, RwFrame* (*callback)(RwFrame*, void*), void* data);
void* fn_80226468(void* geometry);
void fn_80226440(RpAtomic* atomic, void* hierarchy);
}

RwFrame* s02KameWaveGetChildFrameHierarchy(RwFrame* frame, void* data);

RpAtomic* s02KameWaveSetHierarchyForSkinAtomic(RpAtomic* atomic, void* data)
{
	if (fn_80226468(*(void**)((u8*)atomic + 0x18)) != NULL)
		fn_80226440(atomic, data);
	return atomic;
}

RpHAnimHierarchy* s02KameWaveGetHierarchy(RpClump* clump)
{
	RpHAnimHierarchy* hierarchy = NULL;
	hierarchy                   = fn_8013F484((RwFrame*)((RwObject*)clump)->parent);
	if (hierarchy == NULL)
		fn_8019EB10(
		    (RwFrame*)((RwObject*)clump)->parent, s02KameWaveGetChildFrameHierarchy, &hierarchy);
	return hierarchy;
}

RwFrame* s02KameWaveGetChildFrameHierarchy(RwFrame* frame, void* data)
{
	RpHAnimHierarchy* hierarchy = fn_8013F484(frame);
	if (hierarchy == NULL) {
		fn_8019EB10(frame, s02KameWaveGetChildFrameHierarchy, data);
		return frame;
	} else {
		*(RpHAnimHierarchy**)data = hierarchy;
		return NULL;
	}
}
