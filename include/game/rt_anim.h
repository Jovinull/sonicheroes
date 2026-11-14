#ifndef GAME_RT_ANIM_H
#define GAME_RT_ANIM_H

#include "game/rw_engine.h"

// Key-frame interpolation schemes registered with the animation toolkit (HYPOTHESIS:
// RtAnimInterpolatorInfo, 0x30 bytes, error plugin 0x1B7). Only the type ID and the four
// callbacks copied by fn_8020C864 are named.
struct RtAnimInterpolatorInfo {
	s32 typeID; // 0x0
	u8 pad4[0x8];
	void* callbacks[4]; // 0xC
	u8 pad1C[0x30 - 0x1C];
};

#define RT_ANIM_PLUGIN_ID         0x1B7
#define RT_ANIM_MAX_INTERPOLATORS 16

extern "C" {
// Registered schemes and their count.
extern RtAnimInterpolatorInfo lbl_8040EBA4[RT_ANIM_MAX_INTERPOLATORS];
extern s32 lbl_8042CF78;
}

#endif
