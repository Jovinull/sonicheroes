#include "types.h"

// The s03dLight object's EditOnChange (s03dLightEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py;
// the limits are the module's constants, which other code shares).

typedef struct S03dLightParams {
	s8 f00; // 0x00
	u8 pad01[0x3];
	f32 f04; // 0x04
	f32 f08; // 0x08
	f32 f0C; // 0x0C
} S03dLightParams;

typedef struct S03dLightEdit {
	u8 unk00[0x2C];
	S03dLightParams* params; // 0x2C
} S03dLightEdit;

extern "C" const f32 s03dLightEditLimit[1];

extern "C" void s03dLightEditOnChange(void* object, S03dLightEdit* edit)
{
	S03dLightParams* params = edit->params;
	const f32* limit;

	if (params->f04 < *(limit = s03dLightEditLimit)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = s03dLightEditLimit)) {
		params->f08 = *limit;
	}
	if (params->f0C < *(limit = s03dLightEditLimit)) {
		params->f0C = *limit;
	}
	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 2) {
		params->f00 = 1;
	}
}
