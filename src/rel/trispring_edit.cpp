#include "types.h"

// The trispring object's EditOnChange (trispringEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct TrispringParams {
	f32 f00; // 0x00
	s8 f04;  // 0x04
	s8 f05;  // 0x05
	s8 f06;  // 0x06
} TrispringParams;

typedef struct TrispringEdit {
	u8 unk00[0x2C];
	TrispringParams* params; // 0x2C
} TrispringEdit;

extern "C" void trispringEditOnChange(void* object, TrispringEdit* edit)
{
	TrispringParams* params = edit->params;

	if (params->f05 < 0) {
		params->f05 = 0;
	}
	if (params->f05 >= 2) {
		params->f05 = 1;
	}
	if (params->f00 < 0.1f) {
		params->f00 = 0.1f;
	}
	if (params->f04 < 0) {
		params->f04 = 0;
	}
	if (params->f04 > 1) {
		params->f04 = 1;
	}
	if (params->f06 < 1) {
		params->f06 = 1;
	}
	if (params->f06 > 64) {
		params->f06 = 64;
	}
}
