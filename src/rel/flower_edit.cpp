#include "types.h"

// The flower object's EditOnChange (flowerObjectEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct FlowerParams {
	s8 f00; // 0x00
	u8 pad01[0x3];
	f32 f04; // 0x04
	f32 f08; // 0x08
} FlowerParams;

typedef struct FlowerEdit {
	u8 unk00[0x2C];
	FlowerParams* params; // 0x2C
} FlowerEdit;

extern "C" const char* flowerObjectFieldNames[];
extern "C" const char* flowerFields0[];
extern "C" const char* flowerFields1[];

extern "C" const f32 flowerBound0[1];
extern "C" const f32 flowerBound1[1];
extern "C" const f32 flowerBound2[1];

extern "C" void flowerObjectEditOnChange(void* object, FlowerEdit* edit)
{
	FlowerParams* params = edit->params;
	const f32* limit;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 > 2) {
		params->f00 = 2;
	}
	if (params->f04 < *(limit = flowerBound0)) {
		params->f04 = *limit;
	}
	if (params->f04 > *(limit = flowerBound1)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = flowerBound2)) {
		params->f08 = *limit;
	}
	flowerObjectFieldNames[0] = flowerFields0[params->f00];
	flowerObjectFieldNames[2] = flowerFields1[params->f00];
}
