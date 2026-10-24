#include "types.h"

// The side cannon's EditOnChange (s13HoudaiYokoEditOnChange here): its range
// is kept at its minimum at least, its interval at 10 frames at least, and its
// kind at 1 at most.

typedef struct S13HoudaiYokoParams {
	u16 interval; // 0x00
	u8 unk02[0x2];
	f32 range; // 0x04
	u8 kind;   // 0x08
} S13HoudaiYokoParams;

typedef struct S13HoudaiYokoEdit {
	u8 unk00[0x2C];
	S13HoudaiYokoParams* params; // 0x2C
} S13HoudaiYokoEdit;

extern "C" const f32 s13HoudaiYokoEditMin[1];

extern "C" void s13HoudaiYokoEditOnChange(void* object, S13HoudaiYokoEdit* edit)
{
	S13HoudaiYokoParams* params = edit->params;
	const f32* min;

	if (params->range < *(min = s13HoudaiYokoEditMin)) {
		params->range = *min;
	}
	if (params->interval < 10) {
		params->interval = 10;
	}
	if (params->kind > 1) {
		params->kind = 1;
	}
}
