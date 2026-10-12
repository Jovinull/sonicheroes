#include "types.h"

// The bobin object's EditOnChange (bobinEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct BobinParams {
	f32 f00; // 0x00
} BobinParams;

typedef struct BobinEdit {
	u8 unk00[0x2C];
	BobinParams* params; // 0x2C
} BobinEdit;

extern "C" void bobinEditOnChange(void* object, BobinEdit* edit)
{
	BobinParams* params = edit->params;

	if (params->f00 <= 0.1f) {
		params->f00 = 0.1f;
	}
}
