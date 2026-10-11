#include "types.h"

// The egghawkColli object's EditOnChange (egghawkColliEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct EgghawkColliParams {
	s16 f00; // 0x00
	s16 f02; // 0x02
	s16 f04; // 0x04
} EgghawkColliParams;

typedef struct EgghawkColliEdit {
	u8 unk00[0x2C];
	EgghawkColliParams* params; // 0x2C
} EgghawkColliEdit;

extern "C" void egghawkColliEditOnChange(void* object, EgghawkColliEdit* edit)
{
	EgghawkColliParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f02 < 0) {
		params->f02 = 0;
	}
	if (params->f04 < 0) {
		params->f00 = 0;
	}
}
