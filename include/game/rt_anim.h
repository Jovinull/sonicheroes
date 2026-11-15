#ifndef GAME_RT_ANIM_H
#define GAME_RT_ANIM_H

#include "game/rw_engine.h"

// Key-frame interpolation schemes registered with the animation toolkit (HYPOTHESIS:
// RtAnimInterpolatorInfo, 0x30 bytes, error plugin 0x1B7). Only the fields used by the
// reconstructed units are named.
struct RtAnimInterpolatorInfo {
	s32 typeID;             // 0x0
	s32 interpKeyFrameSize; // 0x4
	s32 keyFrameSize;       // 0x8: animation key frame size
	void* callbacks[4];     // 0xC
	u8 pad1C[0x2C - 0x1C];
	s32 customDataSize; // 0x2C
};

// RtAnimAnimation itself is declared in game/object.h (included through rw_engine.h).

// Interpolation frame header (HYPOTHESIS: RtAnimInterpFrameHeader): the two key frames in use.
struct RtAnimInterpFrameHeader {
	void* keyFrame1; // 0x0
	void* keyFrame2; // 0x4
};

typedef void (*RtAnimKeyFrameInterpolateCallBack)(
    void* out, void* in1, void* in2, f32 time, void* customData);

// Interpolator (HYPOTHESIS: RtAnimInterpolator); its interpolation frames start at 0x4C.
struct RtAnimInterpolator {
	RtAnimAnimation* currentAnim; // 0x0
	f32 currentTime;              // 0x4
	void* nextFrame;              // 0x8
	u8 padC[0x24 - 0xC];
	s32 currentInterpKeyFrameSize; // 0x24
	s32 currentAnimKeyFrameSize;   // 0x28
	s32 numInterpFrames;           // 0x2C
	u8 pad30[0x3C - 0x30];
	void* keyFrameApplyCB;                                   // 0x3C
	void* keyFrameBlendCB;                                   // 0x40
	RtAnimKeyFrameInterpolateCallBack keyFrameInterpolateCB; // 0x44
	void* keyFrameAddCB;                                     // 0x48
	u8 interpFrames[1];                                      // 0x4C (extent from the counts)
};

#define RT_ANIM_PLUGIN_ID         0x1B7
#define RT_ANIM_MAX_INTERPOLATORS 16

extern "C" {
// Registered schemes and their count.
extern RtAnimInterpolatorInfo lbl_8040EBA4[RT_ANIM_MAX_INTERPOLATORS];
extern s32 lbl_8042CF78;
}

// Looks a registered scheme up by type (HYPOTHESIS: RtAnimGetInterpolatorInfo, inlined by its
// callers); an unknown type records error 2 of the animation plugin and gives null.
static inline RtAnimInterpolatorInfo* RtAnimGetInterpolatorInfo(s32 typeID)
{
	s32 i;
	for (i = 0; i < lbl_8042CF78; i++) {
		if (typeID == lbl_8040EBA4[i].typeID) {
			return &lbl_8040EBA4[i];
		}
	}
	RwError error;
	error.pluginID  = RT_ANIM_PLUGIN_ID;
	error.errorCode = fn_8019408C(2);
	fn_80193FE8(&error);
	return 0;
}

#endif
