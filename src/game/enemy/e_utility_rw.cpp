#include "game/enemy/e_utility_rw.h"

struct sSearchFactor {
	RwFrame* frame;
	s32 frameID;
};
extern "C" {
RwFrame* fn_8019EB10(RwFrame*, RwFrame* (*)(RwFrame*, void*), void*);
s32 fn_8013F494(RwFrame*);
}
static RwFrame* callbackSearchFrameID(RwFrame*, void*);

RwFrame* nRenderWare::SearchFrameFromFrameID(RwFrame* pFrameParent, s32 FrameID)
{
	sSearchFactor factor;
	factor.frame   = NULL;
	factor.frameID = FrameID;
	fn_8019EB10(pFrameParent, callbackSearchFrameID, &factor);
	return factor.frame;
}

static RwFrame* callbackSearchFrameID(RwFrame* pFrame, void* pData)
{
	sSearchFactor* pfactor = static_cast<sSearchFactor*>(pData);
	if (!pfactor->frame) {
		if (pfactor->frameID == fn_8013F494(pFrame))
			pfactor->frame = pFrame;
		else
			fn_8019EB10(pFrame, callbackSearchFrameID, pfactor);
	}
	return pFrame;
}
