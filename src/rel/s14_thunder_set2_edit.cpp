#include "types.h"

// The second thunder set's EditOnChange (s14ThunderSet2EditOnChange here): its two counts and
// its two distances are kept from going below zero.

typedef struct S14ThunderSet2Params {
	u8 unk00[0x6];
	s16 count0; // 0x06
	s16 count1; // 0x08
	u8 unk0A[0x2];
	f32 range0; // 0x0C
	f32 range1; // 0x10
} S14ThunderSet2Params;

typedef struct S14ThunderSet2Edit {
	u8 unk00[0x2C];
	S14ThunderSet2Params* params; // 0x2C
} S14ThunderSet2Edit;

extern "C" const f32 s14ThunderZero[1];

extern "C" void s14ThunderSet2EditOnChange(void* object, S14ThunderSet2Edit* edit)
{
	S14ThunderSet2Params* params = edit->params;
	const f32* zero;

	if (params->count0 < 0) {
		params->count0 = 0;
	}
	if (params->count1 < 0) {
		params->count1 = 0;
	}
	if (params->range0 < *(zero = s14ThunderZero)) {
		params->range0 = *zero;
	}
	if (params->range1 < *(zero = s14ThunderZero)) {
		params->range1 = *zero;
	}
}
