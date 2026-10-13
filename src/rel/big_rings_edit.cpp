#include "types.h"

// The bigRings object's EditOnChange (bigRingsEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct BigRingsParams {
	s16 f00; // 0x00
	u16 f02; // 0x02
	f32 f04; // 0x04
} BigRingsParams;

typedef struct BigRingsEdit {
	u8 unk00[0x2C];
	BigRingsParams* params; // 0x2C
} BigRingsEdit;

extern "C" const f32 bigRingsBound0[1];

extern "C" void bigRingsEditOnChange(void* object, BigRingsEdit* edit)
{
	BigRingsParams* params = edit->params;
	const f32* limit;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 5) {
		params->f00 = 4;
	}
	if (params->f02 > 3600) {
		params->f02 = 3600;
	}
	if (params->f04 < *(limit = bigRingsBound0)) {
		params->f04 = *limit;
	}
}
