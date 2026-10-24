#include "types.h"

// TObjBushZenmai::EditOnChange (the PS2 build's name; bushZenmaiEditOnChange
// here): an edited size of zero becomes 1, and the size is kept at 0.1 at
// least.

typedef struct BushZenmaiParams {
	f32 size; // 0x00
} BushZenmaiParams;

typedef struct BushZenmaiEdit {
	u8 unk00[0x2C];
	BushZenmaiParams* params; // 0x2C
} BushZenmaiEdit;

extern "C" const f32 bushZenmaiZero[1];
extern "C" const f32 bushZenmaiOne[1];
extern "C" const f32 bushZenmaiMinSize[1];

extern "C" void bushZenmaiEditOnChange(void* object, BushZenmaiEdit* edit)
{
	BushZenmaiParams* params = edit->params;

	if (bushZenmaiZero[0] == params->size) {
		params->size = bushZenmaiOne[0];
	}
	const f32* min;
	if (params->size < *(min = bushZenmaiMinSize)) {
		params->size = *min;
	}
}
