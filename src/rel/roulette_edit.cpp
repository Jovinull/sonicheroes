#include "types.h"

// TObjRoulette::EditOnChange (the PS2 build's name; rouletteEditOnChange
// here): an edited size of zero becomes 1, and the size is kept at 0.1 at
// least.

typedef struct RouletteParams {
	f32 size; // 0x00
} RouletteParams;

typedef struct RouletteEdit {
	u8 unk00[0x2C];
	RouletteParams* params; // 0x2C
} RouletteEdit;

extern "C" const f32 rouletteEditUnset[1];
extern "C" const f32 rouletteEditDefault[1];
extern "C" const f32 rouletteEditMin[1];

extern "C" void rouletteEditOnChange(void* object, RouletteEdit* edit)
{
	RouletteParams* params = edit->params;

	if (rouletteEditUnset[0] == params->size) {
		params->size = rouletteEditDefault[0];
	}
	const f32* min;
	if (params->size < *(min = rouletteEditMin)) {
		params->size = *min;
	}
}
