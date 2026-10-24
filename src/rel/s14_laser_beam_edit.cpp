#include "types.h"

// The s14LaserBeam object's EditOnChange (s14LaserBeamEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S14LaserBeamParams {
	s8 f00; // 0x00
	u8 pad01[0x1];
	s16 f02; // 0x02
} S14LaserBeamParams;

typedef struct S14LaserBeamEdit {
	u8 unk00[0x2C];
	S14LaserBeamParams* params; // 0x2C
} S14LaserBeamEdit;

extern "C" void s14LaserBeamEditOnChange(void* object, S14LaserBeamEdit* edit)
{
	S14LaserBeamParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 9) {
		params->f00 = 8;
	}
	if (params->f02 < 0) {
		params->f02 = 0;
	}
}
