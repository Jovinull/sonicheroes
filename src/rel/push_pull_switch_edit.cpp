#include "types.h"

// TObjPushPullSwitch's editor callback. It clamps the frame's single byte
// parameter into the two values the object understands, then points the
// editor's second field label at the matching name.
//
// The claim is .text 0x0005169C to 0x000516F8 and nothing else. It reads no
// constant, so it owns no rodata.
//
// The name is read from the layout and from what it writes: the run sits
// directly before pushPullSwitchReset and stores into
// pushPullSwitchFieldNames, which rel/push_pull_switch_register.cpp already
// names.
//
// Same shape as rel/lens_flare_edit.cpp with one difference: the frame's
// parameters are read without a null check here, so the source has no guard.
//
// The run is the same in the nine stage modules that carry it, checked by
// normalising the disassembly and comparing across modules.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct SETDATA_PARAM {
	Vec3 position; // 0x00
	s32 angleX;    // 0x0C
	s32 angleY;    // 0x10
	s32 angleZ;    // 0x14
	u32 flags;     // 0x18
	u8 pad1C[0x10];
	s8* params; // 0x2C
} SETDATA_PARAM;

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" const char* pushPullSwitchFieldNames[];
extern "C" const char* pushPullSwitchModeNames[];

extern "C" void pushPullSwitchEditOnChange(void* object, SETDATA_PARAM* frame)
{
	s8* mode = frame->params;

	if (*mode < 0) {
		*mode = 0;
	}

	if (*mode >= 2) {
		*mode = 1;
	}

	pushPullSwitchFieldNames[0] = pushPullSwitchModeNames[*mode];
}
