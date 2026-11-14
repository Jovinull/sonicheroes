// Creates an animation for a registered key-frame type (HYPOTHESIS: RtAnimAnimationCreate): one
// engine heap block holds the 0x18-byte header, numFrames key frames of the scheme's size and the
// scheme's custom data, which follows the frames when the scheme has any. The allocation is not
// checked. Returns the animation, or null for an unknown type.
#include "game/rt_anim.h"

// Animation header (HYPOTHESIS: RtAnimAnimation).
struct RtAnimAnimation8020C1AC {
	RtAnimInterpolatorInfo* interpInfo; // 0x0
	s32 numFrames;                      // 0x4
	s32 flags;                          // 0x8
	f32 duration;                       // 0xC
	void* frames;                       // 0x10
	void* customData;                   // 0x14
};

extern "C" {
RtAnimAnimation8020C1AC* fn_8020C1AC(s32 typeID, s32 numFrames, s32 flags, f32 duration)
{
	RtAnimInterpolatorInfo* info = RtAnimGetInterpolatorInfo(typeID);
	RtAnimAnimation8020C1AC* animation;

	if (!info) {
		return 0;
	}
	animation = (RtAnimAnimation8020C1AC*)lbl_8042C9A4->rwmalloc(
	    sizeof(RtAnimAnimation8020C1AC) + numFrames * info->keyFrameSize + info->customDataSize);
	animation->numFrames  = numFrames;
	animation->duration   = duration;
	animation->flags      = flags;
	animation->interpInfo = info;
	animation->frames     = animation + 1;
	if (info->customDataSize > 0) {
		animation->customData = (u8*)animation->frames + numFrames * info->keyFrameSize;
	} else {
		animation->customData = 0;
	}
	return animation;
}
}
