#include "types.h"

// The ironball object's EditOnChange (EditOnChange__12TObjIronballFP13SETDATA_PARAM here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct IronballParams {
	s32 f00; // 0x00
	f32 f04; // 0x04
	f32 f08; // 0x08
} IronballParams;

typedef struct IronballEdit {
	u8 unk00[0x2C];
	IronballParams* params; // 0x2C
} IronballEdit;

extern "C" const char* ironballFieldNames[];
extern "C" const char* ironballFields0[];
extern "C" const char* ironballFields1[];

extern "C" const f32 ironballBound0[1];
extern "C" const f32 ironballBound1[1];
extern "C" const f32 ironballZero[1];
extern "C" const f32 ironballBound3[1];

extern "C" void EditOnChange__12TObjIronballFP13SETDATA_PARAM(void* object, IronballEdit* edit)
{
	IronballParams* params = edit->params;
	const f32* limit;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 2) {
		params->f00 = 1;
	}
	if (params->f04 < *(limit = ironballBound0)) {
		params->f04 = *limit;
	}
	if (params->f04 > *(limit = ironballBound1)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = ironballZero)) {
		params->f08 = *limit;
	}
	if (params->f08 > *(limit = ironballBound3)) {
		params->f08 = *limit;
	}
	ironballFieldNames[0] = ironballFields0[params->f00];
	ironballFieldNames[2] = ironballFields1[params->f00];
}
