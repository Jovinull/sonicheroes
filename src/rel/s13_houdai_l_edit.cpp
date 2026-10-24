#include "types.h"

// The large cannon's EditOnChange (s13HoudaiLEditOnChange here): its two
// counts are kept at zero at least and the first at 0x8000 at most, its range
// at its minimum, its interval at 10 frames at least, and its two flags at 1
// at most.

typedef struct S13HoudaiLParams {
	u16 interval; // 0x00
	u8 unk02[0x2];
	s32 count0; // 0x04
	s32 count1; // 0x08
	f32 range;  // 0x0C
	u8 flag0;   // 0x10
	u8 flag1;   // 0x11
} S13HoudaiLParams;

typedef struct S13HoudaiLEdit {
	u8 unk00[0x2C];
	S13HoudaiLParams* params; // 0x2C
} S13HoudaiLEdit;

extern "C" const f32 s13HoudaiLEditMin[1];

extern "C" void s13HoudaiLEditOnChange(void* object, S13HoudaiLEdit* edit)
{
	S13HoudaiLParams* params = edit->params;
	const f32* min;

	if (params->count0 < 0) {
		params->count0 = 0;
	}
	if (params->count1 < 0) {
		params->count1 = 0;
	}
	if (params->count0 > 0x8000) {
		params->count0 = 0x8000;
	}
	if (params->range < *(min = s13HoudaiLEditMin)) {
		params->range = *min;
	}
	if (params->interval < 10) {
		params->interval = 10;
	}
	if (params->flag1 > 1) {
		params->flag1 = 1;
	}
	if (params->flag0 > 1) {
		params->flag0 = 1;
	}
}
