#include "types.h"

// The bigslot object's EditOnChange (bigslotEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct BigslotParams {
	s32 f00; // 0x00
} BigslotParams;

typedef struct BigslotEdit {
	u8 unk00[0x2C];
	BigslotParams* params; // 0x2C
} BigslotEdit;

extern "C" void bigslotEditOnChange(void* object, BigslotEdit* edit)
{
	BigslotParams* params = edit->params;

	if (params->f00 >= 5) {
		params->f00 = 4;
	}
	if (params->f00 < 0) {
		params->f00 = 0;
	}
}
