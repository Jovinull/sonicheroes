#include "types.h"

// The s03dPole object's EditOnChange (s03dPoleEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py;
// the limits are the module's constants, which other code shares).

typedef struct S03dPoleParams {
	s8 f00; // 0x00
	u8 pad01[0x3];
	f32 f04; // 0x04
	f32 f08; // 0x08
} S03dPoleParams;

typedef struct S03dPoleEdit {
	u8 unk00[0x2C];
	S03dPoleParams* params; // 0x2C
} S03dPoleEdit;

extern "C" const f32 s03dPoleEditLimit[1];

extern "C" void s03dPoleEditOnChange(void* object, S03dPoleEdit* edit)
{
	S03dPoleParams* params = edit->params;
	const f32* limit;

	if (params->f04 < *(limit = s03dPoleEditLimit)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = s03dPoleEditLimit)) {
		params->f08 = *limit;
	}
	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 2) {
		params->f00 = 1;
	}
}
