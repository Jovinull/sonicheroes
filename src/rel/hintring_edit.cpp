#include "types.h"

// The hintring object's EditOnChange (hintringEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct HintringParams {
	u8 pad00[0x2];
	s8 f02; // 0x02
} HintringParams;

typedef struct HintringEdit {
	u8 unk00[0x2C];
	HintringParams* params; // 0x2C
} HintringEdit;

extern "C" const char* hintringObjectFieldNames[];
extern "C" const char* hintringFields0[];

extern "C" void hintringEditOnChange(void* object, HintringEdit* edit)
{
	HintringParams* params = edit->params;

	if (params->f02 < 0) {
		params->f02 = 0;
	}
	if (params->f02 > 1) {
		params->f02 = 1;
	}
	hintringObjectFieldNames[1] = hintringFields0[params->f02];
}
