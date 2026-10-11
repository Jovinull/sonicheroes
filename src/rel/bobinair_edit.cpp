#include "types.h"

// The bobinair object's EditOnChange (bobinairEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct BobinairParams {
	f32 f00; // 0x00
} BobinairParams;

typedef struct BobinairEdit {
	u8 unk00[0x2C];
	BobinairParams* params; // 0x2C
} BobinairEdit;

extern "C" void bobinairEditOnChange(void* object, BobinairEdit* edit)
{
	BobinairParams* params = edit->params;

	if (params->f00 <= 0.1f) {
		params->f00 = 0.1f;
	}
}
