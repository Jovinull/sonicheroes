#include "types.h"

// TObjMushanim::EditOnChange (the PS2 build's name; mushanimEditOnChange
// here): an edited size of zero becomes 1, and the size is kept at 0.1 at
// least.

typedef struct MushanimParams {
	f32 size; // 0x00
} MushanimParams;

typedef struct MushanimEdit {
	u8 unk00[0x2C];
	MushanimParams* params; // 0x2C
} MushanimEdit;

extern "C" const f32 mushanimEditUnset[1];
extern "C" const f32 mushanimEditDefault[1];
extern "C" const f32 mushanimEditMin[1];

extern "C" void mushanimEditOnChange(void* object, MushanimEdit* edit)
{
	MushanimParams* params = edit->params;

	if (mushanimEditUnset[0] == params->size) {
		params->size = mushanimEditDefault[0];
	}
	const f32* min;
	if (params->size < *(min = mushanimEditMin)) {
		params->size = *min;
	}
}
