#include "types.h"

// The s11light object's EditOnChange (s11lightEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S11lightParams {
	s32 f00; // 0x00
} S11lightParams;

typedef struct S11lightEdit {
	u8 unk00[0x2C];
	S11lightParams* params; // 0x2C
} S11lightEdit;

extern "C" void s11lightEditOnChange(void* object, S11lightEdit* edit)
{
	S11lightParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 4) {
		params->f00 = 3;
	}
}
