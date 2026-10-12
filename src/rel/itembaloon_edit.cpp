#include "types.h"

// The itembaloon object's EditOnChange (EditOnChange__14TObjItembaloonFP13SETDATA_PARAM here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct ItembaloonParams {
	s8 f00; // 0x00
	u8 pad01[0x3];
	f32 f04; // 0x04
} ItembaloonParams;

typedef struct ItembaloonEdit {
	u8 unk00[0x2C];
	ItembaloonParams* params; // 0x2C
} ItembaloonEdit;

extern "C" const char* itembaloonObjectFieldNames[];
extern "C" const char* scrollItembaloonFields0[];

extern "C" const f32 itembaloonMinusOne[1];
extern "C" const f32 scrollItembaloonBound2[1];

extern "C" void EditOnChange__14TObjItembaloonFP13SETDATA_PARAM(void* object, ItembaloonEdit* edit)
{
	ItembaloonParams* params = edit->params;
	const f32* limit;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 13) {
		params->f00 = 12;
	}
	if (params->f04 < *(limit = itembaloonMinusOne)) {
		params->f04 = *limit;
	}
	if (params->f04 > *(limit = scrollItembaloonBound2)) {
		params->f04 = *limit;
	}
	itembaloonObjectFieldNames[0] = scrollItembaloonFields0[params->f00];
}
