#include "types.h"

// The floating jump's EditOnChange (floatjEditOnChange here): its first parameter is
// kept at its minimum at least.

typedef struct FloatjParams {
	f32 size; // 0x00
} FloatjParams;

typedef struct FloatjEdit {
	u8 unk00[0x2C];
	FloatjParams* params; // 0x2C
} FloatjEdit;

extern "C" const f32 floatjEditMin[1];

extern "C" void floatjEditOnChange(void* object, FloatjEdit* edit)
{
	FloatjParams* params = edit->params;
	const f32* min;

	if (params->size < *(min = floatjEditMin)) {
		params->size = *min;
	}
}
