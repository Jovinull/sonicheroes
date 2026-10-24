#include "types.h"

// The s04dECylinder object's EditOnChange (s04dECylinderEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py;
// the limits are the module's constants, which other code shares).

typedef struct S04dECylinderParams {
	s8 f00; // 0x00
	u8 pad01[0x3];
	f32 f04; // 0x04
	f32 f08; // 0x08
} S04dECylinderParams;

typedef struct S04dECylinderEdit {
	u8 unk00[0x2C];
	S04dECylinderParams* params; // 0x2C
} S04dECylinderEdit;

extern "C" const f32 s04dECylinderEditLimit0[1];
extern "C" const f32 s04dECylinderEditLimit1[1];

extern "C" void s04dECylinderEditOnChange(void* object, S04dECylinderEdit* edit)
{
	S04dECylinderParams* params = edit->params;
	const f32* limit;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 > 2) {
		params->f00 = 1;
	}
	if (params->f08 < *(limit = s04dECylinderEditLimit0)) {
		params->f08 = *limit;
	}
	if (params->f04 < *(limit = s04dECylinderEditLimit0)) {
		params->f04 = *limit;
	}
	if (params->f04 >= *(limit = s04dECylinderEditLimit1)) {
		params->f04 = *limit;
	}
}
