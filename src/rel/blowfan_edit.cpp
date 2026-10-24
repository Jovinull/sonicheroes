#include "types.h"

// The blowing fan's EditOnChange (blowfanEditOnChange here): two words of the
// object's record are cleared and its strength is kept between its minimum
// and its maximum.

typedef struct BlowfanParams {
	f32 strength; // 0x00
} BlowfanParams;

typedef struct BlowfanEdit {
	u8 unk00[0x2C];
	BlowfanParams* params; // 0x2C
} BlowfanEdit;

typedef struct BlowfanRecord {
	u8 unk00[0xC];
	s32 e0C; // 0x0C
	u8 unk10[0x4];
	s32 e14; // 0x14
} BlowfanRecord;

typedef struct BlowfanObject {
	u8 unk00[0x28];
	BlowfanRecord* record; // 0x28
} BlowfanObject;

extern "C" const f32 blowfanEditMax[1];
extern "C" const f32 blowfanEditMin[1];

extern "C" void blowfanEditOnChange(BlowfanObject* object, BlowfanEdit* edit)
{
	BlowfanParams* params = edit->params;
	const f32* limit;

	object->record->e0C = 0;
	object->record->e14 = 0;
	if (params->strength > *(limit = blowfanEditMax)) {
		params->strength = *limit;
	}
	if (params->strength < *(limit = blowfanEditMin)) {
		params->strength = *limit;
	}
}
