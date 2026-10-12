#include "types.h"

// The s12wall object's EditOnChange (s12wallEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S12wallParams {
	s32 f00; // 0x00
} S12wallParams;

typedef struct S12wallEdit {
	u8 unk00[0x2C];
	S12wallParams* params; // 0x2C
} S12wallEdit;

extern "C" void s12wallEditOnChange(void* object, S12wallEdit* edit)
{
	S12wallParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	} else if (params->f00 >= 2) {
		params->f00 = 1;
	}
}
