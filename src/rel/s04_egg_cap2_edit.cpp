#include "types.h"

// TObjS04EggCap2's EditOnChange (s04EggCap2EditOnChange here; the class is the
// one whose vtable holds it): it keeps each edited parameter within its bounds
// and names the editor's fields for the values that pick them. The body of
// pushPullSwitchEditOnChange (rel/push_pull_switch_edit.cpp), with the module's
// own tables. The fields are named by their offsets (written with
// notes/tools/clampgen.py).

typedef struct S04EggCap2Params {
	s8 f00; // 0x00
} S04EggCap2Params;

typedef struct S04EggCap2Edit {
	u8 unk00[0x2C];
	S04EggCap2Params* params; // 0x2C
} S04EggCap2Edit;

extern "C" const char* s04EggCap2FieldNames[];
extern "C" const char* s04EggCap2Fields0[];

extern "C" void s04EggCap2EditOnChange(void* object, S04EggCap2Edit* edit)
{
	S04EggCap2Params* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 2) {
		params->f00 = 1;
	}
	s04EggCap2FieldNames[0] = s04EggCap2Fields0[params->f00];
}
