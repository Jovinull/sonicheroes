#include "types.h"

// The s66Star object's EditOnChange (s66StarEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S66StarParams {
	u8 pad00[0x4];
	f32 f04; // 0x04
} S66StarParams;

typedef struct S66StarEdit {
	u8 unk00[0x2C];
	S66StarParams* params; // 0x2C
} S66StarEdit;

extern "C" const f32 s66StarBound0[1];

extern "C" void s66StarEditOnChange(void* object, S66StarEdit* edit)
{
	S66StarParams* params = edit->params;
	const f32* limit;

	if (params->f04 < *(limit = s66StarBound0)) {
		params->f04 = *limit;
	}
}
