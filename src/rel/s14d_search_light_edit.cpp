#include "types.h"

// The s14dSearchLight family's EditOnChange (s14dSearchLightEditOnChange here): its two distances are kept at their
// minimum at least.

typedef struct S14dSearchLightParams {
	f32 range0; // 0x00
	f32 range1; // 0x04
} S14dSearchLightParams;

typedef struct S14dSearchLightEdit {
	u8 unk00[0x2C];
	S14dSearchLightParams* params; // 0x2C
} S14dSearchLightEdit;

extern "C" const f32 s14dSearchLightEditMin[1];

extern "C" void s14dSearchLightEditOnChange(void* object, S14dSearchLightEdit* edit)
{
	S14dSearchLightParams* params = edit->params;
	const f32* limit;

	if (params->range0 < *(limit = s14dSearchLightEditMin)) {
		params->range0 = *limit;
	}
	if (params->range1 < *(limit = s14dSearchLightEditMin)) {
		params->range1 = *limit;
	}
}
