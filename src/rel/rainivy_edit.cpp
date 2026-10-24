#include "types.h"

// The rain ivy's EditOnChange (rainivyEditOnChange here): the record's draw
// distance is kept at 0x80 at least and its two sizes at their minimums.

typedef struct RainivyParams {
	f32 size0; // 0x00
	f32 size1; // 0x04
} RainivyParams;

typedef struct RainivyEdit {
	u8 unk00[0x2A];
	u8 distance; // 0x2A
	u8 unk2B;
	RainivyParams* params; // 0x2C
} RainivyEdit;

extern "C" const f32 rainivyEditMin0[1];
extern "C" const f32 rainivyEditMin1[1];

extern "C" void rainivyEditOnChange(void* object, RainivyEdit* edit)
{
	RainivyParams* params = edit->params;
	const f32* min;

	if (edit->distance < 0x80) {
		edit->distance = 0x80;
	}
	if (params->size0 < *(min = rainivyEditMin0)) {
		params->size0 = *min;
	}
	if (params->size1 < *(min = rainivyEditMin1)) {
		params->size1 = *min;
	}
}
