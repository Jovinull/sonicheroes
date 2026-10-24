#include "types.h"

// The bigfireworks object's EditOnChange (bigfireworksEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py;
// the limits are the module's constants, which other code shares).

typedef struct BigfireworksParams {
	u8 pad00[0x4];
	f32 f04; // 0x04
	f32 f08; // 0x08
	f32 f0C; // 0x0C
	f32 f10; // 0x10
} BigfireworksParams;

typedef struct BigfireworksEdit {
	u8 unk00[0x2C];
	BigfireworksParams* params; // 0x2C
} BigfireworksEdit;

extern "C" const f32 bigfireworksEditLimit0[1];
extern "C" const f32 bigfireworksEditLimit1[1];

extern "C" void bigfireworksEditOnChange(void* object, BigfireworksEdit* edit)
{
	BigfireworksParams* params = edit->params;
	const f32* limit;

	if (params->f04 < *(limit = bigfireworksEditLimit0)) {
		params->f04 = *limit;
	}
	if (params->f04 > *(limit = bigfireworksEditLimit1)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = bigfireworksEditLimit1)) {
		params->f08 = *limit;
	}
	if (params->f0C < *(limit = bigfireworksEditLimit1)) {
		params->f0C = *limit;
	}
	if (params->f10 < *(limit = bigfireworksEditLimit1)) {
		params->f10 = *limit;
	}
}
