#include "types.h"

// The s14LaserSign object's EditOnChange (s14LaserSignEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S14LaserSignParams {
	s8 f00; // 0x00
} S14LaserSignParams;

typedef struct S14LaserSignEdit {
	u8 unk00[0x2C];
	S14LaserSignParams* params; // 0x2C
} S14LaserSignEdit;

extern "C" void s14LaserSignEditOnChange(void* object, S14LaserSignEdit* edit)
{
	S14LaserSignParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 9) {
		params->f00 = 8;
	}
}
