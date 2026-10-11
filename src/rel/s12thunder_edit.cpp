#include "types.h"

// The s12thunder object's EditOnChange (s12thunderEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S12thunderParams {
	s32 f00; // 0x00
} S12thunderParams;

typedef struct S12thunderEdit {
	u8 unk00[0x2C];
	S12thunderParams* params; // 0x2C
} S12thunderEdit;

extern "C" void s12thunderEditOnChange(void* object, S12thunderEdit* edit)
{
	S12thunderParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	} else if (params->f00 >= 3) {
		params->f00 = 2;
	}
}
