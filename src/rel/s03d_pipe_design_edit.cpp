#include "types.h"

// The s03dPipeDesign object's EditOnChange (s03dPipeDesignEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py;
// the limits are the module's constants, which other code shares).

typedef struct S03dPipeDesignParams {
	s8 f00; // 0x00
	u8 pad01[0x3];
	f32 f04; // 0x04
	f32 f08; // 0x08
	f32 f0C; // 0x0C
} S03dPipeDesignParams;

typedef struct S03dPipeDesignEdit {
	u8 unk00[0x2C];
	S03dPipeDesignParams* params; // 0x2C
} S03dPipeDesignEdit;

extern "C" const f32 s03dPipeDesignEditLimit[1];

extern "C" void s03dPipeDesignEditOnChange(void* object, S03dPipeDesignEdit* edit)
{
	S03dPipeDesignParams* params = edit->params;
	const f32* limit;

	if (params->f04 < *(limit = s03dPipeDesignEditLimit)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = s03dPipeDesignEditLimit)) {
		params->f08 = *limit;
	}
	if (params->f0C < *(limit = s03dPipeDesignEditLimit)) {
		params->f0C = *limit;
	}
	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 4) {
		params->f00 = 3;
	}
}
