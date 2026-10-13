#include "types.h"

// The breakableWeight object's EditOnChange (breakableWeightEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct BreakableWeightParams {
	s8 f00; // 0x00
	u8 pad01[0x1];
	s16 f02; // 0x02
	f32 f04; // 0x04
	f32 f08; // 0x08
	s16 f0C; // 0x0C
	s16 f0E; // 0x0E
	f32 f10; // 0x10
} BreakableWeightParams;

typedef struct BreakableWeightEdit {
	u8 unk00[0x2C];
	BreakableWeightParams* params; // 0x2C
} BreakableWeightEdit;

extern "C" const char* breakableWeightFieldNames[];
extern "C" const char* breakableWeightFields0[];
extern "C" const char* breakableWeightFields1[];
extern "C" const char* breakableWeightFields2[];
extern "C" const char* breakableWeightFields3[];

extern "C" const f32 breakableWeightBound0[1];
extern "C" const f32 breakableWeightBound1[1];

extern "C" void breakableWeightEditOnChange(void* object, BreakableWeightEdit* edit)
{
	BreakableWeightParams* params = edit->params;
	const f32* limit;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 6) {
		params->f00 = 5;
	}
	if (params->f0C < -20) {
		params->f0C = -20;
	}
	if (params->f0C > 3580) {
		params->f0C = 3580;
	}
	if (params->f0E < -20) {
		params->f0E = -20;
	}
	if (params->f0E > 3580) {
		params->f0E = 3580;
	}
	if (params->f04 < *(limit = breakableWeightBound0)) {
		params->f04 = *limit;
	}
	if (params->f04 > *(limit = breakableWeightBound1)) {
		params->f04 = *limit;
	}
	if (params->f10 < *(limit = breakableWeightBound0)) {
		params->f10 = *limit;
	}
	if (params->f10 > *(limit = breakableWeightBound1)) {
		params->f10 = *limit;
	}
	if (params->f08 < *(limit = breakableWeightBound0)) {
		params->f08 = *limit;
	}
	if (params->f08 > *(limit = breakableWeightBound1)) {
		params->f08 = *limit;
	}
	if (params->f02 < -40) {
		params->f02 = -40;
	}
	if (params->f02 > 960) {
		params->f02 = 960;
	}
	breakableWeightFieldNames[0] = breakableWeightFields0[params->f00];
	breakableWeightFieldNames[1] = breakableWeightFields1[params->f00];
	breakableWeightFieldNames[5] = breakableWeightFields2[params->f00];
	breakableWeightFieldNames[6] = breakableWeightFields3[params->f00];
}
