#include "types.h"

// The flipper object's EditOnChange (flipperEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct FlipperParams {
	u8 pad00[0x4];
	u8 f04; // 0x04
	s8 f05; // 0x05
	u8 pad06[0x1];
	s8 f07; // 0x07
} FlipperParams;

typedef struct FlipperEdit {
	u8 unk00[0xC];
	s32 e0C; // 0x0C
	u8 unk10[0x4];
	s32 e14; // 0x14
	u8 unk18[0x14];
	FlipperParams* params; // 0x2C
} FlipperEdit;

extern "C" void flipperEditOnChange(void* object, FlipperEdit* edit)
{
	FlipperParams* params = edit->params;

	edit->e0C = 0;
	edit->e14 = 0;
	if (params->f04 == 0) {
		params->f04 = 3;
	}
	if (params->f04 > 3) {
		params->f04 = 1;
	}
	if (params->f05 < 0) {
		params->f05 = 0;
	}
	if (params->f05 > 1) {
		params->f05 = 1;
	}
	if (params->f07 > 2) {
		params->f07 = 2;
	}
	if (params->f07 < 0) {
		params->f07 = 0;
	}
}
