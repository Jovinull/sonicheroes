#include "types.h"

// The s14BombSwitch object's EditOnChange (s14BombSwitchEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct S14BombSwitchParams {
	s8 f00; // 0x00
} S14BombSwitchParams;

typedef struct S14BombSwitchEdit {
	u8 unk00[0x2C];
	S14BombSwitchParams* params; // 0x2C
} S14BombSwitchEdit;

extern "C" const char* s14BombSwitchFieldNames[];
extern "C" const char* s14BombSwitchFields0[];

extern "C" void s14BombSwitchEditOnChange(void* object, S14BombSwitchEdit* edit)
{
	S14BombSwitchParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 3) {
		params->f00 = 2;
	}
	s14BombSwitchFieldNames[0] = s14BombSwitchFields0[params->f00];
}
