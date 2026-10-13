#include "types.h"

// The weight object's EditOnChange (weightEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct WeightParams {
	s8 f00; // 0x00
	u8 pad01[0x1];
	s16 f02; // 0x02
	f32 f04; // 0x04
	f32 f08; // 0x08
	s16 f0C; // 0x0C
	s16 f0E; // 0x0E
	f32 f10; // 0x10
} WeightParams;

typedef struct WeightEdit {
	u8 unk00[0x2C];
	WeightParams* params; // 0x2C
} WeightEdit;

extern "C" const char* weightFieldNames[];
extern "C" const char* weightFields0[];
extern "C" const char* weightFields1[];
extern "C" const char* weightFields2[];
extern "C" const char* weightFields3[];

extern "C" const f32 weightBound0[1];
extern "C" const f32 weightBound1[1];

extern "C" void weightEditOnChange(void* object, WeightEdit* edit)
{
	WeightParams* params = edit->params;
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
	if (params->f04 < *(limit = weightBound0)) {
		params->f04 = *limit;
	}
	if (params->f04 > *(limit = weightBound1)) {
		params->f04 = *limit;
	}
	if (params->f10 < *(limit = weightBound0)) {
		params->f10 = *limit;
	}
	if (params->f10 > *(limit = weightBound1)) {
		params->f10 = *limit;
	}
	if (params->f08 < *(limit = weightBound0)) {
		params->f08 = *limit;
	}
	if (params->f08 > *(limit = weightBound1)) {
		params->f08 = *limit;
	}
	if (params->f02 < -40) {
		params->f02 = -40;
	}
	if (params->f02 > 960) {
		params->f02 = 960;
	}
	weightFieldNames[0] = weightFields0[params->f00];
	weightFieldNames[1] = weightFields1[params->f00];
	weightFieldNames[5] = weightFields2[params->f00];
	weightFieldNames[6] = weightFields3[params->f00];
}
