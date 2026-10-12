#include "types.h"

// The s11warp object's EditOnChange (s11warpEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S11warpParams {
	u8 pad00[0xC];
	s8 f0C; // 0x0C
	s8 f0D; // 0x0D
} S11warpParams;

typedef struct S11warpEdit {
	u8 unk00[0x2C];
	S11warpParams* params; // 0x2C
} S11warpEdit;

extern "C" const char* s11warpObjectFieldNames[];
extern "C" const char* s11warpFields0[];
extern "C" const char* s11warpFields1[];

extern "C" void s11warpEditOnChange(void* object, S11warpEdit* edit)
{
	S11warpParams* params = edit->params;

	if (params->f0C < 0) {
		params->f0C = 0;
	} else if (params->f0C > 1) {
		params->f0C = 1;
	}
	if (params->f0D < 0) {
		params->f0D = 0;
	}
	if (params->f0D > 1) {
		params->f0D = 1;
	}
	s11warpObjectFieldNames[3] = s11warpFields0[params->f0C];
	s11warpObjectFieldNames[4] = s11warpFields1[params->f0D];
}
