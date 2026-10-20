#include "types.h"

// The s02Green object's EditOnChange (s02GreenEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S02GreenParams {
	s8 f00; // 0x00
	u8 pad01[0x3];
	f32 f04; // 0x04
} S02GreenParams;

typedef struct S02GreenEdit {
	u8 unk00[0x2C];
	S02GreenParams* params; // 0x2C
} S02GreenEdit;

extern "C" const f32 s02GreenBound0[1];

extern "C" void s02GreenEditOnChange(void* object, S02GreenEdit* edit)
{
	S02GreenParams* params = edit->params;
	const f32* limit;

	if (params->f04 < *(limit = s02GreenBound0)) {
		params->f04 = *limit;
	}
	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 2) {
		params->f00 = 1;
	}
}
