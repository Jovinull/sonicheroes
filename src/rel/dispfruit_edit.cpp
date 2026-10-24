#include "types.h"

// TObjDispfruit::EditOnChange (the PS2 build's name; dispfruitEditOnChange
// here): an edited size of zero becomes 1, and the size is kept at 0.1 at
// least.

typedef struct DispfruitParams {
	f32 size; // 0x00
} DispfruitParams;

typedef struct DispfruitEdit {
	u8 unk00[0x2C];
	DispfruitParams* params; // 0x2C
} DispfruitEdit;

extern "C" const f32 dispfruitEditUnset[1];
extern "C" const f32 dispfruitEditDefault[1];
extern "C" const f32 dispfruitEditMin[1];

extern "C" void dispfruitEditOnChange(void* object, DispfruitEdit* edit)
{
	DispfruitParams* params = edit->params;

	if (dispfruitEditUnset[0] == params->size) {
		params->size = dispfruitEditDefault[0];
	}
	const f32* min;
	if (params->size < *(min = dispfruitEditMin)) {
		params->size = *min;
	}
}
