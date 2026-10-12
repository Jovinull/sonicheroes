#include "types.h"

// The s12door object's EditOnChange (s12doorEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S12doorParams {
	s32 f00; // 0x00
} S12doorParams;

typedef struct S12doorEdit {
	u8 unk00[0x2C];
	S12doorParams* params; // 0x2C
} S12doorEdit;

extern "C" const char* s12doorObjectFieldNames[];
extern "C" const char* s12doorFields0[];

extern "C" void s12doorEditOnChange(void* object, S12doorEdit* edit)
{
	S12doorParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	} else if (params->f00 >= 3) {
		params->f00 = 2;
	}
	s12doorObjectFieldNames[0] = s12doorFields0[params->f00];
}
