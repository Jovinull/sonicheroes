#include "types.h"

// The s11fire object's EditOnChange (s11fireEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S11fireParams {
	s32 f00; // 0x00
	s32 f04; // 0x04
	u8 pad08[0x8];
	s8 f10; // 0x10
	s8 f11; // 0x11
	s8 f12; // 0x12
	s8 f13; // 0x13
} S11fireParams;

typedef struct S11fireEdit {
	u8 unk00[0x2C];
	S11fireParams* params; // 0x2C
} S11fireEdit;

extern "C" const char* s11fireObjectFieldNames[];
extern "C" const char* s11fireFields0[];
extern "C" const char* s11fireFields1[];
extern "C" const char* s11fireFields2[];
extern "C" const char* s11fireFields3[];
extern "C" const char* s11fireFields4[];
extern "C" const char* s11fireFields5[];
extern "C" const char* s11fireFields6[];

extern "C" void s11fireEditOnChange(void* object, S11fireEdit* edit)
{
	S11fireParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	} else if (params->f00 > 1) {
		params->f00 = 1;
	}
	if (params->f04 < 0) {
		params->f04 = 0;
	}
	if (params->f04 >= 3) {
		params->f04 = 2;
	}
	if (params->f10 < 0) {
		params->f10 = 0;
	}
	if (params->f10 > 1) {
		params->f10 = 1;
	}
	if (params->f11 < 0) {
		params->f11 = 0;
	}
	if (params->f11 >= 3) {
		params->f11 = 2;
	}
	if (params->f12 < 0) {
		params->f12 = 0;
	}
	if (params->f12 > 1) {
		params->f12 = 1;
	}
	if (params->f13 < 0) {
		params->f13 = 0;
	}
	if (params->f13 > 1) {
		params->f13 = 1;
	}
	s11fireObjectFieldNames[0] = s11fireFields0[params->f00];
	s11fireObjectFieldNames[1] = s11fireFields1[params->f04];
	s11fireObjectFieldNames[2] = s11fireFields2[params->f04];
	s11fireObjectFieldNames[4] = s11fireFields3[params->f10];
	s11fireObjectFieldNames[5] = s11fireFields4[params->f11];
	s11fireObjectFieldNames[6] = s11fireFields5[params->f12];
	s11fireObjectFieldNames[7] = s11fireFields6[params->f13];
}
