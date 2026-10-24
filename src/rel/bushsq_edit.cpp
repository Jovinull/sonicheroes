#include "types.h"

// TObjBushsq::EditOnChange (the PS2 build's name; bushsqEditOnChange
// here): an edited size of zero becomes 1, and the size is kept at 0.1 at
// least.

typedef struct BushsqParams {
	f32 size; // 0x00
} BushsqParams;

typedef struct BushsqEdit {
	u8 unk00[0x2C];
	BushsqParams* params; // 0x2C
} BushsqEdit;

extern "C" const f32 bushsqEditUnset[1];
extern "C" const f32 bushsqEditDefault[1];
extern "C" const f32 bushsqEditMin[1];

extern "C" void bushsqEditOnChange(void* object, BushsqEdit* edit)
{
	BushsqParams* params = edit->params;

	if (bushsqEditUnset[0] == params->size) {
		params->size = bushsqEditDefault[0];
	}
	const f32* min;
	if (params->size < *(min = bushsqEditMin)) {
		params->size = *min;
	}
}
