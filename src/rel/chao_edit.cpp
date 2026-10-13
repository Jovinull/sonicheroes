#include "types.h"

// The chao object's EditOnChange (EditOnChange__8TObjChaoFP13SETDATA_PARAM here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct ChaoParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
} ChaoParams;

typedef struct ChaoEdit {
	u8 unk00[0x2C];
	ChaoParams* params; // 0x2C
} ChaoEdit;

extern "C" const f32 chaoZero[1];
extern "C" const f32 chaoBound1[1];
extern "C" const f32 chaoBound2[1];
extern "C" const f32 chaoBound3[1];

extern "C" void EditOnChange__8TObjChaoFP13SETDATA_PARAM(void* object, ChaoEdit* edit)
{
	ChaoParams* params = edit->params;
	const f32* limit;

	if (params->f00 < *(limit = chaoZero)) {
		params->f00 = *limit;
	}
	if (params->f00 > *(limit = chaoBound1)) {
		params->f00 = *limit;
	}
	if (params->f04 < *(limit = chaoBound2)) {
		params->f04 = *limit;
	}
	if (params->f04 > *(limit = chaoBound3)) {
		params->f04 = *limit;
	}
}
