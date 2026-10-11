#include "types.h"

// The s11ghost object's EditOnChange (s11ghostEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S11ghostParams {
	s32 f00; // 0x00
} S11ghostParams;

typedef struct S11ghostEdit {
	u8 unk00[0x2C];
	S11ghostParams* params; // 0x2C
} S11ghostEdit;

extern "C" const char* s11ghostObjectFieldNames[];
extern "C" const char* s11ghostFields0[];
extern "C" const char* s11ghostFields1[];

extern "C" void s11ghostEditOnChange(void* object, S11ghostEdit* edit)
{
	S11ghostParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	} else if (params->f00 > 2) {
		params->f00 = 2;
	}
	s11ghostObjectFieldNames[0] = s11ghostFields0[params->f00];
	s11ghostObjectFieldNames[2] = s11ghostFields1[params->f00];
}
