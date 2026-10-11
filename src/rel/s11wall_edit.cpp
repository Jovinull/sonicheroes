#include "types.h"

// The s11wall object's EditOnChange (s11wallEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S11wallParams {
	s32 f00; // 0x00
	s8 f04;  // 0x04
} S11wallParams;

typedef struct S11wallEdit {
	u8 unk00[0x2C];
	S11wallParams* params; // 0x2C
} S11wallEdit;

extern "C" const char* s11wallObjectFieldNames[];
extern "C" const char* s11wallFields0[];

extern "C" void s11wallEditOnChange(void* object, S11wallEdit* edit)
{
	S11wallParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	} else if (params->f00 >= 2) {
		params->f00 = 1;
	}
	if (params->f04 < 0) {
		params->f04 = 0;
	}
	if (params->f04 > 1) {
		params->f04 = 1;
	}
	s11wallObjectFieldNames[1] = s11wallFields0[params->f04];
}
