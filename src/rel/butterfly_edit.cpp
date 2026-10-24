#include "types.h"

// The butterfly object's EditOnChange (butterflyEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py;
// the limits are the module's constants, which other code shares).

typedef struct ButterflyParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
	f32 f08; // 0x08
	s32 f0C; // 0x0C
} ButterflyParams;

typedef struct ButterflyEdit {
	u8 unk00[0xC];
	s32 e0C; // 0x0C
	s32 e10; // 0x10
	s32 e14; // 0x14
	u8 unk18[0x14];
	ButterflyParams* params; // 0x2C
} ButterflyEdit;

extern "C" const f32 butterflyEditLimit[1];

extern "C" void butterflyEditOnChange(void* object, ButterflyEdit* edit)
{
	ButterflyParams* params = edit->params;
	const f32* limit;

	if (params->f00 < *(limit = butterflyEditLimit)) {
		params->f00 = *limit;
	}
	if (params->f04 < *(limit = butterflyEditLimit)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = butterflyEditLimit)) {
		params->f08 = *limit;
	}
	if (params->f0C < 1) {
		params->f0C = 1;
	}
	edit->e0C = 0;
	edit->e10 = 0;
	edit->e14 = 0;
}
