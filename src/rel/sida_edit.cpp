#include "types.h"

// The sida's EditOnChange (sidaEditOnChange here): a first parameter
// below its minimum is reset to its default.

typedef struct SidaParams {
	f32 size; // 0x00
} SidaParams;

typedef struct SidaEdit {
	u8 unk00[0x2C];
	SidaParams* params; // 0x2C
} SidaEdit;

extern "C" const f32 sidaEditMin[1];
extern "C" const f32 sidaEditDefault[1];

extern "C" void sidaEditOnChange(void* object, SidaEdit* edit)
{
	SidaParams* params = edit->params;

	if (params->size < sidaEditMin[0]) {
		params->size = sidaEditDefault[0];
	}
}
