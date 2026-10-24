#include "types.h"

// The s03BigBridge2 object's EditOnChange (s03BigBridge2EditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py;
// the limits are the module's constants, which other code shares).

typedef struct S03BigBridge2Params {
	f32 f00; // 0x00
	f32 f04; // 0x04
	f32 f08; // 0x08
	f32 f0C; // 0x0C
} S03BigBridge2Params;

typedef struct S03BigBridge2Edit {
	u8 unk00[0x2C];
	S03BigBridge2Params* params; // 0x2C
} S03BigBridge2Edit;

extern "C" const f32 s03BigBridge2EditLimit[1];

extern "C" void s03BigBridge2EditOnChange(void* object, S03BigBridge2Edit* edit)
{
	S03BigBridge2Params* params = edit->params;
	const f32* limit;

	if (params->f00 < *(limit = s03BigBridge2EditLimit)) {
		params->f00 = *limit;
	}
	if (params->f04 < *(limit = s03BigBridge2EditLimit)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = s03BigBridge2EditLimit)) {
		params->f08 = *limit;
	}
	if (params->f0C < *(limit = s03BigBridge2EditLimit)) {
		params->f0C = *limit;
	}
}
