// HYPOTHESIS: RenderWare RtAnimInterpolatorCreateSubInterpolator. Allocates an interpolator
// (0x4C header + numNodes * maxKeyFrameSize frame bytes) and initialises it, inheriting the
// parent interpolator's maxKeyFrameSize when the argument is -1.

#include "types.h"

typedef struct RtAnimInterpolator RtAnimInterpolator;
struct RtAnimInterpolator {
	void* pCurrentAnim;                  /* 0x00 */
	f32 currentTime;                     /* 0x04 */
	void* pNextFrame;                    /* 0x08 */
	void* pAnimCallBack;                 /* 0x0C */
	void* pAnimCallBackData;             /* 0x10 */
	f32 animCallBackTime;                /* 0x14 */
	void* pAnimLoopCallBack;             /* 0x18 */
	void* pAnimLoopCallBackData;         /* 0x1C */
	s32 maxKeyFrameSize;                 /* 0x20 */
	s32 currentKeyFrameSize;             /* 0x24 */
	s32 offsetInParent;                  /* 0x28 */
	s32 numNodes;                        /* 0x2C */
	s32 isSubInterpolator;               /* 0x30 */
	s32 startNode;                       /* 0x34 */
	RtAnimInterpolator* parentAnimation; /* 0x38 */
	void* keyFrameApplyCB;               /* 0x3C */
	void* keyFrameBlendCB;               /* 0x40 */
	void* keyFrameAddCB;                 /* 0x44 */
	void* keyFrameMulRecipCB;            /* 0x48 */
};

typedef struct RwEngineInstance {
	u8 pad0[0x134];
	void* (*fpMalloc)(u32 size); /* 0x134 */
} RwEngineInstance;

extern "C" {
extern RwEngineInstance* lbl_8042C9A4;
extern f32 lbl_804300F0;
extern f32 lbl_804300F4;

RtAnimInterpolator* fn_8020D120(
    RtAnimInterpolator* parent, s32 startNode, s32 numNodes, s32 maxKeyFrameSize)
{
	RtAnimInterpolator* interpolator;

	if (maxKeyFrameSize == -1)
		maxKeyFrameSize = parent->maxKeyFrameSize;

	interpolator = (RtAnimInterpolator*)lbl_8042C9A4->fpMalloc(
	    sizeof(RtAnimInterpolator) + numNodes * maxKeyFrameSize);

	interpolator->numNodes              = numNodes;
	interpolator->pCurrentAnim          = 0;
	interpolator->pNextFrame            = 0;
	interpolator->currentTime           = lbl_804300F0;
	interpolator->pAnimCallBack         = 0;
	interpolator->animCallBackTime      = lbl_804300F4;
	interpolator->pAnimCallBackData     = 0;
	interpolator->pAnimLoopCallBack     = 0;
	interpolator->pAnimLoopCallBackData = 0;
	interpolator->currentKeyFrameSize   = maxKeyFrameSize;
	interpolator->offsetInParent        = -1;
	interpolator->maxKeyFrameSize       = maxKeyFrameSize;
	interpolator->isSubInterpolator     = 0;
	interpolator->startNode             = 0;
	interpolator->parentAnimation       = interpolator;
	interpolator->keyFrameApplyCB       = 0;
	interpolator->keyFrameAddCB         = 0;
	interpolator->keyFrameBlendCB       = 0;
	interpolator->keyFrameMulRecipCB    = 0;
	interpolator->parentAnimation       = parent;
	interpolator->startNode             = startNode;
	interpolator->isSubInterpolator     = 1;

	return interpolator;
}
}
