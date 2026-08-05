#include "types.h"

// TObjCheckpoint's editor callback. It refuses a negative value on the frame's
// single parameter, clamping it back to zero, and then clamps it against the
// signed sixteen bit maximum.
//
// The claim is .text 0x0001079C to 0x000107CC and nothing else. It reads no
// constant, so it owns no rodata.
//
// The name is read from the layout and the shape: the run sits directly before
// checkpointUnload in the checkpoint family, and it takes the frame in the
// second argument and reaches its parameters at +0x2C, which is what the
// reconstructed editor callback in rel/o_s01_base.cpp also does.
//
// The upper clamp cannot fire for a halfword that was just sign extended, but
// the comparison is in the original, so it is in the source too.
//
// The run is the same in the twelve stage modules that carry it, checked by
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
	s16* params; // 0x2C
} SETDATA_PARAM;

extern "C" void checkpointEditOnChange(void* object, SETDATA_PARAM* frame)
{
	s16* value = frame->params;

	if (*value < 0) {
		*value = 0;
	}

	if (*value > 32767) {
		*value = 32767;
	}
}
