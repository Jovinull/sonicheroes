// Makes an animation the interpolator's current one (HYPOTHESIS:
// RtAnimInterpolatorSetCurrentAnim): resets the time to the .sdata2 constant lbl_804300F0
// (HYPOTHESIS 0.0f), takes the key-frame sizes and the four callbacks from the animation's scheme,
// interpolates each interpolation frame between key frame i and key frame i + n at time 0 and
// points its header at those two frames, and sets the next frame to the first key frame after
// them. Always returns 1.
// NonMatching: same 78 instructions; the first loop's argument scheduling and the second loop's
// register assignment differ (31 words).
#include "game/rt_anim.h"

extern "C" {
extern f32 lbl_804300F0;

s32 fn_8020C72C(RtAnimInterpolator* interpolator, RtAnimAnimation* animation)
{
	s32 i;
	RtAnimInterpolatorInfo* info;

	interpolator->currentAnim               = animation;
	interpolator->currentTime               = lbl_804300F0;
	info                                    = (RtAnimInterpolatorInfo*)animation->interpInfo;
	interpolator->currentInterpKeyFrameSize = info->interpKeyFrameSize;
	interpolator->currentAnimKeyFrameSize   = info->keyFrameSize;
	interpolator->keyFrameApplyCB           = info->callbacks[0];
	interpolator->keyFrameBlendCB           = info->callbacks[1];
	interpolator->keyFrameInterpolateCB     = (RtAnimKeyFrameInterpolateCallBack)info->callbacks[2];
	interpolator->keyFrameAddCB             = info->callbacks[3];

	for (i = 0; i < interpolator->numInterpFrames; i++) {
		interpolator->keyFrameInterpolateCB(
		    interpolator->interpFrames + i * interpolator->currentInterpKeyFrameSize,
		    (u8*)animation->pFrames + i * interpolator->currentAnimKeyFrameSize,
		    (u8*)animation->pFrames
		        + (i + interpolator->numInterpFrames) * interpolator->currentAnimKeyFrameSize,
		    lbl_804300F0, animation->customData);
	}
	{
		RtAnimInterpFrameHeader* header;
		u8* keyFrame2;
		s32 j;
		u8* keyFrame1;

		header    = (RtAnimInterpFrameHeader*)interpolator->interpFrames;
		keyFrame1 = (u8*)animation->pFrames;
		keyFrame2
		    = keyFrame1 + interpolator->numInterpFrames * interpolator->currentAnimKeyFrameSize;
		for (j = 0; j < interpolator->numInterpFrames; j++) {
			header->keyFrame1 = keyFrame1;
			header->keyFrame2 = keyFrame2;
			keyFrame1 += interpolator->currentAnimKeyFrameSize;
			keyFrame2 += interpolator->currentAnimKeyFrameSize;
			header
			    = (RtAnimInterpFrameHeader*)((u8*)header + interpolator->currentInterpKeyFrameSize);
		}
	}
	interpolator->nextFrame = (u8*)animation->pFrames
	    + interpolator->numInterpFrames * 2 * interpolator->currentAnimKeyFrameSize;
	return 1;
}
}
