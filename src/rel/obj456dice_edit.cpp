#include "types.h"

// The dice's EditOnChange (obj456diceEditOnChange here): its range is kept at
// its minimum at least and its kind at 0 or 1; with kind 0 its height is kept
// above its minimum.

typedef struct Obj456diceParams {
	f32 height; // 0x00
	f32 range;  // 0x04
	u8 unk08[0x6];
	s16 kind; // 0x0E
} Obj456diceParams;

typedef struct Obj456diceEdit {
	u8 unk00[0x2C];
	Obj456diceParams* params; // 0x2C
} Obj456diceEdit;

extern "C" const f32 obj456diceEditMin[1];
extern "C" const f32 obj456diceEditHeight[1];

extern "C" void obj456diceEditOnChange(void* object, Obj456diceEdit* edit)
{
	Obj456diceParams* params = edit->params;
	const f32* limit;

	if (params->range < *(limit = obj456diceEditMin)) {
		params->range = *limit;
	}
	if (params->kind < 0) {
		params->kind = 0;
	}
	if (params->kind >= 2) {
		params->kind = 1;
	}
	if (params->kind == 0 && params->height <= *(limit = obj456diceEditHeight)) {
		params->height = *limit;
	}
}
