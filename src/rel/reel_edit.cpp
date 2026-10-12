#include "types.h"

// The reel object's EditOnChange (reelEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct ReelParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
	f32 f08; // 0x08
	s16 f0C; // 0x0C
} ReelParams;

typedef struct ReelEdit {
	u8 unk00[0x2C];
	ReelParams* params; // 0x2C
} ReelEdit;

extern "C" const char* reelFieldNames[];
extern "C" const char* reelFields0[];

extern "C" const f32 reelZero[1];
extern "C" const f32 reelBound1[1];
extern "C" const f32 reelBound2[1];
extern "C" const f32 reelBound3[1];
extern "C" const f32 reelBound4[1];
extern "C" const f32 reelBound5[1];

extern "C" void reelEditOnChange(void* object, ReelEdit* edit)
{
	ReelParams* params = edit->params;
	const f32* limit;

	if (params->f00 < *(limit = reelZero)) {
		params->f00 = *limit;
	}
	if (params->f00 > *(limit = reelBound1)) {
		params->f00 = *limit;
	}
	if (params->f04 < *(limit = reelBound2)) {
		params->f04 = *limit;
	}
	if (params->f04 > *(limit = reelBound3)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = reelBound4)) {
		params->f08 = *limit;
	}
	if (params->f08 > *(limit = reelBound5)) {
		params->f08 = *limit;
	}
	if (params->f0C < 0) {
		params->f0C = 0;
	}
	if (params->f0C >= 2) {
		params->f0C = 1;
	}
	reelFieldNames[3] = reelFields0[params->f0C];
}
