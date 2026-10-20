#include "types.h"

// The s02Pole object's EditOnChange (s02PoleEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S02PoleParams {
	s8 f00; // 0x00
	u8 pad01[0x3];
	f32 f04; // 0x04
} S02PoleParams;

typedef struct S02PoleEdit {
	u8 unk00[0x2C];
	S02PoleParams* params; // 0x2C
} S02PoleEdit;

extern "C" const f32 s02PoleBound0[1];

extern "C" void s02PoleEditOnChange(void* object, S02PoleEdit* edit)
{
	S02PoleParams* params = edit->params;
	const f32* limit;

	if (params->f04 < *(limit = s02PoleBound0)) {
		params->f04 = *limit;
	}
	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 2) {
		params->f00 = 1;
	}
}
