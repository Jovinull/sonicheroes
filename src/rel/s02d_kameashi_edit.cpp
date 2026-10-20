#include "types.h"

// The s02dKameashi object's EditOnChange (s02dKameashiEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S02dKameashiParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
} S02dKameashiParams;

typedef struct S02dKameashiEdit {
	u8 unk00[0x2C];
	S02dKameashiParams* params; // 0x2C
} S02dKameashiEdit;

extern "C" const f32 s02dKameashiBound0[1];

extern "C" void s02dKameashiEditOnChange(void* object, S02dKameashiEdit* edit)
{
	S02dKameashiParams* params = edit->params;
	const f32* limit;

	if (params->f00 < *(limit = s02dKameashiBound0)) {
		params->f00 = *limit;
	}
	if (params->f04 < *(limit = s02dKameashiBound0)) {
		params->f04 = *limit;
	}
}
