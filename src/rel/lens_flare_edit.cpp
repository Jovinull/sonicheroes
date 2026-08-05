#include "types.h"

// TObjLensFlare's editor callback. It clamps the frame's single byte parameter
// into the two values the object understands, then points the editor's second
// field label at the matching name.
//
// The claim is .text 0x00045444 to 0x000454A8 and nothing else. It reads no
// constant, so it owns no rodata.
//
// The name is read from the layout and from what it writes: the run sits inside
// the lens flare block and stores into lensFlareFieldNames, which
// rel/lens_flare_register.cpp already names.
//
// The frame's parameters can be absent here, unlike the checkpoint's, so the
// null check is in the original and in the source.
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
extern "C" const char* lensFlareFieldNames[];
extern "C" const char* lensFlareModeNames[];

extern "C" void lensFlareEditOnChange(void* object, SETDATA_PARAM* frame)
{
	s8* mode = frame->params;

	if (mode == NULL) {
		return;
	}

	if (*mode < 0) {
		*mode = 0;
	}

	if (*mode >= 2) {
		*mode = 1;
	}

	lensFlareFieldNames[0] = lensFlareModeNames[*mode];
}
