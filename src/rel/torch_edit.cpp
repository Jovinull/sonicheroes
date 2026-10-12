#include "types.h"

// The torch object's EditOnChange (torchEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct TorchParams {
	s32 f00; // 0x00
} TorchParams;

typedef struct TorchEdit {
	u8 unk00[0x2C];
	TorchParams* params; // 0x2C
} TorchEdit;

extern "C" void torchEditOnChange(void* object, TorchEdit* edit)
{
	TorchParams* params = edit->params;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 > 1) {
		params->f00 = 1;
	}
}
