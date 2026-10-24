#include "types.h"

// The third thunder set's EditOnChange (s14ThunderSet3EditOnChange here): its two counts and
// its two distances are kept from going below zero.

typedef struct S14ThunderSet3Params {
	u8 unk00[0x6];
	s16 count0; // 0x06
	s16 count1; // 0x08
	u8 unk0A[0x2];
	f32 range0; // 0x0C
	f32 range1; // 0x10
} S14ThunderSet3Params;

typedef struct S14ThunderSet3Edit {
	u8 unk00[0x2C];
	S14ThunderSet3Params* params; // 0x2C
} S14ThunderSet3Edit;

extern "C" const f32 s14ThunderSet3Zero[1];

extern "C" void s14ThunderSet3EditOnChange(void* object, S14ThunderSet3Edit* edit)
{
	S14ThunderSet3Params* params = edit->params;
	const f32* zero;

	if (params->count0 < 0) {
		params->count0 = 0;
	}
	if (params->count1 < 0) {
		params->count1 = 0;
	}
	if (params->range0 < *(zero = s14ThunderSet3Zero)) {
		params->range0 = *zero;
	}
	if (params->range1 < *(zero = s14ThunderSet3Zero)) {
		params->range1 = *zero;
	}
}
