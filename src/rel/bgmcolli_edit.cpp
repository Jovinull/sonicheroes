#include "types.h"

// The bgmcolli object's EditOnChange (bgmcolliEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct BgmcolliParams {
	u16 f00; // 0x00
	u8 pad02[0x2];
	u32 f04; // 0x04
} BgmcolliParams;

typedef struct BgmcolliEdit {
	u8 unk00[0x2C];
	BgmcolliParams* params; // 0x2C
} BgmcolliEdit;

extern "C" const char* bgmcolliObjectFieldNames[];
extern "C" const char* bgmcolliFields0[];
extern "C" const char* bgmcolliFields1[];
extern "C" const char* bgmcolliFields2[];
extern "C" const char* bgmcolliFields3[];

extern "C" void bgmcolliEditOnChange(void* object, BgmcolliEdit* edit)
{
	BgmcolliParams* params = edit->params;

	if (params->f04 >= 3) {
		params->f04 = 2;
	}
	if (params->f00 > 6) {
		params->f00 = 5;
	}
	bgmcolliObjectFieldNames[1] = bgmcolliFields0[params->f04];
	bgmcolliObjectFieldNames[2] = bgmcolliFields1[params->f04];
	bgmcolliObjectFieldNames[3] = bgmcolliFields2[params->f04];
	bgmcolliObjectFieldNames[4] = bgmcolliFields3[params->f04];
}
