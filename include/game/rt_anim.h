#ifndef GAME_RT_ANIM_H
#define GAME_RT_ANIM_H

#include "game/rw_engine.h"

// Key-frame interpolation schemes registered with the animation toolkit (HYPOTHESIS:
// RtAnimInterpolatorInfo, 0x30 bytes, error plugin 0x1B7). Only the fields used by the
// reconstructed units are named.
struct RtAnimInterpolatorInfo {
	s32 typeID; // 0x0
	u8 pad4[0x4];
	s32 keyFrameSize;   // 0x8
	void* callbacks[4]; // 0xC
	u8 pad1C[0x2C - 0x1C];
	s32 customDataSize; // 0x2C
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
