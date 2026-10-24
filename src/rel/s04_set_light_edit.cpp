#include "types.h"

// TObjS04SetLight's EditOnChange (s04SetLightEditOnChange here; the class is
// the one whose vtable holds it): it keeps each edited parameter within its
// bounds. The body of s01ObjectBaseEditOnChange (rel/o_s01_base.cpp), with the
// module's own tables. The fields are named by their offsets (written with
// notes/tools/clampgen.py).

typedef struct S04SetLightParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
	f32 f08; // 0x08
} S04SetLightParams;

typedef struct S04SetLightEdit {
	u8 unk00[0x2C];
	S04SetLightParams* params; // 0x2C
} S04SetLightEdit;

extern "C" const f32 s04SetLightBound0[1];

extern "C" void s04SetLightEditOnChange(void* object, S04SetLightEdit* edit)
{
	S04SetLightParams* params = edit->params;
	const f32* limit;

	if (params->f00 < *(limit = s04SetLightBound0)) {
		params->f00 = *limit;
	}
	if (params->f04 < *(limit = s04SetLightBound0)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = s04SetLightBound0)) {
		params->f08 = *limit;
	}
}
