#include "types.h"

// The cage object's EditOnChange (EditOnChange__8TObjCageFP13SETDATA_PARAM here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct CageParams {
	s32 f00; // 0x00
	f32 f04; // 0x04
	f32 f08; // 0x08
	f32 f0C; // 0x0C
} CageParams;

typedef struct CageEdit {
	u8 unk00[0x2C];
	CageParams* params; // 0x2C
} CageEdit;

extern "C" const char* cageFieldNames[];
extern "C" const char* cageFields0[];
extern "C" const char* cageFields1[];
extern "C" const char* cageFields2[];
extern "C" const char* cageFields3[];

extern "C" const f32 cageZero[1];
extern "C" const f32 cageBound1[1];
extern "C" const f32 cageBound2[1];

extern "C" void EditOnChange__8TObjCageFP13SETDATA_PARAM(void* object, CageEdit* edit)
{
	CageParams* params = edit->params;
	const f32* limit;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 4) {
		params->f00 = 3;
	}
	if (params->f04 < *(limit = cageZero)) {
		params->f04 = *limit;
	}
	if (params->f04 > *(limit = cageBound1)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = cageZero)) {
		params->f08 = *limit;
	}
	if (params->f08 > *(limit = cageBound2)) {
		params->f08 = *limit;
	}
	if (params->f0C < *(limit = cageZero)) {
		params->f0C = *limit;
	}
	if (params->f0C > *(limit = cageBound2)) {
		params->f0C = *limit;
	}
	cageFieldNames[0] = cageFields0[params->f00];
	cageFieldNames[1] = cageFields1[params->f00];
	cageFieldNames[2] = cageFields2[params->f00];
	cageFieldNames[3] = cageFields3[params->f00];
}
