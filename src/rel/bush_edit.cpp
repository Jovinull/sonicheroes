#include "types.h"

// The bush's EditOnChange (bushEditOnChange here): a first parameter
// below its minimum is reset to its default.

typedef struct BushParams {
	f32 size; // 0x00
} BushParams;

typedef struct BushEdit {
	u8 unk00[0x2C];
	BushParams* params; // 0x2C
} BushEdit;

extern "C" const f32 bushEditMin[1];
extern "C" const f32 bushEditDefault[1];

extern "C" void bushEditOnChange(void* object, BushEdit* edit)
{
	BushParams* params = edit->params;

	if (params->size < bushEditMin[0]) {
		params->size = bushEditDefault[0];
	}
}
