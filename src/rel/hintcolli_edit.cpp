#include "types.h"

// The hintcolli object's EditOnChange (hintcolliEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct HintcolliParams {
	u16 f00; // 0x00
	u8 pad02[0x2];
	u32 f04; // 0x04
} HintcolliParams;

typedef struct HintcolliEdit {
	u8 unk00[0x2C];
	HintcolliParams* params; // 0x2C
} HintcolliEdit;

extern "C" const char* hintcolliObjectFieldNames[];
extern "C" const char* hintcolliFields0[];
extern "C" const char* hintcolliFields1[];
extern "C" const char* hintcolliFields2[];
extern "C" const char* hintcolliFields3[];
extern "C" const char* hintcolliFields4[];

extern "C" void hintcolliEditOnChange(void* object, HintcolliEdit* edit)
{
	HintcolliParams* params = edit->params;

	if (params->f00 >= 3) {
		params->f00 = 2;
	}
	if (params->f04 >= 3) {
		params->f04 = 2;
	}
	hintcolliObjectFieldNames[0] = hintcolliFields0[params->f00];
	hintcolliObjectFieldNames[2] = hintcolliFields1[params->f04];
	hintcolliObjectFieldNames[3] = hintcolliFields2[params->f04];
	hintcolliObjectFieldNames[4] = hintcolliFields3[params->f04];
	hintcolliObjectFieldNames[5] = hintcolliFields4[params->f04];
}
