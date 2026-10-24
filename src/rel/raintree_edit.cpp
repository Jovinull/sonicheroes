#include "types.h"

// The rain tree's EditOnChange (raintreeEditOnChange here): the edit's flags
// keep bit 0x80 set at least, and the tree's size is kept at its minimum at
// least.

typedef struct RaintreeParams {
	f32 size; // 0x00
} RaintreeParams;

typedef struct RaintreeEdit {
	u8 unk00[0x2A];
	u8 flags; // 0x2A
	u8 unk2B[0x1];
	RaintreeParams* params; // 0x2C
} RaintreeEdit;

extern "C" const f32 raintreeEditMin[1];

extern "C" void raintreeEditOnChange(void* object, RaintreeEdit* edit)
{
	RaintreeParams* params = edit->params;
	const f32* min;

	if (edit->flags < 0x80) {
		edit->flags = 0x80;
	}
	if (params->size < *(min = raintreeEditMin)) {
		params->size = *min;
	}
}
