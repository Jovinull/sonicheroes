#include "types.h"

// TObjS13ShipDestroy's EditOnChange (s13KankyohakaiEditOnChange here; the class
// is the one whose vtable holds it): it keeps each edited parameter within its
// bounds and names the editor's fields for the values that pick them. The body
// of pushPullSwitchEditOnChange (rel/push_pull_switch_edit.cpp), with the
// module's own tables. The fields are named by their offsets (written with
// notes/tools/clampgen.py).

typedef struct S13KankyohakaiParams {
	s8 f00; // 0x00
} S13KankyohakaiParams;

typedef struct S13KankyohakaiEdit {
	u8 unk00[0x2C];
	S13KankyohakaiParams* params; // 0x2C
} S13KankyohakaiEdit;

extern "C" const char* s13KankyohakaiFieldNames[];
extern "C" const char* s13KankyohakaiFields0[];

extern "C" void s13KankyohakaiEditOnChange(void* object, S13KankyohakaiEdit* edit)
{
	S13KankyohakaiParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 2) {
		params->f00 = 1;
	}
	s13KankyohakaiFieldNames[0] = s13KankyohakaiFields0[params->f00];
}
