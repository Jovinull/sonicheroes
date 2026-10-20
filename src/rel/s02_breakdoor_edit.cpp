#include "types.h"

// The s02Breakdoor object's EditOnChange (s02BreakdoorEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S02BreakdoorParams {
	f32 f00; // 0x00
} S02BreakdoorParams;

typedef struct S02BreakdoorEdit {
	u8 unk00[0x2C];
	S02BreakdoorParams* params; // 0x2C
} S02BreakdoorEdit;

extern "C" const f32 s02BreakdoorBound0[1];

extern "C" void s02BreakdoorEditOnChange(void* object, S02BreakdoorEdit* edit)
{
	S02BreakdoorParams* params = edit->params;
	const f32* limit;

	if (params->f00 <= *(limit = s02BreakdoorBound0)) {
		params->f00 = *limit;
	}
}
