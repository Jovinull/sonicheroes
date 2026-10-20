#include "types.h"

// The hermitcrab object's EditOnChange (hermitcrabEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct HermitcrabParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
} HermitcrabParams;

typedef struct HermitcrabEdit {
	u8 unk00[0x2C];
	HermitcrabParams* params; // 0x2C
} HermitcrabEdit;

extern "C" const f32 hermitcrabBound0[1];
extern "C" const f32 hermitcrabBound1[1];
extern "C" const f32 hermitcrabBound2[1];
extern "C" const f32 hermitcrabBound3[1];

extern "C" void hermitcrabEditOnChange(void* object, HermitcrabEdit* edit)
{
	HermitcrabParams* params = edit->params;
	const f32* limit;

	if (params->f00 < *(limit = hermitcrabBound0)) {
		params->f00 = *limit;
	}
	if (params->f00 > *(limit = hermitcrabBound1)) {
		params->f00 = *limit;
	}
	if (params->f04 < *(limit = hermitcrabBound2)) {
		params->f04 = *limit;
	}
	if (params->f04 > *(limit = hermitcrabBound3)) {
		params->f04 = *limit;
	}
}
