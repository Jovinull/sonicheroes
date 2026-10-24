#include "types.h"

// The duct object's EditOnChange (ductEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py;
// the limits are the module's constants, which other code shares).

typedef struct DuctParams {
	f32 f00; // 0x00
} DuctParams;

typedef struct DuctEdit {
	u8 unk00[0x2C];
	DuctParams* params; // 0x2C
} DuctEdit;

extern "C" const f32 ductEditLimit[1];

extern "C" void ductEditOnChange(void* object, DuctEdit* edit)
{
	DuctParams* params = edit->params;
	const f32* limit;

	if (params->f00 > *(limit = ductEditLimit)) {
		params->f00 = *limit;
	}
}
