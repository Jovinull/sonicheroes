#include "types.h"

// The s02Water object's EditOnChange (s02WaterEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S02WaterParams {
	s8 f00; // 0x00
	u8 pad01[0x3];
	f32 f04; // 0x04
} S02WaterParams;

typedef struct S02WaterEdit {
	u8 unk00[0x2C];
	S02WaterParams* params; // 0x2C
} S02WaterEdit;

extern "C" const f32 s02WaterBound0[1];

extern "C" void s02WaterEditOnChange(void* object, S02WaterEdit* edit)
{
	S02WaterParams* params = edit->params;
	const f32* limit;

	if (params->f04 < *(limit = s02WaterBound0)) {
		params->f04 = *limit;
	}
	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 10) {
		params->f00 = 9;
	}
}
