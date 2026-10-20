#include "types.h"

// The s02ColliForQuake object's EditOnChange (s02ColliForQuakeEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S02ColliForQuakeParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
	f32 f08; // 0x08
	f32 f0C; // 0x0C
	s32 f10; // 0x10
} S02ColliForQuakeParams;

typedef struct S02ColliForQuakeEdit {
	u8 unk00[0x2C];
	S02ColliForQuakeParams* params; // 0x2C
} S02ColliForQuakeEdit;

extern "C" const f32 s02ColliForQuakeBound0[1];

extern "C" void s02ColliForQuakeEditOnChange(void* object, S02ColliForQuakeEdit* edit)
{
	S02ColliForQuakeParams* params = edit->params;
	const f32* limit;

	if (params->f00 < *(limit = s02ColliForQuakeBound0)) {
		params->f00 = *limit;
	}
	if (params->f04 < *(limit = s02ColliForQuakeBound0)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = s02ColliForQuakeBound0)) {
		params->f08 = *limit;
	}
	if (params->f10 < 1) {
		params->f10 = 1;
	}
	if (params->f0C < *(limit = s02ColliForQuakeBound0)) {
		params->f0C = *limit;
	}
}
