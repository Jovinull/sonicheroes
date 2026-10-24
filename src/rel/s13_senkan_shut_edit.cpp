#include "types.h"

// The s13SenkanShut object's EditOnChange (s13SenkanShutEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S13SenkanShutParams {
	s16 f00; // 0x00
	s16 f02; // 0x02
	s16 f04; // 0x04
} S13SenkanShutParams;

typedef struct S13SenkanShutEdit {
	u8 unk00[0x2C];
	S13SenkanShutParams* params; // 0x2C
} S13SenkanShutEdit;

extern "C" void s13SenkanShutEditOnChange(void* object, S13SenkanShutEdit* edit)
{
	S13SenkanShutParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f02 < 0) {
		params->f02 = 0;
	}
	if (params->f04 < 0) {
		params->f04 = 0;
	}
}
