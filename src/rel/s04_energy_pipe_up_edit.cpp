#include "types.h"

// TObjS04PipeUp's EditOnChange (s04ENERGYPipeUpEditOnChange here; the class is
// the one whose vtable holds it): it keeps each edited parameter within its
// bounds and names the editor's fields for the values that pick them. The body
// of pushPullSwitchEditOnChange (rel/push_pull_switch_edit.cpp), with the
// module's own tables. The fields are named by their offsets (written with
// notes/tools/clampgen.py).

typedef struct S04ENERGYPipeUpParams {
	s8 f00; // 0x00
} S04ENERGYPipeUpParams;

typedef struct S04ENERGYPipeUpEdit {
	u8 unk00[0x2C];
	S04ENERGYPipeUpParams* params; // 0x2C
} S04ENERGYPipeUpEdit;

extern "C" const char* s04ENERGYPipeUpFieldNames[];
extern "C" const char* s04ENERGYPipeUpFields0[];

extern "C" void s04ENERGYPipeUpEditOnChange(void* object, S04ENERGYPipeUpEdit* edit)
{
	S04ENERGYPipeUpParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 2) {
		params->f00 = 1;
	}
	s04ENERGYPipeUpFieldNames[0] = s04ENERGYPipeUpFields0[params->f00];
}
