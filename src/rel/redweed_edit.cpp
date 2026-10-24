#include "types.h"

// The red weed's EditOnChange (redweedEditOnChange here): the record's draw
// distance is kept at 0x80 at least and its first size at its minimum; a
// second size under its minimum is set back to its default.

typedef struct RedweedParams {
	f32 size0; // 0x00
	f32 size1; // 0x04
} RedweedParams;

typedef struct RedweedEdit {
	u8 unk00[0x2A];
	u8 distance; // 0x2A
	u8 unk2B;
	RedweedParams* params; // 0x2C
} RedweedEdit;

extern "C" const f32 redweedEditMin0[1];
extern "C" const f32 redweedEditMin1[1];
extern "C" const f32 redweedEditDefault1[1];

extern "C" void redweedEditOnChange(void* object, RedweedEdit* edit)
{
	RedweedParams* params = edit->params;
	const f32* min;

	if (edit->distance < 0x80) {
		edit->distance = 0x80;
	}
	if (params->size0 < *(min = redweedEditMin0)) {
		params->size0 = *min;
	}
	if (params->size1 < *redweedEditMin1) {
		params->size1 = *redweedEditDefault1;
	}
}
