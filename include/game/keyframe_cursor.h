#ifndef GAME_KEYFRAME_CURSOR_H
#define GAME_KEYFRAME_CURSOR_H

#include "game/rw_engine.h"

// Cursor over a list of time-stamped key frames, used by the units around 0x80200934
// (HYPOTHESIS: an animation interpolator). Field names are inferred from fn_80200AC4 and
// fn_80200CB0 only.

struct KeyFrame {
	f32 time;   // 0x0
	void* data; // 0x4
};

struct KeyFrameCursor {
	RwSList* keyFrames; // 0x0: list of KeyFrame
	u8 pad4[0x4];
	f32 time; // 0x8
	u8 padC[0x4];
	KeyFrame* previous; // 0x10
	KeyFrame* next;     // 0x14
	KeyFrame* last;     // 0x18
};

extern "C" {
// HYPOTHESIS: RwSListGetNumEntries and RwSListGetEntry.
s32 fn_8019469C(RwSList* list);
void* fn_8019472C(RwSList* list, s32 index);
}

#endif
