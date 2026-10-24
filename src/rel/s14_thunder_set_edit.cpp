#include "types.h"

// The s14ThunderSet family's EditOnChange (s14ThunderSetEditOnChange here): its two distances are kept at their
// minimum at least.

typedef struct S14ThunderSetParams {
	u8 unk00[0x8];
	f32 range0; // 0x08
	f32 range1; // 0x0C
} S14ThunderSetParams;

typedef struct S14ThunderSetEdit {
	u8 unk00[0x2C];
	S14ThunderSetParams* params; // 0x2C
} S14ThunderSetEdit;

extern "C" const f32 s14ThunderZero[1];

extern "C" void s14ThunderSetEditOnChange(void* object, S14ThunderSetEdit* edit)
{
	S14ThunderSetParams* params = edit->params;
	const f32* limit;

	if (params->range0 < *(limit = s14ThunderZero)) {
		params->range0 = *limit;
	}
	if (params->range1 < *(limit = s14ThunderZero)) {
		params->range1 = *limit;
	}
}
