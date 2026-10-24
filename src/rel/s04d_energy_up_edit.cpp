#include "types.h"

// The s04dEnergyUp object's EditOnChange (s04dEnergyUpEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py;
// the limits are the module's constants, which other code shares).

typedef struct S04dEnergyUpParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
} S04dEnergyUpParams;

typedef struct S04dEnergyUpEdit {
	u8 unk00[0x2C];
	S04dEnergyUpParams* params; // 0x2C
} S04dEnergyUpEdit;

extern "C" const f32 s04dEnergyUpEditLimit[1];

extern "C" void s04dEnergyUpEditOnChange(void* object, S04dEnergyUpEdit* edit)
{
	S04dEnergyUpParams* params = edit->params;
	const f32* limit;

	if (params->f04 < *(limit = s04dEnergyUpEditLimit)) {
		params->f04 = *limit;
	}
	if (params->f00 < *(limit = s04dEnergyUpEditLimit)) {
		params->f00 = *limit;
	}
}
