// HYPOTHESIS: RenderWare RtAnimInterpolatorBlend. Blends the frame data of three
// interpolators: for every key frame, calls the keyFrameBlendCB at +0x40 with the
// three frame payloads (immediately after the 0x4C interpolator header) and alpha,
// then returns 1.

#include "types.h"

typedef struct RtAnimInterpolator RtAnimInterpolator;
typedef void (*RtAnimKeyFrameBlendCallBack)(void*, void*, void*, f32);

// Layout from the matched sibling fn_8020D120 (RenderWare 3.x RtAnimInterpolator);
// the interpolator's key frame data starts at +0x4C, i.e. right after the struct.
struct RtAnimInterpolator {
	void* pCurrentAnim;                          /* 0x00 */
	f32 currentTime;                             /* 0x04 */
	void* pNextFrame;                            /* 0x08 */
	void* pAnimCallBack;                         /* 0x0C */
	void* pAnimCallBackData;                     /* 0x10 */
	f32 animCallBackTime;                        /* 0x14 */
	void* pAnimLoopCallBack;                     /* 0x18 */
	void* pAnimLoopCallBackData;                 /* 0x1C */
	s32 maxKeyFrameSize;                         /* 0x20 */
	s32 currentKeyFrameSize;                     /* 0x24 */
	s32 offsetInParent;                          /* 0x28 */
	s32 numInterpolators;                        /* 0x2C */
	s32 isSubInterpolator;                       /* 0x30 */
	s32 startNode;                               /* 0x34 */
	RtAnimInterpolator* parentAnimation;         /* 0x38 */
	void* keyFrameApplyCB;                       /* 0x3C */
	RtAnimKeyFrameBlendCallBack keyFrameBlendCB; /* 0x40 */
	void* keyFrameAddCB;                         /* 0x44 */
	void* keyFrameMulRecipCB;                    /* 0x48 */
};

extern "C" s32 fn_8020D070(
    RtAnimInterpolator* out, RtAnimInterpolator* in1, RtAnimInterpolator* in2, f32 alpha)
{
	s32 i;

	for (i = 0; i < out->numInterpolators; i++) {
		out->keyFrameBlendCB((u8*)(out + 1) + i * out->currentKeyFrameSize,
		    (u8*)(in1 + 1) + i * in1->currentKeyFrameSize,
		    (u8*)(in2 + 1) + i * in2->currentKeyFrameSize, alpha);
	}
	return 1;
}
