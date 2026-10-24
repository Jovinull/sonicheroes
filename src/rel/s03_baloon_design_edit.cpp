#include "types.h"

// The s03BaloonDesign object's EditOnChange (s03BaloonDesignEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py;
// the limits are the module's constants, which other code shares).

typedef struct S03BaloonDesignParams {
	s8 f00; // 0x00
	u8 pad01[0x7];
	f32 f08; // 0x08
	f32 f0C; // 0x0C
} S03BaloonDesignParams;

typedef struct S03BaloonDesignEdit {
	u8 unk00[0x2C];
	S03BaloonDesignParams* params; // 0x2C
} S03BaloonDesignEdit;

extern "C" const char* s03BaloonDesignFieldNames[];
extern "C" const char* s03BaloonDesignFields0[];

extern "C" const f32 s03BaloonDesignEditLimit[1];

extern "C" void s03BaloonDesignEditOnChange(void* object, S03BaloonDesignEdit* edit)
{
	S03BaloonDesignParams* params = edit->params;
	const f32* limit;

	if (params->f0C < *(limit = s03BaloonDesignEditLimit)) {
		params->f0C = *limit;
	}
	if (params->f08 < *(limit = s03BaloonDesignEditLimit)) {
		params->f08 = *limit;
	}
	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 2) {
		params->f00 = 1;
	}
	s03BaloonDesignFieldNames[0] = s03BaloonDesignFields0[params->f00];
}
